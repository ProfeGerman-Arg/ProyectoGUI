#include <glib/gi18n.h>

#include "proyectogui-config.h"
#include "proyectogui-application.h"

/*7-Borrar la función on_activate 
static void
on_activate (GtkApplication *app)...hasta
	gtk_window_present (window);
} incluido*/


int
main (int   argc,
      char *argv[])
{
	//7-Cambia GtkApplication por ProyectoguiApplication
  g_autoptr(ProyectoguiApplication) app = NULL;
	int ret;

	/* Set up gettext translations */
	bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);

	/*
	 * Create a new GtkApplication. The application manages our main loop,
	 * application windows, integration with the window manager/compositor, and
	 * desktop features such as file opening and single-instance applications.
	 */
	//7-cambiar gtk_application_new ("org.my.ProyectoGUI", G_APPLICATION_FLAGS_NONE) por proyectogui_application_new ()
  app = proyectogui_application_new ();

/* 7-Borrar comentarios e instrucción g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);

	/*
	 * Run the application. This function will block until the applicaiton
	 * exits. Upon return, we have our exit code to return to the shell. (This
	 * is the code you see when you do `echo $?` after running a command in a
	 * terminal.
	 *
	 * Since GtkApplication inherits from GApplication, we use the parent class
	 * method "run". But we need to cast, which is what the "G_APPLICATION()"
	 * macro does.
	 */
	ret = g_application_run (G_APPLICATION (app), argc, argv);

	return ret;
}
