#ifndef TYPES_H
#define TYPES_H

#include "vec.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "edge.h"
#include "matrix.h"
#include <vector>

using point_t = Vec2f;
using points_t = std::vector<point_t>;
using edge_t = edge2f;
using edges_t = std::vector<edge_t>;
using edgevertex2f_t = EdgeVertex<2, double>;
using edgevertex2i_t = EdgeVertex<2, int>;
using window_point_t = point_t;
using window_points_t = std::vector<point_t>;
using window_edge_t = edge_t;
using window_edges_t = std::vector<window_edge_t>;
using vp_point_t = Vec2i;
using vp_points_t = std::vector<vp_point_t>;
using vp_edge_t = vpedge2;
using vp_edges_t = std::vector<vp_edge_t>;
using vp_shape_t = std::vector<vp_edge_t>;

using vp_shapes_t = std::vector<vp_shape_t>;
using tranform_t = matrix3f;
using unit = double;
using window_unit = double;
using angle_t = double;
using shapeId_t = int;

using control_point_t = point_t;
using control_points_t = std::vector<control_point_t>;;

#endif
	 	  	 	     	   		   	      	 	    	 	
