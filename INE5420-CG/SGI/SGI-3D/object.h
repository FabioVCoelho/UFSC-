#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"
#include "object_traits.h"
#include "clipping.h"
#include "color.h"
#include <vector>
#include <string>
#include <memory>

template<size_t Dim>
class Object;

template<size_t Dim>
using object_t = Object<Dim>;

using object2_t = object_t<2>;
using object3_t = object_t<3>;

template<size_t Dim>
using object_ptr_t = std::shared_ptr<Object<Dim>>;

using object2_ptr_t = object_ptr_t<2>;
using object3_ptr_t = object_ptr_t<3>;

template<size_t Dim>
class Object {
public:
	Object(const shape_t<Dim>& shape);

	Object(const shape_t<Dim>& shape, const ObjectTraits& traits);

	virtual ~Object() = 0;

	const ObjectTraits& traits() const { return m_traits; }

	ObjectId_t& id() const { return m_id; }	 	  	 	     	   		   	      	 	    	 	

	std::string& name() { return m_name; }
	void name(std::string& name) { m_name = name; }

	shape_t<Dim>& shape() { return m_shape; }
	const shape_t<Dim>& shape() const { return m_shape; }

	shape_t<Dim>& windowShape() { return m_windowShape; }
	const shape_t<Dim>& windowShape() const { return m_windowShape; }

	virtual object_ptr_t<Dim> clone() const = 0;

	virtual void cloneShape(const shape_t<Dim>& shape);

	virtual vertex_t<Dim> center() const = 0;

	virtual void shift(const transform_t<Dim>& shift, const transform_t<Dim>& toWindow) = 0;
	virtual void scale(const transform_t<Dim>& scale, const transform_t<Dim>& toWindow) = 0;
	virtual void rotate(const transform_t<Dim>& rotation, const transform_t<Dim>& toWindow) = 0;

	virtual void worldToWindow(const transform_t<Dim>& transf) = 0;
	virtual void windowToWorld(const transform_t<Dim>& transf) = 0;

	void perspective(double dop);

	//void project()

	virtual void clip(const Clipper& clipper, shape2_t& clippedShape) = 0;

	void setColor(const Color& color) { m_traits.color = color; }

	Color color() const { return m_traits.color; }

protected:
	shape_t<Dim> m_shape;
	shape_t<Dim> m_windowShape;
	//shape2_t m_projectedShape;
	ObjectTraits m_traits;
	mutable ObjectId_t m_id;
	std::string m_name;
};

//template<>
//class Object<2> {	 	  	 	     	   		   	      	 	    	 	
//public:
//	//using object_ptr_t = std::shared_ptr<Object<2>>;
//
//	Object(const vertices2_t& points);
//
//	Object(const vertices2_t& points, const ObjectTraits& traits);
//
//    virtual ~Object() = 0;
//
//	const ObjectTraits& traits() const { return m_traits; }
//
//	ObjectId_t& id() const { return m_id; }
//
//	std::string& name() { return m_name; }
//	void name(std::string& name) { m_name = name; }
//
//	//virtual bool isPolygon() const = 0;
//
//	vertices2_t& points() { return m_object.vertices(); }
//	const vertices2_t& points() const { return m_object.vertices(); }
//	
//	window_vertices2_t& windowPoints() { return m_windowObject.vertices(); }
//	const window_vertices2_t& windowPoints() const { return m_windowObject.vertices(); }
//
//	edges2_t& edges() { return m_object.edges(); }
//	const edges2_t& edges() const { return m_object.edges(); }
//
//	window_edges2_t& windowEdges() { return m_windowObject.edges(); }
//	const window_edges2_t& windowEdges() const { return m_windowObject.edges(); }
//	
//	virtual object_ptr_t<2> clone() const = 0;
//	
//	void reset(const object_t<2>& Object);
//
//	virtual vertex2_t center() const = 0;
//
//    virtual void shift(const matrix3f& shift, const matrix3f& toWindow) = 0;
//	virtual void scale(const matrix3f& scale, const matrix3f& toWindow) = 0;
//	virtual void rotate(const matrix3f& rotation, const matrix3f& toWindow) = 0;
//
//	virtual void worldToWindow(const matrix3f& transf) = 0;
//	virtual void windowToWorld(const matrix3f& transf) = 0;
//
//	virtual void clip(const Clipper& clipper, object_t<2>& clippedObject) = 0;
//
//	void setColor(const Color& color) { m_traits.color = color; }	 	  	 	     	   		   	      	 	    	 	
//
//	Color color() const { return m_traits.color; }
//    
//protected:
//	object_t<2> m_object;
//	object_t<2> m_windowObject;
//	ObjectTraits m_traits;
//	mutable ObjectId_t m_id;
//	std::string m_name;
//};
//
//template<>
//class Object<3> {
//public:
//	//using object_ptr_t = std::shared_ptr<Object<3>>;
//
//	Object(const vertices2_t& points);
//
//	Object(const vertices2_t& points, const ObjectTraits& traits);
//
//	virtual ~Object() = 0;
//
//	const ObjectTraits& traits() const { return m_traits; }
//
//	ObjectId_t& id() const { return m_id; }
//
//	std::string& name() { return m_name; }
//	void name(std::string& name) { m_name = name; }
//
//	//virtual bool isPolygon() const = 0;
//
//	vertices3_t& points() { return m_points.vertices(); }
//	const vertices3_t& points() const { return m_points.vertices(); }
//
//	window_vertices3_t& windowPoints() { return m_windowPoints.vertices(); }
//	const window_vertices3_t& windowPoints() const { return m_windowPoints.vertices(); }	 	  	 	     	   		   	      	 	    	 	
//
//	edges3_t& edges() { return m_points.edges(); }
//	const edges3_t& edges() const { return m_points.edges(); }
//
//	window_edges3_t& windowEdges() { return m_windowPoints.edges(); }
//	const window_edges3_t& windowEdges() const { return m_windowPoints.edges(); }
//
//	virtual Object3_ptr_t clone() const = 0;
//
//	void reset(const faceedgevertex3f_t& Object);
//
//	virtual vertex2_t center() const = 0;
//
//	virtual void shift(const matrix3f& shift, const matrix3f& toWindow) = 0;
//	virtual void scale(const matrix3f& scale, const matrix3f& toWindow) = 0;
//	virtual void rotate(const matrix3f& rotation, const matrix3f& toWindow) = 0;
//
//	virtual void worldToWindow(const matrix3f& transf) = 0;
//	virtual void windowToWorld(const matrix3f& transf) = 0;
//
//	virtual void clip(const Clipper& clipper, edgevertex2f_t& clippedObject) = 0;
//
//	void setColor(const Color& color) { m_traits.color = color; }
//
//	Color color() const { return m_traits.color; }
//
//protected:
//	faceedgevertex3f_t m_points;
//	faceedgevertex3f_t m_windowPoints;
//	ObjectTraits m_traits;
//	mutable ObjectId_t m_id;
//	std::string m_name;
//};


#endif	 	  	 	     	   		   	      	 	    	 	
