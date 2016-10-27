#include <stdio.h>
#include <string.h>

struct person
{
	int ID;
	char name[50];
	char email[50];
	float grade;
};
void print_info(struct person stu);
int main(int argc, char *argv[]){

	struct person alicia;

	alicia.ID = 1001;
	//jack.ID = 1002
	//alicia.name = "alicia";
	strcpy(alicia.name, "alicia");
	printf("email:\n");
	scanf("%s", alicia.email);
	printf("grade:\n");
	scanf("%f", &alicia.grade);

	print_info(alicia);

	return 0;
}

void print_info(struct person stu){
	printf("ID: %d\n",stu.ID);
	printf("name: %s\n",stu.name);
	printf("email: %s\n",stu.email);
	printf("grade: %.1f\n",stu.grade);

}






