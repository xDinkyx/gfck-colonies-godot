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

    auto get_biomes_with_point_at_xpos(std::vector<mapgen::Biome>& biomes, float xPos)
    {
        std::vector<mapgen::Biome*> result;
        for (auto& biome : biomes)
            if (has_point_at_x(*biome.Cell, xPos))
                result.emplace_back(&biome);
        return result;
    }

    auto get_biomes_with_point_at_ypos(std::vector<mapgen::Biome>& biomes, float yPos)
    {
        std::vector<mapgen::Biome*> result;
        for (auto& biome : biomes)
            if (has_point_at_y(*biome.Cell, yPos))
                result.emplace_back(&biome);
        return result;
    }

    bool is_at_edge(const mapgen::Biome& biome)
    {
        for(const auto& edge : biome.Cell->Edges)
            if (edge->Cell1 == nullptr || edge->Cell2 == nullptr)
                return true;
        return false;
    }

    auto get_edge_biomes(std::vector<mapgen::Biome>& biomes)
    {
        std::vector<mapgen::Biome*> edge_biomes;
        for(auto& biome : biomes)
            if (is_at_edge(biome))
                edge_biomes.emplace_back(&biome);
        return edge_biomes;
    }

    void set_edge_biomes_type(std::vector<mapgen::Biome>& biomes, mapgen::BiomeGenerator::MapEdgeFlag edgeFlag, mapgen::Biome::BiomeType type)
    {
        using namespace mapgen;

        for (auto* biome : get_edge_biomes(biomes))
            biome->Type = Biome::WATER;


        //if (edgeFlag & BiomeGenerator::TOP_EDGE)
        //    for (auto& biome : get_biomes_with_point_at_ypos(biomes, 0.f))
        //        biome.Type = Biome::WATER;
        //if (edgeFlag & BiomeGenerator::BOT_EDGE)
        //    for (auto& biome : get_biomes_with_point_at_ypos(biomes, 1.f))
        //        biome.Type = Biome::WATER;
        //if (edgeFlag & BiomeGenerator::LEFT_EDGE)
        //    for (auto& biome : get_biomes_with_point_at_xpos(biomes, 0.f))
        //        biome.Type = Biome::WATER;
        //if (edgeFlag & BiomeGenerator::RIGHT_EDGE)
        //    for ( auto& biome : get_biomes_with_point_at_xpos(biomes, 1.f))
        //        biome.Type = Biome::WATER;
    }
} // namespace

std::vector<mapgen::Biome> mapgen::BiomeGenerator::generate(const voronoi::DiagramData& voronoiDiagram, MapEdgeFlag waterEdgeFlag)
{
    std::vector<Biome> biomes;

    biomes = create_biomes(voronoiDiagram);

    set_edge_biomes_type(biomes, waterEdgeFlag, Biome::WATER);

    return biomes;
}
