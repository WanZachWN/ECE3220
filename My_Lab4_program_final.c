#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* Read file with number data. First row 2 integers seperated by space. First value is length of signal and second is maximum value can be measured. Row 2 to end of file is data samples.
int 1 = signal length and int 2 = max value


Accept user input an open file using argc and argv

-n is telling the program to open file number that is requested
-o is telling the program to do an offset operation on signal
-s is telling the program to do a scale operation on signal
-h shows how to use the program

handle incorrect calls and display help

1) Check calling for program correctly

2) open file and store into an int array

3) Create scale and offset functions

4) Store in Offset_data_nn.txt or Scaled_data_nn.txt

offset (n+offset) || scaled (n*scaled)
*/

//boolean type for checking if file exist, scale or offset requested.
typedef enum {true , false} bool;

//display help to user on how to use the program.
void help()
{
	printf("Welcome To WW838's Lab 4 Program!\nTo call the raw signal file use -n file_value\nTo set a scale on the file use -s scale_value\nTo set an offset on the file use -o offset_value\nHelp is -h\n");
	printf("Example:\n./My_Lab4_program -n 20 -s 0.5\n./My_Lab4_program -n 20 -o -2.5\n./My_Lab4_program -n 20 -s 0.5 -o -2.5\n");
	
	return;
}
//display error to user if program is called incorrectly
void error()
{
	printf("Error calling program! Please try again.\n");
	
	return;
}
//boolean expression to check if there is file, scale or offset. Also store filenumber, signal size, max value, offset and scale value.
struct Openfilereq{  
	bool noFile, noScale, noOffset;
	int filenum, size;
	double max, offset, scale;
};
//save computing signal in this file.
void SaveinFile(struct Openfilereq *opr1, double *processdata)
{
	FILE *save;
	int i = 0;
	char *newFile = (char*)malloc(sizeof(char)*5);
	
	if(opr1->noScale == false) //if scaling is requested set newFile to Scaled_data_nn.txt
	{
		sprintf(newFile, "Scaled_data_%.2d.txt", opr1->filenum);//set the name file
		save = fopen(newFile, "w");//make the file
		fprintf(save, "%d %.1lf\n", opr1->size, opr1->scale);//print first line
		opr1->noScale = true; //set to true if printed to know we have execute this
	}
	else if(opr1->noOffset == false)//if offset is requested set newFile to Offset_data_nn.txt
	{
		sprintf(newFile, "Offset_data_%.2d.txt", opr1->filenum); //set the name file
		save = fopen(newFile, "w"); // make the file
		fprintf(save, "%d %.1lf\n", opr1->size, opr1->offset); //print first line
		opr1->noOffset = true;//set to true if printed to know we have execute this
	}
	//print line after
	while(i < opr1->size)
	{
		fprintf(save, "%0.4lf\n", processdata[i]);
		i++;
	}
	fclose(save);//close file after printing
	return;
}
//scale signal when user ask for scaling
void ScaledData(struct Openfilereq *opr1, int *data, double *process)
{
	for(int i = 0; i < opr1->size; i++)//loop until end of pointer array
	{
		process[i] = data[i]*opr1->scale;//scale data
	}
	return;
}
//offset signal when user ask for offsetting
void OffsetData(struct Openfilereq *opr1, int *data, double *process)
{
	for(int i = 0; i < opr1->size; i++)//loop until end of pointer array
	{
		process[i] = data[i]+opr1->offset;//offset data
	}
	return;
}
//check if calling program is done properly.
int Check(struct Openfilereq *opr1, int argc, char *argv[])
{
	int n = 1; //counter
	if(argc <= 4)//does not satisfy minimum calling
	{
		//if user just do "./My_Lab4_program" or does not do "./My_Lab4_program -h"
		if(argc == 1|| strcmp(argv[n], "-h") != 0)
		{
			error();//display error
		}
		help(); //display help on using the program
		return 0;
	}
	// if everything is called with minimum amount of argument
	else
	{
		while(n < argc)//loop to check content of argv
		{
			if(n == argc-1)//if file number is not stated and n is end of calling
			{
				error();
				help();
				return 0;
			}
			if(strcmp(argv[n], "-n") == 0)//if requesting file number
			{
				if(!(isdigit(*argv[n+1])))//file number request but no value
				{
					error();
					help();
					return 0;
				}
				else//if there is file number given then assign to integer filenum and set the noFile to false.
				{
					sscanf(argv[n+1], "%d", &opr1->filenum);// get file number
					opr1->noFile = false;
				}
			}
			else if(strcmp(argv[n], "-s") == 0)//if requesting scale
			{
				double isvalue;//to save scale value
				char *endptr;//end pointer for string to double
				isvalue = strtod(argv[n+1], &endptr);//check next argument if value
				if(isvalue == 0)//scale request but no value
				{
					error();
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
				double isvalue;//to save offset value
				char *endptr;//end pointer for string to double
				isvalue = strtod(argv[n+1], &endptr); //check next argument if value
				if(isvalue == 0)//offset request but no value
				{
					error();
					help();
					return 0;
				}
				else //if there is offset value given then assign to integer offset and set the noScale to false.
				{
					opr1->offset = isvalue;
					opr1->noOffset = false;
				}
			}
			n += 2;//iterate twice since we check n+1
		}
	}
	return 1;//if everything checks well return 1 as in true
}

//main function
int main(int argc, char *argv[]) //argc - argument count, argv - argument vector
{
	struct Openfilereq opr1 = {true, true, true, 0, 0, 0.0, 0.0, 0.0};//initialization of struct
	int check = 0;
	check = Check(&opr1, argc, argv);//Check() function
	
	//if Check function return 0, exit program
	if(check == 0)
	{
		return 0;
	}
	
	//assign filenum entered by user and open that file
	char *p = (char*)malloc(sizeof(char)*1);//saves file name in heap
	sprintf(p, "raw_data_%.2d.txt", opr1.filenum);//assign filename to pointer p
	printf("Opening %s...\n", p);//print we are opening file number given
	
	int *data;//array to store value
	FILE *openFile = fopen(p, "r");// pointer file to read
	
	//if file requested is empty or does not exist display error, close file, free pointer p and exit program
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
		int i; //counter
		fscanf(openFile, "%d", &opr1.size);//get signal size in file
		fscanf(openFile, "%lf", &opr1.max);//get max value in file
		data = malloc(sizeof(int)*opr1.size); //make allocation in heap for data type int
		for(i = 0; i < opr1.size; i++)//loop to traverse the file since size is known
		{
			fscanf(openFile, "%d", &data[i]);//scan value and store in data[i]
			if(data[i] > opr1.max)
			{
				opr1.size--;
				i--;
			}
		}
		fclose(openFile);//close file
	}
	double *processdata = malloc(sizeof(double)*opr1.size);//store data type double after operation in heap
	
	//if user want to scale data, open and do the scale operation and save in new file
	if(opr1.noFile == false && opr1.noScale == false)
	{
		printf("Scaling data\n");//print that we are offsetting the data
		ScaledData(&opr1, data, processdata);//scale data function
		SaveinFile(&opr1, processdata);//save to new file
	}
	
	//if user want to offset data, open and do the offset operation and save in new file
	if(opr1.noFile == false && opr1.noOffset == false)
	{
		printf("Offsetting data\n");//print that we are offsetting the data
		OffsetData(&opr1, data, processdata);//offset data function
		SaveinFile(&opr1, processdata);//save to new file
	}
	
	free(data);//free pointer data in heap memory
	free(processdata);//free pointer processdata in heap memory
	free(p); //free pointer p

	return 0;
	
}
