#ifndef __WIDGETS_PRIVATE_H
#define __WIDGETS_PRIVATE_H

#include "gtk/gtk.h"
#include "widgets.h"

struct widgets_ctx_t {
  GtkWidget *window;
  GtkWidget *image;

  GtkGesture *gesture_click;
  GtkEventController *motion_controller;

  GtkWidget *main_box;
  GtkWidget *loading_box;

  GtkWidget *header;
  bool alreadyLoaded;
  WebKitWebView *webView;
};

void loading(WebKitWebView *webview, WebKitLoadEvent load_event,
             gpointer user_data);
void setup_webview(widgets_ctx *ctx);
void setup_loading(widgets_ctx *ctx);
void setup_gestures(widgets_ctx *ctx);

#endif
