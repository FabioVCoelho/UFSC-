#include "ui.h"
#include "point.h"
#include "line.h"
#include "wireframe.h"
#include <string>

#include <memory>
#include <cassert>

Control* ctrl_ptr;

#ifdef _MSC_VER
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#ifdef NVPL
#define GLADE_PATH "..\\..\\"
#else
#define GLADE_PATH 
#endif

bool holding = false;

GtkWidget* map;
GtkWidget* minimap;

points_t pointsToAdd(2);
unit& x1_ = pointsToAdd[0][0];
unit& x2_ = pointsToAdd[1][0];
unit& y1_ = pointsToAdd[0][1];
unit& y2_ = pointsToAdd[1][1];
const char* newShapeName;


points_t pointsPolygon;

GtkTreeView* objects_tree_view;
GtkListStore* objects_list_store;
GtkCellRenderer* objects_cell_renderer;
GtkTreeModel* model;
GtkTreeSelection* objects_select;
GtkButton* toggleControl;

std::vector<Drawable>* mapShapes;
std::vector<Drawable>* minimapShapes;
edgevertex2f_t* minimapWindow;



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
void windowRotateL() {
	ctrl_ptr->rotateLeft();
	redraw();
}
void windowRotateR() {
	ctrl_ptr->rotateRight();
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
void objectRotateL() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectRotateL(objName);
		redraw();
	}
}
void objectRotateR() {
	std::string objName = getSelectedObjectName();
	if (!objName.empty()) {
		ctrl_ptr->objectRotateR(objName);
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

extern "C" EXPORT void on_rotateLeft() {
	holding = true;
	if (controlSwitch == WINDOW) {
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowRotateL);
	}
	else {
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectRotateL);
	}
}

extern "C" EXPORT void on_rotateRight() {
	holding = true;
	if (controlSwitch == WINDOW) {
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowRotateR);
	}
	else {
		g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)objectRotateR);
	}
}




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

	for (auto& shape : *minimapShapes) {
		cairo_set_source_rgba(cr, shape.color.red, shape.color.green, shape.color.blue, 1.0);
		if (shape.filled) {
			cairo_move_to(cr, shape.shape.vertices()[0][0], shape.shape.vertices()[0][1]);
			for (auto& vertex : shape.shape.vertices()) {
				cairo_line_to(cr, vertex[0], vertex[1]);
			}
			cairo_fill(cr);
		}
		else {
			for (auto& edge : shape.shape.edges()) {
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

	

	for (auto& shape : *mapShapes) {
		cairo_set_source_rgba(cr, shape.color.red, shape.color.green, shape.color.blue, 1.0);
		if (shape.shape.vertices().empty()) { continue; }
		if (shape.filled) {
			cairo_move_to(cr, shape.shape.vertices()[0][0], shape.shape.vertices()[0][1]);
			for (auto& vertex : shape.shape.vertices()) {
				cairo_line_to(cr, vertex[0], vertex[1]);
			}
			cairo_fill(cr);
		}
		else {
			for (auto& edge : shape.shape.edges()) {
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
	gtk_widget_hide((GtkWidget*) data);
}

extern "C" EXPORT void on_buttonClickedHideWindow(GtkButton *button, gpointer data)	{
	hideWindow(data);
}

extern "C" EXPORT void on_buttonClickedShowWindow(GtkButton *button, gpointer data)	{
	gtk_window_present((GtkWindow*) data);
}

extern "C" EXPORT void onListSelection(GtkWidget *button, gpointer data) {
	controlSwitch = OBJECTS;
	gtk_button_set_label(toggleControl, "Object");
}

void addObjectToTreeView(const char* nome, const char* tipo)	{
	GtkTreeIter iter;
	gtk_list_store_append(objects_list_store, &iter);
	gtk_list_store_set(objects_list_store, &iter, COL_NAME, nome, COL_TYPE, tipo, -1);
}


extern "C" EXPORT void on_buttonClickedShowLine(GtkButton *button, gpointer data)	{
	std::string objName(newShapeName);
	if (ctrl_ptr->objectExists(objName)) {
		return; // Object with same name exists
	}
	Line line(pointsToAdd[0], pointsToAdd[1]);
	addObjectToTreeView(newShapeName, "Line");
	ctrl_ptr->addShape(objName, line);
}

extern "C" EXPORT void on_buttonClickedShowPoint(GtkButton *button, gpointer data)	{
	//std::string objName(newShapeName);

	//if (worldObjects.find(objName) != worldObjects.end()) {
	//	return; // Object with same name exists
	//}

	//Point point(x1_,y1_);

	//addObjectToTreeView(newShapeName, "Point");
	//worldObjects[objName] = uiptr->m_model.addShape(point);

	/*std::unique_ptr<const shape_ptr_t> ppshape(&(uiptr->m_model.addShape(point)));
	worldObjects[objName] = std::move(ppshape);
	hideWindow(data);*/
}

extern "C" EXPORT void on_buttonClickedPolygonAddLine(GtkButton *button, gpointer data)	{
	pointsPolygon.push_back(pointsToAdd[0]);
}

extern "C" EXPORT void on_buttonClickedOkPolygon(GtkButton *button, gpointer data)	{
	std::string objName(newShapeName);

	if (ctrl_ptr->objectExists(objName)) {
		return; // Object with same name exists
	}

	if (pointsPolygon.size() > 0)
		ctrl_ptr->addShape(objName, Wireframe(pointsPolygon));
		pointsPolygon.clear();
		addObjectToTreeView(newShapeName, "Wireframe");
		hideWindow(data);
	}

	extern "C" EXPORT void on_textChangeOnX1(GtkEntry *pointX1)	{
		x1_ = atoi(gtk_entry_get_text(pointX1));
	}

	extern "C" EXPORT void on_textChangeOnY1(GtkEntry *pointY1)	{
		y1_ = atoi(gtk_entry_get_text(pointY1));
	}

	extern "C" EXPORT void on_textChangeOnX2(GtkEntry *pointX2)	{
		x2_ = atoi(gtk_entry_get_text(pointX2));
	}

	extern "C" EXPORT void on_textChangeOnY2(GtkEntry *pointY2)	{
		y2_ = atoi(gtk_entry_get_text(pointY2));
	}

	extern "C" EXPORT void on_textChangeOnName(GtkEntry *name_entry)	{
		newShapeName = gtk_entry_get_text(name_entry);
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
		mapShapes = m_control.mapShapes();
		minimapShapes = m_control.minimapShapes();
		minimapWindow = m_control.minimapWindow();
		redraw();
	}

	void UI::uiInit() {

		gtk_init(nullptr, nullptr);

	/* Construct a GtkBuilder instance and load our UI description */
		gtkBuilder = gtk_builder_new();
		guint i = gtk_builder_add_from_file(gtkBuilder, GLADE_PATH"janela6.glade", NULL);

		gtk_builder_connect_signals(gtkBuilder, NULL);

		map = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawingarea1") );
		minimap = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "minimap"));
		toggleControl = GTK_BUTTON(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "togglebutton1"));
		guint width, height;
		width = gtk_widget_get_allocated_width(map);
		height = gtk_widget_get_allocated_height(map);
		m_control.initMap({ 20, 20, width-40, height-40 });
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
		

		mapShapes = m_control.mapShapes();
		minimapShapes = m_control.minimapShapes();
		minimapWindow = m_control.minimapWindow();

		populateTree();

		gtk_main();

		return;
	}
