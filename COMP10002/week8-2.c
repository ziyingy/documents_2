#include <stdio.h>
#include <string.h>

typedef struct name
{
	char first_name[20];
	char last_name[20];
}full_name;

typedef struct person
{
	int ID;
	full_name name;
	char email[50];
	float grade;
}student;

void print_info(struct person stu);
void get_info(student *stu);

int main(int argc, char *argv[]){

	student alicia;

	get_info(&alicia);

	print_info(alicia);

	return 0;
}

void print_info(struct person stu){
	printf("ID: %d\n",stu.ID);
	printf("name: %s\n",stu.name.first_name);
	printf("email: %s\n",stu.email);
	printf("grade: %.1f\n",stu.grade);

}

void get_info(student *stu){
	stu->ID = 1001;

	strcpy(stu->name.first_name, "alicia");
	printf("email:\n");
	scanf("%s", stu->email);
	printf("grade:\n");
	scanf("%f", &stu->grade);
}






