
#include "image_Processing.h"
#include <math.h>
#include <ctime>
#include <iostream>

#define PI 3.14159265
#define MIN(a,b) ((a < b) ? a : b)
#define MAX(a,b) ((a > b) ? a : b)
#define REDPIXEL 2
#define ANGLEQUANTIZE 5
#define DISTQUANTIZE 10

//int* sobelFilter(int* raw_intensity, int& Width, int& Height, int* gradientX, int* gradientY, int filterSize)
//{
//	int newWidth = (Width - (filterSize - 1));
//	int newHeight = (Height - (filterSize - 1));
//	int* smoothImage = new int[newWidth * newHeight];
//
//	int totalX = 0;
//	int totalY = 0;
//	for (int row = 0; row < newHeight; row++)
//	{
//		for (int col = 0; col < newWidth; col++)
//		{
//			totalX = 0;
//			totalY = 0;
//			for (int i = 0; i < filterSize; i++)
//			{
//				for (int j = 0; j < filterSize; j++)
//				{
//					totalX += raw_intensity[(row + i) * Width + col + j] * gradientX[i * filterSize + j];
//					totalY += raw_intensity[(row + i) * Width + col + j] * gradientY[i * filterSize + j];
//				}
//			}
//			smoothImage[row * newWidth + col] = abs(totalX) + abs(totalY);
//		}
//	}
//
//	Width = newWidth;
//	Height = newHeight;
//	return smoothImage;
//}

int* smoothing(BYTE* raw_intensity, int& Width, int& Height, int* smoothFilter, int filterSize, int divisor)
{
	// image in yeni boyutu : 
	// newSize = (( imageSize + 2 * pooling - filterSize) / stepSize ) + 1

	int newWidth = (Width - filterSize + 1);
	int newHeight = (Height - filterSize + 1);
	int* smoothImage = new int[newWidth * newHeight];

	int total = 0;
	for (int row = 0; row < newHeight; row++)
	{
		for (int col = 0; col < newWidth; col++)
		{
			total = 0;
			for (int i = 0; i < filterSize; i++)
			{
				for (int j = 0; j < filterSize; j++)
				{
					total += raw_intensity[(row + i) * Width + col + j] * smoothFilter[i * filterSize + j];
				}
			}
			smoothImage[row * newWidth + col] = (int)(total / divisor);
		}
	}

	Width = newWidth;
	Height = newHeight;
	return smoothImage;
}

int directionQuantize(int direction)
{
	// 4 yonde kuantalama yap [ 0, 45, 90, 135]

	direction = direction % 180;

	if (direction < 22.5 || direction > 157.5)
		return 0;
	else if (67.5 > direction)
		return 45;
	else if (112.5 > direction)
		return 90;
	else
		return 135;
}

void magnitudeAndDirection(int* image, int& width, int& height, int* gradientX, int* gradientY, int* magnitudeImage, int* quantizedGradientDir, int* gradientDir, int filterSize)
{
	int newWidth = (width - filterSize + 1);
	int newHeight = (height - filterSize + 1);

	int totalX = 0;
	int totalY = 0;
	int direction = 0;
	for (int row = 0; row < newHeight; row++)
	{
		for (int col = 0; col < newWidth; col++)
		{
			totalX = 0;
			totalY = 0;
			for (int i = 0; i < filterSize; i++)
			{
				for (int j = 0; j < filterSize; j++)
				{
					totalX += image[(row + i) * width + col + j] * gradientX[i * filterSize + j];
					totalY += image[(row + i) * width + col + j] * gradientY[i * filterSize + j];
				}
			}
			magnitudeImage[row * newWidth + col] = abs(totalX) + abs(totalY);						// g = |x| + |y|

			direction = (int)(atan2(totalY, totalX) * 180 / PI);									// convert radian to angle
			gradientDir[row * newWidth + col] = (direction + 360) % 360;							// convert angle to [0-360]
			quantizedGradientDir[row * newWidth + col] = directionQuantize(direction + 360);		// convert angle to [0, 45, 90, 135]
		}
	}

	width = newWidth;
	height = newHeight;
}


int* createHistMatris(int* rawIndensity, int width, int height, int histSize)
{
	int* hist = (int*)calloc(histSize, sizeof(int));

	for (int i = 0; i < width * height; i++)
		hist[rawIndensity[i]]++;

	return hist;
}

void deepCopy(int* hostMem, int* copyMem, int width, int height)
{
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			copyMem[row * width + col] = hostMem[row * width + col];
		}
	}
}

