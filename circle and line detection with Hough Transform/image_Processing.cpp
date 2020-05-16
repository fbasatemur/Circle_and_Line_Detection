
#include "image_Processing.h"
#include <math.h>
#include <ctime>
#include <iostream>

#define PI 3.14159265
#define MIN(a,b) ((a < b) ? a : b)
#define MAX(a,b) ((a > b) ? a : b)
#define REDPIXEL 2

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

int* createHistMatris(int* rawIndensity, int width, int height, int histSize)
{
	int* hist = (int*)calloc(histSize, sizeof(int));

	for (int i = 0; i < width * height; i++)
		hist[rawIndensity[i]]++;

	return hist;
}

int* smoothing(BYTE* raw_intensity, int& Width, int& Height, int* smoothFilter, int filterSize, int divisor)
{
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

void magnitudeAndDirection(int* raw_intensity, int& Width, int& Height, int* gradientX, int* gradientY, int* magnitudeImage, int* directionImage, int* directions, int filterSize)
{
	int newWidth = (Width - filterSize + 1);
	int newHeight = (Height - filterSize + 1);

	int totalX = 0;
	int totalY = 0;
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
					totalX += raw_intensity[(row + i) * Width + col + j] * gradientX[i * filterSize + j];
					totalY += raw_intensity[(row + i) * Width + col + j] * gradientY[i * filterSize + j];
				}
			}
			magnitudeImage[row * newWidth + col] = abs(totalX) + abs(totalY);

			int direction = (int)(atan2(totalY, totalX) * 180 / PI);
			directions[row * newWidth + col] = (direction + 360) % 360;
			directionImage[row * newWidth + col] = directionQuantize(direction + 360);
		}
	}

	Width = newWidth;
	Height = newHeight;
}

void displayBinaryBitmap(int* intensityMat, int Width, int Height, System::Drawing::Bitmap^ bitmap)
{
	System::Drawing::Color color;
	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			if (intensityMat[row * Width + col] == 0)
				color = System::Drawing::Color::FromArgb(0, 0, 0);
			else
				color = System::Drawing::Color::FromArgb(255, 255, 255);

			bitmap->SetPixel(col, row, color);
		}
	}
}

void deepCopy(int* hostMem, int* copyMem, int Width, int Height)
{
	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			copyMem[row * Width + col] = hostMem[row * Width + col];
		}
	}
}

