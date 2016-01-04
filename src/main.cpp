#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

int static const FLIP_INDEX = 0;
int static const FLOP_INDEX = 1;
int static const height = 80;
int static const width = 127;

static uint8_t board[2][height][width] = { 0 };

int countneighbors(int c, int h, int w) {
	int count = 0;

	// 1 2 3
	// 4 ! 5
	// 6 7 8

	for (int y = -1; y < 2; ++y) {
		for (int x = -1; x < 2; ++x) {
			if (h + y < 0 || w + x < 0 || h + y >= height || w + x >= width) {
				continue;
			}

			if (y == 0 && x == 0) {
				continue;
			}

			if (board[c][h + y][w + x] == 1) {
				++count;
			}
		}
	}
	
	return count;
}

int main() {
	int currentIndex = FLIP_INDEX;

	// Block
	/*board[FLIP_INDEX][1][1] = 1;
	board[FLIP_INDEX][1][2] = 1;
	board[FLIP_INDEX][2][1] = 1;

	board[FLIP_INDEX][6][2] = 1;
	board[FLIP_INDEX][6][3] = 1;
	board[FLIP_INDEX][6][4] = 1;
	board[FLIP_INDEX][7][2] = 1;

	// Blinker
	board[FLIP_INDEX][1][6] = 1;
	board[FLIP_INDEX][2][6] = 1;
	board[FLIP_INDEX][3][6] = 1;*/

	//R-pentomino
	board[FLIP_INDEX][height / 2 - 1][width / 2] = 1;
	board[FLIP_INDEX][height / 2][width / 2] = 1;
	board[FLIP_INDEX][height / 2 + 1][width / 2] = 1;
	board[FLIP_INDEX][height / 2 - 1][width / 2 + 1] = 1;
	board[FLIP_INDEX][height / 2][width / 2 - 1] = 1;


	for (uint64_t generation = 0;; ++generation) {
		int nextIndex = (currentIndex == FLIP_INDEX ? FLOP_INDEX : FLIP_INDEX);
		ZeroMemory(board[nextIndex], height*width);

		COORD coords = { 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);

		for (int h = 0; h < height; ++h) {
			for (int w = 0; w < width; ++w) {
				int liveNeighbors = countneighbors(currentIndex, h, w);
				boolean isLiving = board[currentIndex][h][w];
				if (!isLiving && liveNeighbors == 3) {
					board[nextIndex][h][w] = 1;
				}
				else if (isLiving && (liveNeighbors == 2 || liveNeighbors == 3)) {
					board[nextIndex][h][w] = 1;
				}
				else {
					board[nextIndex][h][w] = 0;
				}
				printf("%c", isLiving ? '+' : ' ');
			}
			printf("\n");
		}

		currentIndex = nextIndex;

		printf("Generation: %d", generation);
		//Sleep(1);		
	}
	
	return 0;
}
