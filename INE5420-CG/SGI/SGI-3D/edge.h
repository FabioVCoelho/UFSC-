#ifndef EDGE_H
#define EDGE_H

#include "vec2.h"
#include "vec3.h"
#include <vector>

template <size_t dim, typename T>
class Edge {
public:
	Edge(size_t idx, const Vec<dim, T>& v1, size_t iv1, const Vec<dim, T>& v2, size_t iv2)
		: m_idx(idx), m_v1(&v1), m_v2(&v2), m_iv1(iv1), m_iv2(iv2) {}
	Edge(const Edge<dim, T>& other) 
		:m_idx(other.idx()), m_v1(&(other.v1())), m_v2(&(other.v2())), m_iv1(other.iv1()), m_iv2(other.iv2()) {}
	const Vec<dim, T>& v1() const { return *m_v1; }
	const Vec<dim, T>& v2() const { return *m_v2; }
	size_t iv1() const { return m_iv1; }
	size_t iv2() const { return m_iv2; }
	size_t idx() const { return m_idx; }

private:
	const Vec<dim, T>* m_v1;
	const Vec<dim, T>* m_v2;
	size_t m_iv1;
	size_t m_iv2;
	size_t m_idx;
};

//template <size_t dim>
//class VpEdge {
//public:
//	VpEdge(const Vec<dim, int>& v1, const Vec<dim, int>& v2)
//		: m_v1(v1), m_v2(v2) {}
//	const Vec<dim, int>& v1() const { return m_v1; }
//	const Vec<dim, int>& v2() const { return m_v2; }
//
//private:
//	Vec<dim, int> m_v1, m_v2;
//};



using edge2i = Edge<2, int>;
using edge2f = Edge<2, double>;
using edge3i = Edge<3, int>;
using edge3f = Edge<3, double>;
//using vpedge2 = VpEdge<2>;
//using vpedge3 = VpEdge<3>;


#endif
	 	  	 	     	   		   	      	 	    	 	
