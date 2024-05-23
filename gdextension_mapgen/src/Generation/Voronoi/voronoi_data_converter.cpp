#include "voronoi_data_converter.h"

#include <set>

#include "godot_cpp/variant/vector2.hpp"
#include "godot_cpp/variant/vector4.hpp"

#include "jc_voronoi.h"

#include "cell.h"
#include "voronoi_data.h"

namespace
{
    struct EdgeData
    {
        const jcv_edge* jcv_edge;
    };
    struct SiteData
    {
        std::vector<const jcv_edge*> edges;
        const jcv_site*              jcv_site;
    };

    auto extract_site_data(const jcv_diagram_& diagram)
    {
        std::set<std::unique_ptr<SiteData>> site_data;

        const jcv_site* jcv_sites = jcv_diagram_get_sites(&diagram);
        for (int i = 0; i < diagram.numsites; ++i)
        {
            const jcv_site* jcv_site = &jcv_sites[i];

            auto site      = std::make_unique<SiteData>();
            site->jcv_site = jcv_site;

            const jcv_graphedge* jcv_edge = jcv_site->edges;
            while (jcv_edge)
            {
                auto edge = std::make_unique<EdgeData>();
                site->edges.emplace_back(jcv_edge->edge);

                jcv_edge = jcv_edge->next;
            }

            site_data.emplace(std::move(site));
        }

        return site_data;
    }

    bool cell_contains_point(const mapgen::voronoi::Cell* cell, const mapgen::voronoi::Point* point)
    {
        return std::find(std::begin(cell->Points), std::end(cell->Points), point) != std::end(cell->Points);
    }

    bool cell_contains_edge(const mapgen::voronoi::Cell* cell, const mapgen::voronoi::Edge* edge)
    {
        return std::find(std::begin(cell->Edges), std::end(cell->Edges), edge) != std::end(cell->Edges);
    }

    bool point_contains_cell(const mapgen::voronoi::Point* point, const mapgen::voronoi::Cell* cell)
    {
        return std::find(std::begin(point->Cells), std::end(point->Cells), cell) != std::end(point->Cells);
    }

    bool point_contains_point(const mapgen::voronoi::Point* point, const mapgen::voronoi::Point* other)
    {
        return std::find(std::begin(point->Points), std::end(point->Points), other) != std::end(point->Points);
    }

    bool point_contains_edge(const mapgen::voronoi::Point* point, const mapgen::voronoi::Edge* edge)
    {
        return std::find(std::begin(point->Edges), std::end(point->Edges), edge) != std::end(point->Edges);
    }

    void add_point_to_cell(mapgen::voronoi::Cell* cell, mapgen::voronoi::Point* point)
    {
        if (!cell_contains_point(cell, point))
            cell->Points.emplace_back(point);
    }

    void add_edge_to_cell(mapgen::voronoi::Cell* cell, mapgen::voronoi::Edge* edge)
    {
        assert(!cell_contains_edge(cell, edge));
        assert(cell_contains_point(cell, edge->Point1));
        assert(cell_contains_point(cell, edge->Point2));
        cell->Edges.emplace_back(edge);
    }

    void add_cell_to_point(mapgen::voronoi::Point* point, mapgen::voronoi::Cell* cell)
    {
        if (!point_contains_cell(point, cell))
            point->Cells.emplace_back(cell);
    }

    void add_edge_to_point(mapgen::voronoi::Point* point, mapgen::voronoi::Edge* edge)
    {
        if (!point_contains_edge(point, edge))
            point->Edges.emplace_back(edge);
    }

    void add_point_to_point(mapgen::voronoi::Point* point, mapgen::voronoi::Point* other)
    {
        if (!point_contains_point(point, other))
            point->Points.emplace_back(other);
    }

    auto find_point(godot::Vector2 pos, const std::vector<std::unique_ptr<mapgen::voronoi::Point>>& points)
    {
        using namespace mapgen::voronoi;
        constexpr float epsilon = 0.0000005; // Seems accurate enough, some asserts to catch if it happens to be too big or small.

        auto point = std::find_if(std::begin(points), std::end(points), [pos, epsilon](const std::unique_ptr<Point>& p) {
            return abs(p->Position.x - pos.x) <= epsilon && abs(p->Position.y - pos.y) <= epsilon;
        });
        return point == std::end(points) ? nullptr : (*point).get();
    }

    bool equals(const mapgen::voronoi::Edge& edge, const mapgen::voronoi::Edge& edge2)
    {
        // return edge.
    }

    auto find_edge(godot::Vector2 edgeP1, godot::Vector2 edgeP2, const std::vector<std::unique_ptr<mapgen::voronoi::Edge>>& edges)
    {
        using namespace mapgen::voronoi;

        auto point = std::find_if(std::begin(edges), std::end(edges), [edgeP1, edgeP2](const std::unique_ptr<Edge>& e) {
            if (e->Point1 == nullptr || e->Point2 == nullptr)
                return false;
            if (e->Point1->Position == edgeP1 && e->Point2->Position == edgeP2)
                return true;
            if (e->Point2->Position == edgeP1 && e->Point1->Position == edgeP2)
                return true;
            return false;
        });
        return point == std::end(edges) ? nullptr : (*point).get();
    }

