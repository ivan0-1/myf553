#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <complex>
#include <algorithm>
using namespace std;

#define PI 3.1415926535

BITMAPINFO *lpBitsInfo = NULL;
BITMAPINFO *lpBitsInfoFT = NULL;
BITMAPINFO *lpBitsInfoFFT = NULL;
complex<double>* gFD = NULL;
int isGray = FALSE;
int H[256] = {0, };
int showHistogram = FALSE;

void FT(complex<double>* TD, complex<double>* FD, int M);
void IFT(complex<double>* FD, complex<double>* TD, int M);
void FFT(complex<double>* TD, complex<double>* FD, int r);
void IFFT(complex<double>* FD, complex<double>* TD, int r);
void templateOperate(BYTE *newlpBits, int temp[3][3]);

int checkGray() {

	if (lpBitsInfo->bmiHeader.biBitCount != 8) {
		return FALSE;
	}
	
	int flag = TRUE;
	BYTE R, G, B;
	for (int i = 0; i < 256; i++) {
		R = lpBitsInfo->bmiColors[i].rgbRed;
		G = lpBitsInfo->bmiColors[i].rgbGreen;
		B = lpBitsInfo->bmiColors[i].rgbBlue;
		if (R != G || R != B || G != B) {
			flag = FALSE;
			break;
		}
	}

	return flag;
}

// 读取图片
BOOL loadBmpFile(char * bmpFileName) {

	// 读入图片
	FILE *fp = fopen(bmpFileName,"rb");

	// 读取失败
	if (fp == NULL)
		return 2;
	
	// 读取文件头
	BITMAPFILEHEADER *bf = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
	fread(bf, sizeof(BITMAPFILEHEADER), 1, fp);
	
	// 不是bmp文件
	if (bf->bfType != 0x4d42) {
		// not a bit map file
		return 3;
	}

	// 读取信息头
	BITMAPINFOHEADER *bi = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
	fread(bi, sizeof(BITMAPINFOHEADER), 1, fp);


	// 计算调色板数量
	int numOfColors = 0;
	if (bi->biBitCount != 24) {
		if (bi->biClrUsed == 0) {
			numOfColors = (int)pow(2, bi->biBitCount);
		}else {
			numOfColors = bi->biClrUsed;
		}
	}

	//计算每一行的像素占多少字节
	int lineBytes = (bi->biWidth * bi->biBitCount + 31) / 32 * 4;

	//计算实际图像数据占用的字节数
	int imgSize = lineBytes * bi->biHeight;

	// 计算除文件头外的大小
	int size = sizeof(BITMAPINFOHEADER) + numOfColors * sizeof(RGBQUAD) + imgSize;

	// 为lpBitsInfo分配空间
	free(lpBitsInfo);		// 先free掉防止内存泄漏
	lpBitsInfo = (LPBITMAPINFO)malloc(size);

	// 分配失败
	if(lpBitsInfo == NULL){
		return 4;
	}

	// 将文件指针调至信息头
	fseek(fp, sizeof(BITMAPFILEHEADER), SEEK_SET);

	// 读入lpBitsInfo内容
	fread((char *)lpBitsInfo, size, 1, fp);

	// 修改为正确的biClrUsed
	lpBitsInfo->bmiHeader.biClrUsed = numOfColors;

	// 释放内存
	free(bf);
	free(bi);
	fclose(fp);

	isGray = checkGray();
	showHistogram = FALSE;
	free(lpBitsInfoFT);
	free(lpBitsInfoFFT);
	lpBitsInfoFT = NULL;
	lpBitsInfoFFT = NULL;

	return TRUE;
}

