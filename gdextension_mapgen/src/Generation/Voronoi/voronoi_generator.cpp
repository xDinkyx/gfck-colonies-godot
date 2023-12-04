#include "voronoi_generator.h"
#include "voronoi_data_converter.h"

#include "jc_voronoi.h"

#include <algorithm>

namespace
{
    auto to_jcv_points(const std::vector<godot::Vector2>& points)
    {
        std::vector<jcv_point> jcv_points(points.size());
        std::transform(std::begin(points), std::end(points), std::begin(jcv_points),
                       [](godot::Vector2 p) { return mapgen::voronoi::converter::to_jcv_point(p); });
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

    void fill_diagram_godot_cells(mapgen::voronoi::DiagramData& diagram)
    {
        for (const auto& cell : diagram.Cells)
        {
            diagram.GodotCellCenters.emplace_back(cell->Center);

            std::vector<godot::Vector2> cell_points;
            for (const auto& point : cell->Points)
                cell_points.emplace_back(point->Position);
            diagram.GodotCells.emplace_back(cell_points);
        }
    }

    void fill_diagram_godot_edges(mapgen::voronoi::DiagramData& diagram)
    {
        for (const auto& edge : diagram.Edges)
        {
            godot::Vector4 edgeData;
            edgeData.x = edge->Point1->Position.x;
            edgeData.y = edge->Point1->Position.y;
            edgeData.z = edge->Point2->Position.x;
            edgeData.w = edge->Point2->Position.y;
            diagram.GodotEdges.emplace_back(edgeData);
        }
    }
} // namespace

mapgen::voronoi::DiagramData mapgen::voronoi::generation::generate(const std::vector<godot::Vector2>& points, int width, int height)
{
    auto jcv_points = to_jcv_points(points);

    jcv_diagram jcv_diagram;
    memset(&jcv_diagram, 0, sizeof(jcv_diagram));

    jcv_rect rect = create_rect(width, height);

    jcv_diagram_generate(jcv_points.size(), jcv_points.data(), &rect, 0, &jcv_diagram);

    auto diagram = converter::extract_data(jcv_diagram);
    fill_diagram_godot_cells(diagram);
    fill_diagram_godot_edges(diagram);

    jcv_diagram_free(&jcv_diagram);

    return diagram;
}
