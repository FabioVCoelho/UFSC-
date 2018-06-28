#ifndef WEILER_ATHERTON_H
#define WEILER_ATHERTON_H

#include "types.h"
#include "clipping.h"
#include <set>
#include <list>

class WeilerAtherton : public PolygonClipper {
public:

	struct WAVertex;

	using wpset = std::multiset<WAVertex*, bool(*)(const WAVertex * const &, const WAVertex * const &)>;
	using pplist = std::list<WAVertex*>;

	struct WAVertex {
		WAVertex(const window_vertex2_t& p)
			: m_point(p), m_visited(false), m_next(nullptr) {}

		WAVertex(const window_vertex2_t& p, const pplist::iterator& it)
			: m_point(p), m_visited(false), m_next(nullptr), m_nextinpolylist(it) {}

		const window_vertex2_t& point() const { return m_point; }
		void visit() { m_visited = true; }
		bool& visited() { return m_visited; }
		WAVertex*& next() { return m_next; }
		pplist::iterator& nextinpolylist() { return m_nextinpolylist; }

	private:
		window_vertex2_t m_point;
		WAVertex* m_next;
		bool m_visited;
		pplist::iterator m_nextinpolylist;
	};

	void clip(const shape2_t& shape, shape2_t& clippedShape);

};


#endif;	 	  	 	     	   		   	      	 	    	 	
