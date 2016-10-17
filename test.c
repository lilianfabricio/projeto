#include <allegro.h>

volatile int exit_program;
void fecha_programa()
{
    exit_program = TRUE;
}
END_OF_FUNCTION(fecha_programa)

int main()
{
    allegro_init();
    install_timer();
    install_mouse();
    install_keyboard();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    set_window_title("Tutorial 7 - Mouse");

    exit_program = FALSE;
    LOCK_FUNCTION(fecha_programa);
    LOCK_VARIABLE(exit_program);
    set_close_button_callback(fecha_programa);

    ///BITMAPS
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

    ///GAME LOOP
    while(!exit_program)
    {
        //INPUT
        if(key[KEY_ESC])
            fecha_programa();

        //UPDATE
        rectfill(buffer, 100, 100, 200,200, makecol(0,0,255)); //compactar
        rectfill(buffer, 250, 100, 350,200, makecol(0,0,255)); //descompactar

        if(mouse_x > 100 && mouse_x < 200 && mouse_y > 100 && mouse_y < 200) //compactar
        {
            rectfill(buffer, 100, 100, 200,200, makecol(255,255,0));

            // Função do botão
            if(mouse_b == 1)
            {
                textout_ex(buffer, font, "Botao Esquerdo pressionado!", 100, 300, makecol(255,255,255), -1);
                compress();
            }
            if(mouse_b == 2)
            {
                textout_ex(buffer, font, "Botao Direito pressionado!", 100, 300, makecol(255,255,255), -1);
            }
        }

        if(mouse_x > 250 && mouse_x < 350 && mouse_y > 100 && mouse_y < 200) //descompactar
        {
            rectfill(buffer, 250, 100, 350,200, makecol(255,255,0));

            //Função do botão
            if(mouse_b == 1)
            {
                textout_ex(buffer, font, "Botao Esquerdo pressionado!", 100, 300, makecol(255,255,255), -1);
                descompress();
            }
            if(mouse_b == 2)
            {
                textout_ex(buffer, font, "Botao Direito pressionado!", 100, 300, makecol(255,255,255), -1);
            }
        }

        textout_ex(buffer, font, "Compactar", 110, 150, makecol(255,0,0), -1);
        textout_ex(buffer, font, "Descompactar", 250, 150, makecol(255,0,0), -1);

        //DRAW
        show_mouse(buffer);
        draw_sprite(screen, buffer, 0, 0);
        draw_sprite(screen, buffer, 0, 0);
        clear(buffer);
    }

    ///FINALIZAÇÂO
    destroy_bitmap(buffer);

    return 0;
}
END_OF_MAIN();
