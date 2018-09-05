//#ifndef POINT_H
//#define POINT_H
//
//#include "object.h"
//
//
//class Point : public Object {
//public:
//    Point();
//    Point(double x, double y);
//	Object2_ptr_t clone() const;
//	const vertices2_t& points() const;
//	vertices2_t& points();
//    void xShift(double dx);
//    void yShift(double dy);
//    void shift(double dx, double dy);
//    void xShift(double fx, double rx);
//    void yShift(double fy, double ry);
//    void shift(double fx, double fy, double rx, double ry);
//    void xScale(double sx);
//    void yScale(double sy);
//	void scale(double sx, double sy);
//    void morph(const vertices2_t& points);
//    //void morph(const vertex2_t& point);
//    //int xPos() const { return m_x; }
//	//int yPos() const { return m_y; }
//	double xPos() const { return m_coords[0]; }
//	double yPos() const { return m_coords[1]; }
//
//private:
//	mutable vertices2_t m_points;
//    //int m_x, m_y;
//    Vec2f m_coords;
//};
//
//#endif	 	  	 	     	   		   	      	 	    	 	