int* nonMaximalSuppression(int* magnitudeImage, int* gradientDirections, int Width, int Height)
{
	// deep copy
	int* copyMagnitude = new int[Width * Height];
	deepCopy(magnitudeImage, copyMagnitude, Width, Height);

	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			if (magnitudeImage[row * Width + col] != 0)
				switch (gradientDirections[row * Width + col])
				{

				case 0:
					if (col == 0)
					{
						if (magnitudeImage[row * Width + col] <= magnitudeImage[row * Width + col + 1])
							copyMagnitude[row * Width + col] = 0;
					}

					else if (col == Width - 1)
					{
						if (magnitudeImage[row * Width + col] <= magnitudeImage[row * Width + col - 1])
							copyMagnitude[row * Width + col] = 0;
					}

					else if (magnitudeImage[row * Width + col] <= magnitudeImage[row * Width + col - 1] || magnitudeImage[row * Width + col] <= magnitudeImage[row * Width + col + 1])
						copyMagnitude[row * Width + col] = 0;

					break;

				case 45:

					if (row == 0 && col < Width - 1 || col == 0 && row < Height - 1)
					{
						if (magnitudeImage[row * Width + col] <= magnitudeImage[(row + 1) * Width + col + 1])
							copyMagnitude[row * Width + col] = 0;
					}

					else if (row == Height - 1 && col > 0 || col == Width - 1 && row > 0)
					{
						if (magnitudeImage[row * Width + col] <= magnitudeImage[(row - 1) * Width + col - 1])
							copyMagnitude[row * Width + col] = 0;
					}

					else if (!(row == Height - 1 && col == 0 || row == 0 && col == Width - 1))
					{
						if (magnitudeImage[row * Width + col] <= magnitudeImage[(row - 1) * Width + col - 1] || magnitudeImage[row * Width + col] <= magnitudeImage[(row + 1) * Width + col + 1])
							copyMagnitude[row * Width + col] = 0;
					}

					break;

				case 90:

					if (row == 0)
					{
						if (magnitudeImage[row * Width + col] <= magnitudeImage[(row + 1) * Width + col])
							copyMagnitude[row * Width + col] = 0;
					}

					else if (row == Height - 1)
					{
						if (magnitudeImage[row * Width + col] <= magnitudeImage[(row - 1) * Width + col])
							copyMagnitude[row * Width + col] = 0;
					}

					else if (magnitudeImage[row * Width + col] <= magnitudeImage[(row - 1) * Width + col] || magnitudeImage[row * Width + col] <= magnitudeImage[(row + 1) * Width + col])
						copyMagnitude[row * Width + col] = 0;

					break;

				case 135:

					if (row == 0 && col > 0 || col == Width - 1 && row < Height - 1)
					{
						if (magnitudeImage[row * Width + col] <= magnitudeImage[(row + 1) * Width + col - 1])
							copyMagnitude[row * Width + col] = 0;
					}

					else if (col == 0 && row > 0 || row == Height - 1 && col < Width - 1)
					{
						if (magnitudeImage[row * Width + col] <= magnitudeImage[(row - 1) * Width + col + 1])
							copyMagnitude[row * Width + col] = 0;
					}

					else if (!(row == 0 && col == 0 || row == Height - 1 && col == Width - 1))
					{
						if (magnitudeImage[row * Width + col] <= magnitudeImage[(row - 1) * Width + col + 1] || magnitudeImage[row * Width + col] <= magnitudeImage[(row + 1) * Width + col - 1])
							copyMagnitude[row * Width + col] = 0;
					}

					break;
				}
		}
	}
	return copyMagnitude;
}
void hysteresisThreashold(int* magnitudeImage, int* gradientDirections, int Width, int Height, int TH, int TL)
{
	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			if (magnitudeImage[row * Width + col] <= TL)
				magnitudeImage[row * Width + col] = 0;

			else if (magnitudeImage[row * Width + col] < TH && magnitudeImage[row * Width + col] > TL)
			{

				switch (gradientDirections[row * Width + col] - 90)
				{
				case -90:
					if (row == 0)
					{
						if (!(magnitudeImage[(row + 1) * Width + col] >= TH))
							magnitudeImage[row * Width + col] = 0;
					}

					else if (row == Height - 1)
					{
						if (!(magnitudeImage[(row - 1) * Width + col] >= TH))
							magnitudeImage[row * Width + col] = 0;
					}

					else if (!(magnitudeImage[(row - 1) * Width + col] >= TH || magnitudeImage[(row + 1) * Width + col] >= TH))
						magnitudeImage[row * Width + col] = 0;

					break;

				case -45:

					if (row == 0 && col > 0 || col == Width - 1 && row < Height - 1)
					{
						if (!(magnitudeImage[(row + 1) * Width + col - 1] >= TH))
							magnitudeImage[row * Width + col] = 0;
					}

					else if (col == 0 && row > 0 || row == Height - 1 && col < Width - 1)
					{
						if (!(magnitudeImage[(row - 1) * Width + col + 1] >= TH))
							magnitudeImage[row * Width + col] = 0;
					}
					else if (!(row == 0 && col == 0 || row == Height - 1 && col == Width - 1))
					{
						if (!(magnitudeImage[(row - 1) * Width + col + 1] >= TH || magnitudeImage[(row + 1) * Width + col - 1] >= TH))
							magnitudeImage[row * Width + col] = 0;
					}

					break;


				case 0:
					if (col == 0)
					{
						if (!(magnitudeImage[row * Width + col + 1] >= TH))
							magnitudeImage[row * Width + col] = 0;
					}

					else if (col == Width - 1)
					{
						if (!(magnitudeImage[row * Width + col - 1] >= TH))
							magnitudeImage[row * Width + col] = 0;
					}

					else if (!(magnitudeImage[row * Width + col - 1] >= TH || magnitudeImage[row * Width + col + 1] >= TH))
						magnitudeImage[row * Width + col] = 0;

					break;

				case 45:
					if (row == 0 && col < Width - 1 || col == 0 && row < Height - 1)
					{
						if (!(magnitudeImage[(row + 1) * Width + col + 1] >= TH))
							magnitudeImage[row * Width + col] = 0;
					}
					else if (row == Height - 1 && col > 0 || col == Width - 1 && row > 0)
					{
						if (!(magnitudeImage[(row - 1) * Width + col - 1] >= TH))
							magnitudeImage[row * Width + col] = 0;
					}

					else if (!(row == Height - 1 && col == 0 || row == 0 && col == Width - 1))
					{
						if (!(magnitudeImage[(row - 1) * Width + col - 1] >= TH || magnitudeImage[(row + 1) * Width + col + 1] >= TH))
							magnitudeImage[row * Width + col] = 0;
					}

					break;
				}

			}
		}
	}

	convertToBinary(magnitudeImage, Width, Height);
}

void convertToBinary(int* magnitudeImage, int Width, int Height)
{
	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			if (magnitudeImage[row * Width + col] != 0)
				magnitudeImage[row * Width + col] = 1;
		}
	}
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

int distanceQuantize(int distance)
{
	return rint(double(distance) / 4) * 4;
}

