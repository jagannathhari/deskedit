
#include "ui/main_ui.h"
#include <stdio.h>

void main_ui(struct nk_context *ctx, int w, int h) {
    if (nk_begin(ctx, "Hello world", nk_rect(0, 0, w, h),
                 NK_WINDOW_NO_SCROLLBAR)) {
        nk_layout_row_dynamic(ctx, h - 15, 1);
        if (nk_button_label(ctx, "Hello world")) {
            puts("Hello world");
        }
    }
    nk_end(ctx);
}
