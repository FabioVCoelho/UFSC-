#ifndef SHAPE_H
#define SHAPE_H

#include "edge.h"
#include "face.h"

template<size_t Dim, typename T>
class Shape {};

template<typename T>
class Shape<2,T> {
public:
	Shape() {}

	Shape(size_t size) { //: m_vertices(std::vector<Vec<Dim, T>>(size)) {
		m_vertices.reserve(size);
	}

	Shape(const std::vector<Vec<2, T>>& vert) : m_vertices(vert) {}

	Shape(const Shape<2, T>& other) {
		copy(other);
	}

	Shape(const Shape<3, T>& other) {
		copy(other);
	}

	void addVertex(const Vec<2, T>& vertex) { m_vertices.emplace_back(vertex); }

	void makeEdge(size_t v1, size_t v2) {
		m_edges.emplace_back(Edge<2, T>(m_edges.size(), m_vertices[v1], v1, m_vertices[v2], v2));
	}

	void clearEdges() {
		m_edges.clear();
	}	 	  	 	     	   		   	      	 	    	 	

	void clear() {
		m_vertices.clear();
		clearEdges();
	}

	void reserve(size_t size) {
		m_vertices.reserve(size);
	}

	void defaultEdges(bool closed = true) {
		size_t size = m_vertices.size();
		if (size == 0) {
			return;
		}
		m_edges.clear();
		m_edges.reserve(size);
		for (size_t i = 0; i < size - 1; ++i) {
			m_edges.emplace_back(Edge<2, T>(i, m_vertices[i], i, m_vertices[i + 1], i + 1));
		}
		if (closed) {
			m_edges.emplace_back(Edge<2, T>(size, m_vertices[size - 1], size - 1, m_vertices[0], 0));
		}
	}

	void copy(const Shape<2, T>& other) {
		m_vertices = other.vertices();
		m_edges.clear();
		m_edges.reserve(other.edges().size());
		size_t iv1, iv2;
		for (const Edge<2, T>& e : other.edges()) {
			iv1 = e.iv1();
			iv2 = e.iv2();
			m_edges.emplace_back(e.idx(), m_vertices[iv1], iv1, m_vertices[iv2], iv2);
		}
	}	 	  	 	     	   		   	      	 	    	 	

	void copy(const Shape<3, T>& other) {
		m_vertices = std::vector<Vec<2, T>>(other.vertices().begin(), other.vertices().end());
		m_edges.clear();
		m_edges.reserve(other.edges().size());
		size_t iv1, iv2;
		for (const Edge<3, T>& e : other.edges()) {
			iv1 = e.iv1();
			iv2 = e.iv2();
			m_edges.emplace_back(e.idx(), m_vertices[iv1], iv1, m_vertices[iv2], iv2);
		}
	}

	void copy(const std::vector<Vec<2, T>>& vert) {
		assert(m_vertices.size() == vert.size());
		m_vertices = vert;
	}

	std::vector<Vec<2, T>>& vertices() { return m_vertices; }
	std::vector<Edge<2, T>>& edges() { return m_edges; }

	const std::vector<Vec<2, T>>& vertices() const { return m_vertices; }
	const std::vector<Edge<2, T>>& edges() const { return m_edges; }

private:
	std::vector<Vec<2, T>> m_vertices;
	std::vector<Edge<2, T>> m_edges;
};


template<typename T>
class Shape<3, T> {
public:
	Shape() {}

	Shape(size_t size) : m_vertices(std::vector<Vec<3, T>>(size)) {	 	  	 	     	   		   	      	 	    	 	
		//init();
	}

	Shape(const std::vector<Vec<3, T>>& vert) : m_vertices(vert) {}

	Shape(const Shape<3, T>& other) {
		copy(other);
	}

	Shape(const Shape<2, T>& other) {
		copy(other);
	}

	void addVertex(const Vec<3, T>& vertex) { m_vertices.emplace_back(vertex); }

