#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROW 1000
#define MAX_COL 30
#define MAX_CHAR 50

int mygetchar();
int read_head(char head[MAX_COL][MAX_CHAR]);
int read_data(char data[MAX_ROW][MAX_COL][MAX_CHAR]);
void print_stage_one(char data[MAX_ROW][MAX_COL][MAX_CHAR], 
	char head[MAX_COL][MAX_CHAR], int row_num, int col_num);
void print_stage_two(char data[MAX_ROW][MAX_COL][MAX_CHAR], 
	char head[MAX_COL][MAX_CHAR], int row_num, int col_num);

void print_all(char data[MAX_ROW][MAX_COL][MAX_CHAR], 
	char head[MAX_COL][MAX_CHAR], int row_num, int col_num);

void sort_data(char data[MAX_ROW][MAX_COL][MAX_CHAR], 
	int sort_keys[], int row_num, int col_num);

void swap_str(char **t1, char **t2);
void swap_str2(char *str1, char *str2);

void print_stage_three(char data[MAX_ROW][MAX_COL][MAX_CHAR], 
	char head[MAX_COL][MAX_CHAR], int row_num, int col_num, int sort_keys[]);

int sorted_keys(char (*val1)[MAX_CHAR], char (*val2)[MAX_CHAR], int keys[], int k);

int
main(int argc, char *argv[]){
	//int sort1 = *argv[1]-49;
	//int sort2 = *argv[2]-49;

	char data[MAX_ROW][MAX_COL][MAX_CHAR];
	char head[MAX_COL][MAX_CHAR];

	int col_num = read_head(head);
	int row_num = read_data(data);

	int sort_keys[col_num], i;
	//printf("argc : %d\n", argc);
	for (i = 0; i < (argc-1); i++){
		sort_keys[i] = *argv[i+1]-49;
		printf("sort key: %d\n", sort_keys[i]);
	}
	for (; i<col_num ; i++){
		sort_keys[i] = -1;
		printf("sort key: %d\n", sort_keys[i]);
	}

	print_stage_one(data, head, row_num, col_num);
	//print_all(data, head, row_num, col_num);
	//printf("=======================\n");
	sort_data(data, sort_keys, row_num, col_num);
	print_all(data, head, row_num, col_num);
	print_stage_three(data, head, row_num, col_num, sort_keys);

	return 0;

}

int
mygetchar() {
	int c;
	while ((c=getchar())=='\r') {
	}
	return c;
}

int read_head(char head[MAX_COL][MAX_CHAR]){
	int ch;
	int col_num = 0, i = 0;

	while((ch=mygetchar())!='\n'){
		if(ch == '\t'){
			col_num++;
			i = 0;
		}else{
			head[col_num][i]=ch;
			i++;
		}
	}
	return col_num+1;

}

int read_data(char data[MAX_ROW][MAX_COL][MAX_CHAR]){
	int ch;
	int row_num = 0, col_num = 0, i = 0;

	while((ch=mygetchar())!=EOF){
		if(ch == '\t'){
			col_num++;
			i = 0;
		}else if (ch == '\n'){
			row_num++;
			i = 0;
			col_num = 0;
		}else{
			data[row_num][col_num][i]=ch;
			i++;
		}
	}
	return row_num;

}

void print_stage_one(char data[MAX_ROW][MAX_COL][MAX_CHAR], 
	char head[MAX_COL][MAX_CHAR], int row_num, int col_num){
	
	int i;
	printf("input tsv data has %d rows and %d colums\n", row_num, col_num);
	printf("row %d is:\n", row_num);
	for(i = 0; i < col_num; i++){
		printf("%4d: %s\t%s\n", (i+1), head[i], data[row_num-1][i]);
	}

}