int* nonMaximalSuppression(int* magnitudeImage, int* quantizedGradientDir, int width, int height)
{

	int* copyMagnitude = new int[width * height];
	deepCopy(magnitudeImage, copyMagnitude, width, height);			

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (magnitudeImage[row * width + col] != 0)
				switch (quantizedGradientDir[row * width + col])
				{

				case 0:
					if (col == 0)
					{
						if (magnitudeImage[row * width + col] <= magnitudeImage[row * width + col + 1])
							copyMagnitude[row * width + col] = 0;
					}

					else if (col == width - 1)
					{
						if (magnitudeImage[row * width + col] <= magnitudeImage[row * width + col - 1])
							copyMagnitude[row * width + col] = 0;
					}

					else if (magnitudeImage[row * width + col] <= magnitudeImage[row * width + col - 1] || magnitudeImage[row * width + col] <= magnitudeImage[row * width + col + 1])
						copyMagnitude[row * width + col] = 0;

					break;

				case 45:

					if (row == 0 && col < width - 1 || col == 0 && row < height - 1)
					{
						if (magnitudeImage[row * width + col] <= magnitudeImage[(row + 1) * width + col + 1])
							copyMagnitude[row * width + col] = 0;
					}

					else if (row == height - 1 && col > 0 || col == width - 1 && row > 0)
					{
						if (magnitudeImage[row * width + col] <= magnitudeImage[(row - 1) * width + col - 1])
							copyMagnitude[row * width + col] = 0;
					}

					else if (!(row == height - 1 && col == 0 || row == 0 && col == width - 1))
					{
						if (magnitudeImage[row * width + col] <= magnitudeImage[(row - 1) * width + col - 1] || magnitudeImage[row * width + col] <= magnitudeImage[(row + 1) * width + col + 1])
							copyMagnitude[row * width + col] = 0;
					}

					break;

				case 90:

					if (row == 0)
					{
						if (magnitudeImage[row * width + col] <= magnitudeImage[(row + 1) * width + col])
							copyMagnitude[row * width + col] = 0;
					}

					else if (row == height - 1)
					{
						if (magnitudeImage[row * width + col] <= magnitudeImage[(row - 1) * width + col])
							copyMagnitude[row * width + col] = 0;
					}

					else if (magnitudeImage[row * width + col] <= magnitudeImage[(row - 1) * width + col] || magnitudeImage[row * width + col] <= magnitudeImage[(row + 1) * width + col])
						copyMagnitude[row * width + col] = 0;

					break;

				case 135:

					if (row == 0 && col > 0 || col == width - 1 && row < height - 1)
					{
						if (magnitudeImage[row * width + col] <= magnitudeImage[(row + 1) * width + col - 1])
							copyMagnitude[row * width + col] = 0;
					}

					else if (col == 0 && row > 0 || row == height - 1 && col < width - 1)
					{
						if (magnitudeImage[row * width + col] <= magnitudeImage[(row - 1) * width + col + 1])
							copyMagnitude[row * width + col] = 0;
					}

					else if (!(row == 0 && col == 0 || row == height - 1 && col == width - 1))
					{
						if (magnitudeImage[row * width + col] <= magnitudeImage[(row - 1) * width + col + 1] || magnitudeImage[row * width + col] <= magnitudeImage[(row + 1) * width + col - 1])
							copyMagnitude[row * width + col] = 0;
					}

					break;
				}
		}
	}
	return copyMagnitude;
}

void convertToBinary(int* magnitudeImage, int width, int height)
{
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (magnitudeImage[row * width + col] != 0)
				magnitudeImage[row * width + col] = 1;
		}
	}
}

