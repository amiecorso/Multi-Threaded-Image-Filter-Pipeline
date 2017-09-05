#ifndef PNMWRITER_H
#define PNMWRITER_H

#include <sink.h>

class PNMwriter : public Sink
{
public:
	PNMwriter(void); // constructor
	~PNMwriter();  // destructor

	void Write(char *outfile);  // write to output file
	virtual const char *SinkName();

};

#endif
