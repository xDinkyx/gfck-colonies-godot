#include "test_node2d.h"

#include <godot_cpp/variant/utility_functions.hpp>

namespace gfck_mapgen
{
    void TestNode2D::say_hello(const String& what)
    {
        // Print to Godot Console.
        godot::UtilityFunctions::print("Hello ", what, "!");
    }

    void TestNode2D::_bind_methods()
    {
        // Bind a method to this class.
        godot::ClassDB::bind_method(godot::D_METHOD("say_hello", "what"), &TestNode2D::say_hello);
    }
}