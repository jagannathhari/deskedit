
#include "ui/main_ui.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LABEL_WIDTH 0.30f
#define ENTRY_WIDTH 0.70f

#define APPLICATION_TYPE "Application"
#define DESKTOP_ENTRY "[Desktop Entry]"
#define EMPTY ""
#define APPLICATONS_FOLDER "/.local/share/applications/"
#define EXTENSION ".desktop"
#define DESKTOP_FILE_TEMPLATE                                                  \
    "%s\nType=%s\nName=%s\nComment=%s\nExec=%s\nIcon=%s"

typedef struct {
    char name[NAME_MAX + 1];
    char command[PATH_MAX + 1];
    char icon[PATH_MAX + 1];
    char comment[NAME_MAX + 1];
    char generic_name[NAME_MAX + 1];
    nk_bool terminal;
} DesktopFile;

int check_required(DesktopFile desktop_entry) {
    if (desktop_entry.name[0] == '\0') {
        return 0;
    }
    return 1;
}

void generate_desktop_file(DesktopFile desktop_entry) {
    char file_path[PATH_MAX + 1];
    FILE *f;

    char *home_dir = getenv("HOME");
    if(!home_dir) return;

    snprintf(file_path, PATH_MAX, "%s%s%s%s",home_dir, APPLICATONS_FOLDER,
             desktop_entry.name, EXTENSION);
    f = fopen(file_path, "w");
    if (!f)
        return;
    fprintf(f, DESKTOP_FILE_TEMPLATE, DESKTOP_ENTRY, APPLICATION_TYPE,
            desktop_entry.name, desktop_entry.comment,
            desktop_entry.command, desktop_entry.icon);

    fflush(f);
    fclose(f);
}

void main_ui(WinData *windata) {
    static DesktopFile desktop_entry;
    struct nk_context *ctx = windata->ctx;
    if (nk_begin(ctx, "DeskEdit", nk_rect(0, 0, windata->w, windata->h),
                 NK_WINDOW_NO_SCROLLBAR)) {

        nk_layout_row_begin(ctx, NK_DYNAMIC, 0, 2);
        nk_layout_row_push(ctx, LABEL_WIDTH);
        nk_label(ctx, "Name: ", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_layout_row_push(ctx, ENTRY_WIDTH);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, desktop_entry.name,
                                       NAME_MAX, NULL);
        nk_layout_row_end(ctx);

        nk_layout_row_begin(ctx, NK_DYNAMIC, 0, 2);
        nk_layout_row_push(ctx, LABEL_WIDTH);
        nk_label(ctx, "Icon: ", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_layout_row_push(ctx, ENTRY_WIDTH);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, desktop_entry.icon,
                                       PATH_MAX, NULL);
        nk_layout_row_end(ctx);

        nk_layout_row_begin(ctx, NK_DYNAMIC, 0, 2);
        nk_layout_row_push(ctx, LABEL_WIDTH);
        nk_label(ctx, "Command: ", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_layout_row_push(ctx, ENTRY_WIDTH);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD,
                                       desktop_entry.command, PATH_MAX, NULL);
        nk_layout_row_end(ctx);


        nk_layout_row_begin(ctx, NK_DYNAMIC, 0, 2);
        nk_layout_row_push(ctx, LABEL_WIDTH);
        nk_label(ctx, "Comment: ", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_layout_row_push(ctx, ENTRY_WIDTH);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD,
                                       desktop_entry.comment, NAME_MAX, NULL);
        nk_layout_row_end(ctx);

        nk_layout_row_begin(ctx, NK_DYNAMIC, 0, 2);
        nk_layout_row_push(ctx, LABEL_WIDTH);
        nk_label(ctx, "Generic Name:", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_layout_row_push(ctx, ENTRY_WIDTH);
        nk_edit_string_zero_terminated(
            ctx, NK_EDIT_FIELD, desktop_entry.generic_name, NAME_MAX, NULL);
        nk_layout_row_end(ctx);

        nk_layout_row_dynamic(ctx, 0, 1);
        nk_checkbox_label(ctx,"Run In Terminal", &desktop_entry.terminal);
        nk_spacer(ctx);
        struct nk_image img;
        img = nk_image_ptr(windata->browse_icon);
        if(nk_button_image(ctx,img)){
            puts("asdf");
        }
        if (nk_button_label(ctx, "Generate")) {
            if (check_required(desktop_entry)) {
                generate_desktop_file(desktop_entry);
            } else {
                puts("Please Enter required fileds");
            }
        }
    }
    nk_end(ctx);
}
