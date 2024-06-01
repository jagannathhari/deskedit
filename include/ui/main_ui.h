#ifndef MAIN_UI_H
    #define MAIN_UI_H
    #ifndef NK_NUKLEAR_H_
        #include <nuklear.h>
        #include <SDL.h>
    #endif

#include <linux/limits.h>

typedef struct {
    struct nk_context *ctx;
    SDL_Renderer *renderer;
    SDL_Texture *browse_icon; 
    int w;
    int h;
}WinData;

typedef struct {
    char name[NAME_MAX + 1];
    char command[PATH_MAX + 1];
    char icon[PATH_MAX + 1];
    char comment[NAME_MAX + 1];
    char generic_name[NAME_MAX + 1];
    char working_dir[PATH_MAX + 1];
    char mime_type[NAME_MAX + 1];
    nk_bool terminal;
    nk_bool startup_notify;
}DesktopFile;

void main_ui(WinData *windata);

#endif // MAIN_UI_H
