#ifndef COHEN_SUTHERLAND_H
#define COHEN_SUTHERLAND_H

#include "types.h"
#include "clipping.h"

class CohenSutherland : public WireframeClipper {

public:
	void clip(const window_edges2_t& edges, shape2_t& clippedShape);
	void clip(const window_edges3_t& edges, shape2_t& clippedShape);

private:
	union {
		struct {
			unsigned char b0 : 1;
			unsigned char b1 : 1;
			unsigned char b2 : 1;
			unsigned char b3 : 1;
			unsigned char b4 : 1;
			unsigned char b5 : 1;
			unsigned char b6 : 1;
			unsigned char b7 : 1;
		};
		unsigned char ch;
	};
};

#endif
	 	  	 	     	   		   	      	 	    	 	
