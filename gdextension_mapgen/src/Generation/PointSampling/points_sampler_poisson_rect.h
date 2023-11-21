#ifndef GENERATION_POINTSAMPLING_POINTS_SAMPLER_POISSON_RECT
#define GENERATION_POINTSAMPLING_POINTS_SAMPLER_POISSON_RECT

#include <godot_cpp/variant/packed_vector2_array.hpp>

#include "../../Resource/PointsSampler/points_sampler_rect_data.h"

namespace mapgen
{
    namespace PointsSamplerPoissonRect
    {
        godot::PackedVector2Array sample(const PointsSamplerRectData& data);
    };
} // namespace mapgen

#endif
