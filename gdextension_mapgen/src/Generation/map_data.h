#ifndef RESOURCE_MAP_DATA
#define RESOURCE_MAP_DATA

#include <godot_cpp/variant/packed_vector2_array.hpp>

#include "../Generation/Voronoi/Voronoi.h"

namespace mapgen
{
    struct MapData
    {
        godot::PackedVector2Array sampledPoints;
        Voronoi voronoi;
    };
} // namespace mapgen

#endif