// 图像灰度化
void gray() {

	// 计算新文件的Size
	int lineBytes = (lpBitsInfo->bmiHeader.biWidth * lpBitsInfo->bmiHeader.biBitCount + 31) / 32 * 4;
	int imgSize = lineBytes * lpBitsInfo->bmiHeader.biHeight;

	int size = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256 + imgSize;

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// 分配空间
	BITMAPINFO *newLpBitsInfo = (LPBITMAPINFO)malloc(size);

	// 复制信息头
	memcpy(&newLpBitsInfo->bmiHeader, &lpBitsInfo->bmiHeader, sizeof(BITMAPINFOHEADER));

	// 修改信息头中部分信息
	newLpBitsInfo->bmiHeader.biBitCount = 8;
	newLpBitsInfo->bmiHeader.biClrUsed = 256;
	
	
	// 设置调色板
	int i ,j;

	for(i = 0; i < 256; i++) {
		newLpBitsInfo->bmiColors[i].rgbBlue = i;
		newLpBitsInfo->bmiColors[i].rgbGreen = i;
		newLpBitsInfo->bmiColors[i].rgbRed = i;
		newLpBitsInfo->bmiColors[i].rgbReserved = 0;
	}

	// 转换实际颜色信息
	BYTE *lpBits = (BYTE *)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	BYTE *newLpBits = (BYTE *)&newLpBitsInfo->bmiColors[newLpBitsInfo->bmiHeader.biClrUsed];
	
	for(i = 0, j = 0; i < w * h * 3; i+=3, j++) {
		newLpBits[j] = (lpBits[i] + lpBits[i + 1] + lpBits[i + 2]) / 3;
	}

	// 更新指针
	free(lpBitsInfo);
	lpBitsInfo = newLpBitsInfo;

	isGray = TRUE;
}

