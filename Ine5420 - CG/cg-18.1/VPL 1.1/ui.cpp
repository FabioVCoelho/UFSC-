#include "ui.h"
#include "point.h"
#include "line.h"

UI* uiptr;

#ifdef _MSC_VER
#define EXPORT __declspec(dllexport)
#else
#define EXPORT 
#endif

bool holding = false;

GtkWidget* map;
GtkWidget* minimap;

GtkEntry* name_line;
GtkEntry* x1_line;
GtkEntry* y1_line;
GtkEntry* x2_line;
GtkEntry* y2_line;

GtkEntry* name_point;
GtkEntry* x1_point;
GtkEntry* y1_point;

GtkEntry* name_polygon;
GtkEntry* x1_polygon;
GtkEntry* y1_polygon;
std::vector<Point> pointsPolygon;

GtkTreeView* objects_tree_view;
GtkListStore* objects_list_store;
GtkCellRenderer* objects_cell_renderer;
GtkTreeSelection* objects_select;

enum {
    COL_NAME = 0,
    COL_TYPE,
    NUM_COLS
};

void windowShiftU() {
	uiptr->m_cg.scrollUp();
	gtk_widget_queue_draw(map);
	gtk_widget_queue_draw(minimap);
	
}
void windowShiftD() {
	uiptr->m_cg.scrollDown();
	gtk_widget_queue_draw(map);
	gtk_widget_queue_draw(minimap);
}
void windowShiftL() {
	uiptr->m_cg.scrollLeft();
	gtk_widget_queue_draw(map);
	gtk_widget_queue_draw(minimap);
}
void windowShiftR() {
	uiptr->m_cg.scrollRight();
	gtk_widget_queue_draw(map);
	gtk_widget_queue_draw(minimap);
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

extern "C" EXPORT gboolean on_minimap_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	guint width, height;

	// Get the size of the drawing area
	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);

	uiptr->m_cg.resizeMinimap(Dims2d<int>(0, width, 0, height));

	// Fill whole area to black
	cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
	cairo_rectangle(cr, 0, 0, width, height);
	cairo_fill(cr);
	cairo_set_source_rgba(cr, 1.0, 0.0, 0.0, 1.0);
	cairo_set_line_width(cr, 1);
	for (auto& shape : (uiptr->m_cg).minimapShapes()) {
		auto points = shape->points();
		cairo_move_to(cr, points[0].first, points[0].second);
		for (auto it = points.begin() + 1; it != points.end(); ++it) {
			cairo_line_to(cr, (*it).first, (*it).second);
		}
		cairo_line_to(cr, points[0].first, points[0].second);
	}

	cairo_close_path(cr);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);

	cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 1.0);
	auto points = (uiptr->m_cg).minimapWindow();
	cairo_move_to(cr, points[0].first, points[0].second);	
	for (auto it = points.begin() + 1; it != points.end(); ++it) {
		cairo_line_to(cr, (*it).first, (*it).second);
	}
	cairo_line_to(cr, points[0].first, points[0].second);
	
	cairo_stroke_preserve(cr);

	return FALSE;

}


extern "C" EXPORT gboolean on_drawingarea1_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	guint width, height;
	
	// Get the size of the drawing area
	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);
	
	uiptr->m_cg.resizeMap(Dims2d<int>(0, width, 0, height));
	
	// Fill whole area to black
	cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
	cairo_rectangle(cr, 0, 0, width, height);
	cairo_fill(cr);
	
	// Set fill colour to white
	cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 1.0);
	cairo_set_line_width(cr, 1);

	cairo_set_source_rgba(cr, 1.0, 0.0, 0.0, 1.0);
	for (auto& shape : (uiptr->m_cg).mapShapes()) {
		auto points = shape->points();
		cairo_move_to(cr, points[0].first, points[0].second);
		for (auto it = points.begin() + 1; it != points.end(); ++it) {
			cairo_line_to(cr, (*it).first, (*it).second);
		}
		cairo_line_to(cr, points[0].first, points[0].second);
	}

	cairo_close_path(cr);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);
	
	return FALSE;
}


extern "C" EXPORT gint on_buttonZoomIn_clicked(GtkButton *widget, gpointer data) {
	uiptr->m_cg.zoomIn();
	gtk_widget_queue_draw(GTK_WIDGET(data));
	gtk_widget_queue_draw(minimap);
	return 1;
}

extern "C" EXPORT gint on_buttonZoomOut_clicked(GtkButton *widget, gpointer data) {
	uiptr->m_cg.zoomOut();
	gtk_widget_queue_draw(GTK_WIDGET(data));
	gtk_widget_queue_draw(minimap);
	return 1;
}

extern "C" EXPORT gint on_buttonScroll_released(GtkButton *widget, gpointer data) {
	holding = false;
	return 1;
}

