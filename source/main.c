#include <grrlib.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>

// in RGBA format
#define BARS_WHITE   0xFFFFFFFF
#define BARS_YELLOW  0xBFBF00FF
#define BARS_CYAN    0x00BFBFFF
#define BARS_GREEN   0x00BF00FF
#define BARS_MAGENTA 0xBF00BFFF
#define BARS_RED     0xBF0000FF
#define BARS_BLUE    0x0000BFFF
// #define BARS_BLACK   0x000000FF

#define SQUARES_BLUE 0x00214CFF
#define SQUARES_WHITE 0xFFFFFFFF
#define SQUARES_VIOLET 0x32006AFF
#define SQUARES_GRAY1 0x000000FF
#define SQUARES_GRAY2 0x131313FF
#define SQUARES_GRAY3 0x1D1D1DFF

int with_brightness(int c, int b) {
	int cr = R(c);
	int cg = G(c);
	int cb = B(c);
	int ca = A(c);

	cr = (cr + b > 0xFF) ? 0xFF : cr + b;
	cg = (cg + b > 0xFF) ? 0xFF : cg + b;
	cb = (cb + b > 0xFF) ? 0xFF : cb + b;
	cr = (cr < 0x00) ? 0x00 : cr;
	cg = (cg < 0x00) ? 0x00 : cg;
	cb = (cb < 0x00) ? 0x00 : cb;
	
	return RGBA(cr, cg, cb, ca);
}

void smpte(int screen_width, int screen_height, int brightness) {
	int bbar_height = screen_height / 1.5;
	int bbar_width = screen_width / 7;
	int lbar_height = screen_height / 16;
	int lbar_width = screen_width / 7;
	int sq_width = screen_width / 6;
	int sq_height = screen_height / 4;
	int sq_third = sq_width / 3;	
	GRRLIB_Rectangle(0, 0, bbar_width, bbar_height, with_brightness(BARS_WHITE, brightness), true);
	GRRLIB_Rectangle(bbar_width, 0, bbar_width, bbar_height, with_brightness(BARS_YELLOW, brightness), true);
	GRRLIB_Rectangle(bbar_width*2, 0, bbar_width, bbar_height, with_brightness(BARS_CYAN, brightness), true);
	GRRLIB_Rectangle(bbar_width*3, 0, bbar_width, bbar_height, with_brightness(BARS_GREEN, brightness), true);
	GRRLIB_Rectangle(bbar_width*4, 0, bbar_width, bbar_height, with_brightness(BARS_MAGENTA, brightness), true);
	GRRLIB_Rectangle(bbar_width*5, 0, bbar_width, bbar_height, with_brightness(BARS_RED, brightness), true);
	GRRLIB_Rectangle(bbar_width*6, 0, bbar_width, bbar_height, with_brightness(BARS_BLUE, brightness), true);

	// middle layer of bars (except they're more like rectangles)
	GRRLIB_Rectangle(0, bbar_height, lbar_width, lbar_height, with_brightness(BARS_BLUE, brightness), true);
	// pro life tip: you can save cpu time by not drawing the fully black bars because nobody will ever notice
	GRRLIB_Rectangle(lbar_width*2, bbar_height, lbar_width, lbar_height, with_brightness(BARS_MAGENTA, brightness), true);
	GRRLIB_Rectangle(lbar_width*4, bbar_height, lbar_width, lbar_height, with_brightness(BARS_CYAN, brightness), true);
	GRRLIB_Rectangle(lbar_width*6, bbar_height, lbar_width, lbar_height, with_brightness(BARS_WHITE, brightness), true);

	GRRLIB_Rectangle(0, bbar_height+lbar_height, sq_width, sq_height, with_brightness(SQUARES_BLUE, brightness), true); 
	GRRLIB_Rectangle(sq_width, bbar_height+lbar_height, sq_width, sq_height, with_brightness(SQUARES_WHITE, brightness), true);
	GRRLIB_Rectangle(sq_width*2, bbar_height+lbar_height, sq_width, sq_height, with_brightness(SQUARES_VIOLET, brightness), true);
	GRRLIB_Rectangle(sq_width*3, bbar_height+lbar_height, sq_width, sq_height, with_brightness(SQUARES_GRAY2, brightness), true);
	GRRLIB_Rectangle(sq_width*4, bbar_height+lbar_height, sq_third, sq_height, with_brightness(SQUARES_GRAY1, brightness), true);
	GRRLIB_Rectangle((sq_width*4)+sq_third, bbar_height+lbar_height, sq_third, sq_height, with_brightness(SQUARES_GRAY2, brightness), true);
	GRRLIB_Rectangle((sq_width*4)+(sq_third*2), bbar_height+lbar_height, sq_third+1, sq_height, with_brightness(SQUARES_GRAY3, brightness), true);
	GRRLIB_Rectangle(sq_width*5, bbar_height+lbar_height, sq_width+1, sq_height, with_brightness(SQUARES_GRAY2, brightness), true);	
}

int main() {
	GRRLIB_Init();
	WPAD_Init();
	
	// everything is proportional to the width and height of the screen so it can be ported to any screen size
	// specifically because widescreen mode (however i prefer 4:3 mode because it's cool)
	int brightness = 0;
	int screen_width = rmode->fbWidth;
	int screen_height = rmode->efbHeight;

	while (1) {
		WPAD_ScanPads();
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) break;
		if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_UP) brightness++;
		if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_DOWN) brightness--;
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_B) brightness = 0;

		smpte(screen_width, screen_height, brightness);
		
		GRRLIB_Render();
	}
	GRRLIB_Exit();
	exit(0);
}