void hysteresisThreashold(int* magnitudeImage, int* quantizedGradientDir, int width, int height, int TH, int TL)
{
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (magnitudeImage[row * width + col] <= TL)
				magnitudeImage[row * width + col] = 0;

			else if (magnitudeImage[row * width + col] < TH && magnitudeImage[row * width + col] > TL)
			{

				switch (quantizedGradientDir[row * width + col] - 90)				// gradient yonunden kenar yonune gec
				{

				case -90:
					
					if (row == 0)
					{
						if (!(magnitudeImage[(row + 1) * width + col] >= TH))
							magnitudeImage[row * width + col] = 0;
					}

					else if (row == height - 1)
					{
						if (!(magnitudeImage[(row - 1) * width + col] >= TH))
							magnitudeImage[row * width + col] = 0;
					}

					else if (!(magnitudeImage[(row - 1) * width + col] >= TH || magnitudeImage[(row + 1) * width + col] >= TH))
						magnitudeImage[row * width + col] = 0;

					break;

				case -45:

					if (row == 0 && col > 0 || col == width - 1 && row < height - 1)
					{
						if (!(magnitudeImage[(row + 1) * width + col - 1] >= TH))
							magnitudeImage[row * width + col] = 0;
					}

					else if (col == 0 && row > 0 || row == height - 1 && col < width - 1)
					{
						if (!(magnitudeImage[(row - 1) * width + col + 1] >= TH))
							magnitudeImage[row * width + col] = 0;
					}
					else if (!(row == 0 && col == 0 || row == height - 1 && col == width - 1))
					{
						if (!(magnitudeImage[(row - 1) * width + col + 1] >= TH || magnitudeImage[(row + 1) * width + col - 1] >= TH))
							magnitudeImage[row * width + col] = 0;
					}

					break;

				case 0:

					if (col == 0)
					{
						if (!(magnitudeImage[row * width + col + 1] >= TH))
							magnitudeImage[row * width + col] = 0;
					}

					else if (col == width - 1)
					{
						if (!(magnitudeImage[row * width + col - 1] >= TH))
							magnitudeImage[row * width + col] = 0;
					}

					else if (!(magnitudeImage[row * width + col - 1] >= TH || magnitudeImage[row * width + col + 1] >= TH))
						magnitudeImage[row * width + col] = 0;

					break;

				case 45:

					if (row == 0 && col < width - 1 || col == 0 && row < height - 1)
					{
						if (!(magnitudeImage[(row + 1) * width + col + 1] >= TH))
							magnitudeImage[row * width + col] = 0;
					}
					else if (row == height - 1 && col > 0 || col == width - 1 && row > 0)
					{
						if (!(magnitudeImage[(row - 1) * width + col - 1] >= TH))
							magnitudeImage[row * width + col] = 0;
					}

					else if (!(row == height - 1 && col == 0 || row == 0 && col == width - 1))
					{
						if (!(magnitudeImage[(row - 1) * width + col - 1] >= TH || magnitudeImage[(row + 1) * width + col + 1] >= TH))
							magnitudeImage[row * width + col] = 0;
					}

					break;
				}
			}
		}
	}

	convertToBinary(magnitudeImage, width, height);							// >= TH ( geriye TH dan buyuk olanlar kaldi )
}

void displayBinaryBitmap(int* intensityMat, int width, int height, System::Drawing::Bitmap^ bitmap)
{
	System::Drawing::Color color;

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (intensityMat[row * width + col] == 0)
				color = System::Drawing::Color::FromArgb(0, 0, 0);

			else
				color = System::Drawing::Color::FromArgb(255, 255, 255);

			bitmap->SetPixel(col, row, color);
		}
	}
}

int distanceQuantize(int distance)
{
	return rint(double(distance) / 4) * 4;
}

int* houghTransformLine(int* binaryImage, int width, int height, int imageW, int imageH, int& houghWidth, int& houghHeight)
{
	int imDiff = (imageW - width) / 2;

	houghHeight = (int)(sqrt(imageH * imageH + imageW * imageW));											// goruntudeki max kosegen uzakligi 

	houghWidth = 180;

	int* houghSpace = (int*)calloc(houghHeight * houghWidth, sizeof(int));

	int distance = 0;

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (binaryImage[row * width + col] == 1)
			{
				for (int q = 0; q < 180; q++)
				{
					distance = distanceQuantize(abs((col + imDiff) * cos(q * PI / 180) + (row + imDiff) * sin(q * PI / 180)));
					houghSpace[distance * houghWidth + q]++;
				}
			}
		}
	}

	return houghSpace;
}

bool isExist(std::vector <int>& MaxsD, std::vector <int>& MaxsQ, int d, int Q)
{
	// Maximum secilen nokta, MaxsD icerisindekiler ile bir benzerlik barindiriyorsa true doner
	// Benzerlik kontrolu distance(d) ve angle(Q) degerlerine gore yapilir

	for (int i = 0; i < MaxsD.size(); i++)
	{
		if ((d - DISTQUANTIZE <= MaxsD[i] && MaxsD[i] <= d + DISTQUANTIZE) && (Q - ANGLEQUANTIZE <= MaxsQ[i] && MaxsQ[i] <= Q + ANGLEQUANTIZE))
			return true;
	}
	return false;
}