void pixel(int x, int y, char *str) {

	int h = lpBitsInfo->bmiHeader.biHeight;
	int lineBytes = (lpBitsInfo->bmiHeader.biWidth * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE *lpBits = (BYTE *)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	BYTE *pixel, p;
	int r, g, b;

	switch(lpBitsInfo->bmiHeader.biBitCount) {
		case 1:
			pixel = &lpBits[lineBytes * (h - x - 1) + y / 8];
			p = *pixel & (1 << (7 - y % 8));
			if(p == 0) {
				r = g = b = 0;
			}else {
				r = g = b = 255;
			}
			break;
		case 4:
			pixel = &lpBits[lineBytes * (h - x - 1) + y / 2];
			if(y % 2 == 0) {
				p = *pixel >> 4;
			}else {
				p = *pixel & 0xf;
			}
			r = lpBitsInfo->bmiColors[p].rgbRed;
			g = lpBitsInfo->bmiColors[p].rgbGreen;
			b = lpBitsInfo->bmiColors[p].rgbBlue;
			break;
		case 8:
			pixel = &lpBits[lineBytes * (h - x - 1) + y];
			r = lpBitsInfo->bmiColors[*pixel].rgbRed;
			g = lpBitsInfo->bmiColors[*pixel].rgbGreen;
			b = lpBitsInfo->bmiColors[*pixel].rgbBlue;
			break;
		case 24:
			pixel = &lpBits[lineBytes * (h - x - 1) + y * 3];
			r = pixel[2];
			g = pixel[1];
			b = pixel[0];
			break;
		default:
			return;
	}
	sprintf(str, "RGB( %3d, %3d, %3d)", r, g, b);
}

void histogram() {
	
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	BYTE *lpBits = (BYTE *)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i;
	for (i = 0; i < 256; i++) {
		H[i] = 0;
	}

	for (i = 0; i < w * h; i++) {
		H[lpBits[i]]++;
	}

}

void linearTrans(double a, int b){

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	BYTE *lpBits = (BYTE *)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	double pixel;
	for (int i = 0; i < w * h; i++) {
		pixel = lpBits[i] * a + b +0.5;
		if(pixel > 255) {
			pixel = 255;
		}else if(pixel < 0) {
			pixel = 0;
		}
		lpBits[i] = (BYTE)pixel;
	}

	histogram();
}

void equalize() {

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	BYTE *lpBits = (BYTE *)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	int i;

	histogram();

	double cH[256];
	cH[0] = 1.0 * H[0] / (w * h);
	for(i = 1; i < 256; i++) {
		cH[i] = 1.0 * H[i] / (w * h) + cH[i - 1];
	}

	int D[255];
	for(i = 0; i < 256; i++) {
		D[i] = (int)(cH[i] * 255 + 0.5);
	}


	for(i = 0; i < w * h; i++) {
		lpBits[i] = D[lpBits[i]];
	}

	histogram();
}


void fourier() {

	int lineBytes = (lpBitsInfo->bmiHeader.biWidth * lpBitsInfo->bmiHeader.biBitCount + 31) / 32 * 4;
	int imgSize = lineBytes * lpBitsInfo->bmiHeader.biHeight;
	int size = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256 + imgSize;

	free(lpBitsInfoFT);
	lpBitsInfoFT = (LPBITMAPINFO)malloc(size);
	memcpy(&lpBitsInfoFT->bmiHeader, &lpBitsInfo->bmiHeader, sizeof(BITMAPINFOHEADER));
	
	BYTE *lpBits = (BYTE *)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	BYTE *lpBitsFT = (BYTE *)&lpBitsInfoFT->bmiColors[lpBitsInfoFT->bmiHeader.biClrUsed];


	int i ,j;

	for(i = 0; i < 256; i++) {
		lpBitsInfoFT->bmiColors[i].rgbBlue = i;
		lpBitsInfoFT->bmiColors[i].rgbGreen = i;
		lpBitsInfoFT->bmiColors[i].rgbRed = i;
		lpBitsInfoFT->bmiColors[i].rgbReserved = 0;
	}


	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	complex<double>* TD = new complex<double>[w * h];
	complex<double>* FD = new complex<double>[w * h];
	

	for(i = 0; i < w * h; i++) {
		TD[i] = complex<double>(lpBits[i] * pow(-1, i / lineBytes + i), 0);
	}


	for(i = 0; i < h; i++) {
		FT(&TD[w * i], &FD[w * i], w);
	}
	
	for(i = 0; i < h; i++) {
		for(j = 0; j < w; j++) {
			TD[i + h * j] = FD[j + w * i];
		}
	}

	for(i = 0; i < w; i++) {
		FT(&TD[h * i], &FD[h * i], h);
	}

	for(i = 0; i < w * h; i++) {
		double tmp = sqrt(pow(FD[i].real(), 2) + pow(FD[i].imag(), 2)) * 2000;
		if(tmp > 255) {
			tmp = 255;
		}
		int x = i % w;
		int y = i / w;
		lpBitsFT[x * w + y] = (BYTE)tmp;
	}

	gFD = FD;
	delete TD;
}

void FT(complex<double>* TD, complex<double>* FD, int M) {

	for(int u = 0; u < M; u++) {
		FD[u] = 0;
		for(int x = 0; x < M; x++) {
			double angle = -2 * PI * u * x / M;
			FD[u] += TD[x] * complex<double>(cos(angle), sin(angle));
		}
		FD[u] /= M;
	}
}


void invertFourier() {
	
	int lineBytes = (lpBitsInfo->bmiHeader.biWidth * lpBitsInfo->bmiHeader.biBitCount + 31) / 32 * 4;
	BYTE *lpBits = (BYTE *)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	complex<double>* TD = new complex<double>[w * h];
	complex<double>* temp = new complex<double>[w * h];

	int i, j;

	for(i = 0; i < h; i++) {
		IFT(&gFD[w * i], &TD[w * i], w);
	}

	for(i = 0; i < h; i++) {
		for(j = 0; j < w; j++) {
			temp[i + h * j] = TD[j + w * i];
		}
	}

	for(i = 0; i < w; i++) {
		IFT(&temp[h * i], &TD[h * i], h);
	}

	for(i = 0; i < w * h; i++) {
		double tmp = TD[i].real() * pow(-1, i / lineBytes + i);
		lpBits[i] = (BYTE)tmp;
	}

	delete TD;
	delete temp;

}

void IFT(complex<double>* FD, complex<double>* TD, int M) {

	for(int u = 0; u < M; u++) {
		TD[u] = 0;
		for(int x = 0; x < M; x++) {
			double angle = 2 * PI * u * x / M;
			TD[u] += FD[x] * complex<double>(cos(angle), sin(angle));
		}
	}
}

void fastFourier() {
	//图像的宽度和高度
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	//指向图像数据指针
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// FFT宽度（必须为2的整数次方）
	int FFT_w = 1;
	// FFT宽度的幂数，即迭代次数
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}

	// FFT高度（必须为2的整数次方）
	int FFT_h = 1;
	// FFT高度的幂数，即迭代次数
	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}

	// 分配内存
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	BYTE* pixel;
	
	for(i = 0; i < FFT_h; i++)  // 行
	{
		for(j = 0; j < FFT_w; j++)  // 列
		{
			// 指向DIB第i行，第j个象素的指针
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// 给时域赋值
			TD[j + FFT_w * i] = complex<double>(*pixel* pow(-1,i+j), 0);
		}
	}
	
	for(i = 0; i < FFT_h; i++)
	{
		// 对y方向进行快速付立叶变换
		FFT(&TD[FFT_w * i], &FD[FFT_w * i], wp);
	}
	
	// 保存中间变换结果
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			TD[i + FFT_h * j] = FD[j + FFT_w * i];
		}
	}
	
	for(i = 0; i < FFT_w; i++)
	{
		// 对x方向进行快速付立叶变换
		FFT(&TD[i * FFT_h], &FD[i * FFT_h], hp);
	}

	// 删除临时变量
	delete TD;

	//生成频谱图像
	//为频域图像分配内存
	LONG size = 40 + 1024 + LineBytes * height;
	lpBitsInfoFFT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpBitsInfoFFT)
		return;
	memcpy(lpBitsInfoFFT, lpBitsInfo, size);

	//指向频域图像数据指针
	lpBits = (BYTE*)&lpBitsInfoFFT->bmiColors[lpBitsInfoFFT->bmiHeader.biClrUsed];

	double temp;
	for(i = 0; i < FFT_h; i++) // 行
	{
		for(j = 0; j < FFT_w; j++) // 列
		{
			// 计算频谱幅度
			temp = sqrt(FD[j * FFT_h + i].real() * FD[j * FFT_h + i].real() + 
				        FD[j * FFT_h + i].imag() * FD[j * FFT_h + i].imag()) *2000;
			
			// 判断是否超过255
			if (temp > 255)
			{
				// 对于超过的，直接设置为255
				temp = 255;
			}
			
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// 更新源图像
			*pixel = (BYTE)(temp);
		}
	}

	gFD=FD;
}

