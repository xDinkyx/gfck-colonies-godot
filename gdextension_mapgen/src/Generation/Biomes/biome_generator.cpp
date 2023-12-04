#include "biome_generator.h"

#include "../Voronoi/voronoi_data.h"

#include "biome_type.h"

namespace
{
    auto create_biomes(const mapgen::voronoi::DiagramData& voronoiDiagram)
    {
        std::vector<mapgen::Biome> biomes;

        for (const auto& cell : voronoiDiagram.Cells)
            biomes.emplace_back(mapgen::Biome(cell.get()));

        return biomes;
    }

    bool has_point_at_x(const mapgen::voronoi::Cell& cell, float xPos)
    {
        auto point = std::find_if(std::begin(cell.Points), std::end(cell.Points),
                                  [xPos](const mapgen::voronoi::Point* p) { return abs(xPos - p->Position.x) <= std::numeric_limits<float>::epsilon(); });
        return point != std::end(cell.Points);
    }

    bool has_point_at_y(const mapgen::voronoi::Cell& cell, float yPos)
    {
        auto point = std::find_if(std::begin(cell.Points), std::end(cell.Points),
                                  [yPos](const mapgen::voronoi::Point* p) { return abs(yPos - p->Position.y) <= std::numeric_limits<float>::epsilon(); });
        return point != std::end(cell.Points);
    }

    void set_biomes_with_point_at_xpos_type(std::vector<mapgen::Biome>& biomes, float xPos, mapgen::Biome::BiomeType type)
    {
        for (auto& biome : biomes)
            if (has_point_at_x(*biome.Cell, xPos))
                biome.Type = type;
    }

    auto set_biomes_with_point_at_ypos_type(std::vector<mapgen::Biome>& biomes, float yPos, mapgen::Biome::BiomeType type)
    {
        for (auto& biome : biomes)
            if (has_point_at_y(*biome.Cell, yPos))
                biome.Type = type;
    }

    void set_edge_biomes_type(std::vector<mapgen::Biome>& biomes, mapgen::BiomeGenerator::MapEdgeFlag edgeFlag, mapgen::Biome::BiomeType type)
    {
        using namespace mapgen;

        if (edgeFlag & BiomeGenerator::TOP_EDGE)
            set_biomes_with_point_at_ypos_type(biomes, 0.f, type);
        if (edgeFlag & BiomeGenerator::BOT_EDGE)
            set_biomes_with_point_at_ypos_type(biomes, 1.f, type);
        if (edgeFlag & BiomeGenerator::LEFT_EDGE)
            set_biomes_with_point_at_xpos_type(biomes, 0.f, type);
        if (edgeFlag & BiomeGenerator::RIGHT_EDGE)
            set_biomes_with_point_at_xpos_type(biomes, 1.f, type);
    }
} // namespace

std::vector<mapgen::Biome> mapgen::BiomeGenerator::generate(const voronoi::DiagramData& voronoiDiagram, MapEdgeFlag waterEdgeFlag)
{
    std::vector<Biome> biomes;

    biomes = create_biomes(voronoiDiagram);

    set_edge_biomes_type(biomes, waterEdgeFlag, Biome::WATER);

    return biomes;
}
