#include "proyectogui-config.h"
#include "proyectogui-window.h"

struct _ProyectoguiWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  /* 12-widgets utilizados en el diseño de la UI*/ 
  GtkBox              *box;
  GtkButton           *button_oka;
  GtkButton           *button_limpiar;
  GtkButton           *button_salir;
  GtkEntry            *entry_nombre;
  GtkLabel            *label_nombre;
  GtkLabel            *label_datos;
  GtkLabel            *label_nombreing;
  GtkSeparator        *separator_datos;
  
  
};

G_DEFINE_TYPE (ProyectoguiWindow, proyectogui_window, GTK_TYPE_APPLICATION_WINDOW)

static void
proyectogui_window_class_init (ProyectoguiWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/my/ProyectoGUI/proyectogui-window.ui");
  gtk_widget_class_bind_template_child (widget_class, ProyectoguiWindow, header_bar);
  /*10-Borrar inicialización de label
  gtk_widget_class_bind_template_child (widget_class, ProyectoguiWindow, label);*/
  
  /* 12-Inicialización de los widgets utilizados en el diseño de la UI*/
  gtk_widget_class_bind_template_child (widget_class, ProyectoguiWindow, box);
  gtk_widget_class_bind_template_child (widget_class, ProyectoguiWindow, button_oka);
  gtk_widget_class_bind_template_child (widget_class, ProyectoguiWindow, button_limpiar);
  gtk_widget_class_bind_template_child (widget_class, ProyectoguiWindow, button_salir);
  gtk_widget_class_bind_template_child (widget_class, ProyectoguiWindow, entry_nombre);
  gtk_widget_class_bind_template_child (widget_class, ProyectoguiWindow, label_nombre);
  gtk_widget_class_bind_template_child (widget_class, ProyectoguiWindow, label_datos);
  gtk_widget_class_bind_template_child (widget_class, ProyectoguiWindow, label_nombreing);
  gtk_widget_class_bind_template_child (widget_class, ProyectoguiWindow, separator_datos);
}

static void
limpiar_clickeado (ProyectoguiWindow *self)
{
  /*14-Evento que captura la acción click del botón limpiar, "win.limpiar" debe declararse durante el diseño de la UI*/
  gtk_entry_set_text (GTK_ENTRY (self->entry_nombre), "");
  gtk_label_set_text (GTK_ENTRY (self->label_datos), "");
}

static void
cargar_clickeado (ProyectoguiWindow *self)
{
  /*14-Evento que captura la acción click del botón oka, "win.cargar" debe declararse durante el diseño de la UI
       Toma el dato del entry_nombre y lo muestra en label_datos*/
  gtk_label_set_text (GTK_LABEL (self->label_datos), gtk_entry_get_text (GTK_ENTRY (self->entry_nombre)));
}

static void//
capturar_accion (ProyectoguiWindow *self, gchar *action_name, GCallback handler)
{
  /*14-Función que captura una acción en los controles de la UI, implementada luego en el código*/
  GSimpleAction *action = g_simple_action_new (action_name, NULL);
  g_signal_connect_swapped (action, "activate", handler, self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION (action));
}

static void
proyectogui_window_init (ProyectoguiWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
  
  /*14-Invocar a la función que registra eventuales acciones en los controles de la ventana
  este función posiblemente pudiera invocarse en el activate o startup (debiera chequearse)*/ 
  capturar_accion (self, "limpiar", G_CALLBACK(limpiar_clickeado));
  capturar_accion (self, "cargar", G_CALLBACK(cargar_clickeado));
}
