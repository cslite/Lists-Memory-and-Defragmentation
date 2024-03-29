#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <limits.h>

int free_list = -1;
int *ram;
int ram_size;
int *list_seq;	//array containing heads of the created lists.
int lseq_size = 10;	//Max amount of list which the program can support (this will dynamically grow)
int next_list_num;

void inc_lseq_size(){	//doubles the size of list_seq (to dynamically increase the max no. of lists supported)
	list_seq = (int *)(realloc(list_seq,2*lseq_size*sizeof(int)));
	for(int i=lseq_size;i<(2*lseq_size);i++){
		list_seq[i] = -1;
	}
	lseq_size *= 2;
}

int get_head(int list_num){		//function to get the head of given list
	if(0 <= list_num && list_num < next_list_num){
		return list_seq[list_num];
	}
	else
		return -2;	//error code is -2
}

void set_head(int list_num, int head){		//function to set the head of the given list as given head
	if(list_num >= lseq_size)	//growable list_seq
		inc_lseq_size();
	list_seq[list_num] = head;
}

int get_next_lno(){
	return next_list_num;
}



int get_next(int node){		//get the address of next node
	if(node!=-1)
		return ram[node+1];
	else
		return -1;
}
int get_prev(int node){		//get the address of previous node
	if(node!=-1)
		return ram[node+2];
	else
		return -1;
}
int get_key(int node){		//get the key stored in node
		return ram[node];
}
void set_next(int node, int n){		//set the next pointer of the node
	if(node!=-1)
		ram[node+1] = n;
}
void set_prev(int node, int p){		//set the prev pointer of the node
	if(node!=-1)
		ram[node+2] = p;
}
void set_key(int node, int k){		//set the key of the node
	if(node!=-1)
		ram[node] = k;
}
void set_ram(int size){				//allocate ram (array) of given size
	ram_size = size;
	ram = (int *)(calloc(size,sizeof(int)));
}



void push(int node){
	//to push an object to the free_list list
	if(node==-1)	return;
	set_next(node,free_list);
	free_list = node;
}

int pop(){
	//to pop an object from the free_list list
	if(free_list == -1)		//no free object available
		return -1;
	else{
		int node = free_list;
		free_list = get_next(free_list);
		set_next(node,-1);
		set_prev(node,-1);
		return node;
	}
}

void allocate_ram(int size){	//this function allocates the set amount of ram and initializes the list_seq
	set_ram(size);
	int last_idx = ((ram_size/3)-1)*3;
	list_seq = (int *)(calloc(lseq_size,sizeof(int)));
	int i;
	for(i=0;i<lseq_size;i++)
		list_seq[i] = -1;
	for(i=last_idx;i>=0;i-=3){
		push(i);
	}
	next_list_num = 0;
	printf("NOTE:\n1. Current Configuration can handle at max %d nodes.\n",size/3); 
	printf("(This can be changed by an optional command line argument, for example for 100 nodes run as ./exe 100)\n");
	printf("2. No. of lists supported grows dynamically.\n");
	printf("3. Valid Range for keys is from %d to %d.\n",INT_MIN+1,INT_MAX);
}

void insert_between(int node, int prev_node, int next_node){
	set_next(node,next_node);
	set_prev(node,prev_node);
	if(prev_node != -1)		//when insertion is to be done at the first position, prev_node is -1
		set_next(prev_node,node);
	if(next_node != -1)		//when insertion is to be done at the last position, next_node is -1
		set_prev(next_node,node);
}

int newlist(int key){		//create a new list with key as the first node's value and return the head
	int head=pop();		//pop a node from the free_list
	if(head == -1)		//no memory available
		return -1;
	set_key(head,key);
	return head;
}

int createlist(int key){	//create a new list with key as the first node on next available list number
	int head = newlist(key);
	if(head == -1){
		return -1;
	}
	else{
		set_head(next_list_num,head);
		next_list_num++;
		return 0;
	}
}

int insert(int lno, int key){		//insert the key in sorted order in list starting at head
	int head = get_head(lno);
	if(head == -2){		//When no such list exists
		return -2;
	}
	int newnode = pop();
	if(newnode == -1)		//no memory available
		return -1;
	set_key(newnode,key);
	if(head==-1)	{	//if list was empty initially
		set_head(lno,newnode);
		return 0;
	}
	else{
		if(key <= get_key(head)){
			insert_between(newnode,-1,head);	//insert at first position
			head = newnode;
			set_head(lno,head);
			return 0;
		}
		int node;
		for(node=head; get_next(node)!= -1;node=get_next(node)){
			if(key > get_key(node) && key<= get_key(get_next(node))){
				insert_between(newnode,node,get_next(node));	//insertion in between two nodes
				set_head(lno,head);
				return 0;
			}
		}
		insert_between(newnode,node,-1);	//insertion at last position
		set_head(lno,head);
		return 0;	
	}
}



