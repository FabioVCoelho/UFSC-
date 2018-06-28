#ifndef UI_H
#define UI_H

#include "cg_system.h"
#include <gtk/gtk.h>
#include "control.h"

class UI {
public:
	UI(Control& control);
    void uiInit();
	
	void draw();
    
private:
	GtkBuilder* gtkBuilder;
	Control& m_control;
    int m_xMinVp, m_xMaxVp, m_yMinVp, m_yMaxVp;
};

#endif