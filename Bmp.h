// Bmp.h : Bmp.cpp header file 
//


extern LPBITMAPINFO lpBitsInfo;
extern BITMAPINFO *lpBitsInfoFT;
extern BITMAPINFO *lpBitsInfoFFT;
extern int isGray;
extern int H[256];
extern int showHistogram;

BOOL loadBmpFile(char * bmpFileName);
void gray();
void pixel(int x, int y, char *str);
void histogram();
void linearTrans(double a, int b);
void equalize();
void fourier();
void invertFourier();
void fastFourier();
void invertFastFourier();
void averageFilter();
void medianFilter();
void gradientSharpen();
void laplaceSharpen();