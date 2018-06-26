#include "obj_reader.h"
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

WinDims<unit> parseWindow(std::istringstream& ss, const points_t& vertices) {
	size_t i1, i2;
	ss >> i1 >> i2;
	point_t center = vertices[i1-1];
	point_t dims = vertices[i2-1];
	point_t min = { center[0] - dims[0] / 2, center[1] - dims[1] / 2 };

	return WinDims<unit>(min[0], min[1], dims[0], dims[1]);
}

point_t parseVertex(std::istringstream& ss) {
	unit x, y;
	ss >> x >> y;
	return point_t(x, y);
}

shape_ptr_t parseShape(std::istringstream& ss, const points_t& vertices, Color color, bool fill) {
	std::vector<size_t> indexes;
	size_t i;
	while (ss >> i) {
		indexes.push_back(i);
	}
	if (indexes.size() == 2) {
		Line line(vertices[indexes[0]-1], vertices[indexes[1]-1], color);
		return line.clone();

	}
	else {
		points_t points;
		for (size_t i : indexes) {
			points.push_back(vertices[i-1]);
		}
		if (fill) {
			Polygon polygon(points, color);
			return polygon.clone();
		}
		else {
			Wireframe wireframe(points, color);
			return wireframe.clone();
		}
	}
	
}

void parseObject(
		std::fstream& fs, 
		std::istringstream& ss, 
		Control& control,
		const points_t& vertices
) 
{
	std::string objname, line;
	ss >> objname;
	bool fill = false;
	Color color;
	while (std::getline(fs, line)) {
		std::istringstream ss2(line);
		char ch = '0';
		ss2 >> ch;
		switch (ch) {
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
			control.addShapeInit(objname, *parseShape(ss2, vertices, color, fill));
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

	points_t vertices;
	std::vector<shape_ptr_t> shapes;
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