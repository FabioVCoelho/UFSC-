//#include "point.h"
//#include <cassert>
//#include <cmath>
//
//Point::Point() 
//    : Point(0, 0) {}
//
// Point::Point(double x, double y) 
//     : m_coords(x,y) {}
//
////Point::Point(double x, double y) 
////    : m_x(x), m_y(y) {}
//
//Object2_ptr_t Point::clone() const {
//	return std::shared_ptr<Point>(new Point(*this));
//}
//
//const vertices2_t& Point::points() const {
//	//m_points = { {m_x,m_y} };
//	//return m_points;
//	return m_coords;
//}
//
//vertices2_t& Point::points() {
//	m_points = { { m_x,m_y } };
//	return m_points;
//}
//    
//void Point::xShift(double dx) {
//    m_x += dx;
//}
//
//void Point::yShift(double dy) {
//    m_y += dy;	
//}
//
//void Point::shift(double dx, double dy) {	 	  	 	     	   		   	      	 	    	 	
//    m_x += dx;
//    m_y += dy;
//}
//
//void Point::xShift(double fx, double rx) {
//	double inc = fx > 0 ?
//		ceil(fx * rx) : floor(fx * rx);
//    m_x += inc;
//}
//void Point::yShift(double fy, double ry) {
//    double inc = fy > 0 ?
//		ceil(fy * ry) : floor(fy * ry);
//    m_y += inc;
//}
//void Point::shift(double fx, double fy, double rx, double ry) {
//    double incx = fx > 0 ?
//		ceil(fx * rx) : floor(fx * rx);
//    double incy = fy > 0 ?
//		ceil(fy * ry) : floor(fy * ry);
//    m_x += incx;
//    m_y += incy;
//}
//
//void Point::xScale(double sx) {
//    return;
//
//}
//void Point::yScale(double sy) { 
//    return;
//}
//void Point::scale(double sx, double sy) {
//    return;
//}
//
//void Point::morph(const vertices2_t& points) {
//    assert(points.size() == 1);
//    m_x = points[0].first;
//    m_y = points[0].second;
//}	 	  	 	     	   		   	      	 	    	 	
//
//void Point::morph(const vertex2_t& point) {
//    m_x = point.first;
//    m_y = point.second;
//}