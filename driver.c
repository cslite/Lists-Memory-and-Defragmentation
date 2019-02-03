#include<stdio.h>
#include<stdlib.h>
#include "list.h"

int *list_seq;
int lseq_size = 10;
int next_list_num;
int mem=160;

void allocate_ram(int size){
	set_ram(size);
	int last_idx = ((mem/3)-1)*3;
	list_seq = (int *)(calloc(lseq_size,sizeof(int)));
	int i;
	for(i=0;i<lseq_size;i++)
		list_seq[i] = -1;
	for(i=last_idx;i>=0;i-=3){
		push(i);
	}
	next_list_num = 0;
}

void inc_lseq_size(){	//doubles the size of list_seq
	list_seq = (int *)(realloc(list_seq,2*lseq_size*sizeof(int)));
	for(int i=lseq_size;i<(2*lseq_size);i++){
		list_seq[i] = -1;
	}
	lseq_size *= 2;
}

int get_head(int list_num){
	if(list_num < next_list_num){
		return list_seq[list_num];
	}
	else
		return -2;	//error code is -2
}

void set_head(int list_num, int head){
	list_seq[list_num] = head;
}

int main(){
	// printf("Enter the required Array Length (in terms of how many nodes, it can support): ");
	// scanf("%d",&mem);
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
		int lno,key,head,ct;
		switch(ch){
			case 1:
				if(next_list_num >= lseq_size)	//growable list_seq
					inc_lseq_size();
				printf("The sequence number of the newly created list is %d\n",next_list_num);
				printf("Enter key value to be inserted in the newly created list-%d:",next_list_num);
				scanf("%d",&key);
				head = newlist(key);
				if(head == -1){
					printf("FAILURE: MEMORY NOT AVAILABLE\n");
				}
				else{
					set_head(next_list_num,head);
					next_list_num++;
					printf("SUCCESS\n");
				}
				break;
			case 2:
				printf("List you want to insert in: ");
				scanf("%d",&lno);
				printf("Enter the key value: ");
				scanf("%d",&key);
				head = get_head(lno);
				if(head == -2){
					printf("FAILURE: NO SUCH LIST. (A list should exist before you can insert into it)\n");
				}
				else{
					head = insert(head,key);
					if(head==-1){
						printf("FAILURE: MEMORY NOT AVAILABLE\n");
					}
					else{
						set_head(lno,head);
						printf("SUCCESS\n");
					}
				}
				break;
			case 3:
				printf("List you want to delete from: ");
				scanf("%d",&lno);
				printf("Enter the key value: ");
				scanf("%d",&key);
				head = get_head(lno);
				if(head == -2){
					printf("FAILURE: NO SUCH LIST\n");
				}
				else{
					head = delete(head,key);
					if(head==-2){
						printf("FAILURE: ELEMENT NOT THERE / LIST EMPTY\n");
					}
					else{
						set_head(lno,head);
						printf("SUCCESS\n");
					}
				}
				break;
			case 4:
				ct = count_total(mem);
				printf("Total Number of nodes in all lists are %d\n",ct);
				break;
			case 5:
				printf("Enter the list number: ");
				scanf("%d",&lno);
				ct = count_nodes(get_head(lno));
				if(ct==-1)
					printf("FAILURE: Invalid List\n");
				else
					printf("Total Number of nodes in list %d are %d\n",lno,ct);
				break;
			case 6:
				if(next_list_num==0)
					printf("NO LISTS MADE SO FAR!");
				for(lno = 0; lno<next_list_num;lno++){
					printf("Elements of list-%d are:\n",lno);
					display(get_head(lno));	
				}
				printf("\n");
				break;
			case 7:
				displayFree();
				break;
			case 8:
				defrag(list_seq,next_list_num);
				printf("SUCCESS\n");
				break;
			default:
				printf("Invalid Choice\n");
				break;
		}
	}while(ch!=0);
return 0;
}
