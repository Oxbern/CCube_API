#include "connexion.h"
#include <stdio.h>

int main(int argc, char* argv[]) {

	uint8_t codop = 0x01;
	uint16_t size = 117;
	uint8_t data[size];
	int nb_buffer = getNumberOfBuffer(size);	
	buffer* l_buf; 

	for (uint8_t i = 0; i < size; i++)
		data[i] = i;

	//Encoding of data
	l_buf = data_encoding(codop, size, data);

	//Display
	for (int j = 0; j < nb_buffer; j++) {
		printf("BUFFER %d : \n", j+1);
		printf("Header : %x | ", l_buf[j][0]);
		printf("Codop : %x | ", l_buf[j][1]);
		printf("Size remaining : %d%d| ", l_buf[j][2], l_buf[j][3]);
		printf("Data : ");
		for (int k =4; k < BUFFER_MAX_INDEX-2; k++)
			printf("%d ", l_buf[j][k]);

		printf(" | CRC : %x%x", l_buf[j][BUFFER_MAX_INDEX-2], l_buf[j][BUFFER_MAX_INDEX-1]);
		printf("\n");
	}
}