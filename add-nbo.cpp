#include <stddef.h>		// for size_t
#include <stdint.h>		// for uint8_t
#include <stdio.h>		// for printf
#include <netinet/in.h> // for ntohl()
#include <fstream>		// for open()
#include <stdlib.h>		// for exit()

uint32_t read_file_to_number(const char *file)
{
	FILE *bin;
	bin = fopen(file, "rb");
	if (bin == NULL)
	{
		printf("invalid input value...\n");
		exit(-1);
	}

	uint8_t network_buffer[4];
	fread(network_buffer, 1, sizeof(uint32_t), bin);
	uint32_t *p = reinterpret_cast<uint32_t *>(network_buffer);
	uint32_t operand = ntohl(*p);

	fclose(bin);

	return operand;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("invalid use... Please use the method below.\n");
		printf("./add-nbo <first_file> <second_file>\n");
		exit(-1);
	}

	uint32_t first = read_file_to_number(argv[1]);
	uint32_t second = read_file_to_number(argv[2]);

	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", int(first), first, int(second), second, int(first + second), first + second);
	return 0;
}
