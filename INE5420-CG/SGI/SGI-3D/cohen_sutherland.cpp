#include "cohen_sutherland.h"


void CohenSutherland::clip(const window_edges2_t& edges, shape2_t& clippedShape) {
	/*window_vertices2_t& clippedPoints = clippedObject.vertices();
	window_edges2_t& clippedEdges = clippedObject.edges();*/
	/*clippedPoints.reserve(2 * edges.size());
	clippedPoints.clear();
	clippedEdges.clear();*/
	clippedShape.clear();
	clippedShape.reserve(2 * edges.size());
	ch = 0;
	size_t numEdges = edges.size();
	window_unit xc1, xc2, yc1, yc2;
	//size_t edge_id = 0, v1_id = 0, v2_id = 1;

	for (size_t i = 0; i < numEdges; ++i) {
		const window_vertex2_t& p1 = edges[i].v1();
		const window_vertex2_t& p2 = edges[i].v2();

		b0 = (p1[0] < -1.0);
		b1 = (p1[0] > 1.0);
		b2 = (p1[1] < -1.0);
		b3 = (p1[1] > 1.0);
		b4 = (p2[0] < -1.0);
		b5 = (p2[0] > 1.0);
		b6 = (p2[1] < -1.0);
		b7 = (p2[1] > 1.0);

		if (ch >> 4 & (ch & 0x0F)) {
			continue;
		}

		if (p2[0] == p1[0]) {
			if (p2[0] < -1 || p2[0] > 1) {
				continue;
			}	 	  	 	     	   		   	      	 	    	 	
			xc1 = p2[0];
			xc2 = p2[0];
			yc1 = (p1[1] < -1 ? -1 : (p1[1] > 1 ? 1 : p1[1]));
			yc2 = (p2[1] < -1 ? -1 : (p2[1] > 1 ? 1 : p2[1]));
			/*clippedPoints.emplace_back(window_vertex2_t(xc1, yc1));
			clippedPoints.emplace_back(window_vertex2_t(xc2, yc2));*/
			clippedShape.addVertex(window_vertex2_t(xc1, yc1));
			clippedShape.addVertex(window_vertex2_t(xc2, yc2));
			continue;
		}


		double m = (p2[1] - p1[1]) / (p2[0] - p1[0]);

		if ((ch & 0x0F) == 0) {
			//clippedPoints.emplace_back(window_vertex2_t(p1));
			clippedShape.addVertex(window_vertex2_t(p1));
		}
		else {
			xc1 = (b3 == b2) ? (b1 - b0) : (((b3 - b2) - p1[1]) / m + p1[0]);
			yc1 = (b1 == b0) ? (b3 - b2) : (m*((b1 - b0) - p1[0]) + p1[1]);
			if ((xc1 > 1 || xc1 < -1) && (yc1 > 1 || yc1 < -1)) {
				continue;
			}
			xc1 = (xc1 < -1 ? -1 : (xc1 > 1 ? 1 : xc1));
			yc1 = (yc1 < -1 ? -1 : (yc1 > 1 ? 1 : yc1));

			//clippedPoints.emplace_back(window_vertex2_t(xc1, yc1));
			clippedShape.addVertex(window_vertex2_t(xc1, yc1));

		}

		if ((ch & 0xF0) == 0) {
			//clippedPoints.emplace_back(window_vertex2_t(p2));
			clippedShape.addVertex(window_vertex2_t(xc1, yc1));
		}	 	  	 	     	   		   	      	 	    	 	
		else {
			xc2 = (b7 == b6) ? (b5 - b4) : (((b7 - b6) - p2[1]) / m + p2[0]);
			yc2 = (b5 == b4) ? (b7 - b6) : (m*((b5 - b4) - p2[0]) + p2[1]);
			xc2 = (xc2 < -1 ? -1 : (xc2 > 1 ? 1 : xc2));
			yc2 = (yc2 < -1 ? -1 : (yc2 > 1 ? 1 : yc2));
			//clippedPoints.emplace_back(window_vertex2_t(xc2, yc2));
			clippedShape.addVertex(window_vertex2_t(xc2, yc2));


		}
		/*clippedEdges.emplace_back(
		window_edge_t(edge_id, *(clippedPoints.crbegin() + 1), v1_id, *clippedPoints.crbegin(), v2_id)
		);*/
		size_t size = clippedShape.vertices().size();
		clippedShape.makeEdge(size - 2, size - 1);
		/*++edge_id;
		++v1_id;
		++v2_id;*/
	}

	return;
}

