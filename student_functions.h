#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Student{
	char name[50];
	struct Student *next, *prev;
}Student;

Student *insert_student(Student *node, char *name, char *prev_name);

int delete_student(Student *node, char *name);

Student *search_list(Student *node, char *name);

void swap(Student *node1, Student *node2);

void free_list(Student *node);
