#pragma once
#include <windows.h>
#include <vector>
#include <atlstr.h>	

//int* sobelFilter(int*, int&, int&, int*, int*, int);
int* createHistMatris(int*, int, int, int);
int* smoothing(BYTE* raw_intensity, int& Width, int& Height, int* smoothFilter, int filterSize, int divisor);
void magnitudeAndDirection(int* raw_intensity, int& Width, int& Height, int* gradientX, int* gradientY, int* magnitudeImage, int* directionImage, int* directions, int filterSize);
void displayBinaryBitmap(int* intensityMat, int Width, int Height, System::Drawing::Bitmap^ bitmap);
int directionQuantize(int direction);
int* nonMaximalSuppression(int* magnitudeImage, int* gradientDirections, int Width, int Height);
void hysteresisThreashold(int* magnitudeImage, int* gradientDirections, int Width, int Height, int T1, int T2);
void convertToBinary(int* magnitudeImage, int Width, int Height);
int* houghTransformLine(BYTE* raw_intensity, int imageW, int imageH, int* binaryImage, int Width, int Height, int &houghWidth, int &houghHeight);
void deepCopy(int* hostMem, int* copyMem, int Width, int Height);
void searchMaxEdge(int* houghSpace, int houghWidth, int houghHeight, std::vector <int>& MaxsD, std::vector<int>& MaxsQ, int numOfMaks);
void controlMaxEdge(BYTE* raw_intensity, int imWidth, int imHeight, int* binaryEdge, int Width, int Height, std::vector <int>& MaxsD, std::vector<int>& MaxsQ);
void displayLineBitmap(BYTE* raw_intensity, int imWidth, int imHeight, System::Drawing::Bitmap^ bitmap);

void displayHoughBitmap(int* houghSpace, int houghWidth, int houghHeight, System::Drawing::Bitmap^ bitmap);
int* houghTransformCircle(int* binaryImage, int* gradientDirections, int * directions,int Width, int Height, int& houghWidth, int& houghHeight, int circleR, int imWidth, int imHeight);
void controlMaxCircle(BYTE* raw_intensity, int imWidth, int imHeight, int* binaryEdge, int Width, int Height, std::vector <int>& MaxsD, std::vector<int>& MaxsQ, int circleR);







