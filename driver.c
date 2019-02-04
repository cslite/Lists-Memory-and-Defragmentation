// driver.c for DSA Assignment


#include<stdio.h>
#include<stdlib.h>
#include "list.h"


int mem=160;	//Size of the RAM (RAM can support at max mem/3 nodes) 
				//[You can change mem to change the size of ram]


int main(int argc, char *argv[]){
	// printf("Enter the required Array Length (in terms of how many nodes, it can support): ");
	// scanf("%d",&mem);
	if(argc==2)
		mem = atoi(argv[1]) * 3;
	allocate_ram(mem);

	int ch;	//ch is for choice
	do{
		printf("\nMENU\n");
		printf("1. Create a new list\n");
		printf("2. Insert a new element in a given list in sorted order\n");
		printf("3. Delete an element from a given list\n");
		printf("4. Count total elements excluding free list\n");
		printf("5. Count total elements of a list\n");
		printf("6. Display all lists\n");
		printf("7. Display free list\n");
		printf("8. Perform Defragmentation\n");
		printf("0. Press 0 to Exit\n");
		printf("Select an option: ");

		scanf("%d",&ch);
		int lno,key,head,ct,r;
		switch(ch){
			case 1:
				printf("The sequence number of the newly created list is %d\n",get_next_lno());
				printf("Enter key value to be inserted in the newly created list-%d:",get_next_lno());
				scanf("%d",&key);
				if(createlist(key)==-1)
					printf("FAILURE: MEMORY NOT AVAILABLE\n");
				else
					printf("SUCCESS\n");
				break;
			case 2:
				printf("List you want to insert in: ");
				scanf("%d",&lno);
				printf("Enter the key value: ");
				scanf("%d",&key);
				r = insert(lno,key);
				if(r==-2)
					printf("FAILURE: NO SUCH LIST. (A list should exist before you can insert into it)\n");
				else if(r==-1)
					printf("FAILURE: MEMORY NOT AVAILABLE\n");
				else
					printf("SUCCESS\n");
				break;
			case 3:
				printf("List you want to delete from: ");
				scanf("%d",&lno);
				printf("Enter the key value: ");
				scanf("%d",&key);
				r = delete(lno,key);
				if(r==-2)
					printf("FAILURE: NO SUCH LIST\n");
				else if(r==-1)
					printf("FAILURE: ELEMENT NOT THERE / LIST EMPTY\n");
				else
					printf("SUCCESS\n");
				break;
			case 4:
				ct = count_total(mem);
				printf("Total Number of nodes in all lists are %d\n",ct);
				break;
			case 5:
				printf("Enter the list number: ");
				scanf("%d",&lno);
				ct = count_nodes_lno(lno);
				if(ct==-1)
					printf("FAILURE: Invalid List\n");
				else
					printf("Total Number of nodes in list %d are %d\n",lno,ct);
				break;
			case 6:
				displayAll();
				break;
			case 7:
				displayFree();
				break;
			case 8:
				defrag();
				printf("SUCCESS\n");
				break;
			case 0:
				break;
			default:
				printf("Invalid Choice\n");
				break;
		}
	}while(ch!=0);
return 0;
}
