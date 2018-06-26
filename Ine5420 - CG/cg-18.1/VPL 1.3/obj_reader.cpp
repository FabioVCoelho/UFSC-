#include "obj_reader.h"
#include "line.h"
#include "polygon.h"
#include <sstream>
#include <memory>
#include <vector>

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

Shape::shape_ptr_t parseShape(std::istringstream& ss, const points_t& vertices) {
	std::vector<size_t> indexes;
	size_t i;
	while (ss >> i) {
		indexes.push_back(i);
	}
	if (indexes.size() == 2) {
		Line line(vertices[indexes[0]-1], vertices[indexes[1]-1]);
		return line.clone();

	}
	else {
		points_t points;
		for (size_t i : indexes) {
			points.push_back(vertices[i-1]);
		}
		Polygon polygon(points);
		return polygon.clone();
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
	while (std::getline(fs, line)) {
		std::istringstream ss2(line);
		char ch;
		ss2 >> ch;
		switch (ch) {
		case 'p':
			break;
		case 'l':
			control.addShape(objname, *parseShape(ss2, vertices));
			break;
		case 'w':
			control.resizeWindow(parseWindow(ss2, vertices));
			break;
		case 'o':
			parseObject(fs, ss2, control, vertices);
			break;
		default : 
			break;
		}
	}
}

void ObjReader::read(std::string filename, Control& control) {
    m_fs.open(filename, std::ios::in);
	if (!m_fs) {
		return;
	}

	points_t vertices;
	std::vector<Shape::shape_ptr_t> shapes;
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