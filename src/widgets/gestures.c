#include "gtk/gtk.h"
#include "widgets_private.h"

static void pressed(GtkGestureClick *self, gint n_press, gdouble x, gdouble y,
                    gpointer user_data) {
  // printf("pressed! %0.2f %0.2f\n", x, y);
}
static void released(GtkGestureClick *self, gint n_press, gdouble x, gdouble y,
                     gpointer user_data) {
  // printf("released! %0.2f %0.2f\n", x, y);
}
static void motion(GtkGestureClick *self, gint n_press, gdouble x, gdouble y,
                   gpointer user_data) {
  // printf("motion! %0.2f %0.2f\n", x, y);
}

void setup_gestures(widgets_ctx *ctx) {
  ctx->gesture_click = gtk_gesture_click_new();
  ctx->motion_controller = gtk_event_controller_motion_new();

  g_signal_connect(ctx->gesture_click, "pressed", G_CALLBACK(pressed),
                   (gpointer)ctx);
  g_signal_connect(ctx->gesture_click, "released", G_CALLBACK(released),
                   (gpointer)ctx);

  g_signal_connect(ctx->motion_controller, "motion", G_CALLBACK(motion),
                   (gpointer)ctx);

  gtk_widget_add_controller(ctx->main_box,
                            GTK_EVENT_CONTROLLER(ctx->gesture_click));
  gtk_widget_add_controller(ctx->main_box,
                            GTK_EVENT_CONTROLLER(ctx->motion_controller));
}
