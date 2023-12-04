#ifndef RESOURCE_MAP_DATA
#define RESOURCE_MAP_DATA

#include <godot_cpp/variant/packed_vector2_array.hpp>

#include "../Generation/Voronoi/voronoi_data.h"
#include "../Generation/Biomes/biome_data.h"

namespace mapgen
{
    struct MapData
    {
        godot::PackedVector2Array SampledPoints;
        voronoi::DiagramData      VoronoiDiagram;
        std::vector<Biome>        Biomes;
    };
} // namespace mapgen

#endif
