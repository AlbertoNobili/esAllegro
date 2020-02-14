#include <stdio.h>
#include <allegro.h>

void get_keycodes(char* ascii, char*scan)
{
int	a;
	
	a = readkey();
	*ascii = a & 0xFF;
	*scan = a >> 8;	
}

void get_string(char* str, int x, int y, int c, int b)
{
char	scan, ascii, s[2];
int		i = 0;

	do {
		get_keycodes(&ascii, &scan);
		if (scan != KEY_ENTER){
			str[i++] = ascii;
			s[0] = ascii;
			s[1] = '\0';
			textout_ex(screen, font, s, x, y, c, b);
			x = x + 8;
		}
	} while (scan != KEY_ENTER);	
	str[i] = '\0';
}


int main()
{
char	str[20];
float	x;

	allegro_init();
	set_color_depth(8);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	install_keyboard();

	textout_ex(screen, font, "x: ", 10, 30, 3, 0);
get_string(str, 34, 30, 3, 0);
	sscanf(str, "%f", &x);
	printf("%f\n", x);
	
	return 0;
}
