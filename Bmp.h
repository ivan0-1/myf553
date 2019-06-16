// Bmp.h : Bmp.cpp header file 
//

#include <complex>

extern LPBITMAPINFO lpBitsInfo;
extern BITMAPINFO *lpBitsInfoFT;
extern BITMAPINFO *lpBitsInfoFFT;
extern int isGray;
extern int H[256];
extern int showHistogram;
extern std::complex<double> *gFD;

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
void frequencyDomainFilter(int D);
