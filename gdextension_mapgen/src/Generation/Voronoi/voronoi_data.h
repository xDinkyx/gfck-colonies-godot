#ifndef GENERATION_VORONOI_VORONOI_DATA
#define GENERATION_VORONOI_VORONOI_DATA

#include <memory>
#include <vector>

#include "cell.h"

namespace mapgen::voronoi
{
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