void searchMaxPoint(int* houghSpace, int houghWidth, int houghHeight, std::vector <int>& MaxsD, std::vector<int>& MaxsQ, int numOfMaks)
{
	int tempD = 0, tempQ = 0, temp = 0, temp2 = 0;

	while (MaxsD.size() < numOfMaks)
	{
		tempD = 0;
		tempQ = 0;
		temp = 0;
		temp2 = temp;
		for (int d = 0; d < houghHeight; d++)
		{
			for (int Q = 0; Q < houghWidth; Q++)
			{
				if (houghSpace[d * houghWidth + Q] >= temp && !isExist( MaxsD, MaxsQ, d, Q))			// benzer olan noktalar max olarak alinmaz
				{
					tempD = d;
					tempQ = Q;
					temp = houghSpace[d * houghWidth + Q];
				}
			}
		}

		if (temp == temp2)																				// daha fazla maksimum deger yoksa
			break;

		MaxsD.push_back(tempD);
		MaxsQ.push_back(tempQ);
	}
}

void controlMaxEdge(BYTE* raw_intensity, int imWidth, int* binaryEdge, int Width, int Height, std::vector <int>& MaxsD, std::vector<int>& MaxsQ)
{

	int imDiff = (imWidth - Width) / 2;
	int distance = 0;

	for (int i = 0; i < MaxsD.size(); i++)
	{
		for (int row = 0; row < Height; row++)
		{
			for (int col = 0; col < Width; col++)
			{
				if (binaryEdge[row * Width + col] == 1)
				{
					for (int i = 0; i < MaxsD.size(); i++)
					{
						distance = distanceQuantize(abs((col)*cos(MaxsQ[i] * PI / 180) + (row)*sin(MaxsQ[i] * PI / 180)));

						if (MaxsD[i] == distance)
						{
							raw_intensity[(row + imDiff) * imWidth + col + imDiff] = REDPIXEL;
							break;
						}
					}
				}
			}
		}
	}


	//for (int i = 0; i < MaxsD.size(); i++)
	//{
	//	int Q = MaxsQ[i];
	//	int d = MaxsD[i];

	//	int col = (int)std::abs(d * cos(Q * PI / 180));
	//	int row = (int)std::abs(d * sin(Q * PI / 180));
	//	int tempRow = row;
	//	int tempCol = col;
	//	switch (directionQuantize(Q)- 90)
	//	{
	//	case -90:
	//		while ((row + imDiff) != 0)
	//		{
	//			raw_intensity[(row + imDiff) * imWidth + col + imDiff] = '*';
	//			row--;
	//		}
	//		row = tempRow;
	//		while ((row + imDiff) != imHeight - 1)
	//		{
	//			raw_intensity[(row + imDiff) * imWidth + col + imDiff] = '*';
	//			row++;
	//		}
	//		break;

	//	case -45:

	//		while ((row + imDiff) != 0 && col + imDiff != imWidth - 1)
	//		{
	//			raw_intensity[(row + imDiff) * imWidth + col + imDiff] = '*';
	//			row--;
	//			col++;
	//		}
	//		row = tempRow;
	//		col = tempCol;
	//		while ((row + imDiff) != imHeight - 1 && col + imDiff != 0)
	//		{
	//			raw_intensity[(row + imDiff) * imWidth + col + imDiff] = '*';
	//			row++;
	//			col--;
	//		}
	//		break;

	//	case 0:
	//		while (col + imDiff != 0)
	//		{
	//			raw_intensity[(row + imDiff) * imWidth + col + imDiff] = '*';
	//			col--;
	//		}
	//		col = tempCol;
	//		while (col + imDiff != imWidth - 1)
	//		{
	//			raw_intensity[(row + imDiff) * imWidth + col + imDiff] = '*';
	//			col++;
	//		}
	//		break;

	//	case 45:
	//		while ((row + imDiff) != 0 && col + imDiff != 0)
	//		{
	//			raw_intensity[(row + imDiff) * imWidth + col + imDiff] = '*';
	//			row--;
	//			col--;
	//		}
	//		row = tempRow;
	//		col = tempCol;
	//		while ((row + imDiff) != imHeight - 1 && col + imDiff != imWidth - 1)
	//		{
	//			raw_intensity[(row + imDiff) * imWidth + col + imDiff] = '*';
	//			row++;
	//			col++;
	//		}
	//		break;
	//	}

}

