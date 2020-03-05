#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <strtol>
#include <stdexcept>
using namespace std;

/*
	-n filenum
	-a offset
	-S scale
	-h help
	-d data directory
*/
bool Check()
{
	try{
		int n = 1;
		if(argc != 7)
		{
			throw runtime_error("Invalid number of arguments");
		}
		while
		{
			if(strcmp(argv[n], "-n") == 0 || strcmp(argv[n], "-a") == 0 || strcmp(argv[n], "-n") == 0)
			{
				int isvalue;
				size_t = sz;
				isvalue = stoi(argv[i+1], &sz);
				if(isvalue == 0)
				{
					ostringstream = error_msg;
					error_msg << "Invalid value" << argv[n];
					throw runtime_error(error_msg.str());
				}
				else
				{
					return true;
				}
			
			}
			else if(strcmp(argv[n], "-h") == 0 )
			{
				help();
				return false;
			}
			n += 2;
		}
	}
	
}


int main(int argc, char *argv[])
{
	bool check = false;
	
	try{
		check = Check(argc, argv);
		if(check == false)
		{
			return 0;
		}
				
		ostringstream filename;
		filename << "raw_data_" << /*value for data file*/ << ".txt";
		
		ifstream file;
		file.open(filename.str());
		if( !file )
		{
			ostringstream error_msg;
			error_msg << "Fail to open raw data file " << filename.str() << ends;
			throw runtime_error(error_msg.str());
		}
		vector<int> data;
		while()
		{
			int value;
			file >> value;
			if(!file)
			{
				if(file.eof()) break;
			}
			else
			{
				ostringstream error_msg;
				error_msg << "Fail to read input file " << fname.str() << ends;
				throw runtime_error(error_msg.str());
			}
			data.push_back(value);
		}
	}
	catch(const runtime_error &err)
	{
		cerr <<;
	}
	catch(...)
	{

	}
}
