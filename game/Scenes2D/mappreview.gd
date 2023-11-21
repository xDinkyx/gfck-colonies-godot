extends Node2D

@export var size_factor = 100.0:
	set(value):
		size_factor = value
		queue_redraw()
@export_range(1, 10) var point_size = 3.5:
	set(value):
		point_size = value
		queue_redraw()
@export var sampled_point_color = Color.CORNFLOWER_BLUE:
	set(value):
		sampled_point_color = value
		queue_redraw()
@export var voronoi_vertex_color = Color.CORAL:
	set(value):
		voronoi_vertex_color = value
		queue_redraw()
@export var voronoi_edge_color = Color.SKY_BLUE:
	set(value):
		voronoi_edge_color = value
		queue_redraw()
@export_range(1, 10) var edge_thickness = 1.5:
	set(value):
		edge_thickness = value
		queue_redraw()
		
@onready var Generator = $MapGenerator

# Called when the node enters the scene tree for the first time.
func _ready():
	Generator.generate()
	
	print(Generator.get_sampled_points().size())
	print(Generator.get_voronoi_vertices().size())
	
	_center_on_screen()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass

func _draw():

	for edge in Generator.get_voronoi_edges():
		var p1 = Vector2(edge.x, edge.y) * size_factor
		var p2 = Vector2(edge.z, edge.w) * size_factor
		draw_line(p1, p2, voronoi_edge_color, edge_thickness)
		
	for v in Generator.get_voronoi_vertices():
		draw_circle(v * size_factor, point_size, voronoi_vertex_color)

func _center_on_screen():
	var screen_center = get_viewport_rect().size / 2
	position = screen_center - Vector2.ONE * size_factor / 2
