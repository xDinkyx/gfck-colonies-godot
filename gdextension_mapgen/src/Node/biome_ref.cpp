#include "biome_ref.h"

#include "../Generation/Biomes/biome_data.h"

void BiomeRef::set_biome(const mapgen::Biome* biome)
{
    Biome = biome;
}

godot::PackedVector2Array BiomeRef::get_vertices() const
{
    godot::PackedVector2Array vertices;
    for (const auto& p : Biome->Cell->Points)
        vertices.append(p->Position);
    return vertices;
}

BiomeRef::BiomeType BiomeRef::get_biome_type() const
{
    switch (Biome->Type)
    {
    case mapgen::Biome::WATER:
        return BiomeRef::WATER;
    case mapgen::Biome::LAND:
    default:
        return BiomeRef::LAND;
    }
}

void BiomeRef::_bind_methods()
{
    using namespace godot;
    
    ClassDB::bind_method(D_METHOD("get_biome_type"), &get_biome_type);
    ClassDB::bind_method(D_METHOD("get_vertices"), &get_vertices);
}
