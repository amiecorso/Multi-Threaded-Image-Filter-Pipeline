#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <filters.h>
#include <logging.h>
using namespace std;

// FILTER
Filter::Filter(void) {};

Filter::~Filter() {};     // destructor

void Filter::Update() 
{
	char msg[128];

	if (img1 == NULL) {
		sprintf(msg, "%s: no input1!", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}

	if ( (img1 != NULL) && (img1->GetStatus() == false) ) {
		sprintf(msg, "%s: about to update input1", SinkName());
		Logger::LogEvent(msg);
		img1->Update();
		sprintf(msg, "%s: done updating input1", SinkName());
		Logger::LogEvent(msg);
	}

	if ( (img2 != NULL) && (img2->GetStatus() == false)) {
		sprintf(msg, "%s: about to update input2", SinkName());
		Logger::LogEvent(msg);
		img2->Update();
		sprintf(msg, "%s: done updating input2", SinkName());
		Logger::LogEvent(msg);
	}

	sprintf(msg, "%s: about to execute", SourceName());
	Logger::LogEvent(msg);
	Execute();
	//img.SetStatus(true);  // tell your image that it's updated now... 
	sprintf(msg, "%s: done executing", SourceName());
	Logger::LogEvent(msg);
};

const char *Filter::SourceName()
{
	return FilterName();
};

const char *Filter::SinkName()
{
	return FilterName();
};



// SHRINKER
Shrinker::Shrinker(void) // default constructor
{
	img.SetFilter(this);
};

Shrinker::~Shrinker()    // destructor
{
	// shouldn't need any additional destructor behavior beyond that of the source / sink?
};

void Shrinker::Execute()
{	
	// inputs valid, proceed
	int in_width = img1->GetWidth();
	int in_height = img1->GetHeight();
	int out_width = in_width / 2;
	int out_height = in_height / 2;

	img.SetSize(out_width, out_height);

	int outputindex = 0;
	for (int i = 0; i < (out_height); i++) {
		int start = 2 * i * in_width;
		for (int j = start; j < (start + in_width); j+=2) {
			img.GetBuffer()[outputindex] = img1->GetBuffer()[j];
			outputindex++;
		}
	}
};

const char *Shrinker::FilterName()
{
	return "Shrinker";
};



// LRCONCAT
LRConcat::LRConcat(void){ // default constructor
	img.SetFilter(this);
};

LRConcat::~LRConcat(){}; // destructor

void LRConcat::Execute()
{
	char msg[1024];
	// check for input2
	if (img2 == NULL) {
		sprintf(msg, "no input2!");
		DataFlowException e(FilterName(), msg);
		throw e;
	}

	// check for equal heights
	if (img1->GetHeight() != img2->GetHeight()) {
		sprintf(msg, "Heights must match: %d, %d", img1->GetHeight(), img2->GetHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	// inputs valid, proceed
	img.SetSize(img1->GetWidth() + img2->GetWidth(), img1->GetHeight());

	int outputindex = 0;
	for (int i = 0; i < img.GetHeight(); i++) { //for every row
		int left_row_start = i * img1->GetWidth();
		for (int j = left_row_start; j < (left_row_start + img1->GetWidth()); j++) {
			img.GetBuffer()[outputindex] = img1->GetBuffer()[j];
			outputindex++;
		}
		int right_row_start = i * img2->GetWidth();
		for (int j = right_row_start; j < (right_row_start + img2->GetWidth()); j++) {
			img.GetBuffer()[outputindex] = img2->GetBuffer()[j];
			outputindex++;
		}
	}
};

const char *LRConcat::FilterName()
{
	return "LRConcat";
};



// TBCONCAT
TBConcat::TBConcat(void) // default constructor
{	
	img.SetFilter(this);
}; 

TBConcat::~TBConcat(){}; // destructor

void TBConcat::Execute()
{
	char msg[1024];
	// check for input2
	if (img2 == NULL) {
		sprintf(msg, "no input2!");
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	// check for equal widths
	if (img1->GetWidth() != img2->GetWidth()) {
		sprintf(msg, "%s: Widths must match: %d, %d", SinkName(), img1->GetWidth(), img2->GetWidth());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	// input valid, proceed
	img.SetSize(img1->GetWidth(), img2->GetHeight() + img1->GetHeight());

	int outputindex = 0;
	for (int i = 0; i < (img1->GetWidth() * img1->GetHeight()); i++) {
		img.GetBuffer()[outputindex] = img1->GetBuffer()[i];
		outputindex++;
	}
	for (int i = 0; i < (img2->GetWidth() * img2->GetHeight()); i++) {
		img.GetBuffer()[outputindex] = img2->GetBuffer()[i];
		outputindex++;
	}
};

const char *TBConcat::FilterName()
{
	return "TBConcat";
};



// BLENDER
Blender::Blender(void) // default constructor
{
	img.SetFilter(this);
}; 

Blender::Blender(float fact) // parameterized constructor
{
	factor = fact;
};

Blender::~Blender(){}; // destructor

void Blender::SetFactor(float fact)
{
	factor = fact;
};

void Blender::Execute()
{
	// check for valid factor value
	char msg[1024];
	if (factor < 0 || factor > 1.0) {
		sprintf(msg, "Invalid factor for Blender: %f", factor);
		DataFlowException e(FilterName(), msg);
		throw e;
	}

	// inputs valid, proceed
	img.SetSize(img1->GetWidth(), img1->GetHeight());
	float factor2 = (1 - factor);

	for (int i = 0; i < (img.GetHeight() * img.GetWidth()); i++) {
		img.GetBuffer()[i].R = (factor * (img1->GetBuffer()[i].R)) + (factor2 * (img2->GetBuffer()[i].R));
		img.GetBuffer()[i].G = (factor * (img1->GetBuffer()[i].G)) + (factor2 * (img2->GetBuffer()[i].G));
		img.GetBuffer()[i].B = (factor * (img1->GetBuffer()[i].B)) + (factor2 * (img2->GetBuffer()[i].B));

	}
};

const char *Blender::FilterName()
{
	return "Blender";
};



// MIRROR
Mirror::Mirror(void)
{
	img.SetFilter(this);
};

void Mirror::Execute()
{
	// error checking here...
	// input valid, proceed
    int grab_index  = 0;
    int place_index = 0;
	img.SetSize(img1->GetWidth(), img1->GetHeight());
    int image_width  = img.GetWidth();
	for (int row = 0; row < img.GetHeight(); row++) { // go by row
		for (int i = 0; i < image_width; i++) { // and then by index
			grab_index = ((image_width - 1) - i) + (row * image_width);
			place_index = (row * image_width) + i;
			img.GetBuffer()[place_index] = img1->GetBuffer()[grab_index];
		}
	}
};

const char *Mirror::FilterName()
{
	return "Mirror";
};



// ROTATE
Rotate::Rotate(void)
{
	img.SetFilter(this);
};

void Rotate::Execute() 
{
	img.SetSize(img1->GetHeight(), img1->GetWidth()); // swap width/height of input image
	for (int row = 0; row < img1->GetHeight(); row++) { // for row in original
		for (int i = 0; i < img1->GetWidth(); i++) { // for column in original row
			int grab_index = (img1->GetWidth() * row) + i;
			int place_index = (img.GetWidth() - 1 - row) + (img.GetWidth() * i);
			img.GetBuffer()[place_index] = img1->GetBuffer()[grab_index];
		}
	}
};

const char *Rotate::FilterName()
{
	return "Rotate";
};



// SUBTRACT
Subtract::Subtract(void)
{
	img.SetFilter(this);
};

void Subtract::Execute()
{
	img.SetSize(img1->GetWidth(), img1->GetHeight());
	for (int i = 0; i < img.GetWidth() * img.GetHeight(); i++) {
		// red channel
		if (img1->GetBuffer()[i].R > img2->GetBuffer()[i].R) {
			img.GetBuffer()[i].R = img1->GetBuffer()[i].R - img2->GetBuffer()[i].R;
		}
		else {img.GetBuffer()[i].R = 0;}
		// green channel
		if (img1->GetBuffer()[i].G > img2->GetBuffer()[i].G) {
			img.GetBuffer()[i].G = img1->GetBuffer()[i].G - img2->GetBuffer()[i].G;
		}
		else {img.GetBuffer()[i].G = 0;}
		// blue channel
		if (img1->GetBuffer()[i].B > img2->GetBuffer()[i].B) {
			img.GetBuffer()[i].B = img1->GetBuffer()[i].B - img2->GetBuffer()[i].B;
		}
		else {img.GetBuffer()[i].B = 0;}
	}
};

const char *Subtract::FilterName()
{
	return "Subtract";
};



// GRAYSCALE
Grayscale::Grayscale(void)
{
	img.SetFilter(this);
};

void Grayscale::Execute()
{
	img.SetSize(img1->GetWidth(), img1->GetHeight());
	for (int i = 0; i < img.GetWidth() * img.GetHeight(); i++) {
		img.GetBuffer()[i].R = (img1->GetBuffer()[i].R) / 5 + (img1->GetBuffer()[i].G) / 2 + (img1->GetBuffer()[i].B) / 4;
		img.GetBuffer()[i].G = (img1->GetBuffer()[i].R) / 5 + (img1->GetBuffer()[i].G) / 2 + (img1->GetBuffer()[i].B) / 4;
		img.GetBuffer()[i].B = (img1->GetBuffer()[i].R) / 5 + (img1->GetBuffer()[i].G) / 2 + (img1->GetBuffer()[i].B) / 4;

	}
};

const char *Grayscale::FilterName()
{
	return "Grayscale";
};



// BLUR
Blur::Blur(void)
{
	img.SetFilter(this);
};

void Blur::Execute()
{
	img.SetSize(img1->GetWidth(), img1->GetHeight());
    
    int target,east,west,north,south,nw,ne,sw,se = 0;
	for (int i = 0; i < img.GetWidth() * img.GetHeight(); i++) {
		img.GetBuffer()[i] = img1->GetBuffer()[i]; // populate entire image
	}
	for (int row = 1; row < img.GetHeight() - 1; row++) {
		for (int i = 1; i < img.GetWidth() - 1; i++) {
			target = (row * img.GetWidth()) + i; // target pixel index
			east = target + 1;
			west = target - 1;
			north = target - img.GetWidth();
			south = target + img.GetWidth();
			nw = north - 1;
			ne = north + 1;
			sw = south - 1;
			se = south + 1;
			img.GetBuffer()[target].R = img1->GetBuffer()[east].R/8 + img1->GetBuffer()[west].R/8 + img1->GetBuffer()[north].R/8 + 
				img1->GetBuffer()[south].R/8 + img1->GetBuffer()[nw].R/8 + img1->GetBuffer()[ne].R/8 + 
					img1->GetBuffer()[sw].R/8 + img1->GetBuffer()[se].R/8;
			img.GetBuffer()[target].G = img1->GetBuffer()[east].G/8 + img1->GetBuffer()[west].G/8 + img1->GetBuffer()[north].G/8 + 
				img1->GetBuffer()[south].G/8 + img1->GetBuffer()[nw].G/8 + img1->GetBuffer()[ne].G/8 + 
					img1->GetBuffer()[sw].G/8 + img1->GetBuffer()[se].G/8;
			img.GetBuffer()[target].B = img1->GetBuffer()[east].B/8 + img1->GetBuffer()[west].B/8 + img1->GetBuffer()[north].B/8 + 
				img1->GetBuffer()[south].B/8 + img1->GetBuffer()[nw].B/8 + img1->GetBuffer()[ne].B/8 + 
					img1->GetBuffer()[sw].B/8 + img1->GetBuffer()[se].B/8;
		}
	}
};

const char *Blur::FilterName()
{
	return "Blur";
};



// CONSTANT COLOR
Color::Color(void)
{
	img.SetFilter(this);
};

Color::Color(int w, int h, unsigned char r, unsigned char g, unsigned char b) // parameterized constructor.
{
	img.SetFilter(this);
	img.SetSize(w, h);
	red = r;
	green = g;
	blue = b;
};


void Color::Execute() 
{
	for (int i = 0; i < img.GetWidth() * img.GetHeight(); i++) {
		img.GetBuffer()[i].R = red;
		img.GetBuffer()[i].G = green;
		img.GetBuffer()[i].B = blue;
	}
};

const char *Color::SourceName()
{
	return "Color";
};



// CHECKSUM
CheckSum::CheckSum(void) // default constructor
{

};

void CheckSum::OutputCheckSum(const char *filename)
{
	redsum = 0;
	greensum = 0;
	bluesum = 0;
	for (int i = 0; i < img1->GetWidth() * img1->GetHeight(); i++) {
		redsum += img1->GetBuffer()[i].R;
		greensum += img1->GetBuffer()[i].G;
		bluesum += img1->GetBuffer()[i].B;
	}

	redsum = redsum % 256;
	greensum = greensum % 256;
	bluesum = bluesum % 256;

	ofstream f_out;
	f_out.open(filename, ios::out);
	f_out << "CHECKSUM: " << redsum << ", " << greensum << ", " << bluesum << endl;
	f_out.close();

};

const char *CheckSum::SinkName()
{
	return "CheckSum";
};