void displayLineBitmap(BYTE* raw_intensity, int imWidth, int imHeight, System::Drawing::Bitmap^ bitmap)
{
	System::Drawing::Color color;

	for (int row = 0; row < imHeight; row++)
	{
		for (int col = 0; col < imWidth; col++)
		{
			if (raw_intensity[row * imWidth + col] == REDPIXEL)
				color = System::Drawing::Color::FromArgb(255, 0, 0);

			else
				color = System::Drawing::Color::FromArgb(raw_intensity[row * imWidth + col] % 255, raw_intensity[row * imWidth + col] % 255, raw_intensity[row * imWidth + col] % 255);

			bitmap->SetPixel(col, row, color);
		}
	}
}

int* houghTransformCircle(int* binaryImage, int* gradientDir, int width, int height, int& houghWidth, int& houghHeight, int circleR, int imageW, int imageH)
{
	int imDiff = (imageW - width) / 2;

	houghHeight = (int)(sqrt(imageH * imageH + imageW * imageW));											// goruntudeki max kosegen uzakligi 

	houghWidth = 180;																				

	int* houghSpace = (int*)calloc(houghHeight * houghWidth, sizeof(int));

	int distance = 0;
	int a = 0, b = 0;

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (binaryImage[row * width + col] == 1)
			{
				if (180 < gradientDir[row * width + col] <= 270)
				{
					a = col + circleR * abs(cos((gradientDir[row * width + col] - 180) * PI / 180));
					b = row + circleR * abs(sin((gradientDir[row * width + col] - 180) * PI / 180));

				}
				else if (90 < gradientDir[row * width + col] <= 180)
				{
					a = col + circleR * abs(cos((90 - (gradientDir[row * width + col] - 90)) * PI / 180));
					b = row - circleR * abs(sin((90 - (gradientDir[row * width + col] - 90)) * PI / 180));

				}
				else if (gradientDir[row * width + col] <= 90)
				{
					a = col - circleR * abs(cos(gradientDir[row * width + col] * PI / 180));
					b = row - circleR * abs(sin(gradientDir[row * width + col] * PI / 180));

				}
				else if (270 < gradientDir[row * width + col] <= 360)
				{
					a = col - circleR * abs(cos((90 - (gradientDir[row * width + col] - 270)) * PI / 180));
					b = row + circleR * abs(sin((90 - (gradientDir[row * width + col] - 270)) * PI / 180));

				}
				distance = a * cos(atan2(b, a)) + b * sin(atan2(b, a));						// distance calculate
				houghSpace[distance * houghWidth + int(atan2(b, a) * (180 / PI))]++;		// convert radian to angle
			}
		}
	}

	return houghSpace;
}

void displayHoughBitmap(int* houghSpace, int houghWidth, int houghHeight, System::Drawing::Bitmap^ bitmap)
{
	System::Drawing::Color color;
	for (int row = 0; row < houghHeight; row++)
	{
		for (int col = 0; col < houghWidth; col++)
		{
			if (houghSpace[row * houghWidth + col] == 0)
				color = System::Drawing::Color::FromArgb(0, 0, 0);
			else
				color = System::Drawing::Color::FromArgb(houghSpace[row * houghWidth + col] % 255, houghSpace[row * houghWidth + col] * houghSpace[row * houghWidth + col] % 255, (houghSpace[row * houghWidth + col] * houghSpace[row * houghWidth + col] * houghSpace[row * houghWidth + col]) % 255);

			bitmap->SetPixel(col, row, color);
		}
	}
}

int newCoordinate(int& x, int& y, int angle, int radius)
{
	if ((x < 0) || (y < 0))
		return NULL;

	x = x + (radius)*cos(angle);
	y = y + (radius)*sin(angle);
}

void drawCircle(BYTE* buffer, int width, int x, int y, int radius)
{
	int tempX = x;
	int tempY = y;

	for (int angle = 0; angle < 360; angle++)
	{
		x = tempX;
		y = tempY;

		newCoordinate(x, y, angle, radius);

		buffer[y * width + x] = REDPIXEL;
	}
}

int drawMaxCircle(BYTE* raw_intensity, int imWidth, int Width, std::vector <int>& MaxsD, std::vector<int>& MaxsQ, int circleR)
{
	int imDiff = (imWidth - Width) / 2;
	for (int i = 0; i < MaxsD.size(); i++)
	{
		int Q = MaxsQ[i];

		int d = MaxsD[i];

		int col = abs(d * cos(Q * PI / 180));
		int row = abs(d * sin(Q * PI / 180));

		drawCircle(raw_intensity, imWidth, col + imDiff, row + imDiff, circleR);

	}
	return MaxsD.size();
}