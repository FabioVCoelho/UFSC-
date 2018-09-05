#include "ui.h"
#include "point.h"
#include "line.h"
#include "wireframe.h"
#include "curva2.h"
#include <string>
#include <sstream>

#include <memory>
#include <cassert>

Control* ctrl_ptr;

#ifdef _MSC_VER
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#ifdef NVPL
#define GLADE_PATH "res\\"
#else
#define GLADE_PATH 
#endif

bool holding = false;

GtkWidget* map;
GtkWidget* minimap;
GtkComboBox* rotationAxisSelector;
GtkComboBox* projectionSelector;

struct Either {
	Either() : isString(false) {}
	operator std::string() { return isString ? s : ""; }
	operator unit() { return isString ? 0.0 : u; }
	unit u;
	std::string s;
	bool isString;
};

void operator >>(std::istream& is, Either& either) {	 	  	 	     	   		   	      	 	    	 	
	if (either.isString) {
		is >> either.s;
	}
	else {
		is >> either.u;
	}
}

std::vector<Either> fields(13);
Either& field0 = fields[0];
Either& field1 = fields[1]; 
Either& field2 = fields[2];
Either& field3 = fields[3];
Either& field4 = fields[4];
Either& field5 = fields[5]; 
Either& field6 = fields[6];
Either& field7 = fields[7];
Either& field8 = fields[8];
Either& field9 = fields[9]; 
Either& field10 = fields[10];
Either& field11 = fields[11];
Either& field12 = fields[12];

vertices3_t pointsPolygon;

GtkTreeView* objects_tree_view;
GtkListStore* objects_list_store;
GtkCellRenderer* objects_cell_renderer;
GtkTreeModel* model;
GtkTreeSelection* objects_select;
GtkButton* toggleControl;

std::vector<Drawable>* mapObjects;
std::vector<Drawable>* minimapObjects;
shape_t<2>* minimapWindow;

enum ControlSwitch {	 	  	 	     	   		   	      	 	    	 	
	WINDOW = 0,
	OBJECTS
};

ControlSwitch controlSwitch = WINDOW;

enum {
	COL_NAME = 0,
	COL_TYPE,
	NUM_COLS
};

enum RotationAxis {
	X = 0,
	Y,
	Z
};

RotationAxis rotationAxis = X;

enum Projection {
	Orthogonal = 0,
	Perspective
};

Projection projection = Orthogonal;

std::string getSelectedObjectName() {
	GtkTreeIter iter;
	if (!gtk_tree_selection_get_selected(objects_select, nullptr, &iter)) {
		return "";
	}
	gchar *name, *type;
	gtk_tree_model_get(GTK_TREE_MODEL(objects_list_store), &iter, 0, &name, 1, &type, -1);
	return std::string(name);
}	 	  	 	     	   		   	      	 	    	 	

void redraw() {
	gtk_widget_queue_draw(map);
	gtk_widget_queue_draw(minimap);
}

void windowShiftU() {
	ctrl_ptr->scrollUp();
	redraw();
}
void windowShiftD() {
	ctrl_ptr->scrollDown();
	redraw();
}
void windowShiftL() {
	ctrl_ptr->scrollLeft();
	redraw();
}
void windowShiftR() {
	ctrl_ptr->scrollRight();
	redraw();
}
void windowXRotateAc() {
	ctrl_ptr->windowXRotateAc();
	redraw();
}
void windowXRotateC() {
	ctrl_ptr->windowXRotateC();
	redraw();
}
void windowYRotateAc() {
	ctrl_ptr->windowYRotateAc();
	redraw();
}
void windowYRotateC() {
	ctrl_ptr->windowYRotateC();
	redraw();
}	 	  	 	     	   		   	      	 	    	 	
void windowZRotateAc() {
	ctrl_ptr->windowZRotateAc();
	redraw();
}
void windowZRotateC() {
	ctrl_ptr->windowZRotateC();
	redraw();
}

void objectShiftU() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectShiftU(objName);
		redraw();
	}
}
void objectShiftD() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectShiftD(objName);
		redraw();
	}
}
void objectShiftL() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectShiftL(objName);
		redraw();
	}
}
void objectShiftR() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectShiftR(objName);
		redraw();
	}	 	  	 	     	   		   	      	 	    	 	
}
void objectShiftB() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectShiftB(objName);
		redraw();
	}
}
void objectShiftF() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectShiftF(objName);
		redraw();
	}
}
void objectXRotateAc() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectXRotateAc(objName);
		redraw();
	}
}
void objectXRotateC() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectXRotateC(objName);
		redraw();
	}
}
void objectYRotateAc() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectYRotateAc(objName);
		redraw();
	}
}	 	  	 	     	   		   	      	 	    	 	
void objectYRotateC() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectYRotateC(objName);
		redraw();
	}
}
void objectZRotateAc() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectZRotateAc(objName);
		redraw();
	}
}
void objectZRotateC() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectZRotateC(objName);
		redraw();
	}
}

