#include <stdio.h>
#include <string.h>

#define MAX 3
#define LEN 99

typedef struct node
{
	int id;
	char data[LEN];
	//node_t* next;
}node_t;

void read_node(node_t *node){
	printf("Enter the id:\n");
	scanf("%d", &(node->id));
	printf("Enter the data:\n");
	scanf("%s", node->data);

	printf(">> OK!\n");

}
void print_node_list(node_t *list, int node_num){
	int i = 0;
	printf("-----Print List-----\n");	

	while(i < node_num){
		printf("id: %-8d data: %s\n",(list+i)->id, list[i].data);
		i++;
	}

	printf("--------------------\n");
}


int main(){
	node_t list[MAX];
	int node_num = 0;
	int num = -1;

	while(num != 0){
		printf("-----Menu------\n");
		printf("1. Enter data\n");
		printf("2. Print list\n");
		printf("0. Quit\n");

		printf(">> Enter your choice: ");
		scanf("%d", &num);

		if(num == 1){
			if(node_num < MAX){
				read_node( &list[node_num] );
				node_num++;
			}else{
				printf(">> list is full! <<\n");
			}
		}
		if(num == 2){
			print_node_list(list, node_num);
		}
		if(num == 0){
			printf("See You :)\n");
		}
	}
	
	return 0;

}



