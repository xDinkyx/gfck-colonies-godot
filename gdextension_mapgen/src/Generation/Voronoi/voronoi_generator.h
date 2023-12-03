#ifndef SRC_GENERATION_VORONOI_VORONOI
#define SRC_GENERATION_VORONOI_VORONOI

#include <vector>

#include "godot_cpp/variant/vector2.hpp"
#include "godot_cpp/variant/vector4.hpp"

#include "voronoi_data.h"

namespace mapgen::voronoi::generation
{
    DiagramData generate(const std::vector<godot::Vector2>& points, int width, int height);
}

#endif