extern "C" EXPORT void on_control_toggle(GtkButton *button, gpointer data) {
	if (controlSwitch == OBJECTS) {
		controlSwitch = WINDOW;
		gtk_button_set_label(button, "Window");
	}
	else {
		controlSwitch = OBJECTS;
		gtk_button_set_label(button, "Object");
	}
}

extern "C" EXPORT void set_rotation_axis(GtkButton *button, gpointer data) {
	int idx = gtk_combo_box_get_active(rotationAxisSelector);

	switch (idx) {	 	  	 	     	   		   	      	 	    	 	
	case 0:
		rotationAxis = X;
		break;
	case 1:
		rotationAxis = Y;
		break;
	case 2:
		rotationAxis = Z;
		break;
	default:
		break;
	}
}

extern "C" EXPORT void set_projection(GtkButton *button, gpointer data) {
	int idx = gtk_combo_box_get_active(projectionSelector);

	switch (idx) {
	case 0:
		projection = Orthogonal;
		ctrl_ptr->setPerspective(false);
		break;
	case 1:
		projection = Perspective;
		ctrl_ptr->setPerspective(true);
		break;
	default:
		break;
	}
	redraw();
	
}



extern "C" EXPORT gint on_buttonZoomIn_clicked(GtkButton *widget, gpointer data) {	 	  	 	     	   		   	      	 	    	 	
	if (controlSwitch == WINDOW) {
		ctrl_ptr->zoomIn();
		redraw();
	}
	else {
		std::string objName = getSelectedObjectName();
		if (!objName.empty()) {
			ctrl_ptr->objectScaleU(objName);
			redraw();
		}
	}
	return 1;
}

extern "C" EXPORT gint on_buttonZoomOut_clicked(GtkButton *widget, gpointer data) {
	if (controlSwitch == WINDOW) {
		ctrl_ptr->zoomOut();
		redraw();
	}
	else {
		std::string objName = getSelectedObjectName();
		if (!objName.empty()) {
			ctrl_ptr->objectScaleD(objName);
			redraw();
		}
	}
	return 1;
}

gboolean holdingButton(gpointer data) {
	if (holding) {
		auto func = (void(*)())(data);
		func();
	}
	return holding;
}	 	  	 	     	   		   	      	 	    	 	

void releaseButton() {
	holding = false;
}


extern "C" EXPORT gint on_buttonScroll_released(GtkButton *widget, gpointer data) {
	holding = false;
	return 1;
}

extern "C" EXPORT gint on_buttonUp_pressed(GtkButton *widget, gpointer data) {
	holding = true;
	if (controlSwitch == WINDOW) {
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowShiftU);
	}
	else {
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectShiftU);
	}
	return 1;
}


extern "C" EXPORT gint on_buttonDown_pressed(GtkButton *widget, gpointer data) {
	holding = true;
	if (controlSwitch == WINDOW) {
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowShiftD);
	}
	else {
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectShiftD);
	}
	return 1;
}
extern "C" EXPORT gint on_buttonLeft_pressed(GtkButton *widget, gpointer data) {
	holding = true;
	if (controlSwitch == WINDOW) {	 	  	 	     	   		   	      	 	    	 	
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowShiftL);
	}
	else {
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectShiftL);
	}
	return 1;
}
extern "C" EXPORT gint on_buttonRight_pressed(GtkButton *widget, gpointer data) {
	holding = true;
	if (controlSwitch == WINDOW) {
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowShiftR);
	}
	else {
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectShiftR);
	}
	return 1;
}
extern "C" EXPORT gint on_buttonIn_pressed(GtkButton *widget, gpointer data) {
	holding = true;
	if (controlSwitch == WINDOW) {
		//g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowShiftR);
	}
	else {
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectShiftF);
	}
	return 1;
}
extern "C" EXPORT gint on_buttonOut_pressed(GtkButton *widget, gpointer data) {
	holding = true;
	if (controlSwitch == WINDOW) {
		//g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowShiftR);
	}
	else {
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectShiftB);
	}
	return 1;
}	 	  	 	     	   		   	      	 	    	 	

