#include "map_generator.h"

#include "../Generation/PointSampling/points_sampler_poisson_rect.h"
#include "../Resource/PointsSampler/points_sampler_rect_data.h"

#include "../Generation/Voronoi/voronoi_generator.h"

#include "../Conversion/godot_to_std.h"

using namespace godot;
using namespace mapgen;

namespace
{
    PackedVector2Array sample_points(const IPointsSamplerData* samplerData)
    {
        if (auto rect_sampler_data = dynamic_cast<const PointsSamplerRectData*>(samplerData))
            return PointsSamplerPoissonRect::sample(*rect_sampler_data);
        return {};
    }
} // namespace

void MapGenerator::generate(int waterEdgeFlag)
{
    mapData.SampledPoints = sample_points(*pointSamplerData);

    mapData.VoronoiDiagram = mapgen::voronoi::generation::generate(to_std_vector(mapData.SampledPoints), 1, 1);

    mapData.Biomes = BiomeGenerator::generate(mapData.VoronoiDiagram, (BiomeGenerator::MapEdgeFlag)waterEdgeFlag);
}

void MapGenerator::set_points_sampler_data(const Ref<IPointsSamplerData>& data)
{
    pointSamplerData = data;
}

Ref<IPointsSamplerData> MapGenerator::get_points_sampler_data() const
{
    return pointSamplerData;
}

godot::PackedVector2Array mapgen::MapGenerator::get_voronoi_vertices() const
{
    godot::PackedVector2Array output;

    for (auto& v : mapData.VoronoiDiagram.GodotCellCenters)
        output.push_back(v);

    return output;
}

godot::Array mapgen::MapGenerator::get_voronoi_edges() const
{
    godot::Array edges;

    for (auto& edge : mapData.VoronoiDiagram.GodotEdges)
        edges.push_back(edge);

    return edges;
}

godot::Array mapgen::MapGenerator::get_voronoi_cells() const
{
    godot::Array cells;

    for (auto& cell : mapData.VoronoiDiagram.GodotCells)
    {
        godot::Array cell_vertices;
        for (auto& p : cell)
            cell_vertices.push_back(p);

        cells.push_back(cell_vertices);
    }

    return cells;
}

PackedVector2Array MapGenerator::get_sampled_points() const
{
    return mapData.SampledPoints;
}

void MapGenerator::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("generate", "map_edge_water_flag"), &generate);
    ClassDB::bind_method(D_METHOD("get_sampled_points"), &get_sampled_points);
    ClassDB::bind_method(D_METHOD("get_voronoi_vertices"), &get_voronoi_vertices);
    ClassDB::bind_method(D_METHOD("get_voronoi_edges"), &get_voronoi_edges);
    ClassDB::bind_method(D_METHOD("get_voronoi_cells"), &get_voronoi_cells);

    ClassDB::bind_method(D_METHOD("get_points_sampler_data"), &get_points_sampler_data);
    ClassDB::bind_method(D_METHOD("set_points_sampler_data", "points_sampler_data"), &set_points_sampler_data);
    ClassDB::add_property("MapGenerator", PropertyInfo(Variant::OBJECT, "points_sampler_data"), "set_points_sampler_data", "get_points_sampler_data");
}