void FFT(complex<double>* TD, complex<double>* FD, int r) {

	LONG count = 1 << r;
	int i;
	double angle;
	complex<double>* W = new complex<double>[count / 2];
	for(i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	complex<double>* X1 = new complex<double>[count];
	memcpy(X1, TD, sizeof(complex<double>) * count);
	
	complex<double>* X2 = new complex<double>[count]; 

	int k,j,p,size;
	complex<double>* temp;
	for (k = 0; k < r; k++)
	{
		for (j = 0; j < 1 << k; j++)
		{
			size = 1 << (r-k);
			for (i = 0; i < size/2; i++)
			{
				p = j * size;
				X2[i + p] = X1[i + p] + X1[i + p + size/2];
				X2[i + p + size/2] = (X1[i + p] - X1[i + p + size/2]) * W[i * (1<<k)];
			}
		}
		temp  = X1;
		X1 = X2;
		X2 = temp;
	}
	
	for (j = 0; j < count; j++)
	{
		p = 0;
		for (i = 0; i < r; i++)
		{
			if (j & (1<<i))
			{
				p += 1<<(r-i-1);
			}
		}
		FD[j]=X1[p];
		FD[j] /= count;
	}
	
	delete W;
	delete X1;
	delete X2;

}

void invertFastFourier() {
	//图像的宽度和高度
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// FFT宽度（必须为2的整数次方）
	int FFT_w = 1;
	// FFT宽度的幂数，即迭代次数
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}

	// FFT高度（必须为2的整数次方）
	int FFT_h = 1;
	// FFT高度的幂数，即迭代次数
	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}

	// 分配内存
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	for(i = 0; i < FFT_h; i++)  // 行
		for(j = 0; j < FFT_w; j++)  // 列
			FD[j + FFT_w * i] = gFD[i + FFT_h*j];
	
	// 沿水平方向进行快速付立叶变换
	for(i = 0; i < FFT_h; i++)
		IFFT(&FD[FFT_w * i], &TD[FFT_w * i], wp);
	
	// 保存中间变换结果
	for(i = 0; i < FFT_h; i++)
		for(j = 0; j < FFT_w; j++)
			FD[i + FFT_h * j] = TD[j + FFT_w * i];
	
	// 沿垂直方向进行快速付立叶变换
	for(i = 0; i < FFT_w; i++)
		IFFT(&FD[i * FFT_h], &TD[i * FFT_h], hp);


	//指向反变换图像数据指针
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	BYTE* pixel;
	double temp;
	for(i = 0; i < FFT_h; i++) // 行
	{
		for(j = 0; j < FFT_w; j++) // 列
		{
			pixel = lpBits + LineBytes * (height - 1 - i) + j;
			temp= (TD[j*FFT_h + i].real() / pow(-1, i+j));
			if (temp < 0)
				temp = 0;
			else if (temp >255)
				temp = 255;
			*pixel = (BYTE)temp;
		}
	}

	// 删除临时变量
	delete FD;
	delete TD;

}

