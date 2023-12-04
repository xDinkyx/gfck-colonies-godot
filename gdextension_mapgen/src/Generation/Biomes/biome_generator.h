#ifndef SRC_GENERATION_BIOMES_BIOME_GENERATOR
#define SRC_GENERATION_BIOMES_BIOME_GENERATOR

#include "biome_data.h"

namespace mapgen
{
    namespace voronoi
    {
        struct DiagramData;
    }

    class BiomeGenerator
    {
      public:
        enum MapEdgeFlag
        {
            TOP_EDGE   = 0b1,
            RIGHT_EDGE = 0b10,
            BOT_EDGE   = 0b100,
            LEFT_EDGE  = 0b1000,
            ALL_EDGES  = 0b1111,
        };

        static std::vector<Biome> generate(const voronoi::DiagramData& voronoiDiagram, MapEdgeFlag waterOption);
    };
} // namespace mapgen

#endif
