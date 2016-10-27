#include <stdio.h>
#include <string.h>

#define MAX_COL 5
#define MAX_CHAR 11

void print_header(char header[MAX_COL][MAX_CHAR], int col_num);
int read_header_scanf(char header[MAX_COL][MAX_CHAR]);
int read_header_getchar(char header[MAX_COL][MAX_CHAR]);
int mygetchar();

int
main(int argc, char *argv[]){

	/* READ AND PRINT STRING */

	//char string[] = "a string"; /*can be changed using scanf*/
	//char *string = "a string too"; /*cannot be changed using scanf*/
	
	//printf("Enter a new string:\n");
	//scanf("%s", string);
	//printf("new string: %s\n", string);


	char header[MAX_COL][MAX_CHAR];
	int col_num;

	col_num = read_header_scanf(header);
	//col_num = read_header_getchar(header);
	print_header(header, col_num);

	return 0;
}



int read_header_scanf(char header[MAX_COL][MAX_CHAR]){
	int col_num = 0;
	//scanf() delimiter: \n, \t, space...*/
	/*scanf() automatically appends '\0' to the end of the string */

	while(scanf("%s", header[col_num])==1){
		col_num++;
	}
	return col_num;
}

int read_header_getchar(char header[MAX_COL][MAX_CHAR]){
	int col_num = 0, i = 0;
	int ch;

	/*getchar() read character one by one...*/
	while((ch = getchar()) != EOF){
		if(ch == '\t'){
			header[col_num][i] = '\0';
			col_num++;
			i = 0;
		}else if (ch == '\n'){
			header[col_num][i] = '\0';			
			col_num++;
			i = 0;
		}else if (ch == '\r'){

			//do nothing
		}
		else{
			header[col_num][i] = ch;
			i++;
		}

	}
	return col_num;
}

int mygetchar() {
	int c;
	while ((c=getchar())=='\r') {
	}
	return c;
}

void print_header(char header[MAX_COL][MAX_CHAR], int col_num){
	int i=0;
	printf("----------HEADER----------\n");
	while(i < col_num){
		
		/* method 1 */
		printf("%s\n", header[i]);
		

		i++;
	}
}