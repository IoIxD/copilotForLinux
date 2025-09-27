#include "gdk-pixbuf/gdk-pixbuf.h"
#include "gio/gio.h"
#include "glib-object.h"
#include "glib.h"
#include <assert.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>
#include <webkit/webkit.h>

// clang-format off
static const char * copilotSVG = "<svg width='2048' height='2048' style='flex:none;line-height:1' viewBox='-10 -10 44 44' xmlns='http://www.w3.org/2000/svg'><title>Copilot</title><path d='M17.533 1.829A2.528 2.528 0 0015.11 0h-.737a2.531 2.531 0 00-2.484 2.087l-1.263 6.937.314-1.08a2.528 2.528 0 012.424-1.833h4.284l1.797.706 1.731-.706h-.505a2.528 2.528 0 01-2.423-1.829l-.715-2.453z' fill='url(#lobe-icons-copilot-fill-0)' transform='translate(0 1)'></path><path d='M6.726 20.16A2.528 2.528 0 009.152 22h1.566c1.37 0 2.49-1.1 2.525-2.48l.17-6.69-.357 1.228a2.528 2.528 0 01-2.423 1.83h-4.32l-1.54-.842-1.667.843h.497c1.124 0 2.113.75 2.426 1.84l.697 2.432z' fill='url(#lobe-icons-copilot-fill-1)' transform='translate(0 1)'></path><path d='M15 0H6.252c-2.5 0-4 3.331-5 6.662-1.184 3.947-2.734 9.225 1.75 9.225H6.78c1.13 0 2.12-.753 2.43-1.847.657-2.317 1.809-6.359 2.713-9.436.46-1.563.842-2.906 1.43-3.742A1.97 1.97 0 0115 0' fill='url(#lobe-icons-copilot-fill-2)' transform='translate(0 1)'></path><path d='M15 0H6.252c-2.5 0-4 3.331-5 6.662-1.184 3.947-2.734 9.225 1.75 9.225H6.78c1.13 0 2.12-.753 2.43-1.847.657-2.317 1.809-6.359 2.713-9.436.46-1.563.842-2.906 1.43-3.742A1.97 1.97 0 0115 0' fill='url(#lobe-icons-copilot-fill-3)' transform='translate(0 1)'></path><path d='M9 22h8.749c2.5 0 4-3.332 5-6.663 1.184-3.948 2.734-9.227-1.75-9.227H17.22c-1.129 0-2.12.754-2.43 1.848a1149.2 1149.2 0 01-2.713 9.437c-.46 1.564-.842 2.907-1.43 3.743A1.97 1.97 0 019 22' fill='url(#lobe-icons-copilot-fill-4)' transform='translate(0 1)'></path><path d='M9 22h8.749c2.5 0 4-3.332 5-6.663 1.184-3.948 2.734-9.227-1.75-9.227H17.22c-1.129 0-2.12.754-2.43 1.848a1149.2 1149.2 0 01-2.713 9.437c-.46 1.564-.842 2.907-1.43 3.743A1.97 1.97 0 019 22' fill='url(#lobe-icons-copilot-fill-5)' transform='translate(0 1)'></path><defs><radialGradient cx='85.44%' cy='100.653%' fx='85.44%' fy='100.653%' gradientTransform='scale(-.8553 -1) rotate(50.927 2.041 -1.946)' id='lobe-icons-copilot-fill-0' r='105.116%'><stop offset='9.6%' stop-color='#00AEFF'></stop><stop offset='77.3%' stop-color='#2253CE'></stop><stop offset='100%' stop-color='#0736C4'></stop></radialGradient><radialGradient cx='18.143%' cy='32.928%' fx='18.143%' fy='32.928%' gradientTransform='scale(.8897 1) rotate(52.069 .193 .352)' id='lobe-icons-copilot-fill-1' r='95.612%'><stop offset='0%' stop-color='#FFB657'></stop><stop offset='63.4%' stop-color='#FF5F3D'></stop><stop offset='92.3%' stop-color='#C02B3C'></stop></radialGradient><radialGradient cx='82.987%' cy='-9.792%' fx='82.987%' fy='-9.792%' gradientTransform='scale(-1 -.9441) rotate(-70.872 .142 1.17)' id='lobe-icons-copilot-fill-4' r='140.622%'><stop offset='6.6%' stop-color='#8C48FF'></stop><stop offset='50%' stop-color='#F2598A'></stop><stop offset='89.6%' stop-color='#FFB152'></stop></radialGradient><linearGradient id='lobe-icons-copilot-fill-2' x1='39.465%' x2='46.884%' y1='12.117%' y2='103.774%'><stop offset='15.6%' stop-color='#0D91E1'></stop><stop offset='48.7%' stop-color='#52B471'></stop><stop offset='65.2%' stop-color='#98BD42'></stop><stop offset='93.7%' stop-color='#FFC800'></stop></linearGradient><linearGradient id='lobe-icons-copilot-fill-3' x1='45.949%' x2='50%' y1='0%' y2='100%'><stop offset='0%' stop-color='#3DCBFF'></stop><stop offset='24.7%' stop-color='#0588F7' stop-opacity='0'></stop></linearGradient><linearGradient id='lobe-icons-copilot-fill-5' x1='83.507%' x2='83.453%' y1='-6.106%' y2='21.131%'><stop offset='5.8%' stop-color='#F8ADFA'></stop><stop offset='70.8%' stop-color='#A86EDD' stop-opacity='0'></stop></linearGradient></defs></svg>";
// clang-format on