extern "C" EXPORT gint on_buttonUp_pressed(GtkButton *widget, gpointer data) {
	uiptr->m_cg.scrollUp();
	gtk_widget_queue_draw(map);
	gtk_widget_queue_draw(minimap);
	holding = true;
	g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowShiftU);
	return 1;
}

extern "C" EXPORT gint on_buttonDown_pressed(GtkButton *widget, gpointer data) {
	uiptr->m_cg.scrollDown();
	gtk_widget_queue_draw(map);
	gtk_widget_queue_draw(minimap);
	holding = true;
	g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowShiftD);
	return 1;
}
extern "C" EXPORT gint on_buttonLeft_pressed(GtkButton *widget, gpointer data) {
	uiptr->m_cg.scrollLeft();
	gtk_widget_queue_draw(map);
	gtk_widget_queue_draw(minimap);
	holding = true;
	g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowShiftL);
	return 1;
}
extern "C" EXPORT gint on_buttonRight_pressed(GtkButton *widget, gpointer data) {
	uiptr->m_cg.scrollRight();
	gtk_widget_queue_draw(map);
	gtk_widget_queue_draw(minimap);
	holding = true;
	g_timeout_add(20, (GSourceFunc)holdingButton, (gpointer)windowShiftR);
	return 1;
}

extern "C" EXPORT void on_buttonClickedHideWindow(GtkButton *button, gpointer data)	{
	gtk_widget_hide((GtkWidget*) data);
}

extern "C" EXPORT void on_buttonClickedShowWindow(GtkButton *button, gpointer data)	{
    gtk_window_present((GtkWindow*) data);
}

void addObjectToTreeView(const char* nome, const char* tipo)	{
	GtkTreeIter iter;
    gtk_list_store_append(objects_list_store, &iter);
	gtk_list_store_set(objects_list_store, &iter, COL_NAME, nome, COL_TYPE, tipo, -1);
}

extern "C" EXPORT void on_buttonClickedShowLine(GtkButton *button, gpointer data)	{
	Line line(
	Point(atoi(gtk_entry_get_text(x1_line)),atoi(gtk_entry_get_text(y1_line))),
	Point(atoi(gtk_entry_get_text(x2_line)),atoi(gtk_entry_get_text(y2_line)))
	);
	uiptr->m_model.addShape(line);

	addObjectToTreeView(gtk_entry_get_text(name_line), "Line");
}

extern "C" EXPORT void on_buttonClickedShowPoint(GtkButton *button, gpointer data)	{
	uiptr->m_model.addShape(Point(atoi(gtk_entry_get_text(x1_point)),atoi(gtk_entry_get_text(y1_point))));

	addObjectToTreeView(gtk_entry_get_text(name_point), "Point");
}

extern "C" EXPORT void on_buttonClickedPolygonAddLine(GtkButton *button, gpointer data)	{
	pointsPolygon.push_back(Point(atoi(gtk_entry_get_text(x1_polygon)),atoi(gtk_entry_get_text(y1_polygon))));
}

extern "C" EXPORT void on_buttonClickedOkPolygon(GtkButton *button, gpointer data)	{
	if (pointsPolygon.size() > 0)
		for (int i = 0; i < pointsPolygon.size() - 1; i++)
		{
			uiptr->m_model.addShape(Line(pointsPolygon[i],pointsPolygon[i+1]));
		}
	pointsPolygon.clear();
	addObjectToTreeView(gtk_entry_get_text(name_polygon), "Polygon");
}

UI::UI(Model& model, CGSys& cg)
    : m_model(model), m_cg(cg)
{
    uiptr = this;
}

void UI::uiInit() {

	gtk_init(nullptr, nullptr);

	/* Construct a GtkBuilder instance and load our UI description */
	gtkBuilder = gtk_builder_new();
	guint i = gtk_builder_add_from_file(gtkBuilder, "..\\..\\janela4.glade", NULL);

	gtk_builder_connect_signals(gtkBuilder, NULL);

	map = GTK_WIDGET( gtk_builder_get_object( GTK_BUILDER(gtkBuilder), "drawingarea1") );
	minimap = GTK_WIDGET(gtk_builder_get_object(GTK_BUILDER(gtkBuilder), "minimap"));
	guint width, height;
	width = gtk_widget_get_allocated_width(map);
	height = gtk_widget_get_allocated_height(map);
	


	/*
	 * Line Entrys
	 */

    name_line = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "name_line"));
	x1_line = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "x1_line"));
    y1_line = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "y1_line"));
    x2_line = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "x2_line"));
    y2_line = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "y2_line"));

	/*
	 * Point Entrys
	 */

    name_point = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "name_point"));
	x1_point = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "x1_point"));
    y1_point = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "y1_point"));

	/*
	 * Polygon Entrys
	 */
    name_polygon = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "name_polygon"));
	x1_polygon = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "x1_polygon"));
    y1_polygon = GTK_ENTRY(gtk_builder_get_object(gtkBuilder, "y1_polygon"));


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

	gtk_main();

	return;
}
