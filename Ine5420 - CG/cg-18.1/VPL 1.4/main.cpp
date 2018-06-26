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

int main(int argc, char *argv[]) {
	
	Model m(WinDims<unit>(-4000, -3000, 8000, 6000));
	//initShapes(m);
	CGSys cg(m);
	Control ctrl(m, cg);
	ObjReader reader;
	reader.read(OBJ_PATH"objects.obj", OBJ_PATH"mats.mtl", ctrl);

	//cg.resizeWindow(WinDims<int>(-650, -650, 200, 200));
	
	UI ui(ctrl);

	ui.uiInit();

	return 0;
}