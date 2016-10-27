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
	pair pairs[LEN];
	int term_freq;
}term_t;

typedef struct
{
	term_t *tree;
	int index_size;
	int pair_num;
	int N;
	//float doc_ave; //average docment length

}index_t;

typedef struct
{
	int len;//document length
	float score;
	float Ld;
	
}doc;

void free_and_reset(char **term){ //KEY POINT
	if(*term!=NULL){
		free(*term);
		*term = NULL; // "term = NULL" HAS NO IMPACT IN THIS FUNCTION IF ARGUMENT IS "char *term"
	}
	*term = (char *) malloc(2);
}

void read_pairs(FILE *fp, term_t *t, int* pair_num, int *N){
	int ch;
	char *term = (char *) malloc(2);
	char str[2]="";
	str[1]='\0';
	int flag = 1;
	int i = 1;
	int k = 0;
	while((ch=getc(fp))!=EOF){
		if((ch == ' ')||(ch == '\r')){
			i = 1;
			if(flag==1){
				t->pairs[k].doc_id = atoi(term);

				//update if necessary
				if(atoi(term)>*N){
					*N = atoi(term);
				}

				flag=2;
				free_and_reset(&term);
				
			}
			else{
				t->pairs[k].freq = atoi(term);
				//printf("pair read: <%d,%d>",t->pairs[k].doc_id, t->pairs[k].freq);
				k++;
				free_and_reset(&term);
				flag = 1;

				if(ch == '\r'){ //reading finish
					*pair_num += k;
					free(term);
					term = NULL;
					//printf("\n");
					break;
				}
			}
		}else{
			str[0] = ch;
			if(i>1){
				term = (char *) realloc(term, i);					
					strcat(term, str);
				}else{
					strcpy(term, str);
				}			
				
				i++;
		}
	}
}

//size of index will be returned
void read_data(FILE *fp, index_t *index){
	int ch, i=1;
	int j=0;
	char *term = (char *) malloc(i);
	char str[2]="";
	str[1]='\0';
	int is_term = 1;
	index->pair_num = 0;
	index->N = 0;

	while((ch=getc(fp))!=EOF){

		if(ch == ' '){

			i=1;
			if(is_term==1){				
				/*assert term*/
				index->tree = (term_t *) realloc(index->tree,sizeof(term_t)*(j+1));
				(index->tree)[j].str = (char *) malloc(i);

				strcpy((index->tree)[j].str, term);

				//printf("term found: %s\n", (*tree)[j].str);
								
				is_term = 2;
			}else if(is_term==2){
				//t,f
				(index->tree)[j].term_freq = atoi(term);

				//printf("freq:%d\n",tree[j].term_freq);

				read_pairs(fp, &((index->tree)[j]), &(index->pair_num), &(index->N));
				is_term = 1;

			}

			free_and_reset(&term);
			
		}else if(ch == '\n'){
				//new doc
				is_term = 1;
				j++;
			
		}else{	//form term
				str[0] = ch;
				if(i>1){
					term = (char *) realloc(term, i);					
					strcat(term, str);
				}else{
					strcpy(term, str);
				}							
				i++;			
		}
	}

	index->index_size = j;

}

void print_stage_one(index_t index){
	int i=0,j;
	printf("index has %d terms and %d (d,fdt) pairs\n", index.index_size, index.pair_num);
	for(i=0; i<index.index_size; i++){

		printf("term %d is \"%s\" \n", i, index.tree[i].str);
		for(j=0; j<index.tree[i].term_freq; j++){
			printf("<%d,%d> ", index.tree[i].pairs[j].doc_id, index.tree[i].pairs[j].freq);
		}
		printf("\n");
	}
}