    auto get_or_create_point(godot::Vector2 pos, mapgen::voronoi::DiagramData& diagramData)
    {
        using namespace mapgen::voronoi;
        using namespace mapgen::voronoi::converter;

        auto* point = find_point(pos, diagramData.Points);
        if (point == nullptr)
        {
            auto new_point      = std::make_unique<Point>();
            point               = new_point.get();
            new_point->Position = pos;

            diagramData.Points.emplace_back(std::move(new_point));
        }

        return point;
    }

    auto add_or_create_cell_edge(const std::unique_ptr<mapgen::voronoi::Cell>& cell, const jcv_edge* siteEdge, mapgen::voronoi::DiagramData& diagramData)
    {
        using namespace mapgen::voronoi;
        using namespace mapgen::voronoi::converter;

        godot::Vector2 pos1 = to_godot_vector2(siteEdge->pos[0]);
        godot::Vector2 pos2 = to_godot_vector2(siteEdge->pos[1]);

        auto edge = find_edge(pos1, pos2, diagramData.Edges);
        if (edge == nullptr)
        {
            auto new_edge = std::make_unique<Edge>();
            edge          = new_edge.get();

            auto point1 = get_or_create_point(pos1, diagramData);
            auto point2 = get_or_create_point(pos2, diagramData);

            assert(point1 != point2);

            // Update edge
            new_edge->Cell1  = cell.get();
            new_edge->Point1 = point1;
            new_edge->Point2 = point2;

            // Update point1
            add_edge_to_point(point1, new_edge.get());
            add_cell_to_point(point1, cell.get());
            add_point_to_point(point1, point2);
            // Update point2
            add_edge_to_point(point2, new_edge.get());
            add_cell_to_point(point2, cell.get());
            add_point_to_point(point2, point1);

            // Update cell
            add_point_to_cell(cell.get(), point1);
            add_point_to_cell(cell.get(), point2);
            add_edge_to_cell(cell.get(), new_edge.get());

            diagramData.Edges.emplace_back(std::move(new_edge));
        }
        else // Edge already exists, and is being looped over by different cell.
        {
            // Update cell
            add_point_to_cell(cell.get(), edge->Point2);
            add_point_to_cell(cell.get(), edge->Point1);
            add_edge_to_cell(cell.get(), edge);

            // Update edge
            assert(edge->Cell2 == nullptr);
            edge->Cell2 = cell.get();

            // Update points
            add_cell_to_point(edge->Point1, cell.get());
            add_cell_to_point(edge->Point2, cell.get());
        }

        return edge;
    }

    auto get_non_equal_point_from_edge(const mapgen::voronoi::Edge* edge, const mapgen::voronoi::Point* point)
    {
        if (edge->Point1 == point)
            return edge->Point2;
        return edge->Point1;
    }

    auto get_ordered_cell_points(mapgen::voronoi::Cell* cell)
    {
        assert(!cell->Points.empty());

        std::vector<mapgen::voronoi::Point*> ordered_points{cell->Points[0]};

        for (const auto& edge : cell->Edges)
            ordered_points.emplace_back(get_non_equal_point_from_edge(edge, ordered_points.back()));
        ordered_points.pop_back();

        return ordered_points;
    }

    auto create_cell(const SiteData& site, mapgen::voronoi::DiagramData& diagramData)
    {
        using namespace mapgen::voronoi;
        using namespace mapgen::voronoi::converter;

        auto cell    = std::make_unique<Cell>();
        cell->Center = to_godot_vector2(site.jcv_site->p);

        for (auto& site_edge : site.edges)
            add_or_create_cell_edge(cell, site_edge, diagramData);

       cell->Points = get_ordered_cell_points(cell.get());

        return cell;
    }
} // namespace

godot::Vector2 mapgen::voronoi::converter::to_godot_vector2(const jcv_point_& p)
{
    godot::Vector2 v;
    v.x = p.x;
    v.y = p.y;
    return v;
}

godot::Vector4 mapgen::voronoi::converter::to_godot_vector4(const jcv_point_& p1, const jcv_point_& p2)
{
    godot::Vector4 v;
    v.x = p1.x;
    v.y = p1.y;
    v.z = p2.x;
    v.w = p2.y;
    return v;
}

jcv_point_ mapgen::voronoi::converter::to_jcv_point(const godot::Vector2& v)
{
    jcv_point p;
    p.x = v.x;
    p.y = v.y;
    return p;
}

mapgen::voronoi::DiagramData mapgen::voronoi::converter::extract_data(const jcv_diagram_& jcv_diagram)
{
    DiagramData data;


    auto site_data = extract_site_data(jcv_diagram);
    for (auto& site : site_data)
        data.Cells.emplace_back(create_cell(*site, data));

#ifdef _DEBUG
    for (const auto& point : data.Points)
        if (point->Edges.size() < 2)
            assert(point->Edges.size() >= 2);
    for (const auto& cell : data.Cells)
        if (cell->Edges.size() != cell->Points.size())
            assert(cell->Edges.size() == cell->Points.size());
    for (const auto& edge : data.Edges)
        if (edge->Cell1 == nullptr)
            assert(edge->Cell1 != nullptr);
#endif

    return data;
}
