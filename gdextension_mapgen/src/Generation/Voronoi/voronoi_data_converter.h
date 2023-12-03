#ifndef SRC_GENERATION_VORONOI_VORONOI_DATA_CONVERTER
#define SRC_GENERATION_VORONOI_VORONOI_DATA_CONVERTER

struct jcv_point_;
struct jcv_diagram_;

namespace godot
{
    struct Vector2;
    struct Vector4;
} // namespace godot

namespace mapgen::voronoi
{
    struct DiagramData;
}

namespace mapgen::voronoi::converter
{
    godot::Vector2 to_godot_vector2(const jcv_point_& p);
    godot::Vector4 to_godot_vector4(const jcv_point_& p1, const jcv_point_& p2);
    jcv_point_     to_jcv_point(const godot::Vector2& v);

    DiagramData extract_data(const jcv_diagram_& jcv_diagram);
} // namespace mapgen::voronoi::converter

#endif
