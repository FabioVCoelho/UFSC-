#ifndef EDGE_H
#define EDGE_H

#include "vec2.h"
#include "vec3.h"
#include <vector>

template <size_t dim, typename T>
class Edge {
public:
	Edge(const Vec<dim, T>& v1, const Vec<dim, T>& v2)
		: m_v1(v1), m_v2(v2) {}
	const Vec<dim, T>& v1() const { return m_v1; }
	const Vec<dim, T>& v2() const { return m_v2; }

private:
	const Vec<dim, T>& m_v1;
	const Vec<dim, T>& m_v2;
};

template <size_t dim>
class VpEdge {
public:
	VpEdge(const Vec<dim, int>& v1, const Vec<dim, int>& v2)
		: m_v1(v1), m_v2(v2) {}
	const Vec<dim, int>& v1() const { return m_v1; }
	const Vec<dim, int>& v2() const { return m_v2; }

private:
	Vec<dim, int> m_v1, m_v2;
};

template <size_t dim, typename T>
struct EdgeVertex {

	EdgeVertex() {}

	EdgeVertex(size_t size, bool closed = true) : m_vertices(std::vector<Vec<dim, T>>(size)) {	 	  	 	     	   		   	      	 	    	 	
		init(closed);
	}

	explicit EdgeVertex(const std::vector<Vec<dim, T>>& vertices, bool closed = true)
		: EdgeVertex(vertices.size(), closed)
	{
		copy(vertices);
	}
	
	void reset(bool closed = true) {
		m_edges.clear();
		init(closed);
	}

	void reset(const std::vector<Vec<dim, T>>& vertices, bool closed = true) {
		m_edges.clear();
		m_vertices = vertices;
		init(closed);
	}


	void copy(const std::vector<Vec<dim, T>>& vertices) {
		assert(m_vertices.size() == vertices.size());
		m_vertices = vertices;
	}

	void copy(const EdgeVertex<dim, T>& other) {
		assert(m_vertices.size() == other.vertices().size());
		m_vertices = other.vertices();
	}

	std::vector<Vec<dim, T>>& vertices() { return m_vertices; }
	std::vector<Edge<dim, T>>& edges() { return m_edges; }

	const std::vector<Vec<dim, T>>& vertices() const { return m_vertices; }
	const std::vector<Edge<dim, T>>& edges() const { return m_edges; }	 	  	 	     	   		   	      	 	    	 	

private:
	void init(bool closed = true) {
		size_t size = m_vertices.size();
		if (size == 0) { return; }
		m_edges.reserve(size);
		for (size_t i = 0; i < size - 1; ++i) {
			m_edges.emplace_back(Edge<dim, T>(m_vertices[i], m_vertices[i + 1]));
		}
		if (closed) {
			m_edges.emplace_back(Edge<dim, T>(m_vertices[size - 1], m_vertices[0]));
		}
	}

	std::vector<Vec<dim, T>> m_vertices;
	std::vector<Edge<dim, T>> m_edges;
};

using edge2i = Edge<2, int>;
using edge2f = Edge<2, double>;
using edge3i = Edge<3, int>;
using edge3f = Edge<3, double>;
using vpedge2 = VpEdge<2>;
using vpedge3 = VpEdge<3>;


#endif
	 	  	 	     	   		   	      	 	    	 	
