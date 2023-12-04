#ifndef NODE_MAP_GENERATOR
#define NODE_MAP_GENERATOR

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>

#include "../Resource/PointsSampler/points_sampler_data.h"
#include "../Generation/map_data.h"
#include "../Generation/Biomes/biome_type.h"
#include "../Generation/Biomes/biome_generator.h"

namespace mapgen
{
    class MapGenerator : public godot::Node
    {
      public:
        GDCLASS(MapGenerator, godot::Node)

        // generation
        void generate(int waterGenFlag);

        // point sampler
        void                      set_points_sampler_data(const godot::Ref<IPointsSamplerData>& data);
        godot::PackedVector2Array get_sampled_points() const;

        godot::Ref<IPointsSamplerData> get_points_sampler_data() const;

        // voronoi
        godot::PackedVector2Array get_voronoi_vertices() const;
        godot::Array              get_voronoi_edges() const;
        godot::Array              get_voronoi_cells() const;

      protected:
        static void _bind_methods();

      private:
        // input
        godot::Ref<IPointsSamplerData> pointSamplerData;

        // output
        MapData mapData;
    };

} // namespace mapgen

#endif
