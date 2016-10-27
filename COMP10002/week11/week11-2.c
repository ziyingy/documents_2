#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define MAX 3

typedef struct node node_t;
/* >> why we need typedef before the struct? */

struct node
{
	int id;
	char data[99];
	node_t *next;
};

node_t* read_node(node_t *list){
	
	node_t *new_node = (node_t*)malloc(sizeof(node_t));
	
	/*why it cannot be: node_t new_node */
	
	printf("Enter the id:\n");
	scanf("%d", &new_node->id);
	printf("Enter the data:\n");
	scanf("%s", new_node->data);

	printf(">> OK!\n");

	new_node->next = list;
	/* assign what the *list points to, to the *next of the new node */
	
	list = new_node;
	/* let the *list point to the new node */

	free(new_node);

	return list;

}




void print_node_list(node_t *list){
	printf("-----Print List-----\n");
	
	node_t* node_pt = list;
	/* point to the head of the list */
	
	while(node_pt != NULL){
		printf("id: %-8d data: %s\n",node_pt->id, node_pt->data);
		
		node_pt = node_pt->next;
		/* move to the next node*/
	}

	printf("--------------------\n");
}
int main(){
	
	node_t *list = NULL;
	
	/*we do not need to record node number anymore*/
	//int node_num = 0; 
	
	int num = -1;

	while(num != 0){
		printf("-----Menu------\n");
		printf("1. Enter data\n");
		printf("2. Print list\n");
		printf("0. Quit\n");

		printf(">> Enter your choice: ");
		scanf("%d", &num);

		if(num == 1){			
			list = read_node(list);				
		}
		if(num == 2){
			print_node_list(list);
		}
		if(num == 0){
			printf("See You :)\n");
		}
	}
	
	return 0;
	
}



