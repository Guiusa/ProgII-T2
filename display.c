#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Allegro */
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include "display.h"

Window initWindow(int width, int height){
    Window window = {NULL, NULL, NULL, {0, 0, 0, 0}};

    al_init();
    al_init_image_addon();
    al_init_native_dialog_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    puts("Modos 60Hz disponíveis:\n");
    int i;
    for(i = 0; i < al_get_num_display_modes(); ++i){
        al_get_display_mode(i, &window.disp_data);
        if(window.disp_data.refresh_rate == 60)
            printf("%d: %d %d\n", i, window.disp_data.width, window.disp_data.height);
        if(window.disp_data.width == width && window.disp_data.height == height)
            break;
    }

    al_get_display_mode(i, &window.disp_data);
    al_set_new_display_flags(ALLEGRO_WINDOWED);

    window.display = al_create_display(window.disp_data.width, window.disp_data.height);

    al_install_mouse();
    al_install_keyboard();
    window.timer = al_create_timer(1.0 / window.disp_data.refresh_rate);

    window.event_queue = al_create_event_queue();
    al_register_event_source(window.event_queue, al_get_display_event_source(window.display));
    al_register_event_source(window.event_queue, al_get_mouse_event_source());
    al_register_event_source(window.event_queue, al_get_keyboard_event_source());
    al_register_event_source(window.event_queue, al_get_timer_event_source(window.timer));

    al_clear_to_color(PIXEL(255, 120, 0));
    al_flip_display();
    al_start_timer(window.timer);

    return window;
}

void deinitWindow(Window win)
{
  al_destroy_timer(win.timer);
  al_destroy_event_queue(win.event_queue);
  al_destroy_display(win.display);
}



ALLEGRO_BITMAP* createImg(char* name, int width, int height, Window win){
    ALLEGRO_BITMAP *img, *bmp;

    bmp = al_create_bitmap(width, height);
    al_set_target_bitmap(bmp);


    if(name){
        img = al_load_bitmap(name);
        al_draw_bitmap(img, 0, 0, 0);
    }

    al_set_target_bitmap(al_get_backbuffer(win.display));

    return bmp;
}