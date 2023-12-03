#ifndef SRC_GENERATION_VORONOI_EDGE
#define SRC_GENERATION_VORONOI_EDGE

#include <vector>

#include "godot_cpp/variant/vector2.hpp"

namespace mapgen::voronoi
{
    struct Point;
    struct Cell;

    struct Edge
    {
        mapgen::voronoi::Point* Point1 = nullptr;
        mapgen::voronoi::Point* Point2 = nullptr;
        mapgen::voronoi::Cell*  Cell1 = nullptr;
        mapgen::voronoi::Cell*  Cell2 = nullptr;
    };
} // namespace mapgen::voronoi

#endif
