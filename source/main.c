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
#define BARS_BLACK   0x000000FF

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

#define TELEFUNKEN_GRAY   0x404040FF
#define TELEFUNKEN_GRAY2  0x2D2D2DFF
#define TELEFUNKEN_GRAY3  0x7F7F7FFF
#define TELEFUNKEN_WHITE  0xFFFFFFFF
#define TELEFUNKEN_WHITE2 0xC0C0C0FF

void telefunken_fubk(int screen_width, int screen_height, int brightness) {
	int grid_size = screen_width / 20;
	GRRLIB_FillScreen(with_brightness(TELEFUNKEN_GRAY, brightness));
	
	// grid
	for (int i = 0; i < 20; i++) {
		GRRLIB_Line(0, grid_size * i, screen_width, grid_size * i, with_brightness(TELEFUNKEN_WHITE, brightness));
	}
	for (int j = 0; j < 20; j++) {
		GRRLIB_Line(grid_size * j, 0, grid_size * j, screen_height, with_brightness(TELEFUNKEN_WHITE, brightness));
	}

	// center rectangle
	GRRLIB_Rectangle(grid_size * 4, grid_size * 3, grid_size * 12, grid_size * 10, with_brightness(TELEFUNKEN_WHITE, brightness), true);

	// bars
	int offset_x = grid_size * 4;
	int offset_y = grid_size * 3;
	int bar_width = (grid_size * 12) / 8;
	int bar_height = grid_size * 3;

	int colors[8] = {TELEFUNKEN_WHITE2, BARS_YELLOW, BARS_CYAN, BARS_GREEN, BARS_MAGENTA, BARS_RED, BARS_BLUE, BARS_BLACK};
	for (int k = 0; k < 8; k++) {
		GRRLIB_Rectangle(bar_width * k + offset_x, 0 + offset_y, bar_width, bar_height, with_brightness(colors[k], brightness), true);
	}

	// lower squares
	int squares_width = bar_width * 2;
	int squares_height = grid_size * 2;
	int colors2[4] = {BARS_BLACK, TELEFUNKEN_GRAY2, TELEFUNKEN_GRAY3, TELEFUNKEN_WHITE};
	for (int l = 0; l < 4; l++) {
		GRRLIB_Rectangle(squares_width * l + offset_x, bar_height + offset_y, squares_width, squares_height, with_brightness(colors2[l], brightness), true);
	}

	// center black bar
	int cbb_width = (squares_width * 2) + (squares_width / 3);
	GRRLIB_Rectangle((int)(squares_width * 2/3) + offset_x, bar_height+squares_height+offset_y, cbb_width, grid_size, with_brightness(BARS_BLACK, brightness), true); 

	// circle
	int center_x = screen_width / 2;
	int center_y = screen_height / 2;
	int radius_x = grid_size * 14;
	int radius_y = grid_size * 16;
	GRRLIB_Ellipse(center_x, center_y, radius_x, radius_y, with_brightness(TELEFUNKEN_WHITE, brightness), false);
}

void ebu_colour_bars(int screen_width, int screen_height, int brightness) {
	int bar_width = screen_width / 8;
	GRRLIB_Rectangle(0, 0, bar_width, screen_height, with_brightness(BARS_WHITE, brightness), true);
	GRRLIB_Rectangle(bar_width, 0, bar_width, screen_height, with_brightness(BARS_YELLOW, brightness), true);
	GRRLIB_Rectangle(bar_width*2, 0, bar_width, screen_height, with_brightness(BARS_CYAN, brightness), true);
	GRRLIB_Rectangle(bar_width*3, 0, bar_width, screen_height, with_brightness(BARS_GREEN, brightness), true);
	GRRLIB_Rectangle(bar_width*4, 0, bar_width, screen_height, with_brightness(BARS_MAGENTA, brightness), true);
	GRRLIB_Rectangle(bar_width*5, 0, bar_width, screen_height, with_brightness(BARS_RED, brightness), true);
	GRRLIB_Rectangle(bar_width*6, 0, bar_width, screen_height, with_brightness(BARS_BLUE, brightness), true);
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

int clamp_card_number(int v, int min, int max) {
	return (v - min + (max - min + 1)) % (max-min+1) + min;
}

int main() {
	GRRLIB_Init();
	WPAD_Init();
	
	// everything is proportional to the width and height of the screen so it can be ported to any screen size
	// specifically because widescreen mode (however i prefer 4:3 mode because it's cool)
	int brightness = 0;
	int current_card = 0;
	int screen_width = rmode->fbWidth;
	int screen_height = rmode->efbHeight;

	while (1) {
		WPAD_ScanPads();
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) break;
		if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_UP) brightness++;
		if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_DOWN) brightness--;
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_B) brightness = 0;
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_RIGHT) { current_card += 1; current_card = clamp_card_number(current_card, 0, 2); }
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_LEFT) { current_card -= 1; current_card = clamp_card_number(current_card, 0, 2); }

		GRRLIB_FillScreen(with_brightness(0x000000FF, brightness)); // added this so the empty space's brightness increases along with the colored shapes because i left them empty for :sparkles: OPTIMIZATION :sparkles:

		switch (current_card) {
			case 0:
				smpte(screen_width, screen_height, brightness);
				break;
			case 1:
				ebu_colour_bars(screen_width, screen_height, brightness);
				break;
			case 2:
				telefunken_fubk(screen_width, screen_height, brightness);
				break;
			default:
				// clamp didn't work all hope is lost just kill the program
				GRRLIB_Exit();
				exit(0);
		}
		
		GRRLIB_Render();
	}
	GRRLIB_Exit();
	exit(0);
}
