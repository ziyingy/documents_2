#include <stdio.h>

#define ASCI_0 48

int
main(int argc, char *argv[]){

	int a_int = *argv[1] - ASCI_0;
	char a_char = *argv[2];
	
	printf("File: %s ", argv[0]);
	printf("received %d arguments\n", argc);
	printf("first: %d\n", a_int);
	printf("second: %c\n", a_char);

	return 0;
}