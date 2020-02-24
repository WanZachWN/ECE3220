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

1) open file and store into an int arr[]

2) Create scale and offset functions

3) place in new file

4) Store Offset_data_nn.txt or Scaled_data_nn.txt

5) offset (n+offset) scaled (n/scaled)

convert to int and %2d
*/

//boolean type for checking if file exist, scale or offset requested.
typedef enum {true , false} bool;

//display help to user on how to use the program.
void help()
{
	printf("Welcome To WW838's Lab 4 Program!\nTo call the raw data file use -n file_value\nTo set a scale on the file use -s scale_value\nTo set an offset on the file use -o offset_value\nHelp is -h\n");
	
	return;
}

//boolean expression to check if there is file, scale or offset when calling program
struct Openfilereq{  
	bool noFile, noScale, noOffset;
	int filenum;
	double offset, scale;
};

//save computing data in this file.
void SaveinFile(double arr[])
{
	File *save;
	int i = 0;

	save = fopen(nameFile, "w");
	while(fscanf(save, "%d", arr[i]) != EOF)
	{
		if(i > 1)
		{
			fprintf("%d\n", arr[i]);
		}
		else
		{
			fprintf("%d %lf", arr[0], arr[1]);
			i = i+2;
		}
	}
	fclose(save);
}
//scale data when user ask for scaling
void ScaledData(double scaled_arr[], double scale, size_t s)
{
	printf("%lf %lf\n", scaled_arr[0], scaled_arr[1]);
	for(int i = 2; i < s; i++)
	{
		scaled_arr[i] = scaled_arr[i]/scale;
		printf("%lf\n", scaled_arr[i]);
	}
	return;
}

//offset data when user ask for offsetting
void OffsetData(double offset_arr[], double offset, size_t s)
{
	for(int i = 2; i < s; i++)
	{
		offset_arr[i] = offset_arr[i]+offset;
		printf("%lf\n", offset_arr[i]);
	}
	return;
}
//check if calling program is done properly.
int Check(struct Openfilereq *opr1, int argc, char *argv[])
{
	int n = 1; //counter
	if(argc <= 4 || argc > 5)
	{
		//if user does not call for help and calls the program incorrectly
		if(strcmp(argv[n], "-h") != 0)
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
	//if 
	else if(argc <= 5)
	{
		while(n < argc)
		{
			if(strcmp(argv[n], "-n") == 0)
			{
				printf("-n exist\n");
				if(!(isdigit(*argv[n+1])))
				{
					printf("-n does not have value\n");//if -n but no value
					help();//display help on using the program
					return 0;
				}
				else//if there is file number given then assign to integer filenum and set the noFile to false.
				{
					printf("-n has value\n");
					sscanf(argv[n+1], "%d", &opr1->filenum);
					printf("file number: %d\n", opr1->filenum);
					opr1->noFile = false;
				}
			}
			else if(strcmp(argv[n], "-s") == 0)
			{
				printf("-s exist\n");
				if(!(isdigit(*argv[n+1])))
				{
					printf("-s has no value\n");//if -s but no value
					help();
					return 0;;
				}
				else//if there is scale value given then assign to integer scale and set the noScale to false.
				{
					printf("-s has value\n");
					sscanf(argv[n+1], "%lf", &opr1->scale);
					printf("scaling: %lf\n", opr1->scale);
					opr1->noScale = false;
				}
			}
			else if(strcmp(argv[n], "-o") == 0)
			{
				printf("-o exist\n");
				if(!(isdigit(*argv[n+1])))
				{
					printf("-o has no value\n");//if -o but no value
					help();
					return 0;
				}
				else //if there is offset value given then assign to integer offset and set the noScale to false.
				{
					printf("-o has value\n");
					sscanf(argv[n+1], "%lf", &opr1->offset);
					printf("offsetting: %lf\n", opr1->offset);
					opr1->noOffset = false;
				}
			}
			if(n == argc-1 && opr1->noFile == true)//if file number is not stated
			{
				printf("Error file number is not stated!\n");
				help();
				return 0;
			}
			n++;
		}
	}
	return 1;
}

//main function
int main(int argc, char *argv[]) //argc - argument count, argv - argument vector
{
	struct Openfilereq opr1 = {true, true, true, 0, 0 ,0};
	int check = 0;
	check = Check(&opr1, argc, argv);
	if(check == 0)
	{
		return 0;
	}
	
	//assign filenum entered by user and open that file
	char *p = (char*)malloc(sizeof(char)*1);
	sprintf(p, "raw_data_%d.txt", opr1.filenum);
	printf("opening %s...\n", p);
	
	//double *arr = (double *)malloc(sizeof(double)*10);
	double arr[10];//array to store value
	size_t s = sizeof(arr)/sizeof(arr[0]);//size of array
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
		int i = 0;
		printf("File content: \n");
		while(fscanf(openFile, "%lf", &arr[i]) != EOF)
		{
			i++;
		}
		fclose(openFile);
	}
	//if user want to scale data open and do the scale operation
	if(opr1.noFile == false && opr1.noScale == false)
	{
		printf("Scaling %lf of data\n", opr1.scale);
		ScaledData(arr, opr1.scale, s);
	}
	//if user want to offset data open and do the offset operation
	else if(opr1.noFile == false && opr1.noOffset == false)
	{
		printf("Offsetting %lf of data\n", opr1.offset);
		OffsetData(arr, opr1.offset, s);
	}
	free(p);

	return 0;
	
}
