//#include <iostream>
#include <stdlib.h>
#include <sink.h>

// constructor
Sink::Sink(void)
{
	img1 = NULL;
	img2 = NULL;
};

// destructor
Sink::~Sink() {};


//*should not make copies of its image inputs, simply point at images that come from sources
// sets the image pointers
void Sink::SetInput(const Image * input1)
{
	img1 = input1;
};

void Sink::SetInput2(const Image * input2)
{
	img2 = input2;
};