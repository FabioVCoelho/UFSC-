#ifndef FACE_H
#define FACE_H

#include "edge.h"
#include <vector>

template <size_t Dim, typename T>
class Face {
public:
	Face(const std::vector<Edge<Dim, T>*>& edges)
		: m_edges(edges) 
	{
		for (Edge<Dim, T>* e : edges) {
			m_edgesIdxs.emplace_back(e->idx());
		}
	}
	const std::vector<Edge<Dim, T>*>& edges() const { return m_edges; }
	std::vector<Edge<Dim, T>*>& edges() { return m_edges; }
	const std::vector<size_t>& edgesIdxs() const { return m_edgesIdxs; }

private:
	std::vector<Edge<Dim, T>*> m_edges;
	std::vector<size_t> m_edgesIdxs;
	
};

//template <size_t Dim, typename T>
//struct FaceEdgeVertex {
//
//	FaceEdgeVertex() {}
//
//	FaceEdgeVertex(size_t size) : m_vertices(std::vector<Vec<Dim, T>>(size)) {
//		//init();
//	}
//
//	FaceEdgeVertex(const FaceEdgeVertex<Dim, T>& other ) {
//		copy(other);
//	}	 	  	 	     	   		   	      	 	    	 	
//
//	void addVertex(const Vec<Dim, T>& vertex) { m_edgeVextex.addVertex(vertex); }
//
//	void makeEdge(size_t v1, size_t v2) {
//		m_edgeVextex.makeEdge(v1, v2);
//	}
//
//	void makeFace(std::vector<size_t> edge_ids) {
//		std::vector<Edge<dim, T>*> faceEdges;
//		faceEdges.reserve(edge_ids.size());
//		for (size_t id : edge_ids) {
//			faceEdges.emplace_back(&(m_edgeVextex.edges()[id]));
//		}
//		m_faces.emplace_back(face_edges);
//	}
//
//	/*explicit EdgeVertex(const std::vector<Vec<dim, T>>& vertices)
//		: EdgeVertex(vertices.size())
//	{
//		copy(vertices);
//	}*/
//
//	/*void reset() {
//		m_edges.clear();
//		init();
//	}
//
//	void reset(const std::vector<Vec<dim, T>>& vertices) {
//		m_edges.clear();
//		m_vertices = vertices;
//		init();
//	}*/
//
//
//	/*void copy(const std::vector<Vec<dim, T>>& vertices) {
//		assert(m_vertices.size() == vertices.size());
//		m_vertices = vertices;
//	}*/
//
//	/*void clear() {	 	  	 	     	   		   	      	 	    	 	
//		m_vertices.clear();
//		m_edges.clear();
//		m_faces.clear();
//	}*/
//
//	void copy(const FaceEdgeVertex<Dim, T>& other) {
//		//assert(m_vertices.size() == other.vertices().size());
//		//clear();
//		/*m_vertices = other.vertices();
//		m_edges.clear();
//		m_edges.reserve(other.edges().size());
//		size_t iv1, iv2;
//		for (const Edge& e : other.edges()) {
//			iv1 = e.iv1();
//			iv2 = e.iv2();
//			m_edges.emplace_back(e.idx(), m_vertices[iv1], iv1, m_vertices[iv1], iv2);
//		}*/
//		m_edgeVextex.copy(other.ev());
//
//		m_faces = other.faces();
//		for (const Face& f : m_faces) {
//			for (Edge* e : f.edges()) {
//				*e = &(m_edges[e->idx()]);
//			}
//		}
//	}
//
//	std::vector<Vec<Dim, T>>& vertices() { return m_edgeVextex.vertices(); }
//	const std::vector<Vec<Dim, T>>& vertices() const { return m_edgeVextex.vertices(); }
//
//	std::vector<Edge<Dim, T>>& edges() { return m_edgeVextex.edges(); }
//	const std::vector<Edge<Dim, T>>& edges() const { return m_edgeVextex.edges(); }
//
//	EdgeVertex<Dim, T>& ev() { return m_edgeVextex; }
//	const EdgeVertex<Dim, T>& ev() const { return m_edgeVextex; }
//
//	std::vector<Face<Dim, T>>& faces{ return m_faces; }	 	  	 	     	   		   	      	 	    	 	
//	const std::vector<Face<Dim, T>>& faces() const { return m_faces; }
//
//
//private:
//	/*void init() {
//		size_t size = m_vertices.size();
//		if (size == 0) { return; }
//		m_edges.reserve(size);
//		for (size_t i = 0; i < size - 1; ++i) {
//			m_edges.emplace_back(Edge<dim, T>(m_vertices[i], m_vertices[i + 1]));
//		}
//	}*/
//	std::vector<Face<Dim, T>> m_faces;
//	EdgeVertex<Dim, T> m_edgeVextex;
//	/*std::vector<Edge<dim, T>> m_edges;
//	std::vector<Vec<dim, T>> m_vertices;*/
//};

using face3i = Face<3, int>;
using face3f = Face<3, double>;

//using edge2i = Edge<2, int>;
//using edge2f = Edge<2, double>;
//using edge3i = Edge<3, int>;
//using edge3f = Edge<3, double>;
//using vpedge2 = VpEdge<2>;
//using vpedge3 = VpEdge<3>;

#endif
	 	  	 	     	   		   	      	 	    	 	
