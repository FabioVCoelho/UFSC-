#ifndef UI_H
#define UI_H

#include "cg_system.h"
#include <gtk/gtk.h>

class UI {
public:
    UI(Model& model, CGSys& cg);
    void uiInit();
	Model& m_model;
	CGSys& m_cg;
    
private:
	GtkBuilder* gtkBuilder;
    int m_xMinVp, m_xMaxVp, m_yMinVp, m_yMaxVp;
};

#endif