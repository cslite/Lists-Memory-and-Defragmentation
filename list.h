
int get_next_lno();		//to get the number of next new list
void allocate_ram(int size);//allocate ram (array) of given size and perform some initializations	
void push(int node);		//to push an object to the free_list list
int pop();					//to pop an object from the free_list list
int createlist(int key);		//create a new list with key as the first node's value at next new list position
int insert(int lno, int key);	//insert the key in sorted order in list at list no. lno
int delete(int lno, int key);	//delete the first occurrence of key in the list at list no. lno
int count_nodes_lno(int lno);	//to count number of nodes of the given list
int count_total();			//count total non-free nodes in the memory
void displayAll();		//to display all nodes of all lists
void displayFree();			//to display nodes of the free_list
int defrag();	//to perform defragmentation
