#include "Voronoi.h"

#include "jc_voronoi.h"

#include <algorithm>

namespace
{
    auto to_godot_vector2(const jcv_point& p)
    {
        godot::Vector2 v;
        v.x = p.x;
        v.y = p.y;
        return v;
    }
    auto to_godot_vector4(const jcv_point& p1, const jcv_point& p2)
    {
        godot::Vector4 v;
        v.x = p1.x;
        v.y = p1.y;
        v.z = p2.x;
        v.w = p2.y;
        return v;
    }
    auto to_jcv_point(const godot::Vector2& v)
    {
        jcv_point p;
        p.x = v.x;
        p.y = v.y;
        return p;
    }

    auto to_jcv_points(const std::vector<godot::Vector2>& points)
    {
        std::vector<jcv_point> jcv_points(points.size());
        std::transform(std::begin(points), std::end(points), std::begin(jcv_points), [](godot::Vector2 p) { return to_jcv_point(p); });
        return jcv_points;
    }

    auto create_rect(int width, int height)
    {
        jcv_point min;
        min.x = 0;
        min.y = 0;
        jcv_point max;
        max.x = static_cast<jcv_real>(width);
        max.y = static_cast<jcv_real>(height);

        jcv_rect rect;
        rect.min = min;
        rect.max = max;

        return rect;
    }
} // namespace

void mapgen::Voronoi::generate(const std::vector<godot::Vector2>& points, int width, int height)
{
    auto jcv_points = to_jcv_points(points);

    jcv_diagram diagram;
    memset(&diagram, 0, sizeof(jcv_diagram));

    jcv_rect rect = create_rect(width, height);

    jcv_diagram_generate(jcv_points.size(), jcv_points.data(), &rect, 0, &diagram);

    StoreSitesAndCells(diagram);
    StoreEdges(diagram);

    jcv_diagram_free(&diagram);
}

void mapgen::Voronoi::StoreSitesAndCells(const jcv_diagram_& diagram)
{
    sites.clear();

    const jcv_site* jcv_sites = jcv_diagram_get_sites(&diagram);
    for (int i = 0; i < diagram.numsites; ++i)
    {
        const auto site = &jcv_sites[i];
        sites.emplace_back(to_godot_vector2(site->p));

        const jcv_graphedge*        e = site->edges;
        std::vector<godot::Vector2> cell;
        cell.emplace_back(to_godot_vector2(e->pos[0]));
        while (e)
        {
            cell.emplace_back(to_godot_vector2(e->pos[1]));
            e = e->next;
        }
        cells.emplace_back(cell);
    }
}

void mapgen::Voronoi::StoreEdges(const jcv_diagram_& diagram)
{
    const jcv_edge* edge = jcv_diagram_get_edges(&diagram);
    while (edge)
    {
        edges.emplace_back(to_godot_vector4(edge->pos[0], edge->pos[1]));
        edge = jcv_diagram_get_next_edge(edge);
    }
}

std::vector<godot::Vector2> mapgen::Voronoi::get_sites() const
{
    return sites;
}

std::vector<std::vector<godot::Vector2>> mapgen::Voronoi::get_cells() const
{
    return cells;
}

std::vector<godot::Vector4> mapgen::Voronoi::get_edges() const
{
    return edges;
}
