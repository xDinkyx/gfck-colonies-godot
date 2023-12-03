#ifndef SRC_GENERATION_VORONOI_CELL
#define SRC_GENERATION_VORONOI_CELL

#include <vector>

#include "godot_cpp/variant/vector2.hpp"

#include "point.h"
#include "edge.h"

namespace mapgen::voronoi
{
    struct Cell
    {
        std::vector<Point*> Points;
        std::vector<Edge*>  Edges;

        godot::Vector2 Center;
    };
} // namespace mapgen::voronoi

#endif
