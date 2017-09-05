#include <iostream>
#include <fstream>
#include <stdio.h>
#include <PNMwriter.h>
using namespace std;


// constructor
PNMwriter::PNMwriter(void) {};


// destructor
PNMwriter::~PNMwriter() {};


// write to output file
void PNMwriter::Write(char *outfile)
{
	ofstream f_out;
	f_out.open(outfile, ios::out);
	f_out << "P6\n" << img1->GetWidth() << " " << img1->GetHeight() << "\n" << 255 << endl;
	f_out.write( (char *) img1->GetBuffer(), 3 * img1->GetWidth() * img1->GetHeight());
	f_out.close();
};


const char *PNMwriter::SinkName()
{
	return "PNMWriter";
};