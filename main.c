#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include "raylib.h"

#define SQ_SIDE 5
#define COLS 200
#define ROWS 200
#define SPAWN_SIZE 5
#define COLOR_CHANGE_SPEED 0.01

#define WIDTH COLS*SQ_SIDE
#define HEIGHT ROWS*SQ_SIDE

int main(void) {
	SetTargetFPS(120);
	srand(time(NULL));
	InitWindow(WIDTH, HEIGHT, "sand");
	float polje[2][ROWS][COLS] = { 0 };
	int curr = 1;
	float hue = 0;
	while(!WindowShouldClose()) {		
		curr = 1 - curr;
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				polje[1-curr][i][j] = 0;
			}
		}

		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {	
				if (polje[curr][i][j]) {
					if (i < ROWS - 1) {
						if (!polje[1-curr][i+1][j] && !polje[curr][i+1][j]) {
							polje[1-curr][i+1][j] = polje[curr][i][j];
						} else { // ne moze dole
							int r = rand()%2;
							if (r == 1) { //prvo livo
								if 		(j > 0 && 		!polje[curr][i+1][j-1]) polje[1-curr][i+1][j-1] = polje[curr][i][j];
								else if (j < COLS-1 &&	!polje[curr][i+1][j+1]) polje[1-curr][i+1][j+1] = polje[curr][i][j];
								else 	polje[1-curr][i][j] = polje[curr][i][j];
							} else { // prvo desno
								if 		(j < COLS-1 && 	!polje[curr][i+1][j+1]) polje[1-curr][i+1][j+1] = polje[curr][i][j];
								else if (j > 0 && 		!polje[curr][i+1][j-1]) polje[1-curr][i+1][j-1] = polje[curr][i][j];
								else 	polje[1-curr][i][j] = polje[curr][i][j];
							}
						}
					} else {
						polje[1-curr][i][j] = polje[curr][i][j];
					}
				}
			}
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 mouse = GetMousePosition();
			int rmi = mouse.y / (HEIGHT) * ROWS;
			int rmj = mouse.x / (WIDTH)  * COLS;	
			for (int di = -SPAWN_SIZE; di <= SPAWN_SIZE; di++) {
				for (int dj = -SPAWN_SIZE; dj <= SPAWN_SIZE; dj++) {
					int mi = di + rmi;
					int mj = dj + rmj;
					if (mi > ROWS - 1) mi = ROWS-1;
					if (mi < 0) mi = 0;
					if (mj > COLS - 1) mj = COLS-1;
					if (mj < 0) mj = 0;
					if (!polje[1-curr][mi][mj])
						polje[1-curr][mi][mj] = hue;
						hue += COLOR_CHANGE_SPEED;
				}
			}
			if (hue > 360) hue = hue-360;	
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			Vector2 mouse = GetMousePosition();
			int rmi = mouse.y / (HEIGHT) * ROWS;
			int rmj = mouse.x / (WIDTH)  * COLS;	
			for (int di = -SPAWN_SIZE; di <= SPAWN_SIZE; di++) {
				for (int dj = -SPAWN_SIZE; dj <= SPAWN_SIZE; dj++) {
					int mi = di + rmi;
					int mj = dj + rmj;
					if (mi > ROWS - 1) mi = ROWS-1;
					if (mi < 0) mi = 0;
					if (mj > COLS - 1) mj = COLS-1;
					if (mj < 0) mj = 0;
					if (polje[1-curr][mi][mj])
						polje[1-curr][mi][mj] = 0;
				}
			}
		}


		BeginDrawing();
			ClearBackground(BLACK);
			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS; j++) {
					if (polje[1-curr][i][j]) DrawRectangle(j*SQ_SIDE, i*SQ_SIDE, SQ_SIDE, SQ_SIDE, ColorFromHSV(polje[1-curr][i][j], 1, 1));
				}
			}
		EndDrawing();	
	}
	CloseWindow();
}
