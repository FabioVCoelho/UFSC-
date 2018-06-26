#include "Bspline.h"
#include "vec.h"
#include "types.h"
#include <math.h>
#include <string>
#include "transforms.h"
#include <cassert>
#include <cmath>
#include <cstdio>

const double DELTAE = 0.01;

points_t Bspline::bSpline(points_t controlPoints)    {
    double d1 = DELTAE;
    double d2 = d1*d1;
    double d3 = d2*d1;
    points_t allPoints;
    
    for(int k = 0; k < controlPoints.size() - 3; k++)   {
        Vec4f Gx = {controlPoints.at(k).m_x,controlPoints.at(k+1).m_x,
        controlPoints.at(k+2).m_x,controlPoints.at(k+3).m_x};
        Vec4f Gy = {controlPoints.at(k).m_y,controlPoints.at(k+1).m_y,
        controlPoints.at(k+2).m_y,controlPoints.at(k+3).m_y};

    //    Vec4f Gx = {1,2,3,4};
    //    Vec4f Gy = {1,2,2,1};

        //Divisão dentro do indice não funcionou =/
        std::vector<Vec4f> mbs;
        mbs.push_back(Vec4f{-0.16666666667,0.5,-0.5,(0.16666666667)});
        mbs.push_back(Vec4f{0.5,-1,0.5,0});
        mbs.push_back(Vec4f{-0.5,0,0.5,0});
        mbs.push_back(Vec4f{(0.16666666667),(0.66666666666667),(0.16666666667),0});

        std::vector<Vec4f> E;
        E.push_back(Vec4f{0,0,0,1});
        E.push_back(Vec4f{d3,d2,d1,0});
        E.push_back(Vec4f{6*d3,2*d2,0,0});
        E.push_back(Vec4f{6*d3,0,0,0});

        Vec4f Cx = {0,0,0,0};
        Vec4f Cy = {0,0,0,0};
        Vec4f MatrixDeltaX = {0,0,0,0};
        Vec4f MatrixDeltaY = {0,0,0,0};

        for (int j = 0; j < 4; j++){
            for (int i = 0; i < 4; i++) {
                Cx[j] += mbs.at(j)[i] * Gx[i];
                Cy[j] += mbs.at(j)[i] * Gy[i];
            }       
    //        printf("Cx[%d] = %f \n",j, Cx[j]);
    //        printf("Cy[%d] = %f \n",j, Cy[j]);
    //        fflush( stdout );
        }

        for (int j = 0; j < 4; j++){
            for (int i = 0; i < 4; i++) {
                MatrixDeltaX[j] += E.at(j)[i]*Cx[i];
                MatrixDeltaY[j] += E.at(j)[i]*Cy[i];
            }
    //        printf("MatrixDeltaX[%d] = %f \n",j, MatrixDeltaX[j]);
    //        printf("MatrixDeltaY[%d] = %f \n",j, MatrixDeltaY[j]);
    //        fflush( stdout );
        }
        
        points_t linePoints = forwardDiff(1/d1,MatrixDeltaX[0],MatrixDeltaX[1],MatrixDeltaX[2],MatrixDeltaX[3],
                                             MatrixDeltaY[0],MatrixDeltaY[1],MatrixDeltaY[2],MatrixDeltaY[3]);
        
        for (int i = 0; i < linePoints.size(); i++) {
            allPoints.push_back(linePoints.at(i));
        }

    }
    return allPoints;
}

points_t Bspline::forwardDiff(float n, double x, double x1, double x2, double x3
                        , double y, double y1, double y2, double y3)  {
    int i = 1;
    double xvelho,yvelho;
    points_t pointsToUse;
    xvelho = x;
    yvelho = y;
    while(i <= n)    {
//        printf("Valor de i: %d \n",i);
        i = i+1;
        x = x + x1; x1 = x1 + x2; x2 = x2 + x3;
        y = y + y1; y1 = y1 + y2; y2 = y2 + y3;
        xvelho = x; yvelho = y;
        pointsToUse.push_back(Vec2f(x,y));
//        printf("Valor de x: %f, Valor de y:%f \n",x,y);
//        printf("Valor de x1: %f, Valor de y1:%f \n",x1,y1);
//        printf("Valor de x2: %f, Valor de y2:%f \n",x2,y2);
    }
    calcCenter(pointsToUse);
    return pointsToUse;
}

void Bspline::calcCenter(points_t pointsToUse) {
	unit xavg = 0;
	unit yavg = 0;

        xavg = (pointsToUse[0].m_x + pointsToUse[pointsToUse.size()].m_x)/2;
        yavg = (pointsToUse[0].m_y + pointsToUse[pointsToUse.size()].m_y)/2;
	
        m_center = { xavg, yavg };
}

Bspline::Bspline(points_t controlPoints)
	: Shape::Shape(bSpline(controlPoints), ShapeTraits(Color(), false, false))
{}

Bspline::Bspline(points_t controlPoints, const Color& color)
	: Shape::Shape(bSpline(controlPoints), ShapeTraits(color, false, false))
{}

Bspline::Bspline(points_t controlPoints, const ShapeTraits& traits)
	: Shape::Shape(bSpline(controlPoints), traits)
{}

shape_ptr_t Bspline::clone() const {
	std::shared_ptr<Bspline> p(new Bspline(*this));
	p->reset(m_points.vertices());
	return p;
}

void Bspline::shift(const matrix3f& shift, const matrix3f& toWindow) {
	shift >> m_points.vertices();
	shift >> m_center;
	worldToWindow(toWindow);
}

void Bspline::scale(const matrix3f& scale, const matrix3f& toWindow) {
	scale >> m_points.vertices();
	worldToWindow(toWindow);
        calcCenter(m_points.vertices());
}

void Bspline::rotate(const matrix3f& rotation, const matrix3f& toWindow) {
	rotation >> m_points.vertices();
	rotation >> m_center;
	worldToWindow(toWindow);
}

void Bspline::worldToWindow(const matrix3f& transf) {
	mult(m_windowPoints.vertices(), transf, m_points.vertices());
	mult(m_windowCenter, transf, m_center);
}

void Bspline::windowToWorld(const matrix3f& transf) {
	mult(m_points.vertices(), transf, m_windowPoints.vertices());
	mult(m_center, transf, m_windowCenter);
}

void Bspline::clip(const Clipper& clipper, edgevertex2f_t& clippedShape) {
	clipper.clipPoint(m_windowPoints.vertices(), clippedShape.vertices());
	clippedShape.reset(false);
}
