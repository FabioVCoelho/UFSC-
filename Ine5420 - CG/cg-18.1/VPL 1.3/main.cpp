#include <gtk/gtk.h>
#include "ui.h"
#include "cg_system.h"
#include "control.h"
#include "model.h"
#include "line.h"
#include "point.h"
#include "obj_reader.h"

#ifdef NVPL
#define OBJ_PATH "..\\..\\"
#else
#define OBJ_PATH 
#endif

//void initShapes(Model& model) {
//	Line line1(point_t{ 100, 100 }, point_t{ 200, 100 });
//	Line line2(point_t{ 200, 100 }, point_t{ 300, 350 });
//	Line line3(point_t{ 300, 350 }, point_t{ 200, 500 });
//	Line line4(point_t{ 200, 500 }, point_t{ 50 , 300 });
//	Line line5(point_t{ 50 , 300 }, point_t{ 100, 100 });
//	model.addShape(line1);
//	model.addShape(line2);
//	model.addShape(line3);
//	model.addShape(line4);
//	model.addShape(line5);
//
//	Line line6(point_t{ -500, -500 }, point_t{ -600, -500 });
//	Line line7(point_t{ -600, -500 }, point_t{ -600, -600 });
//	Line line8(point_t{ -600, -600 }, point_t{ -500, -600 });
//	Line line9(point_t{ -500, -600 }, point_t{ -500, -500 });
//	model.addShape(line6);
//	model.addShape(line7);
//	model.addShape(line8);
//	model.addShape(line9);
//}

int main(int argc, char *argv[]) {
	
	Model m(WinDims<unit>(-4000, -3000, 8000, 6000));
	//initShapes(m);
	CGSys cg(m);
	Control ctrl(m, cg);
	ObjReader reader;
	reader.read(OBJ_PATH"estrela.obj", ctrl);

	//cg.resizeWindow(WinDims<int>(-650, -650, 200, 200));
	
	UI ui(ctrl);

	ui.uiInit();

	return 0;
}