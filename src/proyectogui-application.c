/*11-Las librerias glib/gi18n.h permiten crear ventanas de diálogo*/ 
#include <glib/gi18n.h>
#include "proyectogui-application.h"
#include "proyectogui-window.h"

struct _ProyectoguiApplication
{
//4-Cambiar GObject por GtkApplication  
  GtkApplication parent_instance;
  /*8- Widgets implementados en la UI*/
  GtkWindow *window;
};

//4-Cambiar G_TYPE_OBJECT por GTK_TYPE_APPLICATION 
G_DEFINE_TYPE (ProyectoguiApplication, proyectogui_application, GTK_TYPE_APPLICATION)

static void
proyectogui_application_quit_action (GSimpleAction *action,
                                     GVariant      *parameter,
                                     gpointer      *user_data)
{
  /*11-funcion que cierra la app, invocable luego en el código, es la acción declarada en la UI (app.quit) 
  implementada por código en la app*/
 ProyectoguiApplication *proyectogui;
 proyectogui = PROYECTOGUI_APPLICATION (user_data);
 gtk_widget_destroy (GTK_WIDGET (proyectogui -> window)); 
}

static void
proyectogui_application_about_action (GSimpleAction *action,
                                      GVariant      *parameter,
                                      gpointer      *user_data)
{
  /*11-funcion que abre un cuadro de diálogo con info sobre la app, invocable luego en el código, 
   * es la acción declarada en la UI (app.about_dialog) implementada por código en la app*/
  ProyectoguiApplication *proyectogui;
  proyectogui = PROYECTOGUI_APPLICATION (user_data);
  GtkWidget *about_dialog;
  const gchar *authors[] = {
    "Profesor Germán Grob",
    NULL
  };
  const gchar *artists[] = {
    "Profesor Germán Grob",
    NULL
  };
  about_dialog = g_object_new (GTK_TYPE_ABOUT_DIALOG,
                               "transient-for", GTK_WINDOW (proyectogui -> window),
                               "modal", TRUE,
                               "destroy-with-parent", TRUE,
                               "program-name", "ProyectoGUI",
                               "comments", "Aplicación con Interfaz de Usuario\nDesarrollado con IDE: GNOME Builder 3.36.0\n\nSobre la base del tutorial Gnome Builder por Danilo Galete",
                               "version", "1.0 - BETA",
                               "website-label", "https://youtu.be/edHM0iIf3eA?si=RACsXSL9oO0RL72H",
                               "website", "https://youtu.be/edHM0iIf3eA?si=RACsXSL9oO0RL72H",
                               "authors", authors,
                               "artists", artists,
                               NULL);
  gtk_widget_show_all (about_dialog);
  
}

static void
proyectogui_application_activate (GtkApplication *application)
{
  /*8-Funcion que activa la app, invocable luego en el código*/
  ProyectoguiApplication *proyectogui;
  g_assert (GTK_IS_APPLICATION (application));
  proyectogui = PROYECTOGUI_APPLICATION (application);
  proyectogui -> window = gtk_application_get_active_window (application);
  if (proyectogui -> window == NULL)
    proyectogui -> window = g_object_new (PROYECTOGUI_TYPE_WINDOW,
                                 "application",application,
                                 NULL);
  gtk_window_present (proyectogui -> window);
}

static void
proyectogui_application_startup (GtkApplication *application)
{
  /*11-funcion que arranca la app, invocable luego en el código
  nótese que incluye las acciones de los controles declaradas al diseñar la UI*/
  ProyectoguiApplication *proyectogui;
  proyectogui = PROYECTOGUI_APPLICATION (application);
  static const GActionEntry app_entry[] = {
      {"quit", proyectogui_application_quit_action, NULL, NULL, NULL},
      {"about_dialog", proyectogui_application_about_action, NULL, NULL, NULL},
  };
  g_action_map_add_action_entries (G_ACTION_MAP (application),
                                   app_entry,
                                   G_N_ELEMENTS (app_entry),
                                   application);
  G_APPLICATION_CLASS (proyectogui_application_parent_class) -> startup (application);
  
}

/*4-Borrar el sgte código
enum {
  PROP_0,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];*/

ProyectoguiApplication *
proyectogui_application_new (void)
{
  /*8-Incluir los siguientes parámetros*/
  return g_object_new (PROYECTOGUI_TYPE_APPLICATION, 
                       "resource_base_path", "Proyectos/Builder/ProyectoGUI",
                       "application-id", "/org/my/ProyectoGUI",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);
}

/*4-Borrar código desde
static void
proyectogui_application_finalize (GObject *object)...hasta lo INMEDIATAMENTE ANTERIOR a
static void
proyectogui_application_class_init (ProyectoguiApplicationClass *klass)*/
/*proyectogui_application_class_init (ProyectoguiApplicationClass *klass) es el encabezado de la función
que inicia las clases que NO DEBE BORRARSE*/

static void
proyectogui_application_class_init (ProyectoguiApplicationClass *klass)
{
  /* 4-borrar las funciones invocadas
  object_class->finalize = proyectogui_application_finalize;
  object_class->get_property = proyectogui_application_get_property;
  object_class->set_property = proyectogui_application_set_property;*/
  
  /*8-Inicialización de las clases con llamadas a funciones previamente declaradas*/
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  G_APPLICATION_CLASS (klass) ->activate = proyectogui_application_activate;
  /*11-Inicialización de la clase startup con llamada a la función previamente declarada, se implementa
  cuando la GUI invoca una acción, no debe implementarse si no hay llamada a acción*/
  G_APPLICATION_CLASS (klass) ->startup = proyectogui_application_startup;
}

static void
proyectogui_application_init (ProyectoguiApplication *self)
{
  /*13-Inicializa la app, nótese que incluye la acción limpiar de la ventana para vaciar el entry_nombre
   y las demás*/
  gtk_application_set_accels_for_action (GTK_APPLICATION (self),
                                         "win.limpiar",
                                         (const char *[]) { NULL, NULL});
  gtk_application_set_accels_for_action (GTK_APPLICATION (self),
                                         "win.cargar",
                                         (const char *[]) { NULL, NULL});
}
