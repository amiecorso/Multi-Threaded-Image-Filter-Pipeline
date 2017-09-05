#ifndef IMAGE_330
#define IMAGE_330

class Source;

struct Pixel
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};


class Image
{
private: // is this redundant, since Image is a class?
	int width, height;
	Source *myfilter; // pointer to Source object that HAS this image
	Pixel *buffer; 
	bool isUpdated; // determines whether img has been populated with good content by its owner Source object, whether PNMreader or Filter

public:
	Image(void); // default constructor
	Image(int w, int h); // parameterized constructor
	Image(Image &); // copy constructor
	~Image(); // destructor

	void SetSize(int width, int height);  // establishes width, height and mallocs new Pixel buffer
	void SetFilter(Source *filter);
	void SetStatus(bool status);

	int GetHeight() const;
	int GetWidth() const;
	Pixel * GetBuffer() const;
	Source * GetFilter() const;
	bool GetStatus() const;

	void Update() const;
};

#endif
