#include <stdio.h>

void print_1D_array(int A[], int size);
void print_2D_array(int size_x, int size_y, int B[][size_y]);
void print_2D_array2(int size_x, int size_y, int (*B)[size_y]);


int
main(int argc, char *argv[]){
	int A[5] = {1, 2, 4, 8, 16};

	//print_1D_array(A, 5);

	/*REVIEW: 	the name of an 1D array, (e.g. A), 
				returns the address of (a pointer that points to) 
				the first element of that array (e.g. &A[0])*/

	/*WHAT IS A: address of (pointer that points to) the first element, &A[0]
	          => address/pointer */

	/*WHAT IS *A: dereference of A, i.e. A[0]
	          => returns the value of the first element */

	//printf("A\t: %d\n*A\t: %d\n\n", (int)A, *A);

	
	/*WHAT IS (A+i): address, (A + i * size of an element), &A[i]
	          => address/pointer */

	/*WHAT IS *(A+i): dereference of (A+i), A[i]
	          => returns the value of the ith element (i=0, 1, ...)*/

	//printf("(A+0)\t: %d\n*(A+0)\t: %d\n\n", (int)(A+0), *(A+0)); 

	//printf("(A+2)\t: %d\n*(A+2)\t: %d\n\n", (int)(A+2), *(A+2));


	int B[2][3] = {{1, 2, 4}, {8, 16, 32}};
	
	
    /*WHAT IS *B / B[0]: address of (pointer to) 
    				   the first element, &B[0][0]
	          => address*/ 

	//printf("*B\t: %d\nB[0]\t: %d\n&B[0][0]: %d\n", (int)(*B), (int) B[0], (int)&B[0][0]);


	/*WHAT IS B: address of (pointer to) a 1D array (has 2 elements B[0] B[1])
				 of 3 integers arrays, &B[0]
	          => address of an address */
	/*        => B is same as &B[0], is same as &(&B[0][0]) which returns &B[0][0]*/

	//printf("B\t: %d\n&B[0]\t: %d\n", (int)B, (int) &B[0]);
	
	
	/*WHAT IS (B+i): address, (B + size of 3 integers * i), &B[i], same as &B[i][0]
	          => address/pointer */


	//print_2D_array(2, 3, B);
	//printf("(B+1) : %d\n", (int)(B+1));

	//print_2D_array2(2, 3, B);

	return 0;
}

void print_1D_array(int A[], int size){
	int i;

	printf("------------------------------\n");
	printf("A[i]:\t value \t address\n");
	printf("------------------------------\n");

	for(i = 0; i < size; i++){
		printf("A[%d]:\t %d \t %d\n", i, A[i], (int) &A[i]);
	}

	printf("------------------------------\n");

}

void print_2D_array(int size_x, int size_y, int B[][size_y]){ //The second and subsequent dimensions must be given:
	int i, j;

	printf("------------------------------\n");
	printf("[i][j]:\t value \t address\n");
	printf("------------------------------\n");

	for(i = 0; i < size_x; i++){
		for(j = 0; j < size_y; j++){
			printf("[%d][%d]:\t %d \t %u\n", i, j, B[i][j], (int) &B[i][j]);
		}		
	}
	printf("------------------------------\n");

}

void print_2D_array2(int size_x, int size_y, int (*B)[size_y]){
	int i, j;

	printf("------------------------------------------\n");
	printf("[i][j]:\t B[i][j]  *(B[i]+j)  *(*(B+i)+j))\n");
	printf("------------------------------------------\n");

	for(i = 0; i < size_x; i++){
		for(j = 0; j < size_y; j++){
			printf("[%d][%d]:\t %-7d  %-9d  %d\n", i, j, B[i][j], *(B[i]+j), *(*(B+i)+j));
		}		
	}
	printf("------------------------------------------\n");
}
