#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "dimensions.h"
#include "types.h"

struct Viewport {
	Viewport() {}
	Viewport(const WinDims<int>& size)
        : m_size(size) {}

    void resize(const WinDims<int>& size) {
        m_size = size;
    }
    const WinDims<int>& size() {return m_size;}

private:
    WinDims<int> m_size;
};

//struct ViewportObject {
//
//	ViewportObject(size_t maxpoints, size_t maxedges)
//		: m_vpPoints(maxpoints), m_numPoints(0), m_numEdges(0)
//	{
//		m_vpEdges.reserve(maxedges);
//		for (size_t i = 0; i < maxedges; ++i) {
//			m_vpEdges.push_back(vp_edge_t(m_vpPoints[0], m_vpPoints[0]));
//		}
//	}
//
//	vp_vertices2_t m_vpPoints;
//	vp_edges_t m_vpEdges;
//	size_t m_numPoints;
//	size_t m_numEdges;
//};

#endif	 	  	 	     	   		   	      	 	    	 	
