switch(input)
		{
			case 1:
				printf("Enter Student name to be added to list\n");
				scanf("%s", name1);
				printf("Enter second student name for the student to be inserted in.\nIf it is the first insert or the second student name could not be found,\nThe program will insert as the last element\n");
				scanf("%s", name2);
				insert_student(head, name1, name2);
				break;	
				
			case 2:
				printf("Enter student name to search in list\n");
				scanf("%s", name1);
				search_list(head, name1);
				break;	
			
			case 3:
				printf("Enter first student name to be swap in list\n");
				scanf("%s", name1);
				printf("Enter second student name to be swap in list\n");
				scanf("%s", name2);
				swap(search_list(head, name1), search_list(head, name2));
				break;	
			
			case 4:
				printf("Enter Student name to be deleted from list\n");
				scanf("%s", name1);
				delete_student(head, name1);
				break;	
				
			case 5:
				printf("Displaying all students in list\n");
				display(head);
				break;
			
			case 6:	
				printf("Ending program\n");
				free_list(head);
				stop = true;
				break;	
			default : 
				printf("Wrong input. Please try again\n");
				break;
		}
		
