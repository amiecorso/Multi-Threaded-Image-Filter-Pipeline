#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <source.h>
#include <image.h>
#include <logging.h>
using namespace std;


// default constructor
Source::Source(void) {};

// destructor
Source::~Source() {};

// pure virtual Source::Execute() {}: ??

void Source::Update()
{
	char msg[128];
	sprintf(msg, "%s: about to execute", SourceName());
	Logger::LogEvent(msg);
	Execute();
	img.SetStatus(true);  // tell your image that it's updated now... 
	//Commented out to match Hank's log file.  Saves time if it is there (never have to run all the way back up to PNMreader).
	sprintf(msg, "%s: done executing", SourceName());
	Logger::LogEvent(msg);
};

Image * Source::GetOutput()
{
	return &img;  // return ADDRESS OF the image data member...
};