void IFFT(complex<double>* FD, complex<double>* TD, int r) {
	// 付立叶变换点数
	LONG	count;
	// 计算付立叶变换点数
	count = 1 << r;

	// 分配运算所需存储器
	complex<double> * X = new complex<double>[count];
	// 将频域点写入X
	memcpy(X, FD, sizeof(complex<double>) * count);
	
	// 求共轭
	for(int i = 0; i < count; i++)
		X[i] = complex<double> (X[i].real(), -X[i].imag());
	
	// 调用快速付立叶变换
	FFT(X, TD, r);
	
	// 求时域点的共轭
	for(i = 0; i < count; i++)
		TD[i] = complex<double> (TD[i].real() * count, -TD[i].imag() * count);
	
	// 释放内存
	delete X;
}

void templateOperate(BYTE *newlpBits, int temp[3][3]) {
	
	BYTE *lpBits = (BYTE *)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	int lineBytes = (lpBitsInfo->bmiHeader.biWidth * lpBitsInfo->bmiHeader.biBitCount + 31) / 32 * 4;

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int i, j, k, l;
	int coef = 0;

	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			coef += temp[i][j]; 
		}
	}

	for(i = 0; i < h; i++) {
		for(j = 0; j < w; j++) {
			if (i == 0 || j == 0 || i == h - 1 || j == w - 1){
				newlpBits[j + i * lineBytes] = lpBits[j + i * lineBytes];
				continue;
			}
			int x = j;
			int y = (h - 1 - i);
			int sum = 0;
			for(k = 0; k < 3; k++) {
				for(l = 0; l < 3; l++) {
					sum += lpBits[(x + k - 1) + (y + l - 1) * lineBytes] * temp[k][l];
				}
			}
			sum /= coef;
			if(sum < 0) {
				sum = 0;
			} else if(sum > 255){
				sum = 255;
			}
			newlpBits[x + y * lineBytes] = (BYTE)sum;
		}
	}
	
}

