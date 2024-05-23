extends Node2D

var biome_ref : BiomeRef = null 
var size_factor : float

@export var edge_width = 0.004:
	set(value):
		edge_width = value
		if(get_node_or_null("Line2D") == null):
			return
		$Line2D.width = edge_width
		queue_redraw()
@export var edge_internal_offset = 0.002:
	set(value):
		edge_internal_offset = value
		_updateLine()
		queue_redraw()
@export var land_color : Color = Color.MEDIUM_SEA_GREEN
@export var water_color : Color = Color.CADET_BLUE
	
# Called when the node enters the scene tree for the first time.
func _ready():
	$Polygon2D.polygon = biome_ref.get_vertices()
	if(biome_ref.get_biome_type() == 0):
		$Polygon2D.color = land_color
	elif (biome_ref.get_biome_type() == 1):
		$Polygon2D.color = water_color
	
	$Line2D.default_color = Color.from_hsv(randf_range(0.0, 6.0), 1.0, 1.0)
	$Line2D.width = edge_width
	_updateLine()
	
	_center_on_screen()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass


func _updateLine():
	if(get_node_or_null("Line2D") == null):
		return
	$Line2D.clear_points()
	$Line2D.points = _getEdgePoints(biome_ref)
	$Line2D.add_point($Line2D.points[0])
	

func _getEdgePoints(biome : BiomeRef):
	var edgePoints = []
	var biomeCenter = _getCenter(biome)
	for vertex in biome.get_vertices():
		var offsetDirection = (biomeCenter - vertex).normalized()
		edgePoints.append(vertex + offsetDirection * edge_internal_offset)
	return edgePoints
	
	
func _getCenter(biome : BiomeRef):
	var center = Vector2.ZERO
	for vertex in biome.get_vertices():
		center += vertex
	center /= biome.get_vertices().size()
	return center


func _center_on_screen():
	var screen_center = get_viewport_rect().size / 2
	position = screen_center# - Vector2.ONE * size_factor / 2
