#ifndef SRC_GENERATION_VORONOI_POINT
#define SRC_GENERATION_VORONOI_POINT

#include <vector>

#include "godot_cpp/variant/vector2.hpp"

namespace mapgen::voronoi
{
    struct Edge;
    struct Cell;

    struct Point
    {
        godot::Vector2 Position;

        std::vector<mapgen::voronoi::Cell*>  Cells;
        std::vector<mapgen::voronoi::Point*> Points;
        std::vector<mapgen::voronoi::Edge*>  Edges;
    };
} // namespace mapgen::voronoi

#endif
