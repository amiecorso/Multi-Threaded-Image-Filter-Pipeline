#ifndef FILTERS_H
#define FILTERS_H

#include <source.h>
#include <sink.h>

// FILTER
class Filter : public Source, public Sink
{
public:
	Filter(void);  // I think we need an initializer here for the source file??
	~Filter(); // destructor
	virtual void Update();
	virtual const char *FilterName() = 0;
	virtual const char *SourceName();
	virtual const char *SinkName();

};

// SHRINKER
class Shrinker : public Filter
{
public:
	Shrinker(void); // default constructor
	~Shrinker(); // destructor

	virtual void Execute();
	virtual const char *FilterName();
};

// LRCONCAT
class LRConcat : public Filter
{
public:
	LRConcat(void); // default constructor
	~LRConcat(); // destructor

	virtual void Execute();
	virtual const char *FilterName();

};

// TBCONCAT
class TBConcat : public Filter
{
public:
	TBConcat(void); // default constructor
	~TBConcat(); // destructor

	virtual void Execute();
	virtual const char *FilterName();

};

// BLENDER
class Blender : public Filter
{
private:
	float factor;

public:
	Blender(void); // default constructor
	Blender(float fact); // parameterized constructor
	~Blender(); // destructor

	void SetFactor(float fact);
	virtual void Execute();
	virtual const char *FilterName();

};

// MIRROR
class Mirror : public Filter
{
public:
	Mirror(void);

	virtual void Execute();
	virtual const char *FilterName();
};

// ROTATE
class Rotate : public Filter
{
public:
	Rotate(void);

	virtual void Execute();
	virtual const char *FilterName();
};

// SUBTRACT
class Subtract : public Filter
{
public:
	Subtract(void);

	virtual void Execute();
	virtual const char *FilterName();
};

// GRAYSCALE
class Grayscale : public Filter
{
public:
	Grayscale(void);

	virtual void Execute();
	virtual const char *FilterName();
};

// BLUR
class Blur : public Filter
{
public:
	Blur(void);

	virtual void Execute();
	virtual const char *FilterName();
};

// CONSTANT COLOR
class Color : public Source
{
private:
	int red;
	int green;
	int blue;

public:
	Color(void); // default constructor??
	Color(int w, int h, unsigned char r, unsigned char g, unsigned char b); // parameterized constructor.  Colors may need to be unsigned chars?

	virtual void Execute();
	virtual const char *SourceName();
};

// CHECKSUM
class CheckSum : public Sink
{
private:
	long int redsum;
	long int greensum;
	long int bluesum;

public:
	CheckSum(void); // default constructor

	virtual const char *SinkName();
	void OutputCheckSum(const char *filename);
};


#endif