void averageFilter() {

	int lineBytes = (lpBitsInfo->bmiHeader.biWidth * lpBitsInfo->bmiHeader.biBitCount + 31) / 32 * 4;
	int imgSize = lineBytes * lpBitsInfo->bmiHeader.biHeight;

	BYTE *lpBits = (BYTE *)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	BYTE *newlpBits = (BYTE *)malloc(imgSize);
	/*
	int temp[3][3] = {
		{1, 2, 1},
		{2, 4, 2},
		{1, 2, 1},
	};
	*/
	int temp[3][3] = {
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1},
	};
	templateOperate(newlpBits, temp);

	memcpy(lpBits, newlpBits, imgSize);
	free(newlpBits);
	histogram();
}


void medianFilter() {

	int lineBytes = (lpBitsInfo->bmiHeader.biWidth * lpBitsInfo->bmiHeader.biBitCount + 31) / 32 * 4;
	int imgSize = lineBytes * lpBitsInfo->bmiHeader.biHeight;

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	BYTE *lpBits = (BYTE *)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	BYTE *newlpBits = (BYTE *)malloc(imgSize);

	int i, j, k, l;

	for(i = 0; i < h; i++) {
		for(j = 0; j < w; j++) {
			if (i == 0 || j == 0 || i == h - 1 || j == w - 1){
				newlpBits[j + i * lineBytes] = lpBits[j + i * lineBytes];
				continue;
			}
			int x = j;
			int y = (h - 1 - i);
			int mid = 0;
			int value[9] = {0, };
			for(k = 0; k < 3; k++) {
				for(l = 0; l < 3; l++) {
					value[k * 3 + l] = lpBits[(x + k - 1) + (y + l - 1) * lineBytes];
				}
			}
			sort(value, value + 9);
			mid = value[4];
			if(mid < 0) {
				mid = 0;
			} else if(mid > 255){
				mid = 255;
			}
			newlpBits[x + y * lineBytes] = (BYTE)mid;
		}
	}

	memcpy(lpBits, newlpBits, imgSize);
	free(newlpBits);
	histogram();
}

void gradientSharpen() {

	int lineBytes = (lpBitsInfo->bmiHeader.biWidth * lpBitsInfo->bmiHeader.biBitCount + 31) / 32 * 4;
	int imgSize = lineBytes * lpBitsInfo->bmiHeader.biHeight;

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	BYTE *lpBits = (BYTE *)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	BYTE *newlpBits = (BYTE *)malloc(imgSize);

	int i, j;

	for(i = 0; i < h; i++) {
		for(j = 0; j < w; j++) {
			if (i == h - 1 || j == w - 1){
				newlpBits[j + i * lineBytes] = lpBits[j + i * lineBytes];
				continue;
			}
			int x = j;
			int y = (h - 1 - i);
			int tmp = 0;
			tmp += abs(lpBits[x + y * lineBytes] - lpBits[(x - 1) + y * lineBytes]);
			tmp += abs(lpBits[x + y * lineBytes] - lpBits[x + (y - 1) * lineBytes]);

			if(tmp < 0) {
				tmp = 0;
			} else if(tmp > 255){
				tmp = 255;
			}
			newlpBits[x + y * lineBytes] = (BYTE)tmp;
		}
	}

	memcpy(lpBits, newlpBits, imgSize);
	free(newlpBits);
	histogram();
}

void laplaceSharpen() {

	int lineBytes = (lpBitsInfo->bmiHeader.biWidth * lpBitsInfo->bmiHeader.biBitCount + 31) / 32 * 4;
	int imgSize = lineBytes * lpBitsInfo->bmiHeader.biHeight;

	BYTE *lpBits = (BYTE *)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	BYTE *newlpBits = (BYTE *)malloc(imgSize);
	
	int temp[3][3] = {
		{ 0, -1,  0},
		{-1,  5, -1},
		{ 0, -1,  0},
	};
	/*
	int temp[3][3] = {
		{-1, -1, -1},
		{-1,  9, -1},
		{-1, -1, -1},
	};
	*/
	templateOperate(newlpBits, temp);

	memcpy(lpBits, newlpBits, imgSize);
	free(newlpBits);
	histogram();
}