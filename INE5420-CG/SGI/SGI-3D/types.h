#ifndef TYPES_H
#define TYPES_H

#include "vec.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "matrix.h"
#include "shape.h"
//#include "edge.h"
//#include "face.h"
#include <vector>
#include <cstddef>

using unit = double;

template<size_t Dim>
using vertex_t = Vec<Dim, unit>;

template<size_t Dim>
using vertices_t = std::vector<vertex_t<Dim>>;

template<size_t Dim>
using edge_t = Edge<Dim, unit>;

template<size_t Dim>
using edges_t = std::vector<edge_t<Dim>>;


using window_unit = double;

template<size_t Dim>
using window_vertex_t = Vec<Dim, window_unit>;

template<size_t Dim>
using window_vertices_t = std::vector<window_vertex_t<Dim>>;

template<size_t Dim>
using window_edge_t = Edge<Dim, window_unit>;

template<size_t Dim>
using window_edges_t = std::vector<window_edge_t<Dim>>;


template<size_t Dim>
using control_point_t = vertex_t<Dim>;

template<size_t Dim>
using shape_t = Shape<Dim, double>;

template<size_t Dim>
using transform_t = Matrix<Dim+1, double>;


using transform2_t = transform_t<2>;
using transform3_t = transform_t<3>;

using angle_t = double;

using ObjectId_t = int;


using vertex2_t = Vec2f;
using vertex3_t = Vec3f;
using vertices2_t = std::vector<vertex2_t>;
using vertices3_t = std::vector<vertex3_t>;

using edge2_t = edge2f;
using edge3_t = edge3f;
using edges2_t = std::vector<edge2_t>;
using edges3_t = std::vector<edge3_t>;

using window_vertex2_t = vertex2_t;
using window_vertices2_t = std::vector<vertex2_t>;
using window_vertex3_t = vertex3_t;
using window_vertices3_t = std::vector<vertex3_t>;

using window_edge2_t = edge2_t;
using window_edges2_t = std::vector<window_edge2_t>;
using window_edge3_t = edge3_t;
using window_edges3_t = std::vector<window_edge3_t>;

using shape2_t = Shape<2, double>;
using shape3_t = Shape<3, double>;


//using edgevertex2f_t = EdgeVertex<2, double>;
//using edgevertex2i_t = EdgeVertex<2, int>;
//using faceedgevertex2f_t = FaceEdgeVertex<2, double>;
//using faceedgevertex2i_t = FaceEdgeVertex<2, int>;
//using faceedgevertex3f_t = FaceEdgeVertex<3, double>;
//using faceedgevertex3i_t = FaceEdgeVertex<3, int>;

//using vp_vertex2_t = Vec2i;
//using vp_vertices2_t = std::vector<vp_vertex2_t>;
//using vp_edge_t = vpedge2;
//using vp_edges_t = std::vector<vp_edge_t>;
//using vp_Object_t = std::vector<vp_edge_t>;
//using vp_Objects_t = std::vector<vp_Object_t>;
//using tranform_t = matrix3f;
//using unit = double;
//using window_unit = double;
//using angle_t = double;
//using ObjectId_t = int;

//template<size_t Dim>
//using control_point_t<Dim> = Vector<Dim, double>;

//using control_point2_t = vertex2_t;
//using control_points2_t = std::vector<control_point2_t>;
//template<>
//using cv<2> = control_point2_t;
//using control_point3_t = vertex3_t;
//using control_points3_t = std::vector<control_point3_t>;
//using cv3_t = control_point3_t;
//using cv<2> = cv2_t;
//using cv<3> = cv3_t;

#endif
	 	  	 	     	   		   	      	 	    	 	
