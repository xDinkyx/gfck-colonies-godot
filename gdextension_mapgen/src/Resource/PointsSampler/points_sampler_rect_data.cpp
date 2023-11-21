#include "points_sampler_rect_data.h"


void mapgen::PointsSamplerRectData::set_dimensions(const godot::Vector2 mapSize)
{
    size = mapSize;
}

void mapgen::PointsSamplerRectData::set_point_count(int count)
{
    pointCount = count;
}

void mapgen::PointsSamplerRectData::set_minimum_distance(float distance)
{
    minimumDistance = distance;
}

godot::Vector2 mapgen::PointsSamplerRectData::get_dimensions() const
{
    return size;
}

int mapgen::PointsSamplerRectData::get_point_count() const
{
    return pointCount;
}

float mapgen::PointsSamplerRectData::get_minimum_distance() const
{
    return minimumDistance;
}

void mapgen::PointsSamplerRectData::_bind_methods()
{
    using namespace godot;

    ClassDB::bind_method(D_METHOD("set_dimensions", "dimensions"), &set_dimensions);
    ClassDB::bind_method(D_METHOD("set_point_count", "count"), &set_point_count);
    ClassDB::bind_method(D_METHOD("set_minimum_distance", "distance"), &set_minimum_distance);

    ClassDB::bind_method(D_METHOD("get_dimensions"), &get_dimensions);
    ClassDB::bind_method(D_METHOD("get_point_count"), &get_point_count);
    ClassDB::bind_method(D_METHOD("get_minimum_distance"), &get_minimum_distance);

    ClassDB::add_property("PointsSamplerRectData", PropertyInfo(Variant::VECTOR2, "dimensions"), "set_dimensions", "get_dimensions");
    ClassDB::add_property("PointsSamplerRectData", PropertyInfo(Variant::INT, "point_number"), "set_point_count", "get_point_count");
    ClassDB::add_property("PointsSamplerRectData", PropertyInfo(Variant::FLOAT, "minimum_distance_sq"), "set_minimum_distance",
                          "get_minimum_distance");
}
