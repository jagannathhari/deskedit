
#include "ui/main_ui.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>


#define LABEL_WIDTH 0.30f
#define ENTRY_WIDTH 0.70f


#define APPLICATION_TYPE "Application"
#define DESKTOP_ENTRY "[Desktop Entry]"

typedef struct {
    char name[NAME_MAX  + 1];
    char command[PATH_MAX + 1];
    char icon[PATH_MAX + 1];
    char comment[NAME_MAX+1];
    char generic_name[NAME_MAX+1];
}DesktopFile;


void generate_desktop_file(DesktopFile desktop_entry){
    (void)desktop_entry;
    //todo
}

void main_ui(struct nk_context *ctx, int w, int h) {
    static DesktopFile desktop_entry;

    if (nk_begin(ctx, "DeskEdit", nk_rect(0, 0, w, h),
                 NK_WINDOW_NO_SCROLLBAR)) {

        nk_layout_row_begin(ctx, NK_DYNAMIC, 0, 2);
        nk_layout_row_push(ctx, LABEL_WIDTH);
        nk_label(ctx, "Name: ", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_layout_row_push(ctx, ENTRY_WIDTH);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD,desktop_entry.name, NAME_MAX, NULL);
        nk_layout_row_end(ctx);


        nk_layout_row_begin(ctx, NK_DYNAMIC, 0, 2);
        nk_layout_row_push(ctx, LABEL_WIDTH);
        nk_label(ctx, "Icon: ", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_layout_row_push(ctx, ENTRY_WIDTH);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD,desktop_entry.icon, PATH_MAX, NULL);
        nk_layout_row_end(ctx);

        nk_layout_row_begin(ctx, NK_DYNAMIC, 0, 2);
        nk_layout_row_push(ctx, LABEL_WIDTH);
        nk_label(ctx, "Command: ", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_layout_row_push(ctx, ENTRY_WIDTH);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD,desktop_entry.command, PATH_MAX, NULL);
        nk_layout_row_end(ctx);

        nk_layout_row_begin(ctx, NK_DYNAMIC, 0, 2);
        nk_layout_row_push(ctx, LABEL_WIDTH);
        nk_label(ctx, "Comment: ", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_layout_row_push(ctx, ENTRY_WIDTH);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD,desktop_entry.comment, NAME_MAX, NULL);
        nk_layout_row_end(ctx);

        nk_layout_row_begin(ctx, NK_DYNAMIC, 0, 2);
        nk_layout_row_push(ctx, LABEL_WIDTH);
        nk_label(ctx, "Generic Name:", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_layout_row_push(ctx, ENTRY_WIDTH);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD,desktop_entry.generic_name, NAME_MAX, NULL);
        nk_layout_row_end(ctx);


        nk_layout_row_dynamic(ctx , 0 ,1);
        if(nk_button_label(ctx, "Generate")){
            generate_desktop_file(desktop_entry);
        }




    }
    nk_end(ctx);
}
