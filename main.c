#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "pio.h"

#define TURN1 0
#define TURN2 1

int main()
{
	/* 
	 * There are three states for any given cell, which prevents us 
	 * from using a bitmask and saving space. Even if it was a 
	 * binary state, we would have to use uint16_t because we have 
	 * 9 cells, which would make savings minimal.
	 */
	uint8_t state[] = {1, 1, 1,
			   0, 0, 0,
			   2, 2, 2};
	uint8_t turn = TURN1;
	while(1) {
		printf("%d,%d,%d,\n%d,%d,%d,\n%d,%d,%d\n"
		"Player %d to move.\n", state[0], state[1], state[2], 
		state[3], state[4], state[5], state[6], state[7],
		state[8], (turn + 1));
		mov_pc(state, &turn);
		// Win conditions
		if ((state[4] != 0) && 
		(((state[3] == state[4]) && (state[4] == state[5])) || 
		((state [0] == state[4]) && (state[4] == state[8]))) || 
		((state[2] == state[4]) && (state[4] == state[6]))) {
			printf("Player %d wins!\n", turn);
			break;
		}
	}
	return 0;
}
