#include "adamacc.h"
#include <stdio.h>
#include <stdlib.h>

unsigned char inputSelect[8] = { 0, 1, 0, 1, 0, 1, 0, 1 };
unsigned char inputData[16] = {
	0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
	0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
};
unsigned char expectedData[8] = {
	0x00, 0x99, 0x22, 0xbb, 0x44, 0xdd, 0x66, 0xff
};
unsigned char outputData[8];

void checkEqualInt(int expected, int actual)
{
	if (expected == actual)
		return;
	printf("Expected %d, got %d\n", expected, actual);
	exit(EXIT_FAILURE);
}

int main(void)
{
	braid_set_select_addr(inputSelect);
	braid_set_input_addr(0, inputData);
	braid_set_input_addr(1, inputData + 8);
	braid_set_output_addr(outputData);
	braid_start(8, SIZE_8);
	asm volatile ("fence");

	for (int i = 0; i < 8; i++) {
		checkEqualInt(expectedData[i], outputData[i]);
	}

	return 0;
}
