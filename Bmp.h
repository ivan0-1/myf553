// Bmp.h : Bmp.cpp header file 
//


extern LPBITMAPINFO lpBitsInfo;
extern int isGray;
extern int H[256];
extern int showHistogram;

BOOL loadBmpFile(char * bmpFileName);
void gray();
void pixel(int x, int y, char *str);
void histogram();