int delete(int lno, int key){		//delete the first occurrence of key in the list starting at head
	//error code for delete function is -2 (as -1 means that the the operation was successful, but list has now become empty)
	int head = get_head(lno);
	if(head == -2){		//When no such list exists
		return -2;
	}
	if(head==-1)	//list empty
		return -1;
	if(get_key(head) == key){	//if the first element is to be deleted
		int newhead = get_next(head);
		if(newhead != -1)
			set_prev(newhead,-1);
		push(head);		//add deleted node to the free_list
		set_head(lno,newhead);	//set the modified list's head
		return 0;	
	}
	for(int node = head; get_next(node) != -1; node = get_next(node)){
		if(get_key(get_next(node)) == key){
			//means that next node is to be deleted
			int delnode = get_next(node);	//delnode stores the node to be deleted
			set_next(node,get_next(delnode));
			if(get_next(node) != -1)
				set_prev(get_next(node),node);
			push(delnode);	//push the delnode to the free_list
			set_head(lno,head);
			return 0;	//head is unchanged as intermediate node is deleted
		}
	}
	return -1;	//no node found with key value same as passed key value
}
int count_nodes(int head){		//to count number of nodes of the given list
	int ct = 0;
	if(head < -1)
		return -1;
	for(int node = head; node != -1; node = get_next(node)){
		ct++;
	}
	return ct;
}
int count_nodes_lno(int lno){
	return count_nodes(get_head(lno));
}

int count_total(){		//count total non-free nodes in the memory
	return ((ram_size/3) - count_nodes(free_list));
}

void display(int head){		//to display all nodes of the given list
	printf("key\tnext\tprev\n");
	for(int node = head; node != -1; node = get_next(node)){
		printf("%d\t",get_key(node));
		if(get_next(node)!=-1)
			printf("%d\t",get_next(node));
		else
			printf("NIL\t");
		if(get_prev(node) != -1)
			printf("%d\n",get_prev(node));
		else
			printf("NIL\n");
	}

	
}

void displayAll(){
	if(next_list_num==0)
		printf("NO LISTS MADE SO FAR!\n");
	for(int lno = 0; lno<next_list_num;lno++){
		printf("Elements of list-%d are:\n",lno);
		display(get_head(lno));	
		printf("\n");
	}
}

void displayFree(){		//to display nodes of the free_list
	// display(free_list);
	printf("Elements of free list are:\n[");
	for(int node = free_list; node != -1; node = get_next(node)){
		printf(" %d",node);
	}
	printf(" ]\n");
}

int defrag(){	//to perform defragmentation
	int n = next_list_num;
	for(int node = free_list; node != -1; node = get_next(node)){
		set_key(node,INT_MIN);
	}
	int lptr = 0;	//searches for free nodes
	int rptr = ((ram_size/3)-1)*3;	//searches for occupied nodes
	while(lptr < rptr){
		if(get_key(lptr) != INT_MIN){
			lptr += 3;
			continue;
		}
		if(get_key(rptr) == INT_MIN){
			rptr -= 3;
			continue;
		}
		//now both lptr and rptr are at right positions and ready to be swapped.
		int tmp;
		//key set
		set_key(lptr,get_key(rptr));
		set_key(rptr,INT_MIN);
		//prev set
		set_prev(lptr,get_prev(rptr));
		if(get_prev(rptr) != -1)
			set_next(get_prev(rptr),lptr);
		else{
			//head of a list needs to me modified
			for(int i=0;i<n;i++){
				if(list_seq[i] == rptr){
					list_seq[i] = lptr;
					break;
				}
			}
		}
		//next set
		set_next(lptr,get_next(rptr));
		if(get_next(rptr) != -1)
			set_prev(get_next(rptr),lptr);
		lptr += 3;
		rptr -= 3;
	}
	rptr = ((ram_size/3)-1)*3;
	free_list = -1;
	while(get_key(rptr) == INT_MIN){
		push(rptr);
		rptr -= 3;
	}
	return 0;
}
