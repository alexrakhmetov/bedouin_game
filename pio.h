#ifndef PIO_H
#define PIO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Takes input in "Chess Notation" and turns into an array index.
// Returns -1 for invalid inputs.
int8_t pinp(int8_t input)
{
	int8_t column = -1;
	int8_t row = -1;
	input = fgetc(stdin);
	switch (input) {
		case 'A':
			column = 0;
			break;
		case 'B':
			column = 1;
			break;
		case 'C':
			column = 2;
			break;
	}
	input = fgetc(stdin);
	switch (input) {
		case '1':
			row = 0;
			break;
		case '2':
			row = 1;
			break;
		case '3':
			row = 2;
			break;
	}

	// Clear out input buffer
	fgetc(stdin);
	if ((row == -1) || (column == -1)) input = -1;
	else input = ((3 * row) + column);
	return input;
}

void mov_pc(char* state, unsigned char* turn)
{
	char input = -1;
	char pc2mov = -1;
	char spc2mov = -1;

	puts("Piece to move:");
	pc2mov = pinp(input);
	if (pc2mov == -1) {
		fputs("Invalid input. "
		"Inputs must be in chess-style notation (i.e. A1)\n",
		stderr);
		return;
	}
	if (state[pc2mov] != (*turn + 1)) {
		fputs("This space is not occupied by the player!\n", 
		stderr);
		return;
	}

	puts("Space to move to:");
	spc2mov = pinp(input);
	if (spc2mov == -1) {
		fputs("Invalid input. "
		"Inputs must be in chess-style notation (i.e. A1)\n",
		stderr);
		return;
	}
	if (state[spc2mov] != 0) {
		fputs("This space is occupied!\n", stderr);
		return;
	}
	
	if ((spc2mov != 4) && (pc2mov != 4)) {
		switch (abs(pc2mov - spc2mov)) {
		case 1:
		case 3:
			break;
		default:
			fputs("The piece cannot reach this space!", stderr);
			return;
		}
	}

	state[pc2mov] = 0;
	state[spc2mov] = (*turn + 1);
	*turn ^= 1;
	return;
}
#endif // PIO_H
