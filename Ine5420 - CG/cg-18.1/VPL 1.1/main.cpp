#include <gtk/gtk.h>
#include "ui.h"
#include "cg_system.h"
#include "model.h"
#include "line.h"
#include "point.h"

void initShapes(Model& model) {
	Line line1(Point(100, 100), Point(200, 100));
	Line line2(Point(200, 100), Point(300, 350));
	Line line3(Point(300, 350), Point(200, 500));
	Line line4(Point(200, 500), Point(50, 300));
	Line line5(Point(50, 300), Point(100, 100));
	model.addShape(line1);
	model.addShape(line2);
	model.addShape(line3);
	model.addShape(line4);
	model.addShape(line5);

	Line line6(Point(-500, -500), Point(-600, -500));
	Line line7(Point(-600, -500), Point(-600, -600));
	Line line8(Point(-600, -600), Point(-500, -600));
	Line line9(Point(-500, -600), Point(-500, -500));
	model.addShape(line6);
	model.addShape(line7);
	model.addShape(line8);
	model.addShape(line9);
}

int main(int argc, char *argv[]) {
	
	Model m(Dims2d<int>(-2000, 2000, -1500, 1500));
	initShapes(m);
	CGSys cg(m);
	cg.resizeWindow(Dims2d<int>(0, 800, 0, 600));
	
	UI ui(m, cg);

	ui.uiInit();

	return 0;
}