	void makeEdge(size_t v1, size_t v2) {
		m_edges.emplace_back(Edge<3, T>(m_edges.size(), m_vertices[v1], v1, m_vertices[v2], v2));
	}

	void makeFace(std::vector<size_t> edge_ids) {
		std::vector<Edge<3, T>*> faceEdges;
		faceEdges.reserve(edge_ids.size());
		for (size_t id : edge_ids) {
			faceEdges.emplace_back(&(m_edges[id]));
		}
		m_faces.emplace_back(faceEdges);
	}

	void copy(const Shape<3, T>& other) {
		m_vertices = other.vertices();
		m_edges.clear();
		m_edges.reserve(other.edges().size());
		size_t iv1, iv2;
		for (const Edge<3, T>& e : other.edges()) {
			iv1 = e.iv1();
			iv2 = e.iv2();
			m_edges.emplace_back(e.idx(), m_vertices[iv1], iv1, m_vertices[iv2], iv2);
		}	 	  	 	     	   		   	      	 	    	 	
		m_faces = other.faces();
		for (const Face<3,T>& f : m_faces) {
			std::vector<Edge<3, T>*> edgevec = f.edges();
			std::vector<size_t> edgeidxvec = f.edgesIdxs();
			for (size_t i = 0; i < f.edges().size(); ++i) {
				edgevec[i] = &(m_edges[edgeidxvec[i]]);
			}
		}
	}

	void copy(const Shape<2, T>& other) {
		m_vertices = std::vector<Vec<2, T>>(other.vertices().begin(), other.vertices().end());
		m_edges.clear();
		m_edges.reserve(other.edges().size());
		size_t iv1, iv2;
		for (const Edge<2, T>& e : other.edges()) {
			iv1 = e.iv1();
			iv2 = e.iv2();
			m_edges.emplace_back(e.idx(), m_vertices[iv1], iv1, m_vertices[iv2], iv2);
		}
		//m_faces = other.faces();
		std::vector<Edge<3, T>*> edgePtrs;
		for (Edge<2, T>* e : other.edges()) {
			edgePtrs.emplace_back(&(m_edges[e->idx()]));
		}
		m_faces.emplace_back(edgePtrs);
		//for (Edge<2,T>* e : f.edges()) {
		//	*e = &(m_edges[e->idx()]);
		//}
		
	}

	//m_vertices = std::vector<Vec<2, T>>(other.vertices().begin(), other.vertices().end());

	std::vector<Vec<3, T>>& vertices() { return m_vertices; }
	const std::vector<Vec<3, T>>& vertices() const { return m_vertices; }	 	  	 	     	   		   	      	 	    	 	

	std::vector<Edge<3, T>>& edges() { return m_edges; }
	const std::vector<Edge<3, T>>& edges() const { return m_edges; }

	/*Shape<2, T>& ev() { return m_edgeVextex; }
	const Shape<2, T>& ev() const { return m_edgeVextex; }*/

	std::vector<Face<3, T>>& faces() { return m_faces; }
	const std::vector<Face<3, T>>& faces() const { return m_faces; }


private:
	std::vector<Vec<3, T>> m_vertices;
	std::vector<Edge<3, T>> m_edges;
	std::vector<Face<3, T>> m_faces;
};