GtkWidget *window;
GtkWidget *image = NULL;
GtkWidget *box = NULL;
GtkWidget *header = NULL;
static bool alreadyLoaded = false;

static void loading(WebKitWebView *webview, gpointer user_data) {
  bool isLoading = webkit_web_view_is_loading(webview);
  if (isLoading && !alreadyLoaded) {
    gtk_window_set_child(GTK_WINDOW(window), GTK_WIDGET(box));
  } else {
    gtk_window_set_child(GTK_WINDOW(window), GTK_WIDGET(webview));
    alreadyLoaded = true;
  }
}

static void button_press_event(GtkApplication *app, gpointer user_data) {
  printf("test\n");
}

static void setup_webview() {
  GdkDisplay *disp = gdk_display_get_default();

  GListModel *monitors = gdk_display_get_monitors(disp);
  g_assert(g_list_model_get_n_items(monitors) != 0);

  GdkRectangle workarea = {0};
  GdkMonitor *monitor = GDK_MONITOR(g_list_model_get_object(monitors, 0));
  gdk_monitor_get_geometry(monitor, &workarea);

  gtk_window_set_default_size(GTK_WINDOW(window), workarea.width * 0.3,
                              workarea.height * 0.9);

  WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

  g_signal_connect(webView, "notify::is-loading", G_CALLBACK(loading), NULL);
  webkit_web_view_load_uri(webView, "https://copilot.microsoft.com");

  g_signal_connect(webView, "button-press-event",
                   G_CALLBACK(button_press_event), NULL);
}

static void setup_loading() {
  GdkPixbufLoader *loader = gdk_pixbuf_loader_new();
  gdk_pixbuf_loader_write(loader, (const guchar *)copilotSVG,
                          strlen(copilotSVG), NULL);
  gdk_pixbuf_loader_close(loader, NULL);

  GdkPixbuf *pixbuf = gdk_pixbuf_loader_get_pixbuf(loader);

  image = gtk_image_new_from_pixbuf(pixbuf);

  box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_set_spacing(GTK_BOX(box), 10);
  gtk_box_prepend(GTK_BOX(box), image);
  gtk_widget_set_hexpand(GTK_WIDGET(image), true);

  g_signal_connect(box, "button-press-event", G_CALLBACK(button_press_event),
                   NULL);
}

static void activate(GtkApplication *app, gpointer user_data) {
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "");

  header = gtk_header_bar_new();
  gtk_window_set_titlebar(GTK_WINDOW(window), header);
  gtk_widget_set_visible(header, true);
  gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(header), false);

  setup_loading();
  while (image == NULL) {
  }
  setup_webview();

  gtk_window_present(GTK_WINDOW(window));
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
