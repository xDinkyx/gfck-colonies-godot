#include "points_sampler_poisson_rect.h"

#include <algorithm>

#include "PoissonGenerator.h"

#include "../../Resource/PointsSampler/points_sampler_rect_data.h"

godot::PackedVector2Array mapgen::PointsSamplerPoissonRect::sample(const PointsSamplerRectData& data)
{
    // Generate
    PoissonGenerator::DefaultPRNG PRNG;
    auto points = PoissonGenerator::generatePoissonPoints(data.get_point_count(), PRNG, false, 30U, data.get_minimum_distance());

    // Transform
    godot::PackedVector2Array out;
    for (const auto& poissonPoint : points)
        out.push_back(godot::Vector2{poissonPoint.x, poissonPoint.y});

    return out;
}