int* houghTransformLine(BYTE* raw_intensity, int imageW, int imageH, int* binaryImage, int Width, int Height, int& houghWidth, int& houghHeight)
{
	int imDiff = (imageW - Width) / 2;

	houghHeight = (int)((imageW)*cos(atan2(imageH, imageW)) + imageH * sin(atan2(imageH, imageW)));	// goruntudeki max kosegen uzakligi 
	houghWidth = 180;																									// [0,45,90,135]

	int* houghSpace = (int*)calloc(houghHeight * houghWidth, sizeof(int));

	int distance = 0;

	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			if (binaryImage[row * Width + col] == 1)
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

bool isExist(std::vector <int>& MaxsTemp, int value)
{
	for (int i = 0; i < MaxsTemp.size(); i++)
	{
		if (MaxsTemp[i] == value)
			return true;
	}
	
	return false;
}

void searchMaxEdge(int* houghSpace, int houghWidth, int houghHeight, std::vector <int>& MaxsD, std::vector<int>& MaxsQ, int numOfMaks)
{
	int tempD = 0, tempQ = 0, temp = 0;
	std::vector <int> MaxsTemp;
	while (MaxsD.size() < numOfMaks)
	{
		tempD = 0;
		tempQ = 0;
		temp = 0;
		for (int d = 0; d < houghHeight; d++)
		{
			for (int Q = 0; Q < houghWidth; Q++)
			{
				if (houghSpace[d * houghWidth + Q] > temp && !isExist(MaxsTemp, houghSpace[d * houghWidth + Q]))
				{
					tempD = d;
					tempQ = Q;
					temp = houghSpace[d * houghWidth + Q];
				}
			}
		}
		MaxsTemp.push_back(temp);
		MaxsD.push_back(tempD);
		MaxsQ.push_back(tempQ);
	}	
}

void controlMaxEdge(BYTE* raw_intensity, int imWidth, int imHeight, int* binaryEdge, int Width, int Height, std::vector <int>& MaxsD, std::vector<int>& MaxsQ)
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

int* houghTransformCircle(int* binaryImage, int* gradientDirections, int* directions, int Width, int Height, int& houghWidth, int& houghHeight, int circleR, int imageW, int imageH)
{
	int imDiff = (imageW - Width) / 2;

	houghHeight = (int)(imageW * cos(atan2(imageH, imageW)) + imageH * sin(atan2(imageH, imageW)));		// goruntudeki max kosegen uzakligi 
	houghWidth = 180;																					// [0,45,90,135]

	int* houghSpace = (int*)calloc(houghHeight * houghWidth, sizeof(int));

	int distance = 0;
	int a = 0, b = 0;
	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			if (binaryImage[row * Width + col] == 1)
			{
				/*a = col + circleR * cos(directions[row * Width + col] * PI / 180);
				b = row + circleR * sin(directions[row * Width + col] * PI / 180);

				distance = distanceQuantize(abs(a * cos(atan2(b, a)) + b * sin(atan2(b, a))));
				houghSpace[distance * houghWidth + int(atan2(b, a) * (180 / PI))]++;*/


				if (180 < directions[row * Width + col] <= 270)
				{
					a = col + circleR * abs(cos((directions[row * Width + col] - 180) * PI / 180));
					b = row + circleR * abs(sin((directions[row * Width + col] - 180) * PI / 180));

				}
				else if (90 < directions[row * Width + col] <= 180)
				{
					a = col + circleR * abs(cos((90 - (directions[row * Width + col] - 90)) * PI / 180));
					b = row - circleR * abs(sin((90 - (directions[row * Width + col] - 90)) * PI / 180));

				}
				else if (directions[row * Width + col] <= 90)
				{
					a = col - circleR * abs(cos(directions[row * Width + col] * PI / 180));
					b = row - circleR * abs(sin(directions[row * Width + col] * PI / 180));

				}
				else if (270 < directions[row * Width + col] <= 360)
				{
					a = col - circleR * abs(cos((90 - (directions[row * Width + col] - 270)) * PI / 180));
					b = row + circleR * abs(sin((90 - (directions[row * Width + col] - 270)) * PI / 180));

				}
				distance = distanceQuantize(abs(a * cos(atan2(b, a)) + b * sin(atan2(b, a))));
				houghSpace[distance * houghWidth + int(atan2(b, a) * (180 / PI))]++;
			}
		}
	}

	return houghSpace;
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
		try
		{
			x = tempX;
			y = tempY;

			newCoordinate(x, y, angle, radius);

			buffer[y * width + x] = REDPIXEL;

		}
		catch (const std::exception & error)
		{
			std::cout << error.what() << std::endl;
		}
	}
}

void controlMaxCircle(BYTE* raw_intensity, int imWidth, int imHeight, int* binaryEdge, int Width, int Height, std::vector <int>& MaxsD, std::vector<int>& MaxsQ, int circleR)
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
}