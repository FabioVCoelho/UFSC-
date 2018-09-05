#include "obj_reader.h"
#include "shape.h"
#include "curva2.h"
#include "line.h"
#include "wireframe.h"
#include "polygon.h"
#include "color.h"
#include <sstream>
#include <memory>
#include <vector>
#include <map>

std::map<std::string, Color> mats;

ObjReader::~ObjReader() {
	if (m_fs.is_open()) {
		m_fs.close();
	}
}

WinDims<unit> parseWindow(std::istringstream& ss, const vertices3_t& vertices) {
	size_t i1, i2;
	ss >> i1 >> i2;
	vertex3_t center = vertices[i1-1];
	vertex3_t dims = vertices[i2-1];
	vertex3_t min = { center[0] - dims[0] / 2, center[1] - dims[1] / 2, center[2] - dims[2] / 2 };

	return WinDims<unit>(min[0], min[1], dims[0], dims[1]);
}

vertex3_t parseVertex(std::istringstream& ss) {
	unit x, y, z;
	ss >> x >> y >> z;
	return vertex3_t(x, y, z);
}

object3_ptr_t parseCurve(std::istringstream& ss, const vertices3_t& vertices, Color color) {	 	  	 	     	   		   	      	 	    	 	
	std::vector<size_t> indexes;
	size_t i;
	while (ss >> i) {
		indexes.push_back(i);
	}
	if (indexes.size() != 4) { throw; }
	curva2<3> curve(vertices[indexes[0] - 1], vertices[indexes[1] - 1], vertices[indexes[2] - 1], vertices[indexes[3] - 1], color);
	return curve.clone();
}

object3_ptr_t parseObject(std::fstream& fs, std::istringstream& ss, const vertices3_t& vertices, Color color, bool fill, bool closed) {
	//std::vector<size_t> vertexindexes;
	//shape3_t shape(vertexindexes.size());
	size_t i;
	shape3_t shape;
	while (ss >> i) {
		shape.addVertex(vertices[i - 1]);
		//vertexindexes.push_back(i);
	}
	std::string line;
	std::getline(fs, line);
	std::stringstream ssEdges(line);
	//ss.str(line);
	//ss.seekg(0, ss.beg);
	char e;
	ssEdges >> e;
	char comma;
	size_t v1, v2;
	while (ssEdges >> v1) {
		ssEdges >> comma;
		ssEdges >> v2;
		shape.makeEdge(v1 - 1, v2 - 1);
	}
	std::getline(fs, line);
	std::stringstream ssFaces(line);
	//ss.str(line);
	char f;
	ssFaces >> f;
	std::string edges;
	while (ssFaces >> edges) {	 	  	 	     	   		   	      	 	    	 	
		std::stringstream ss2(edges);
		size_t edgeIdx;
		std::vector<size_t> edgeIdxVec;
		while (ss2 >> edgeIdx) {
			edgeIdxVec.push_back(edgeIdx - 1);
			ss2 >> comma;
		}
		shape.makeFace(edgeIdxVec);	
	}


	/*for (size_t i : vertexindexes) {
		shape.addVertex(vertices[i]);
	}*/

	//std::string line;
	//std::getline(fs, line);
	//
	

	if (shape.vertices().size() == 2) {
		Line<3> line(shape.vertices()[0], shape.vertices()[1], color);
		return line.clone();

	}
	else {
		/*vertices3_t points;
		points.reserve(vertexindexes.size());
		for (size_t i : vertexindexes) {
			points.emplace_back(vertices[i-1]);
		}*/
		if (fill) {
			Polygon<3> polygon(shape, color);
			return polygon.clone();
		}
		else {	 	  	 	     	   		   	      	 	    	 	
			Wireframe<3> wireframe(shape, color);
			return wireframe.clone();
		}
	}
	
}

void parseObject(
		std::fstream& fs, 
		std::istringstream& ss, 
		Control& control,
		const vertices3_t& vertices
) 
{
	std::string objname, line;
	ss >> objname;
	bool fill = false;
	bool closed = true;
	bool curve = false;
	Color color;
	while (std::getline(fs, line)) {
		std::istringstream ss2(line);
		char ch = '0';
		ss2 >> ch;
		switch (ch) {
		case 'c': {
			ss2.putback(ch);
			std::string s;
			ss2 >> s;
			if (s == "closed") {
				std::string onoff;
				ss2 >> onoff;
				closed = onoff == "on" ? true : false;
				break;
			}
			if (s == "c") {	 	  	 	     	   		   	      	 	    	 	
				ss2 >> objname;
				curve = true;
			}
			break;
		}
		case 'f': {
			ss2.putback(ch);
			std::string s;
			ss2 >> s;
			if (s == "fill") {
				std::string onoff;
				ss2 >> onoff;
				fill = onoff == "on" ? true : false;
			}
			break;
		}
		case 'u': {
			ss2.putback(ch);
			std::string s;
			ss2 >> s;
			if (s == "usemtl") {
				std::string colorname;
				ss2 >> colorname;
				color = mats[colorname];
			}
				break;
		}
		case 'l':
			if (curve) {
				control.addObjectInit(objname, *parseCurve(ss2, vertices, color));
			}
			else {
				control.addObjectInit(objname, *parseObject(fs, ss2, vertices, color, fill, closed));
			}
			curve = false;
			break;
		case 'w':
			control.initWindow(parseWindow(ss2, vertices));
			break;
		case 'o': 
			ss2 >> objname;
			//parseObject(fs, ss2, control, vertices);
			break;
		default : 
			break;
		}	 	  	 	     	   		   	      	 	    	 	
	}
}

void ObjReader::read(std::string objfilename, std::string mtlfilename, Control& control) {
	m_fs.open(mtlfilename, std::ios::in);
	if (m_fs) {
		std::string line;
		while (std::getline(m_fs, line)) {
			std::istringstream ss(line);
			std::string s;
			ss >> s;
			if (s == "newmtl") {
				std::string colorname;
				ss >> colorname;
				std::getline(m_fs, line);
				std::istringstream ss2(line);
				std::string kd;
				ss2 >> kd;
				if (kd == "Kd") {
					double r, g, b;
					ss2 >> r >> g >> b;
					mats[colorname] = Color(r, g, b);
				}

			}
		}
	}
	if (m_fs.is_open()) {
		m_fs.close();
	}
	
	m_fs.open(objfilename, std::ios::in);
	if (!m_fs) {
		return;
	}

	vertices3_t vertices;
	std::vector<object_t<3>> Objects;
	std::string line;
	

	while (std::getline(m_fs, line)) {	 	  	 	     	   		   	      	 	    	 	
		std::istringstream ss(line);
		char ch;
		ss >> ch;
		switch (ch) {
		case 'v' : 
			vertices.push_back(parseVertex(ss));
			break;
		case 'o':
			parseObject(m_fs, ss, control, vertices);
			break;
		default:
			break;
		}
	}
}