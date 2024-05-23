#ifndef SRC_NODE_BIOME_REF
#define SRC_NODE_BIOME_REF

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>

namespace mapgen
{
    struct Biome;
};

class BiomeRef : public godot::RefCounted
{
    GDCLASS(BiomeRef, godot::RefCounted);

  public:
    enum BiomeType
    {
        LAND  = 0,
        WATER = 1,
    };
    
    void set_biome(const mapgen::Biome* biome);

    godot::PackedVector2Array get_vertices() const;
    BiomeType                 get_biome_type() const;

  protected:
    static void _bind_methods();

  private:
    const mapgen::Biome* Biome = nullptr;
};

VARIANT_ENUM_CAST(BiomeRef::BiomeType);

#endif
