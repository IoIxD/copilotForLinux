#include "widgets.h"
#include "widgets_private.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

void setup_webview(widgets_ctx *ctx) {
  GdkDisplay *disp = gdk_display_get_default();

  GListModel *monitors = gdk_display_get_monitors(disp);
  g_assert(g_list_model_get_n_items(monitors) != 0);

  GdkRectangle workarea = {0};
  GdkMonitor *monitor = GDK_MONITOR(g_list_model_get_object(monitors, 0));
  gdk_monitor_get_geometry(monitor, &workarea);

  int winWidth = workarea.width * 0.3;
  if (winWidth <= 300) {
    winWidth = 300;
  }

  gtk_window_set_default_size(GTK_WINDOW(ctx->window), winWidth,
                              workarea.height * 0.95);

  ctx->webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

  webkit_web_view_load_uri(ctx->webView, "https://copilot.microsoft.com");
  gtk_widget_set_hexpand(GTK_WIDGET(ctx->webView), true);
  gtk_widget_set_vexpand(GTK_WIDGET(ctx->webView), true);
  gtk_widget_set_visible(GTK_WIDGET(ctx->webView), false);

  gtk_box_append(GTK_BOX(ctx->main_box), GTK_WIDGET(ctx->webView));

  g_signal_connect(ctx->webView, "notify::is-loading", G_CALLBACK(loading),
                   (gpointer)ctx);
}

void ctx_finish(widgets_ctx *ctx) {
  gtk_window_present(GTK_WINDOW(ctx->window));
}