extern "C" EXPORT void on_rotateLeft() {
	holding = true;
	if (controlSwitch == WINDOW) {
		switch (rotationAxis) {
		case X:
			g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowXRotateAc);
			break;
		case Y:
			g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowYRotateAc);
			break;
		case Z:
			g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowZRotateAc);
			break;
		default:
			break;
		}
	}
	else {
		switch (rotationAxis) {
		case X:
			g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectXRotateAc);
			break;
		case Y:
			g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectYRotateAc);
			break;
		case Z:
			g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectZRotateAc);
			break;
		default:
			break;
		}
	}
}

extern "C" EXPORT void on_rotateRight() {	 	  	 	     	   		   	      	 	    	 	
	holding = true;
	if (controlSwitch == WINDOW) {
		switch (rotationAxis) {
		case X:
			g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowXRotateC);
			break;
		case Y:
			g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowYRotateC);
			break;
		case Z:
			g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowZRotateC);
			break;
		default:
			break;
		}
	}
	else {
		switch (rotationAxis) {
		case X:
			g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectXRotateC);
			break;
		case Y:
			g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectYRotateC);
			break;
		case Z:
			g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectZRotateC);
			break;
		default:
			break;
		}
	}
}

//extern "C" EXPORT void on_rotateRight() {
//	holding = true;
//	if (controlSwitch == WINDOW) {	 	  	 	     	   		   	      	 	    	 	
//		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowRotateR);
//	}
//	else {
//		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectRotateR);
//	}
//}
extern "C" EXPORT gboolean on_minimap_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	guint width, height;

	// Get the size of the drawing area
	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);

	//ctrl_ptr->resizeMinimap(WinDims<int>(0, 0, width, height));

	// Fill whole area to black
	cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
	cairo_rectangle(cr, 0, 0, width, height);
	cairo_fill(cr);
	cairo_set_source_rgba(cr, 1.0, 0.0, 0.0, 1.0);
	cairo_set_line_width(cr, 1);

	for (auto& drawable : *minimapObjects) {
		cairo_set_source_rgba(cr, drawable.traits.color.red, drawable.traits.color.green, drawable.traits.color.blue, 1.0);

		if (drawable.traits.filled) {
			cairo_move_to(cr, drawable.shape.vertices()[0][0], drawable.shape.vertices()[0][1]);
			for (auto& vertex : drawable.shape.vertices()) {
				cairo_line_to(cr, vertex[0], vertex[1]);
			}
			cairo_fill(cr);
		}
		else {
			for (auto& edge : drawable.shape.edges()) {
				cairo_move_to(cr, edge.v1()[0], edge.v1()[1]);
				cairo_line_to(cr, edge.v2()[0], edge.v2()[1]);
			}	 	  	 	     	   		   	      	 	    	 	
		}
		cairo_stroke(cr);
	}

	auto edges = minimapWindow->edges();
	cairo_set_source_rgba(cr, 0.0, 1.0, 0.0, 1.0);
	cairo_move_to(cr, edges.back().v1()[0], edges.back().v1()[1]);
	cairo_line_to(cr, edges.back().v2()[0], edges.back().v2()[1]);
	cairo_stroke(cr); 

	cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 1.0);
	
	for (auto it = edges.begin(); it != edges.end() - 1; ++it) {
		cairo_move_to(cr, (*it).v1()[0], (*it).v1()[1]);
		cairo_line_to(cr, (*it).v2()[0], (*it).v2()[1]);
	}
	cairo_stroke(cr);

	return FALSE;

}


