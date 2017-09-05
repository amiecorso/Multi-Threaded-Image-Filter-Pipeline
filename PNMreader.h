#ifndef PNMREADER_H
#define PNMREADER_H

#include <source.h>

class PNMreader : public Source
{
private:
	char * filename;
public:
	PNMreader(char * input_file); // constructor needs to allocate memory for the filename string and fill it out
	~PNMreader(); // destructor should free this same memory // do destructors need a void argument?
	virtual void Execute(); // reads the file into the resident image, using the resident filename
	virtual const char *SourceName();

};

#endif