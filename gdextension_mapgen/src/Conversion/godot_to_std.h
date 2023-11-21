#ifndef CONVERSION_GODOT_TO_STD
#define CONVERSION_GODOT_TO_STD

#include <godot_cpp/variant/packed_vector2_array.hpp>

#include <vector>

namespace mapgen
{
    inline std::vector<godot::Vector2> to_std_vector(const godot::PackedVector2Array& packedArray)
    {
        return {packedArray.ptr(), packedArray.ptr() + packedArray.size()};
    }
} // namespace mapgen

#endif
