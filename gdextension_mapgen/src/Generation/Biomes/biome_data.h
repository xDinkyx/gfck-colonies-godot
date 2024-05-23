#ifndef SRC_GENERATION_BIOMES_BIOME_DATA
#define SRC_GENERATION_BIOMES_BIOME_DATA

#include "../Voronoi/cell.h"

namespace mapgen
{
    struct Biome
    {
        enum BiomeType
        {
            WATER,
            LAND,
        };

        Biome(const voronoi::Cell* cell) : Cell(cell)
        {
        }

        const voronoi::Cell* Cell = nullptr;
        BiomeType            Type = LAND;
    };
} // namespace mapgen

#endif