extern "C" EXPORT gboolean on_drawingarea1_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	guint width, height;

	// Get the size of the drawing area
	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);

	//ctrl_ptr->resizeMap(WinDims<int>(0, 0, width, height));

	// Fill whole area to black
	cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
	cairo_rectangle(cr, 0, 0, width, height);
	cairo_fill(cr);

	// Set fill colour to white
	cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 1.0);
	cairo_set_line_width(cr, 1);

	

	for (auto& drawable : *mapObjects) {	 	  	 	     	   		   	      	 	    	 	
		cairo_set_source_rgba(cr, drawable.traits.color.red, drawable.traits.color.green, drawable.traits.color.blue, 1.0);
		if (drawable.shape.vertices().empty()) { continue; }
		if (drawable.traits.filled) {
			cairo_move_to(cr, drawable.shape.vertices()[0][0], drawable.shape.vertices()[0][1]);
			for (auto& vertex : drawable.shape.vertices()) {
				cairo_line_to(cr, vertex[0], vertex[1]);
			}
			cairo_fill(cr);
		}
		else {
			for (auto& edge : drawable.shape.edges()) {
				cairo_move_to(cr, edge.v1()[0], edge.v1()[1]);
				cairo_line_to(cr, edge.v2()[0], edge.v2()[1]);
			}
		}
		cairo_stroke(cr);
	}

	cairo_set_source_rgba(cr, 0.0, 1.0, 0.0, 1.0);
	cairo_move_to(cr, 20, 20);
	cairo_line_to(cr, width - 20, 20);
	cairo_line_to(cr, width - 20, height - 20);
	cairo_line_to(cr, 20, height - 20);
	cairo_line_to(cr, 20, 20);
	cairo_stroke(cr);

	return FALSE;
}


void hideWindow(gpointer data) {
	gtk_widget_hide((GtkWidget*)data);
}

extern "C" EXPORT void on_buttonClickedHideWindow(GtkButton *button, gpointer data) {
	hideWindow(data);
}	 	  	 	     	   		   	      	 	    	 	

extern "C" EXPORT void on_buttonClickedShowWindow(GtkButton *button, gpointer data) {
	gtk_window_present((GtkWindow*)data);
}

extern "C" EXPORT void onListSelection(GtkWidget *button, gpointer data) {
	controlSwitch = OBJECTS;
	gtk_button_set_label(toggleControl, "Object");
}

void addObjectToTreeView(const char* nome, const char* tipo) {
	GtkTreeIter iter;
	gtk_list_store_append(objects_list_store, &iter);
	gtk_list_store_set(objects_list_store, &iter, COL_NAME, nome, COL_TYPE, tipo, -1);
}


extern "C" EXPORT void on_buttonClickedShowLine(GtkButton *button, gpointer data) {
	std::string objName(field0);
	if (ctrl_ptr->objectExists(objName)) {
		return; // Object with same name exists
	}
	Line<3> line(vertex3_t(field1, field2, 0.0), vertex3_t(field4, field5, 0.0));
	addObjectToTreeView(objName.c_str(), "Line");
	ctrl_ptr->addObject(objName, line);
}

extern "C" EXPORT void on_buttonClickedShowPoint(GtkButton *button, gpointer data) {
	//std::string objName(field0);

	//if (worldObjects.find(objName) != worldObjects.end()) {
	//	return; // Object with same name exists
	//}

	//Point point(x1_,y1_);

	//addObjectToTreeView(field0, "Point");
	//worldObjects[objName] = uiptr->m_model.addObject(point);

	/*std::unique_ptr<const Object2_ptr_t> ppObject(&(uiptr->m_model.addObject(point)));
	worldObjects[objName] = std::move(ppObject);
	hideWindow(data);*/
}	 	  	 	     	   		   	      	 	    	 	

extern "C" EXPORT void on_buttonClickedPolygonAddLine(GtkButton *button, gpointer data) {
	pointsPolygon.push_back(vertex3_t(field1, field2, 0.0));
}

extern "C" EXPORT void on_buttonClickedOkPolygon(GtkButton *button, gpointer data) {
	std::string objName(field0);

	if (ctrl_ptr->objectExists(objName)) {
		return; // Object with same name exists
	}

	if (pointsPolygon.size() > 0) {
		ctrl_ptr->addObject(objName, Wireframe<3>(pointsPolygon));
		pointsPolygon.clear();
		addObjectToTreeView(objName.c_str(), "Wireframe");
		hideWindow(data);
	}
}

extern "C" EXPORT void on_buttonClickedOkCurve(GtkButton *button, gpointer data) {
	std::string objName(field0);
	if (ctrl_ptr->objectExists(objName)) {
		return; // Object with same name exists
	}

	ctrl_ptr->addObject(objName, curva2<3>({field1, field2, 0.0}, { field4, field5, 0.0 }, { field7, field8, 0.0 }, { field10, field11, 0.0 }));
	addObjectToTreeView(objName.c_str(), "Curve");
	hideWindow(data);
	
}

void on_FieldChange(GtkEntry *text, size_t field) {
	const char* ch = gtk_entry_get_text(text);
	std::stringstream ss(ch);
	ss >> fields[field];
}	 	  	 	     	   		   	      	 	    	 	

