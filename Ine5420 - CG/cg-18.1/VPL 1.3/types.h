#ifndef TYPES_H
#define TYPES_H

#include "vec.h"
#include "vec2.h"
#include "vec3.h"
#include "matrix.h"
#include <vector>

using point_t = Vec2f;
using points_t = std::vector<point_t>;
using shapes_t = std::vector<points_t>;
using window_points_t = std::vector<point_t>;
using window_shape_t = std::vector<point_t>;
using window_shapes_t = std::vector<window_shape_t>;
using vp_shape_t = std::vector<Vec2i>;
using vp_shapes_t = std::vector<vp_shape_t>;
using tranform_t = matrix3f;
using unit = double;
using window_unit = double;
using angle_t = double;
using shapeId_t = int;

#endif
