#include "student_functions.h"
//============================================================================================
typedef enum {true , false} bool; //type bool
//============================================================================================
//insert new student in list
Student *insert_student(Student *node, char *name, char *prev_name)
{
	Student *node_ins = (Student*)malloc(sizeof(Student));//create new node in heap
	memset(node_ins->name, '\0', sizeof(node_ins->name));//set all of insertion node to whitespace (to prevent buffer overflow)
	strcpy(node_ins->name, name);//copy student name given to the node
	
	if(node == NULL)//if list is empty
	{
		node_ins->prev = NULL;
		node_ins->next = NULL;
		node = &node_ins;
	}
	else//if list is not empty
	{
		Student *traverse;
		traverse = node;
		while(traverse != NULL)//traverse
		{
			if(strcmp(traverse->name, prev_name))//if we find the previous name
			{
				break;//break from loop
			}
			traverse = traverse->next;//iterate if we havent found it
		}
		
		if(traverse == NULL)//if last element insert at the back
		{
			traverse->next = node_ins;
			node_ins->prev = traverse;
			node_ins->next = NULL;
		}
		else//insert in between
		{
			node_ins->next = traverse->next;
			traverse->next = node_ins;
			node_ins->prev = traverse;
			node->next->prev = node_ins;
		}
		
	}
	printf("inserted %s\n", node_ins->name);
	return node_ins;//return new node
}
//============================================================================================
//delete a student from the lsit
int delete_student(Student *node, char *name)
{
	struct Student *traverse;
	traverse = node;
	while(traverse != NULL)//traverse equal to null if end of node
	{
		if(strcmp(traverse->name, name) == 0)//If string compare return 0 means we found a match
		{
			if(traverse->prev == NULL)//if Student at first node
			{
				traverse = node->next;//point to next node of pointer node
				free(node);//delete current student from list
				node = traverse;//assign node to the new head in list
				node->prev = NULL;//assign previous node to NULL
				
			}
			else if(traverse->next == NULL)//if Student at last node
			{
				Student *temp;//temp student pointer
				traverse->prev->next = NULL;//set pointer of previous node to NULL
				free(traverse);//delete current student from list
			}
			else//Student in the middle of two nodes
			{
				traverse->prev->next = traverse->next;//change previous node of next pointer to the next node of pointer traverse
				traverse->next->prev = traverse->prev;//change next node of previous pointer to the previoucases node of pointer traverse
				free(traverse);//delete current student from list
			}
			return 1;//return 1 if we succeed in finding the sstudent and delete it
		}
		else
		{
			traverse = traverse->next;//iterate to next node
		}
	}
	return 0;//return if we could not find the student in list to delete
}
//============================================================================================
//search the student
Student *search_list(Student *node, char *name)
{
	struct Student *find;
	find = node;
	while(find != NULL)//if find is not pointing to NULL(end of node) then loop
	{
		if(strcmp(find->name, name) == 0)//If string compare return 0 means we found a match and it will give the first student with that name
		{
			return find;//return the current node find is pointing to
		}
		find = find->next;//iterate to the next node
	}
	return NULL;//return NULL if student is not in the list
}
//============================================================================================
//swap two students in list
void swap(Student *node1, Student *node2)
{
	struct Student *temp;//temp pointer of type student
	
	
	if(node1->prev == NULL)
	{
		
	}
	else
	{
		//temp points to the node after node1 and assign the previous to node2
		temp = node1->next;
		temp->prev = node2;
		
		//temp points to the node previous node2 and assign the next pointer to node1
		temp = node2->prev;
		temp->next = node1;
		
		//temp points to the node before node1. Assign the previous pointer of node1 to previous pointer of node2. Change previous pointer of node2 to the node temp points to. 
		temp = node1->prev;
		node1->prev = node2->prev;
		node2->prev = temp;
		temp->next = node2;
		
		//temp points to thcasee node after node2. Assign the previous pointer of temp to node1. Next pointer of node2 points to next pointer of node1. Next pointer of node1 points to the node temp points to.
		temp = node2->next;
		temp->prev = node1;
		node2->next = node1->next;
		node1->next = temp;
	}
	
}
//============================================================================================
//empty doubly linked-list
void free_list(Student *node)
{
	Student *temp; //temp pointer
	temp = node->next; //temp points to next node of pointer node
	while(temp != NULL || node != NULL)//when both of this is NULL then stop
	{
		free(node);//free node
		node = temp->next;//point to next node of pointer temp
		if(temp == NULL)
		{
			free(node);
		}
		else
		{
			free(temp);
		}
		free(temp);//free temp
		temp = node->next;// point temp to next node of pointer node
	}
	return;//go back to main
}
//===========================================================================================
void display(Student *node)
{
	struct Student *traverse = node;
	if(node == NULL)
	{
		printf("List is empty\n");
		return;
	}
	else
	{
		while(node != NULL)
		{
			printf("%s->", node->name);
			traverse = traverse->next;
		}
	}
	
	return;
}
//============================================================================================
int main()
{
	struct Student *head = (struct Student*)malloc(sizeof(struct Student));
	head = NULL;
	int input = 0;
	
	display(head);
	
	insert_student(head, "zach" , "");
	display(head);
	insert_student(head, "jake" , "zach");//head->zach->jake
	display(head);
	insert_student(head, "bob" , "zach");//head->zach->bob->jake
	display(head);
	insert_student(head, "carl" , "jake");//head->zach->bob->carl->jake
	display(head);
	
	//search_list(head, "zach");
	
	//swap(search_list(head, "zach"), search_list(head, "carl"));//head->carl->bob->zach->jake
	//display(head);
	
	//delete_student(head, "bob");//head->carl->zach->jake
	//display(head);
	
	//free_list(head);
	
	return 0;
}
