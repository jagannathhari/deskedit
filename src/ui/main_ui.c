
#include "ui/main_ui.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define LABEL_WIDTH_MIN 135

#define ICON_SIZE 48.0f

#define APPLICATION_TYPE "Application"
#define DESKTOP_ENTRY "[Desktop Entry]"
#define EMPTY ""
#define APPLICATONS_FOLDER "/.local/share/applications/"
#define EXTENSION ".desktop"
#define DESKTOP_FILE_TEMPLATE                                                  \
    "%s\nType=%s\nName=%s\nComment=%s\nExec=%s\nIcon=%s\nTerminal=%s"

#define CUSTOM_LAYOUT_ROW_TEMPLATE(ctx, height, width) \
    nk_layout_row_template_begin(ctx, height); \
    nk_layout_row_template_push_static(ctx, width); \
    nk_layout_row_template_push_dynamic(ctx); \
    nk_layout_row_template_end(ctx); \

#define CUSTOM_LAYOUT_ROW_TEMPLATE_ICON(ctx, height, width,icon_size) \
    nk_layout_row_template_begin(ctx, height);\
    nk_layout_row_template_push_static(ctx,width);\
    nk_layout_row_template_push_dynamic(ctx);\
    nk_layout_row_template_push_static(ctx,icon_size);\
    nk_layout_row_template_end(ctx);\

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
            desktop_entry.command, desktop_entry.icon,
            (desktop_entry.terminal==nk_true)? "true":"false");

    fflush(f);
    fclose(f);
}

void main_ui(WinData *windata) {

    struct nk_image img;
    static DesktopFile desktop_entry;
    struct nk_context *ctx = windata->ctx;
    img = nk_image_ptr(windata->browse_icon);
    if (nk_begin(ctx, "DeskEdit", nk_rect(0, 0, windata->w, windata->h),
                 NK_WINDOW_NO_SCROLLBAR)) {
    
        
        CUSTOM_LAYOUT_ROW_TEMPLATE(ctx,0,LABEL_WIDTH_MIN)
        nk_label(ctx, "Name: ", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, desktop_entry.name,
                                       NAME_MAX, NULL);

      
        CUSTOM_LAYOUT_ROW_TEMPLATE_ICON(ctx,0,LABEL_WIDTH_MIN,ICON_SIZE)
        nk_label(ctx, "Icon: ", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, desktop_entry.icon,
                                       PATH_MAX, NULL);

        if(nk_button_image(ctx,img)){
            puts("asdf");
        }
        


        CUSTOM_LAYOUT_ROW_TEMPLATE_ICON(ctx,0,LABEL_WIDTH_MIN,ICON_SIZE)
        nk_label(ctx, "Command: ", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD,
                                       desktop_entry.command, PATH_MAX, NULL);
        if(nk_button_image(ctx,img)){
            puts("asdf");
        }


        CUSTOM_LAYOUT_ROW_TEMPLATE(ctx,0,LABEL_WIDTH_MIN)
        nk_label(ctx, "Comment: ", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD,
                                       desktop_entry.comment, NAME_MAX, NULL);

        CUSTOM_LAYOUT_ROW_TEMPLATE(ctx,0,LABEL_WIDTH_MIN)
        nk_label(ctx, "Mime Type:", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_edit_string_zero_terminated(
            ctx, NK_EDIT_FIELD, desktop_entry.generic_name, NAME_MAX, NULL);


        CUSTOM_LAYOUT_ROW_TEMPLATE(ctx,0,LABEL_WIDTH_MIN)
        nk_label(ctx, "Working dir: ", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, desktop_entry.name,
                                       NAME_MAX, NULL);

        CUSTOM_LAYOUT_ROW_TEMPLATE(ctx,0,LABEL_WIDTH_MIN)
            nk_label(ctx, "Generic Name:", NK_TEXT_CENTERED | NK_TEXT_LEFT);
        nk_edit_string_zero_terminated(
                ctx, NK_EDIT_FIELD, desktop_entry.generic_name, NAME_MAX, NULL);

              nk_layout_row_dynamic(ctx, 0, 1);
        nk_checkbox_label(ctx,"Run In Terminal", &desktop_entry.terminal);
        nk_checkbox_label(ctx,"Startup Notify", &desktop_entry.terminal);

       
        nk_layout_space_end(ctx);


        nk_layout_row_dynamic(ctx, 0, 1);
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
