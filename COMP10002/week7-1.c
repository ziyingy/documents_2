#include <stdio.h>
#include <string.h>

void print_string(char *str);

int
main(int argc, char *argv[]){
	
	//String => is a character array with 
	//			a terminating null character*/
	
	char string1[] = "array of char!";

	/* a '\0' will be automatically 
	   assigned to the end of the string*/

	/* Give a size ? 100? 10?*/

	string1[0] = 'A'; /* OK to modify single character */
	//string1 = "another string."; /* is NOT assignable */

	//strcpy(string1, "anothers");

	 //=> Array name is a constant pointer. 
	 //   You CANNOT change the location it points at. */

	print_string(string1);

	char *string2 = "pointer to a string!";
	string2 = "another string."; /*OK to assign new string literal*/
	
	/* => For pointer, you can change where it points at.*/

	// string2[0] = 'A'; /*Error! Can't modify*/

	/*Do not confuse with pointer to a single char*/
	//char letter = 'a';
	//char *char_pointer = &letter;
	//*char_pointer = 'b';

	print_string(string2);
	
	char string3[3] = {'a', 'b', 'c'}; /* bad example */	
	char string4[3+1] = {'a', 'b', 'c', '\0'}; /* good example */
	
	print_string(string4);
	


	//if("a string" == "a string") /* Error! */
	//if(strcmp(string3, string4)==0) /*Right way to compare strings*/
	
	//printf("String Compare: %d\n", strcmp("a string", "a string"));
	
	/* strcmp (str1, str2) returns 0 if str1 equals to str2 */
	
	return 0;
}

void print_string(char *str){
	/* method 1 */
	//printf("%s\n", str);

	/* method 2 */
	int i=0;
	while(str[i] != '\0'){
		printf("%c", str[i]);
		i++;
	}
	printf("\n");
}
