
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int change_value1(){
	int b = 1;
	return b;
}

void change_value2(int *a){
	//a = malloc(sizeof(int));
	*a = 1;
}

int* change_value3(int *a){
	a = malloc(sizeof(int));
	*a = 1;
	return a;
}

void change_value4(int **a){
	*a = malloc(sizeof(int));
	**a = 1;
}

int main(){
	int a=0;
	
	//a = change_value1();

	change_value2( &a );

	printf("a: %d\n", a);

	int *aa = NULL;

	//aa = change_value1(); /* no */
	//change_value2(aa); /* no */
	//aa = change_value3(aa);
	change_value4(&aa);
	printf("aa: %d\n", *aa);


	return 0;
}