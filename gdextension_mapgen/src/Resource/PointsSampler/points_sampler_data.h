#ifndef RESOURCE_POINTSSAMPLER_POINTS_SAMPLER_DATA
#define RESOURCE_POINTSSAMPLER_POINTS_SAMPLER_DATA

#include <godot_cpp/classes/resource.hpp>

namespace mapgen
{
    class IPointsSamplerData : public godot::Resource
    {
      public:
        GDCLASS(IPointsSamplerData, godot::Resource)

      protected:
        static void _bind_methods() {}
    };
} // namespace mapgen

#endif
