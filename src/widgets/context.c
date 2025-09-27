#include "gtk/gtk.h"
#include "widgets.h"
#include "widgets_private.h"
#include <stdio.h>
#include <stdlib.h>
widgets_ctx *ctx;

widgets_ctx *new_widgets_ctx(GtkApplication *app) {
  ctx = malloc(sizeof(struct widgets_ctx_t));

  ctx->window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(ctx->window), "");

  ctx->header = gtk_header_bar_new();
  gtk_window_set_titlebar(GTK_WINDOW(ctx->window), ctx->header);
  gtk_widget_set_visible(ctx->header, true);
  gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(ctx->header), false);

  ctx->main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_window_set_child(GTK_WINDOW(ctx->window), ctx->main_box);

  gtk_widget_set_hexpand(GTK_WIDGET(ctx->main_box), true);
  gtk_widget_set_vexpand(GTK_WIDGET(ctx->main_box), true);

  ctx->loading_box = NULL;
  ctx->image = NULL;
  ctx->webView = NULL;
  ctx->alreadyLoaded = false;

  setup_loading(ctx);
  setup_gestures(ctx);
  setup_webview(ctx);

  return ctx;
}
