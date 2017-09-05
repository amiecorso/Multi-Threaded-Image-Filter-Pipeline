#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <image.h>
//#include <filter.h>
#include <source.h>
using namespace std;

// default constructor
Image::Image(void) 
{
	width = 0;
	height = 0;
	buffer = NULL;
	myfilter = NULL;
	isUpdated = false;
};

// parameterized constructor
Image::Image(int w, int h) 
{
	width = w;
	height = h;
	buffer = (Pixel *)malloc(3 * width * height);
	myfilter = NULL;
	isUpdated = false;
};

// copy constructor
Image::Image(Image &img)
{
	width = img.GetWidth();
	height = img.GetHeight();
	buffer = (Pixel *)malloc(3 * width * height);
	memcpy(buffer, img.GetBuffer(), 3 * width * height);
	myfilter = NULL;
	isUpdated = false;
};

//destructor
Image::~Image()
{
	free(this->buffer);
};


void Image::SetSize(int w, int h) 
{
	width = w;
	height = h;
	buffer = (Pixel *)malloc(3 * width * height);
};

void Image::SetFilter(Source * filter) 
{
	myfilter = filter;
};

void Image::SetStatus(bool status)
{
	isUpdated = status;
};

Pixel * Image::GetBuffer() const
{
	return buffer;
};

int Image::GetHeight() const
{
	return height;
};

int Image::GetWidth() const
{
	return width;
};

Source * Image::GetFilter() const
{
	return myfilter;
};

bool Image::GetStatus() const
{
	return isUpdated;
};

void Image::Update() const
{
	if (isUpdated == false) {
		myfilter->Update();
	}
};



