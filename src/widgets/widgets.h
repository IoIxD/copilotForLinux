#ifndef __WIDGET_H
#define __WIDGET_H

#include <gtk/gtk.h>
#include <webkit/webkit.h>

typedef struct widgets_ctx_t widgets_ctx;

widgets_ctx *new_widgets_ctx(GtkApplication *app);
void ctx_finish(widgets_ctx *ctx);

#endif
