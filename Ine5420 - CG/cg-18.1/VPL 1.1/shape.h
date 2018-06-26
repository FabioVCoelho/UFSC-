#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include <vector>

using point_t = std::pair<int, int>;
using points_t = std::vector<point_t>;

class Shape {
public:
	using shape_ptr = std::unique_ptr<Shape>;

    virtual ~Shape() = 0;
	virtual shape_ptr clone() const = 0;
	virtual points_t points() const = 0;
    virtual void moveX(int dx) = 0;
    virtual void moveY(int dy) = 0;
    virtual void move(int dx, int dy) = 0;
    virtual void morph(const points_t& points) = 0;
    
protected:
    Shape();
};

#endif