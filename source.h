#ifndef SOURCE_H
#define SOURCE_H
#include <image.h>

class Source 
{
protected:
	Image img;
	virtual void Execute() = 0;

public:
	Source(void);
	~Source();

	virtual void Update();
	Image * GetOutput();  // should return pointer to the Image data member
	virtual const char *SourceName() = 0;

};

#endif