void sort_data(char data[MAX_ROW][MAX_COL][MAX_CHAR], 
	int sort_keys[], int row_num, int col_num){
	int i, j, z, k, min_index;
	//first sort key
	for(k = 0; sort_keys[k]>(-1); k++){
		for (i=0; i<row_num; i++){
			min_index = i;
			for(j=i+1; (j<row_num)&&sorted_keys(data[i], data[j], sort_keys, k); j++){
				if(strcmp(data[min_index][sort_keys[k]], data[j][sort_keys[k]])>0){				
					min_index = j;
				}
			}
			if (min_index != i){
				for(z=0;z<col_num;z++){
					swap_str2(data[i][z], data[min_index][z]);
				}
			}
		}
	}

	/*for (i=0; i<row_num; i++){
		min_index = i;
		for(j=i+1; (j<row_num)&&sorted_keys(data[i], data[j], sort1); j++){
			if(strcmp(data[min_index][sort2], data[j][sort2])>0){				
				min_index = j;
			}
		}
		if (min_index != i){
			for(z=0;z<col_num;z++){
				swap_str2(data[i][z], data[min_index][z]);
			}
		}
	}*/

}

int sorted_keys(char (*val1)[MAX_CHAR], char (*val2)[MAX_CHAR], int keys[], int k){
	if(k==0){
		return 1;
	}

	for(k=k-1;k>=0;k--){
		if(strcmp(val1[keys[k]], val2[keys[k]])!=0){
			return 0;
		}
	}

	return 1;
}

void swap_str(char **t1, char **t2)
{
    char *t;

    t = *t1;
    *t1= *t2;
    *t2 = t;
}

void swap_str2(char *str1, char *str2){
  //char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
  char temp[MAX_CHAR];
  strcpy(temp, str1);
  strcpy(str1, str2);
  strcpy(str2, temp);
  //free(temp);
}


void print_stage_two(char data[MAX_ROW][MAX_COL][MAX_CHAR], 
	char head[MAX_COL][MAX_CHAR], int row_num, int col_num){
	
	int i, r;
	printf("row 1 is:\n");
	for(i = 0; i < col_num; i++){
		printf("%4d: %s\t%s\n", (i+1), head[i], data[0][i]);
	}

	if(row_num%2==0){
		r = row_num/2;
	}else{
		r = row_num/2+1;
	}
	printf("row %d is:\n", r);
	for(i = 0; i < col_num; i++){
		
		printf("%4d: %s\t%s\n", (i+1), head[i], data[r-1][i]);
	}

	printf("row %d is:\n", row_num);
	for(i = 0; i < col_num; i++){
		printf("%4d: %s\t%s\n", (i+1), head[i], data[row_num-1][i]);
	}

}

void print_all(char data[MAX_ROW][MAX_COL][MAX_CHAR], 
	char head[MAX_COL][MAX_CHAR], int row_num, int col_num){
	
	int i, j;
	for(j=0;j<col_num;j++){
		printf("%s\t", head[j]);
	}
	printf("\n");
	for(j=0;j<row_num;j++){
		for(i = 0; i < col_num; i++){
			printf("%s\t", data[j][i]);
		}
		printf("\n");
	}


}

void print_stage_three(char data[MAX_ROW][MAX_COL][MAX_CHAR], 
	char head[MAX_COL][MAX_CHAR], int row_num, int col_num, int sort_keys[]){
	
	int i, j, k, count=0;
	for(k=0;sort_keys[k]>(-1);k++){
		for(i=0;i<k;i++){
			printf("\t");
		}
		printf("%s\n", head[sort_keys[k]]);
	}

	
	int z;
	k=0;
	i=0;
		while((sort_keys[k]>(-1))&&(i < row_num)){
			for(z=0;z<k;z++){
				printf("    ");
			}
			if(sort_keys[k+1]>(-1)){
				printf("%s\n", data[i][sort_keys[k]]);
				k++;
				continue;
			}else if(sort_keys[k+1]==(-1)){
				//count
				for(j = i; sorted_keys(data[i], data[j], sort_keys, k+1); j++){					
						count++;										
				}
				//print this level
				printf("%s\t%-5d\n",data[i][sort_keys[k]],count);
				count = 0;

				//check go back steps
				while(!sorted_keys(data[i], data[j], sort_keys, k)){
					k--;
				}
				i=j;
			}

			
		}

}

