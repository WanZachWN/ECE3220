#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;
//===========================================================================================================
class Sensor
{	
	public:
	string sensor[120];
	int size;
	Sensor()
	{
		size = 0;
	}
	int getsize()
	{
		return size;
	}
	string getDatafromS(int i)
	{
		return sensor[i];
	}
};
//===========================================================================================================
class SensorA : public Sensor
{
	public:
	int sensorA[50];
	int size;
	SensorA()
	{
		size = 0;
	}
	
};
//===========================================================================================================
class SensorB : public Sensor
{	
	public:
	string sensorB[70];
	int size;
	SensorB()
	{
		size = 0;
	}
};
//===========================================================================================================
void print_and_sort(Sensor sensorData)
{
	for(int i = 0; i < sensorData.size-1; i++)
	{
		for(int j = 0; j < sensorData.size-1; j++)
		{
			if(sensorData.sensor[i] < sensorData.sensor[j])
			{
				string temp = sensorData.sensor[i];
				sensorData.sensor[i] = sensorData.sensor[j];
				sensorData.sensor[j] = temp;
			}
		}
	}
	for(int p = 0; p < sensorData.size-1; p++)
	{
		cout << sensorData.sensor[p] << " ";
	}
	cout << endl;
	
	return;
}
//===========================================================================================================
void print_and_sort(SensorA sensorDataA)
{
	for(int i = 0; i < sensorDataA.size-1; i++)
	{
		for(int j = 0; j < sensorDataA.size-1; j++)
		{
			if(sensorDataA.sensorA[i] < sensorDataA.sensorA[j])
			{
				int temp = sensorDataA.sensorA[i];
				sensorDataA.sensorA[i] = sensorDataA.sensorA[j];
				sensorDataA.sensorA[j] = temp;
			}
		}
	}
	for(int p = 0; p < sensorDataA.size-1; p++)
	{
		cout << sensorDataA.sensorA[p] << " ";
	}
	cout << endl;
	
	return;
}
//===========================================================================================================
void print_and_sort(SensorB sensorDataB)
{
	for(int i = 0; i < sensorDataB.size-1; i++)
	{
		for(int j = 0; j < sensorDataB.size-1; j++)
		{
			if(sensorDataB.sensorB[i] < sensorDataB.sensorB[j])
			{
				string temp = sensorDataB.sensorB[i];
				sensorDataB.sensorB[i] = sensorDataB.sensorB[j];
				sensorDataB.sensorB[j] = temp;
			}
		}
	}
	for(int p = 0; p < sensorDataB.size-1; p++)
	{
		cout << sensorDataB.sensorB[p] << " ";
	}
	cout << endl;
	
	return;
}
//===========================================================================================================
bool RandGenB()
{
	try{
		ostringstream filenameB;
		filenameB << "SensorB.txt";
		fstream ofilesensorB;
		
		ofilesensorB.open(filenameB.str());
		if(!ofilesensorB.is_open())
		{
			ofilesensorB.close();
			ofilesensorB.open(filenameB.str(), ios::app);
			ofilesensorB.close();
			
			ostringstream err_msg;
			err_msg << "File does not exist, generating Sensor " << filenameB.str().at(6)
				<< " data file " << filenameB.str() << ends;
			throw runtime_error(err_msg.str());
		}
		ofilesensorB.close();
		ofilesensorB.open(filenameB.str(), ios:: out | ios::app);
		
		char rand_char;
		for(int i = 0; i < 7; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				rand_char = 'a' + rand()%26;
				ofilesensorB << rand_char;
			}
			ofilesensorB << endl;
		}
		
		ofilesensorB.close();
		
	}
	catch(const runtime_error &err)
	{
		cerr << err.what() << endl;
		return false;
	}
	return true;
}
//===========================================================================================================
bool RandGenA()
{
	try{
		ostringstream filenameA;
		filenameA << "SensorA.txt";
		fstream ofilesensorA;
		
		ofilesensorA.open(filenameA.str());
		if(!ofilesensorA.is_open())
		{
			ofilesensorA.close();
			ofilesensorA.open(filenameA.str(), ios::app);
			ofilesensorA.close();
			
			ostringstream err_msg;
			err_msg << "File does not exist, generating Sensor " << filenameA.str().at(6)
				<< " data file " << filenameA.str() << ends;
			throw runtime_error(err_msg.str());
		}
		ofilesensorA.close();
		ofilesensorA.open(filenameA.str(), ios:: out | ios::app);
		
		for(int i = 0; i < 5; i++)
		{
			ofilesensorA << (100 + rand() % 900) << endl;
		}
		
		ofilesensorA.close();
		
	}
	catch(const runtime_error &err)
	{
		cerr << err.what() << endl;
		return false;
	}
	return true;
}
//===========================================================================================================
void ReadFile(Sensor &sensorData, SensorA &sensordataA, SensorB &sensordataB)
{
	try{
		ostringstream filenameA;
		ostringstream filenameB;
		filenameA << "SensorA.txt";
		filenameB << "SensorB.txt";
		
		fstream ffilesensorA;
		fstream ffilesensorB;
		
		ffilesensorA.open(filenameA.str(), ios::in);
		if(ffilesensorA.eof())
		{
			ffilesensorA.close();
			ostringstream err_msg;
			err_msg << "File " << filenameA.str()
				<< " is empty, no new data from Sensor A" << ends;
			throw runtime_error(err_msg.str());
		}
		
		ffilesensorB.open(filenameB.str(), ios::in);
		if(ffilesensorB.eof())
		{
			ffilesensorA.close();
			ffilesensorB.close();
			ostringstream err_msg;
			err_msg << "File " << filenameB.str()
				<< " is empty, no new data from Sensor B" << ends;
			throw runtime_error(err_msg.str());
		}
		
		size_t size = 0;
		int value = 0;
		string content1, content2;
		while(!ffilesensorA.eof())
		{
			ffilesensorA >> content1;
			value = stoi(content1, &size);
			
			sensordataA.sensorA[sensordataA.size] = value;
			sensorData.sensor[sensorData.size] = content1;
			sensordataA.size++;
			sensorData.size++;
		}
		while(!ffilesensorB.eof())
		{
			ffilesensorB >> content2;
			
			sensordataB.sensorB[sensordataB.size] = content2;
			sensorData.sensor[sensorData.size] = content2;
			sensordataB.size++;
			sensorData.size++;
		}
		
		ffilesensorA.close();
		ffilesensorB.close();
		
		ffilesensorA.open(filenameA.str(), ios::out);
		ffilesensorA.close();
		
		ffilesensorB.open(filenameB.str(), ios::out);
		ffilesensorB.close();
	}
	catch(const runtime_error &err)
	{
		cerr << err.what() << endl;
	}
	return;
}
//===========================================================================================================
void SaveSensor(Sensor &SensorData)
{
	ostringstream loader;
	loader << "loader.txt";
	
	ofstream loadfile;
	
	try{
		loadfile.open(loader.str());
		if(loadfile.fail())
		{	
			loadfile.close();
			loadfile.open(loader.str(), ios::app);
			loadfile.close();
			
			ostringstream err_msg;
			err_msg << "Save file " << loader.str()
				<< " does not exist, generating new loader.txt" << ends;
			throw runtime_error(err_msg.str());
		}
		loadfile.close();
		loadfile.open(loader.str(), ios::app);
		
		for(int i = 0; i < SensorData.size-1; i++)
		{
			loadfile << SensorData.sensor[i] << endl;
		}
		loadfile.close();
		
	}
	catch(const runtime_error &err)
	{
		cerr << err.what() << endl;
	}
	return; 
}
//===========================================================================================================
bool LoadData(Sensor &sensorData)
{
	ostringstream filename;
	filename << "loader.txt";
	ifstream loadfile;
	
	try{
		loadfile.open(filename.str());
		if(loadfile.fail())
		{
			loadfile.close();
			ostringstream err_msg;
			err_msg << filename.str() << " File does not Exist" << ends;
			throw runtime_error(err_msg.str());
		}
		int i = 0;
		string content;
		while(1)
		{
			loadfile >> content;
			if(!loadfile)
			{
				if(i == 0 && loadfile.eof())
				{
					ostringstream err_msg;
					err_msg << " loader.txt File is empty, no data saved" << ends;
					throw runtime_error(err_msg.str());
				}
				else if(loadfile.eof())
				{cout << "out" << endl;
					break;
				}
			}
			sensorData.sensor[sensorData.size] = content;
			sensorData.size++;
			i++;
		}
	}
	catch(const runtime_error &err)
	{
		cerr << err.what() << endl;
		return false;
	}
	return true;
}
//===========================================================================================================
void CopyA(SensorA &sensor_a)
{
	string str;
	for(int i = 0; i < sensor_a.getsize()-1; i++)
	{
		str = sensor_a.getDatafromS(i);
		if(isdigit(str[0]))
		{	cout << "true" << endl;
			sensor_a.sensorA[sensor_a.size] = stoi(str);
			sensor_a.size++;
		}
	}
}
//===========================================================================================================
void CopyB(SensorB &sensor_b)
{
	string str;
	for(int i = 0; i < sensor_b.getsize()-1; i++)
	{
		str = sensor_b.getDatafromS(i);
		if(!isdigit(str[0]))
		{
			sensor_b.sensorB[sensor_b.size] = str;
			sensor_b.size++;
		}
	}
}
