#include "gio/gio.h"
#include "glib-object.h"
#include "glib.h"
#include "widgets/widgets.h"
#include <assert.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>

static void activate(GtkApplication *app, gpointer user_data) {
  widgets_ctx *ctx = new_widgets_ctx(app);

  ctx_finish(ctx);
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("net.ioi-xd.copilot", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