extern "C" EXPORT void on_Field0Change(GtkEntry *text) {
	on_FieldChange(text, 0);
}
extern "C" EXPORT void on_Field1Change(GtkEntry *text) {
	on_FieldChange(text, 1);
}
extern "C" EXPORT void on_Field2Change(GtkEntry *text) {
	on_FieldChange(text, 2);
}
extern "C" EXPORT void on_Field3Change(GtkEntry *text) {
	on_FieldChange(text, 3);
}
extern "C" EXPORT void on_Field4Change(GtkEntry *text) {
	on_FieldChange(text, 4);
}
extern "C" EXPORT void on_Field5Change(GtkEntry *text) {
	on_FieldChange(text, 5);
}
extern "C" EXPORT void on_Field6Change(GtkEntry *text) {
	on_FieldChange(text, 6);
}
extern "C" EXPORT void on_Field7Change(GtkEntry *text) {
	on_FieldChange(text, 7);
}
extern "C" EXPORT void on_Field8Change(GtkEntry *text) {
	on_FieldChange(text, 8);
}
extern "C" EXPORT void on_Field9Change(GtkEntry *text) {
	on_FieldChange(text, 9);
}
extern "C" EXPORT void on_Field10Change(GtkEntry *text) {
	on_FieldChange(text, 10);
}
extern "C" EXPORT void on_Field11Change(GtkEntry *text) {
	on_FieldChange(text, 11);
}	 	  	 	     	   		   	      	 	    	 	
extern "C" EXPORT void on_Field12Change(GtkEntry *text) {
	on_FieldChange(text, 12);
}

void populateTree() {
	GtkTreeIter iter;
	for (auto& pair : ctrl_ptr->fromObj()) {
		gtk_list_store_append(objects_list_store, &iter);
		gtk_list_store_set(objects_list_store, &iter, COL_NAME, pair.first.c_str(), COL_TYPE, pair.second.c_str(), -1);
	}
}

UI::UI(Control& control)
	: m_control(control)
{
	ctrl_ptr = &control;
}

void UI::draw() {
	mapObjects = m_control.mapObjects();
	minimapObjects = m_control.minimapObjects();
	minimapWindow = m_control.minimapWindow();
	redraw();
}

void UI::uiInit() {

	gtk_init(nullptr, nullptr);

	/* Construct a GtkBuilder instance and load our UI description */
	gtkBuilder = gtk_builder_new();
	guint i = gtk_builder_add_from_file(gtkBuilder, GLADE_PATH"janela6.glade", NULL);

	gtk_builder_connect_signals(gtkBuilder, NULL);

	map = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "drawingarea1"));
	minimap = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "minimap"));
	toggleControl = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "togglebutton1"));
	rotationAxisSelector = reinterpret_cast<GtkComboBox*>(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "rotationAxisSelect"));
	projectionSelector = reinterpret_cast<GtkComboBox*>(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "projectionSelect"));
	guint width, height;
	width = gtk_widget_get_allocated_width(map);
	height = gtk_widget_get_allocated_height(map);
	m_control.initMap({ 20, 20, width - 40, height - 40 });
	width = gtk_widget_get_allocated_width(minimap);
	height = gtk_widget_get_allocated_height(minimap);
	m_control.initMinimap({ 20, 20, width - 40, height - 40 });

	m_control.init();

	/*
	* GtkTree view
	*/
	objects_tree_view = GTK_TREE_VIEW(gtk_builder_get_object(gtkBuilder, "object_list"));
	objects_list_store = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_STRING);
	objects_cell_renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_insert_column_with_attributes(objects_tree_view, -1, "Name", objects_cell_renderer, "text", COL_NAME, NULL);
	gtk_tree_view_insert_column_with_attributes(objects_tree_view, -1, "Type", objects_cell_renderer, "text", COL_TYPE, NULL);
	gtk_tree_view_set_model(objects_tree_view, GTK_TREE_MODEL(objects_list_store));

	objects_select = gtk_tree_view_get_selection(objects_tree_view);
	gtk_tree_selection_set_mode(objects_select, GTK_SELECTION_SINGLE);
	g_signal_connect(objects_select, "changed", G_CALLBACK(onListSelection), NULL);


	mapObjects = m_control.mapObjects();
	minimapObjects = m_control.minimapObjects();
	minimapWindow = m_control.minimapWindow();

	populateTree();

	fields[0].isString = true;

	gtk_main();

	return;
}	 	  	 	     	   		   	      	 	    	 	
