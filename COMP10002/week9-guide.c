
/*Exercise 4
Write a function char* string_dupe(char *s) that creates
a copy of the string s and returns a pointer to it.*/

char* string_dupe(char *s){
    
    char* bkup = NULL; 

    int org_str_size = 0;      

    /*Get the size of the original string => org_str_size*/

    bkup = (char*) malloc((orig_str_size + 1) * sizeof(char));

    /* copy s to bkup_copy */
    
    return bkup;

}

/*Exercise 5
Write a function char **string set dupe(char **S) that
creates a copy of the set of string pointers S, assumed to
have the structure of the set of strings in argv (including a
sentinel pointer of NULL), and returns a pointer to the copy.*/
char** string_set_dupe(char **S){

	/*Find the SIZE/length of **S */

	char** bkup_set = (char **) malloc (sizeof(char*) * SIZE); 
	
	int i=0;

	/*Loop:
	     call string_dupe() for each string, S[i],
	     assign the returned pointer to bkup_set[i]*/
	
	
	/* assign NULL to the pointer after the last string */
	
	return bkup_copy_pt;
}


void string_set_free(char **S){

	/*free all the element of S, i.e S[i]*/
	
	/*then free S*/	

}


int main(int argc, char **argv){
	char** a_set = string_set_dupe(argv);

	string_set_free(a_set);

	return 0;
	
}