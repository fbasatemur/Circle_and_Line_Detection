#pragma once
#include <windows.h>
#include <vector>
#include <atlstr.h>	

//int* sobelFilter(int*, int&, int&, int*, int*, int);

int* smoothing(BYTE* raw_intensity, int& Width, int& Height, int* smoothFilter, int filterSize, int divisor);

void magnitudeAndDirection(int* image, int& width, int& height, int* gradientX, int* gradientY, int* magnitudeImage, int* quantizedGradientDir, int* gradientDir, int filterSize);

int* createHistMatris(int* rawIndensity, int width, int height, int histSize);

int* nonMaximalSuppression(int* magnitudeImage, int* quantizedGradientDir, int width, int height);

void hysteresisThreashold(int* magnitudeImage, int* quantizedGradientDir, int width, int height, int TH, int TL);

void displayBinaryBitmap(int* intensityMat, int width, int height, System::Drawing::Bitmap^ bitmap);

int* houghTransformLine(int* binaryImage, int width, int height, int imageW, int imageH, int& houghWidth, int& houghHeight);

void searchMaxPoint(int* houghSpace, int houghWidth, int houghHeight, std::vector <int>& MaxsD, std::vector<int>& MaxsQ, int numOfMaks);

void markMaxEdge(BYTE* raw_intensity, int imWidth, int* binaryEdge, int Width, int Height, std::vector <int>& MaxsD, std::vector<int>& MaxsQ);

void displayLineBitmap(BYTE* raw_intensity, int imWidth, int imHeight, System::Drawing::Bitmap^ bitmap);

int* houghTransformCircle(int* binaryImage, int* gradientDir, int width, int height, int& houghWidth, int& houghHeight, int circleR, int imageW, int imageH);

void displayHoughBitmap(int* houghSpace, int houghWidth, int houghHeight, System::Drawing::Bitmap^ bitmap);

int drawMaxCircle(BYTE* raw_intensity, int imWidth, int Width, std::vector <int>& MaxsD, std::vector<int>& MaxsQ, int circleR);








