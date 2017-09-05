#ifndef SINK_H
#define SINK_H
#include <image.h>

class Sink 
{
protected:
	const Image *img1; // pointer can change, but the thing it points to can't be modified
	const Image *img2; // this is good, because we need to be able to reassign these from NULL to images...

public:
	Sink(void); // default constructor.... that we maybe don't even need?
	~Sink();    // destructor
	void SetInput(const Image * input1);
	void SetInput2(const Image * input2);
	virtual const char *SinkName() = 0;

};


#endif
