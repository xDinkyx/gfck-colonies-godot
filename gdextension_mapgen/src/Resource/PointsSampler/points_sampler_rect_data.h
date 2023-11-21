#ifndef RESOURCE_POINTSSAMPLER_POINTS_SAMPLER_RECT_DATA
#define RESOURCE_POINTSSAMPLER_POINTS_SAMPLER_RECT_DATA

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "points_sampler_data.h"

namespace mapgen
{
class PointsSamplerRectData : public IPointsSamplerData
{
  public:
    GDCLASS(PointsSamplerRectData, IPointsSamplerData)

    void set_dimensions(const godot::Vector2 size);
    godot::Vector2 get_dimensions() const;

    void set_point_count(int count);
    int get_point_count() const;

    void set_minimum_distance(float distance);
    float get_minimum_distance() const;

  protected:
    static void _bind_methods();

  private:
    godot::Vector2 size = {1.0f, 1.0f};
    unsigned int pointCount = 100;
    float minimumDistance = -1.f;
};
} // namespace mapgen

#endif
