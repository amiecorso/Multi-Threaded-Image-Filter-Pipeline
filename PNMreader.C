#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <PNMreader.h>
using namespace std;

PNMreader::PNMreader(char * input_file)  // constructor needs to allocate memory for the filename string and fill it out
{
	// how do we know the length of input_file?
	int length = 0;
	for (int i = 0; input_file[i] != '\0'; i++) {
		length++;
	}

	filename = new char[length + 1];
	strcpy(filename, input_file);
	filename[length] = '\0'; // don't forget EOL char

	img.SetFilter(this);  // not relevant to my question
};

PNMreader::~PNMreader() // destructor should free this same memory
{
	delete filename;
};



void PNMreader::Execute() // reads the file into the resident image, using the resident filename
{
	char magicNum[128];
	int width, height, maxval;

	ifstream f_in;
	f_in.open(filename, ios::in);
	if (f_in.is_open()) {
		f_in >> magicNum >> width >> height >> maxval;
		f_in.ignore(2, '\n');

		// get a pointer to the image so we can use it I DON'T THINK WE NEED THIS ACTUALLY 
		Image *img_ptr = Source::GetOutput();

		img_ptr->SetSize(width, height);
		f_in.read( (char *) img.GetBuffer(), 3 * width * height);
		f_in.close();
	}

};

const char *PNMreader::SourceName()
{
	return "PNMreader";
};
