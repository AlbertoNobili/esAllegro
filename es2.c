#include <allegro.h>
#include <stdio.h>

int main()
{
int	x, y;
int col = 14;
	allegro_init();
	set_color_depth(8);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	install_keyboard();
	install_mouse();
	show_mouse(screen);
	do {
		if (mouse_b & 1) {
			x = mouse_x;
			y = mouse_y;
			scare_mouse();
			putpixel(screen, x, y, col);
			unscare_mouse();
		}
	} while (!key[KEY_ESC]);
	printf("fine");
	return 0;
}

