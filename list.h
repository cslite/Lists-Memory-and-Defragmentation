

void set_ram(int size);		//allocate ram (array) of given size
void push(int node);		//to push an object to the free_list list
int pop();					//to pop an object from the free_list list
int newlist(int key);		//create a new list with key as the first node's value and return the head
int insert(int head, int key);	//insert the key in sorted order in list starting at head
int delete(int head, int key);	//delete the first occurrence of key in the list starting at head
int count_nodes(int head);	//to count number of nodes of the given list
int count_total();			//count total non-free nodes in the memory
void display(int head);		//to display all nodes of the given list
void displayFree();			//to display nodes of the free_list
int defrag(int *list_seq,int n);	//to perform defragmentation