//	template <size_t Dim, typename T>
//struct EdgeVertex {
//
//	EdgeVertex() {}
//
//	EdgeVertex(size_t size) { //: m_vertices(std::vector<Vec<Dim, T>>(size)) {
//		m_vertices.reserve(size);
//	}
//
//	EdgeVertex(const std::vector<Vec<Dim, T>>& vert) : m_vertices(vert) {}
//
//	EdgeVertex(const EdgeVertex<Dim, T>& other) {
//		copy(other);
//	}
//
//	void addVertex(const Vec<Dim, T>& vertex) { m_vertices.emplace_back(vertex); }
//
//	/*void makeEdge(const Vec<Dim, T>& v1, const Vec<Dim, T>& v2) {
//	m_edges.emplace_back(Edge<Dim, T>(m_edges.size() + 1, v1, , m_vertices[v2]));
//	}*/
//
//	void makeEdge(size_t v1, size_t v2) {	 	  	 	     	   		   	      	 	    	 	
//		m_edges.emplace_back(Edge<Dim, T>(m_edges.size() + 1, m_vertices[v1], v1, m_vertices[v2], v2));
//	}
//
//	void clearEdges() {
//		m_edges.clear();
//	}
//
//	void clear() {
//		m_vertices.clear();
//		clearEdges();
//	}
//
//	void reserve(size_t size) {
//		m_vertices.reserve(size);
//	}
//
//	void defaultEdges(bool closed = true) {
//		size_t size = m_vertices.size();
//		m_edges.reserve(size);
//		for (size_t i = 0; i < size - 1; ++i) {
//			m_edges.emplace_back(Edge<Dim, T>(i, m_vertices[i], i, m_vertices[i + 1], i + 1));
//		}
//		if (closed) {
//			m_edges.emplace_back(Edge<Dim, T>(size, m_vertices[size - 1], size - 1, m_vertices[0], 0));
//		}
//	}
//
//
//	/*explicit EdgeVertex(const std::vector<Vec<Dim, T>>& vertices, bool closed = true)
//	: EdgeVertex(vertices.size(), closed)
//	{
//	copy(vertices);
//	}
//
//	void reset(bool closed = true) {
//	m_edges.clear();
//	init(closed);
//	}	 	  	 	     	   		   	      	 	    	 	
//
//	void reset(const std::vector<Vec<Dim, T>>& vertices, bool closed = true) {
//	m_edges.clear();
//	m_vertices = vertices;
//	init(closed);
//	}*/
//
//
//	/*void copy(const std::vector<Vec<Dim, T>>& vertices) {
//	assert(m_vertices.size() == vertices.size());
//	m_vertices = vertices;
//	}*/
//
//	void copy(const EdgeVertex<Dim, T>& other) {
//		/*assert(m_vertices.size() == other.vertices().size());
//		m_vertices = other.vertices();*/
//
//		m_vertices = other.vertices();
//		m_edges.clear();
//		m_edges.reserve(other.edges().size());
//		size_t iv1, iv2;
//		for (const Edge<Dim, T>& e : other.edges()) {
//			iv1 = e.iv1();
//			iv2 = e.iv2();
//			m_edges.emplace_back(e.idx(), m_vertices[iv1], iv1, m_vertices[iv1], iv2);
//		}
//	}
//
//	void copy(const std::vector<Vec<Dim, T>>& vert) {
//		assert(m_vertices.size() == vert.size());
//		m_vertices = vert;
//	}
//
//	std::vector<Vec<Dim, T>>& vertices() { return m_vertices; }
//	std::vector<Edge<Dim, T>>& edges() { return m_edges; }
//
//	const std::vector<Vec<Dim, T>>& vertices() const { return m_vertices; }	 	  	 	     	   		   	      	 	    	 	
//	const std::vector<Edge<Dim, T>>& edges() const { return m_edges; }
//
//private:
//	/*void init(bool closed = true) {
//	size_t size = m_vertices.size();
//	if (size == 0) { return; }
//	m_edges.reserve(size);
//	for (size_t i = 0; i < size - 1; ++i) {
//	m_edges.emplace_back(Edge<Dim, T>(m_vertices[i], m_vertices[i + 1]));
//	}
//	if (closed) {
//	m_edges.emplace_back(Edge<Dim, T>(m_vertices[size - 1], m_vertices[0]));
//	}
//	}*/
//	std::vector<Vec<Dim, T>> m_vertices;
//	std::vector<Edge<Dim, T>> m_edges;
//};

#endif