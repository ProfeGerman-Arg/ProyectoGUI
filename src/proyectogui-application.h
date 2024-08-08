#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PROYECTOGUI_TYPE_APPLICATION (proyectogui_application_get_type())

//3-cambiar GObject pot GtkApplication
G_DECLARE_FINAL_TYPE (ProyectoguiApplication, proyectogui_application, PROYECTOGUI, APPLICATION, GtkApplication)

ProyectoguiApplication *proyectogui_application_new (void);

G_END_DECLS
