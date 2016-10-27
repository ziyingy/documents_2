#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LEN 999

#define K 1.2
#define B 0.75

typedef struct
{
	int doc_id;
	int freq;
}pair;

typedef struct
{
	char *str;
	pair *pairs;
	int term_freq;
}term_t;

typedef struct
{
	term_t *terms;
	int index_size;
	int pair_num;
	int N;

}index_t;

typedef struct
{
	int len;//document length
	float score;
	float Ld;
	
}doc;


void read_pairs(FILE *fp, term_t *t, int *pair_num, int *N){
	int ch;
	char term[LEN];
	
	int flag = 1;
	int i = 0, k = 0;

	t->pairs = (pair *) malloc(sizeof(pair)*(t->term_freq));

	while((ch=getc(fp))!=EOF){
		if((ch == ' ')||(ch == '\r')){
			
			term[i] = '\0';
			
			if(flag==1){
				t->pairs[k].doc_id = atoi(term);

				//update if necessary
				if(atoi(term) > *N){
					*N = atoi(term);
				}

				flag=2;				
			}
			else{
				t->pairs[k].freq = atoi(term);
				printf("pair read: <%d,%d>\n", t->pairs[k].doc_id, t->pairs[k].freq);
				k++;

				flag = 1;

				if(ch == '\r'){ //reading finish
					
					*pair_num += k;

					break;
				}
			}
		i = 0;
		}else{
			/*form string*/
			term[i] = ch;									
			i++;
		}
	}
}

void read_data(FILE* fp, index_t *index){
	
	/* Recall: each term in the index will be at most 999 characters long */
	char term[LEN]; 
	int ch;

	int i = 0, j = 0;
	int flag = 1;

	while((ch = getc(fp)) != EOF){

		if(ch == ' '){
			/* add \0 to the end of the string */
			term[i] = '\0';
			
			if(flag == 1){	/* reading term string */			

				/* create memory for the new entry using realloc */
				index->terms = (term_t *) realloc(index->terms, sizeof(term_t)*(j+1));
				
				/* create memory for term string using malloc */
				(index->terms)[j].str = (char *) malloc(i);

				/*copy string *term to *str */
				strcpy((index->terms)[j].str, term);

				printf("term: %s  ", (index->terms)[j].str);
						
				flag = 2;

			}else if(flag == 2){ /* reading term frequency */
				
				(index->terms)[j].term_freq = atoi(term);

				printf("freq:%d\n",(index->terms)[j].term_freq);

				read_pairs(fp, &((index->terms)[j]), &(index->pair_num), &(index->N));
				
				flag = 1;
			}

			i = 0;
			
		}else if(ch == '\n'){
				/* new entry */
				flag = 1;
				j++; /* entry index +1 */
			
		}else{	
			    /*form string*/
				/*append ch to term[]*/
				term[i] = ch;									
				i++;			
		}
	}

	index->index_size = j;
		
}



int
main(int argc, char *argv[]){
	
	/* declare a file pointer */
	FILE *fp;
	/* declare a index */
	index_t index;

    if((fp = fopen(argv[1], "r")) != NULL){
     	
     	read_data(fp, &index); 
     	fclose(fp);   
   
   	}

   	printf("%d term(s) have been read\n", index.index_size);
   	printf("%d pair(s) have been read\n", index.pair_num);
   	printf("the largest document ID is %d\n", index.N);
 	
	return 0;

}






