#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define EEPROM_ARGUMENT 2
#define RDWR_ARGUMENT 3
#define MINIMAL_ARGUMENT 4
#define OFFSET_ARGUMENT 4

#define EEPROM_FN "/sys/devices/platform/bus@100000/bus@100000:bus@28380000/42120000.i2c/i2c-1/1-0050/eeprom"

void read_eeprom(int fd, uint16_t offset, unsigned long read_count) {
	char *buff = (char*) malloc(read_count * sizeof(char));
	if (pread(fd, buff, read_count, offset) != read_count) {
		printf("Error: could not read data from device\n");
		close(fd);
		exit(-1);
	}
	printf("Data read: ");
	for (int i = 0; i < read_count; i++) {
		printf("%02x ", buff[i]);
	}
	printf("\n");
	close(fd);
	free(buff);
	exit(0);
}

void write_eeprom(int fd, uint16_t offset, const char* write_word) {
	if (pwrite(fd, write_word, strlen(write_word),offset) != strlen(write_word)) {
		printf("Error: could not write data to device\n");
		exit(-1);
	}
	close(fd);
	exit(0);
}

int main(int argc, char* argv[]) {
	unsigned long read_count;
	const char *mode = argv[1];
	const char *write_word = argv[RDWR_ARGUMENT];
	const char *eeprom;
	uint16_t offset = 0x00;
	int fd;

	if (argc < MINIMAL_ARGUMENT) goto usage;
	if (argv[OFFSET_ARGUMENT])
		offset = strtoul(argv[OFFSET_ARGUMENT], NULL, 0);

	if (!strcmp(argv[EEPROM_ARGUMENT], "at24"))
		eeprom = EEPROM_FN;
	else goto usage;

	if (!strcmp(mode, "read")) {
		read_count = strtoul(argv[RDWR_ARGUMENT], NULL, 0);
		fd = open(eeprom, O_RDONLY);
		if (fd < 0) 
			goto open_error;
		read_eeprom(fd, offset, read_count);
	}

	else if (!strcmp(mode, "write")) {
		fd = open(eeprom, O_WRONLY);
		if (fd < 0) goto open_error;
		write_eeprom(fd, offset, write_word);
	}
	else goto usage;

	return 0;

usage:
	printf("[read/write] [eeprom] [bytes to read/word to write] optional:[offset]\nSupported eeprom: at24");
	return -1;

open_error:
	printf("Error: could not open device file %s\n", eeprom);
	return -1;
}