void CohenSutherland::clip(const window_edges3_t& edges, shape2_t& clippedShape) {
	/*window_vertices2_t& clippedPoints = clippedObject.vertices();
	window_edges2_t& clippedEdges = clippedObject.edges();*/
	/*clippedPoints.reserve(2 * edges.size());
	clippedPoints.clear();
	clippedEdges.clear();*/
	clippedShape.clear();
	clippedShape.reserve(2 * edges.size());
	ch = 0;
	size_t numEdges = edges.size();
	window_unit xc1, xc2, yc1, yc2;
	//size_t edge_id = 0, v1_id = 0, v2_id = 1;
	bool addp1 = true;
	for (size_t i = 0; i < numEdges; ++i) {	 	  	 	     	   		   	      	 	    	 	
		const window_vertex2_t& p1 = edges[i].v1();
		const window_vertex2_t& p2 = edges[i].v2();

		b0 = (p1[0] < -1.0);
		b1 = (p1[0] > 1.0);
		b2 = (p1[1] < -1.0);
		b3 = (p1[1] > 1.0);
		b4 = (p2[0] < -1.0);
		b5 = (p2[0] > 1.0);
		b6 = (p2[1] < -1.0);
		b7 = (p2[1] > 1.0);

		if (ch >> 4 & (ch & 0x0F)) {
			continue;
		}

		//if (p2[0] == p1[0]) {
		//	if (p2[0] < -1 || p2[0] > 1) {
		//		continue;
		//	}
		//	xc1 = p2[0];
		//	xc2 = p2[0];
		//	yc1 = (p1[1] < -1 ? -1 : (p1[1] > 1 ? 1 : p1[1]));
		//	yc2 = (p2[1] < -1 ? -1 : (p2[1] > 1 ? 1 : p2[1]));
		//	/*clippedPoints.emplace_back(window_vertex2_t(xc1, yc1));
		//	clippedPoints.emplace_back(window_vertex2_t(xc2, yc2));*/
		//	clippedShape.addVertex(window_vertex2_t(xc1, yc1));
		//	if (!aux) {
		//		clippedShape.addVertex(window_vertex2_t(xc2, yc2));
		//	}
		//	size_t size = clippedShape.vertices().size();
		//	clippedShape.makeEdge(size - 2, size - 1);
		//	aux = true;
		//	continue;
		//}
		//else {	 	  	 	     	   		   	      	 	    	 	
		//	aux = false;
		//}

		double m;

		if (p2[0] == p1[0]) {
			m = std::numeric_limits<double>::max();
		}
		else {
			m = (p2[1] - p1[1]) / (p2[0] - p1[0]);
		}

		//if (p2[0] == p1[0]) {
		//	if (p2[0] < -1 || p2[0] > 1) {
		//		continue;
		//	}
		//	xc1 = p2[0];
		//	xc2 = p2[0];
		//	yc1 = (p1[1] < -1 ? -1 : (p1[1] > 1 ? 1 : p1[1]));
		//	yc2 = (p2[1] < -1 ? -1 : (p2[1] > 1 ? 1 : p2[1]));
		//	/*clippedPoints.emplace_back(window_vertex2_t(xc1, yc1));
		//	clippedPoints.emplace_back(window_vertex2_t(xc2, yc2));*/
		//	clippedShape.addVertex(window_vertex2_t(xc1, yc1));
		//	if (!aux) {
		//		clippedShape.addVertex(window_vertex2_t(xc2, yc2));
		//	}
		//	size_t size = clippedShape.vertices().size();
		//	clippedShape.makeEdge(size - 2, size - 1);
		//	aux = true;
		//	continue;
		//}
		//else {
		//	aux = false;
		//}
		

		//double m = (p2[1] - p1[1]) / (p2[0] - p1[0]);

		if ((ch & 0x0F) == 0) {	 	  	 	     	   		   	      	 	    	 	
			//clippedPoints.emplace_back(window_vertex2_t(p1));
			//if (addp1) {
				clippedShape.addVertex(window_vertex2_t(p1));
			//}
		}
		else {
			xc1 = (b3 == b2) ? (b1 - b0) : (((b3 - b2) - p1[1]) / m + p1[0]);
			yc1 = (b1 == b0) ? (b3 - b2) : (m*((b1 - b0) - p1[0]) + p1[1]);
			if ((xc1 > 1 || xc1 < -1) && (yc1 > 1 || yc1 < -1)) {
				continue;
			}
			xc1 = (xc1 < -1 ? -1 : (xc1 > 1 ? 1 : xc1));
			yc1 = (yc1 < -1 ? -1 : (yc1 > 1 ? 1 : yc1));

			//clippedPoints.emplace_back(window_vertex2_t(xc1, yc1));
			clippedShape.addVertex(window_vertex2_t(xc1, yc1));

		}

		if ((ch & 0xF0) == 0) {
			//clippedPoints.emplace_back(window_vertex2_t(p2));
			addp1 = false;
			clippedShape.addVertex(window_vertex2_t(p2));
		}
		else {
			addp1 = true;
			xc2 = (b7 == b6) ? (b5 - b4) : (((b7 - b6) - p2[1]) / m + p2[0]);
			yc2 = (b5 == b4) ? (b7 - b6) : (m*((b5 - b4) - p2[0]) + p2[1]);
			xc2 = (xc2 < -1 ? -1 : (xc2 > 1 ? 1 : xc2));
			yc2 = (yc2 < -1 ? -1 : (yc2 > 1 ? 1 : yc2));
			//clippedPoints.emplace_back(window_vertex2_t(xc2, yc2));
			clippedShape.addVertex(window_vertex2_t(xc2, yc2));
		}
		/*clippedEdges.emplace_back(
			window_edge_t(edge_id, *(clippedPoints.crbegin() + 1), v1_id, *clippedPoints.crbegin(), v2_id)
		);*/
		size_t size = clippedShape.vertices().size();
		clippedShape.makeEdge(size - 2, size - 1);
		/*++edge_id;
		++v1_id;
		++v2_id;*/
	}	 	  	 	     	   		   	      	 	    	 	

	return;
}