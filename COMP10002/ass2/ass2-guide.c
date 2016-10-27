/*http://people.eng.unimelb.edu.au/ammoffat/teaching/10002/ass2/*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LEN 999

void read_pairs(FILE *fp, entry *e, int *pair_num, int *N, ...){
	int ch;
	char term[LEN];

	/* malooc memory for pairs */
	/* the number of pairs can be known by e->ft */
	e->pairs = (...) malloc([SIZE]);
	
	while((ch=getc(fp))!=EOF){
		/* read pairs */
	}
}

void read_data(FILE* fp, index_t *index, ...){
	
	/* Recall: each term in the index will be at most 999 characters long */
	char term[LEN]; 
	int ch;

	while((ch = getc(fp)) != EOF){

		if(ch == ' '){
			
			/* add \0 to the end of the string term[] */		
			
			if(/* it is the first space in this line */){	

				index->index_size++; /* entry index +1 */			

				/* 1. realloc memory for the new ENTRY using realloc */
			    /*    the new size is: index->index_size */
				index->entries = (...)realloc(index->entries, ...)
				
				/* 2. malloc memory for entry str using malloc */
				/*    the size is? */
				(index->entries)[...].str = (char *)malloc(...)
				/* or define char str[999] in struct of entry */

				/* 3. copy string *term to *str */
				strcpy(..., term);


			}else{ /* reading term frequency */
				
				(index->terms)[...].ft = atoi(term);
				
				read_pairs(fp, &((index->terms)[j]), &(index->pair_num), &(index->N));

				/* data for this entry finish, next line*/
				
			}

			/*do reseting, if necessary*/
			
		}else if(ch == '\n'){ 
				
			/* */	 
			
		}else{	
			  /*form string by appending ch to term[]*/												
		}
	}
		
}

int main(int argc, char *argv[]){
	
	/* declare a file pointer */
	FILE *fp;
	/* declare a index */
	index_t index;

    if((fp = fopen(argv[..], "r")) != NULL){

     	index.entries = (entry *) malloc(sizeof(entry)*1);
     	
     	read_data(fp, &index); 
     	fclose(fp);   
   
   	}

   	printf("%d term(s) have been read\n", index.index_size);
   	printf("%d pair(s) have been read\n", index.pair_num);
   	printf("the largest document ID is %d\n", index.N);
 	
	return 0;

}






