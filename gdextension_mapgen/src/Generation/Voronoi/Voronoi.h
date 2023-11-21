#ifndef SRC_GENERATION_VORONOI_VORONOI
#define SRC_GENERATION_VORONOI_VORONOI

#include <vector>

#include "godot_cpp/variant/vector2.hpp"
#include "godot_cpp/variant/vector4.hpp"

struct jcv_diagram_;

namespace mapgen
{
    class Voronoi
    {
      public:
        struct Cell
        {
            std::vector<godot::Vector2> points;
        };

        void generate(const std::vector<godot::Vector2>& points, int width, int height);

        std::vector<godot::Vector2>              get_sites() const;
        std::vector<std::vector<godot::Vector2>> get_cells() const;
        std::vector<godot::Vector4>              get_edges() const;

      private:
        void StoreSitesAndCells(const jcv_diagram_& diagram);
        void StoreEdges(const jcv_diagram_& diagram);

        std::vector<godot::Vector2>              sites;
        std::vector<std::vector<godot::Vector2>> cells;
        std::vector<godot::Vector4>              edges;
    };
} // namespace mapgen

#endif
