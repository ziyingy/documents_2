#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* string_dupe(char *s){
	int orig_str_size = 0;
	char *s_pt=s;
    char* bkup_copy = NULL;

    while (*s_pt++ != '\0')
        orig_str_size++;        

    printf("Size of the original string: %d\n", orig_str_size);

    bkup_copy = (char*) malloc((orig_str_size+1) * sizeof(char));

    strcpy(bkup_copy,s);
    return bkup_copy;

}

char** string_set_dupe(char **S){
	char** bkup_copy_pt = (char **)malloc(sizeof(char*)*10); 
	//char** bkup_copy_pt = bkup_copy;
	int i=0;
	*S++;

	while(*S) {
		//bkup_copy[i] = string_dupe(*bkup_copy_pt+1)
		//printf("%s\n", *S);
		*(bkup_copy_pt+i) = string_dupe(*S);

		//printf("%s\n", *(bkup_copy_pt+i));
		//bkup_copy++;
		S++;
		i++;
	}
	*(bkup_copy_pt+i) = NULL;
	return bkup_copy_pt;
}
void string_set_free(char **S){
	int i=0;

	//for(i=0; *(S+i);i++){
		//printf(">>>>%p\n", *(S+i));	
		//printf(">>>>%s\n", *(S+i));	
		//a_set++;	

	//}

	while(i<10){
		printf("%p\n", S[i]);
		free(S[i]);
		i++;
	}
	printf("%p\n", S);
	free(S);
	

		//free(*(S+0));	
	//free(S);
	

}
int main(int argc, char **argv){
	char** a_set = string_set_dupe(argv);
	
	//printf(">>%s\n", *(a_set+4));
	int j,i=0;
	for(i=0; *(a_set+i);i++){
		printf("%d\n", i);
		//printf(">>>>%lu\n", strlen(*(a_set+i)));		
		//a_set++;	

	}
	for(j=0;j<10;j++){
		printf(">>%p\n", *(a_set+j));
	}
	//int **ptr = (int **)malloc(sizeof(int*)*10); 
	//for(int i=0;i<10;i++) 
    // 	ptr[i]=(int*)malloc(sizeof(int)*10);
	string_set_free(a_set);
	//string_set_free(a_set);
	//printf("%s\n", *(argv));
	return 0;
	
}