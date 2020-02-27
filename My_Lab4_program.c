#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* Read file with number data. First row 2 integers seperated by space. First value is legth of signal and second is maximum value can be measured. Row 2 to end of file is data samples.
int 1 = signal length and int 2 = max value


Accept user input an open file using argc and argv

-n open file number
-o will offset signal int 1.
-s scale signal of int 1
-h shows how to use the program

handle incorrect calls and display help

1) Check calling for program correctly

2) open file and store into an int arr[] 

3) Create scale and offset functions

4) Store Offset_data_nn.txt or Scaled_data_nn.txt

offset (n+offset) scaled (n*scaled)
*/

//boolean type for checking if file exist, scale or offset requested.
typedef enum {true , false} bool;

//display help to user on how to use the program.
void help()
{
	printf("Welcome To WW838's Lab 4 Program!\nTo call the raw data file use -n file_value\nTo set a scale on the file use -s scale_value\nTo set an offset on the file use -o offset_value\nHelp is -h\n");
	
	return;
}

//boolean expression to check if there is file, scale or offset. Also store filenumber, max value, offset and scale value.
struct Openfilereq{  
	bool noFile, noScale, noOffset;
	int filenum;
	double max, offset, scale;
};
//linked list to store data in file
struct Node{
	double value; //value of data
	struct Node* next; // node pointer points to next element
};

//save computing data in this file.
void SaveinFile(struct Openfilereq *opr1, double arr[], size_t size)
{
	FILE *save;
	int i = 0;
	char *newFile = (char*)malloc(sizeof(char)*5);
	
	if(opr1->noScale == false) //if scaling is requested set newFile to Scaled_data_nn.txt
	{
		sprintf(newFile, "Scaled_data_%d.txt", opr1->filenum);//set the name file
		save = fopen(newFile, "w");// make the file
		fprintf(save, "%d %0.4lf\n", opr1->filenum, opr1->scale);//print first line
	}
	else//if offset is requested set newFile to Offset_data_nn.txt
	{
		sprintf(newFile, "Offset_data_%d.txt", opr1->filenum); //set the name file
		save = fopen(newFile, "w"); // make the file
		fprintf(save, "%d %0.4lf\n", opr1->filenum, opr1->offset); //print first line
	}
	//print line after
	while(i < size)
	{
		//compare to the max value set if less than print if not skip
		if(arr[i] < opr1->max)
		{
			fprintf(save, "%0.4lf\n", arr[i]);
		}
		i++;
	}
	fclose(save);
	return;
}
//scale data when user ask for scaling
void ScaledData(double scaled_arr[], double scale, size_t size)
{
	for(int i = 0; i < size; i++)
	{
		scaled_arr[i] = scaled_arr[i]*scale;
	}
	return;
}

//offset data when user ask for offsetting
void OffsetData(double offset_arr[], double offset, size_t size)
{
	for(int i = 0; i < size; i++)
	{
		offset_arr[i] = offset_arr[i]+offset;
	}
	return;
}
//check if calling program is done properly.
int Check(struct Openfilereq *opr1, int argc, char *argv[])
{
	int n = 1; //counter
	if(argc <= 4 || argc > 5)
	{
		//if user just do "./My_Lab4_program"
		if(argc == 1)
		{
			printf("Error calling program! Please try again.\n");
		}
		//if user does not call for help and calls the program incorrectly
		else if(strcmp(argv[n], "-h") != 0)
		{
			printf("Error calling program! Please try again.\n");
		}
		//if only one of the calling type is used but no value or incomplete ex:./My_lab4_program -n 5 -s
		else if(strcmp(argv[n], "-n") == 0 || strcmp(argv[n], "-s") == 0 || strcmp(argv[n], "-o") == 0)
		{
			printf("Program Error, please specify file using -n (File data number)\n");
		}
		help(); //display help on using the program
		return 0;
	}
	// if everything is called with correct amount of argument
	else if(argc <= 5)
	{
		while(n < argc)//loop to check content of argv
		{
			if(strcmp(argv[n], "-n") == 0)//if requesting file number
			{
				if(!(isdigit(*argv[n+1])))//file number request but no value
				{
					help();//display help on using the program
					return 0;
				}
				else//if there is file number given then assign to integer filenum and set the noFile to false.
				{
					sscanf(argv[n+1], "%d", &opr1->filenum);
					opr1->noFile = false;
				}
			}
			else if(strcmp(argv[n], "-s") == 0)//if requesting scale
			{
				double isvalue;
				char *endptr;
				isvalue = strtod(argv[n+1], &endptr);//check next argument if value
				if(isvalue == 0)//scale request but no value
				{
					help();
					return 0;;
				}
				else//if there is scale value given then assign to integer scale and set the noScale to false.
				{
					opr1->scale = isvalue;
					opr1->noScale = false;
				}
			}
			else if(strcmp(argv[n], "-o") == 0)//if requesting offset
			{
				double isvalue;
				char *endptr;
				isvalue = strtod(argv[n+1], &endptr); //check next argument if value
				if(isvalue == 0)//offset request but no value
				{
					help();
					return 0;
				}
				else //if there is offset value given then assign to integer offset and set the noScale to false.
				{
					opr1->offset = isvalue;
					opr1->noOffset = false;
				}
			}
			
			n++;
		}
	}
	return 1;
}

//main function
int main(int argc, char *argv[]) //argc - argument count, argv - argument vector
{
	struct Openfilereq opr1 = {true, true, true, 0, 0, 0.0, 0.0};
	int check = 0;
	check = Check(&opr1, argc, argv);
	//if Check function return 0, exit program
	if(check == 0)
	{
		return 0;
	}
	
	//assign filenum entered by user and open that file
	char *p = (char*)malloc(sizeof(char)*1);
	sprintf(p, "raw_data_%d.txt", opr1.filenum);
	printf("opening %s...\n", p);
	
	double arr[5];//array to store value
	size_t size = sizeof(arr)/sizeof(arr[0]);//size of array
	FILE *openFile = fopen(p, "r");// pointer file to read
	
	
	//if file requested is empty or does not exist display error and exit program
	if(openFile == NULL)
	{
		printf("File does not exist. Please use a proper data file and include it in the same directory as the program.\n");
		fclose(openFile);
		free(p);
		return 0;
	}
	//if file exist and is not empty read the content of the file
	else
	{
		int i = 0; //counter
		while(fgetc(openFile) != EOF)
		{
			if(i < 2)
			{
				if(i == 1)
				{
					fscanf(openFile, "%lf", &opr1.max);
				}
			}
			else
			{
				fscanf(openFile, "%lf", &arr[i-2]);
			}
			i++;
		}
		fclose(openFile);
	}
	//if user want to scale data open and do the scale operation
	if(opr1.noFile == false && opr1.noScale == false)
	{
		printf("Scaling data\n");
		ScaledData(arr, opr1.scale, size);
	}
	//if user want to offset data open and do the offset operation
	else if(opr1.noFile == false && opr1.noOffset == false)
	{
		printf("Offsetting data\n");
		OffsetData(arr, opr1.offset, size);
	}
	SaveinFile(&opr1, arr, size); //saves to processed data to a file
	
	free(p); // free pointer p

	return 0;
	
}
