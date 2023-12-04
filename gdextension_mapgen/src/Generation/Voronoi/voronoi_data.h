#ifndef GENERATION_VORONOI_VORONOI_DATA
#define GENERATION_VORONOI_VORONOI_DATA

#include <memory>
#include <vector>

namespace godot
{
    struct Vector2;
    struct Vector4;
}

namespace mapgen::voronoi
{
    struct Cell;
    struct Edge;
    struct Point;

    struct DiagramData
    {
        std::vector<std::unique_ptr<Cell>>  Cells;
        std::vector<std::unique_ptr<Edge>>  Edges;
        std::vector<std::unique_ptr<Point>> Points;

        // godot compatible, stored for efficiency, so we don't need to convert every get.
        // ToDo: Add getters and make private, should only be read, and set once on generation.
        std::vector<godot::Vector2>              GodotCellCenters;
        std::vector<std::vector<godot::Vector2>> GodotCells;
        std::vector<godot::Vector4>              GodotEdges;
    };
}

#endif
