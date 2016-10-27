/*https://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
   char *str;

   /* Initial memory allocation */
   str = (char *) malloc(10);
   strcpy(str, "original.");
   printf("String = %s\t Address = %u\n", str, str);

   /* Reallocating memory */
   str = (char *) realloc(str, 15);
   strcat(str, "new");
   printf("String = %s\t Address = %u\n", str, str);

   free(str);
   
   return(0);
}