int binary_search(term_t *tree, int l, int r, char* query){
  while (l <= r){
    int m = l + (r-l)/2;
 
    // Check if x is present at mid
    if (strcmp(tree[m].str, query)==0) 
        return m;  
 
    // If x greater, ignore left half  
    if (strcmp(tree[m].str, query)<0) 
        l = m + 1; 
 
    // If x is smaller, ignore right half 
    else
        r = m - 1; 
  }
 
  // if we reach here, then element was not present
  return -1; 
}


int mygetchar() {
	int c;
	while ((c=getchar())=='\r') {
		}
	return c;
}

void read_input(index_t index, int stage, doc array[]){
	char query[20][LEN];
	int i=0, j=0, k=0, d=0;
	int ch;
	int query_index;
	int f_dt, f_t;
	float L_d;
	int d_id;

	while((ch = mygetchar())!=EOF){
		if(ch == '\n'){
			//print out results
			query[j][i] = '\0';			
			
			for(k=0;k<=j;k++){
				query_index = binary_search(index.tree, 0, index.index_size-1, query[k]);
				if(stage == 2){
					printf("term %s is %d\n", query[k], query_index);				
				}else if(stage == 3){
					f_t = index.tree[query_index].term_freq;
					for (d=0; d < f_t; d++){

						f_dt = index.tree[query_index].pairs[d].freq;
						d_id = index.tree[query_index].pairs[d].doc_id - 1;
						L_d = array[d_id].Ld;
						

						printf("pair < %d, %d >\n",index.tree[query_index].pairs[d].doc_id, f_dt);
						printf("f_dt: %d  L_d: %f f_t: %d\n", f_dt, L_d, f_t);
						
						array[d_id].score += 
							((1+K)*f_dt*1.0/(L_d + f_dt)*log((index.N+0.5)*1.0/f_t)*1.0/log(2));
					}
					
				}
			}
			

			j=0;
			i=0;
			
		}else if(ch == ' '){
			query[j][i] = '\0';
			j++;
			i = 0;
		}else{
			query[j][i] = ch;
			i++;
		}
	}
}

void calc_doc_len(doc *array, index_t index){
	int i, j;
	int total_len=0;
	//reset to 0
	for(i=0; i<index.N; i++){
		array[i].len = 0;
		array[i].score = 0.0;
	}

	//calc doc len for all docs
	for(i=0; i<index.index_size; i++){
		//for each term
		for(j=0; j<index.tree[i].term_freq; j++){
			array[index.tree[i].pairs[j].doc_id-1].len += index.tree[i].pairs[j].freq;
			//calc average doc len
			total_len += index.tree[i].pairs[j].freq;
		}
	}
	float doc_ave = (total_len*1.0/index.N);
	printf("doc_ave: %f\n", doc_ave);
	//calc Ld for each doc
	for(i=0; i<index.N; i++){
		array[i].Ld = K*((1-B)+B*array[i].len/doc_ave);
	}
}

void read_query_and_rank(doc *array, index_t index){
	int i;
	read_input(index, 3, array);
	for(i=0; i<index.N; i++){
		printf("doc %d: %f\n", i, array[i].score);
	}
}

int
main(int argc, char *argv[]){
	
	FILE *fp;
	index_t index;
	//term_t *tree;


	int i;
	for(i=1;i<argc;i++){
    	if((fp = fopen(argv[i],"r"))==NULL){
     	    fprintf(stderr,"...........failed\n");	    
   		}else{
   			index.tree = (term_t *) malloc(sizeof(term_t));
 	  		read_data(fp, &index);
 	  		fclose(fp);
 	  		//stage one
 	  		print_stage_one(index);
 	  		printf("<< There are totally %d documents >>\n", index.N);
 	  		//stage two
 	  		//read_input(index);
 	  		
 	  		//stage three
 	  		doc doc_array[index.N];
 	  		calc_doc_len(doc_array, index);
 	  		read_query_and_rank(doc_array, index);
 	  		/*for(i=0; i<index.N; i++){
				printf("doc %d: %f\n",i, doc_array[i].Ld);
			}*/
			
    	}	 
 	} 
	return 0;

}






