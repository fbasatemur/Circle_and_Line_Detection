#pragma once
#include<windows.h>
#include <atlstr.h>								// LPCTSTR 
#include<iostream>
#include <stdio.h>
#include<msclr\marshal_cppstd.h>
#include <fstream>
#include <vector>

#include "image_BMP.h"
#include "image_Processing.h"	

namespace Form_Empty {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox4;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBCircleR;
	private: System::Windows::Forms::TextBox^ textBMaxEdge;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::RadioButton^ radioBLine;
	private: System::Windows::Forms::RadioButton^ radioBCircle;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;








	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea5 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBCircleR = (gcnew System::Windows::Forms::TextBox());
			this->textBMaxEdge = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->radioBLine = (gcnew System::Windows::Forms::RadioButton());
			this->radioBCircle = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1278, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->openToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(46, 24);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(128, 26);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 31);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(400, 400);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(418, 31);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(400, 400);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// chart1
			// 
			chartArea5->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea5);
			legend5->Name = L"Legend1";
			this->chart1->Legends->Add(legend5);
			this->chart1->Location = System::Drawing::Point(834, 31);
			this->chart1->Name = L"chart1";
			series5->ChartArea = L"ChartArea1";
			series5->Legend = L"Legend1";
			series5->Name = L"Gradient Hist";
			this->chart1->Series->Add(series5);
			this->chart1->Size = System::Drawing::Size(409, 207);
			this->chart1->TabIndex = 3;
			this->chart1->Text = L"chart1";
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(12, 437);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(400, 400);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox3->TabIndex = 4;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->Location = System::Drawing::Point(418, 437);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(400, 400);
			this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox4->TabIndex = 5;
			this->pictureBox4->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(949, 311);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(56, 17);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Circle r:";
			// 
			// textBCircleR
			// 
			this->textBCircleR->Location = System::Drawing::Point(1035, 311);
			this->textBCircleR->Name = L"textBCircleR";
			this->textBCircleR->Size = System::Drawing::Size(100, 22);
			this->textBCircleR->TabIndex = 8;
			this->textBCircleR->Text = L"60";
			// 
			// textBMaxEdge
			// 
			this->textBMaxEdge->Location = System::Drawing::Point(1035, 343);
			this->textBMaxEdge->Name = L"textBMaxEdge";
			this->textBMaxEdge->Size = System::Drawing::Size(100, 22);
			this->textBMaxEdge->TabIndex = 10;
			this->textBMaxEdge->Text = L"7";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(887, 347);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(125, 17);
			this->label2->TabIndex = 9;
			this->label2->Text = L"MAX num of Edge:";
			this->label2->UseWaitCursor = true;
			// 
			// radioBLine
			// 
			this->radioBLine->AutoSize = true;
			this->radioBLine->Location = System::Drawing::Point(955, 387);
			this->radioBLine->Name = L"radioBLine";
			this->radioBLine->Size = System::Drawing::Size(56, 21);
			this->radioBLine->TabIndex = 11;
			this->radioBLine->Text = L"Line";
			this->radioBLine->UseVisualStyleBackColor = true;
			// 
			// radioBCircle
			// 
			this->radioBCircle->AutoSize = true;
			this->radioBCircle->Checked = true;
			this->radioBCircle->Location = System::Drawing::Point(1035, 387);
			this->radioBCircle->Name = L"radioBCircle";
			this->radioBCircle->Size = System::Drawing::Size(64, 21);
			this->radioBCircle->TabIndex = 12;
			this->radioBCircle->TabStop = true;
			this->radioBCircle->Text = L"Circle";
			this->radioBCircle->UseVisualStyleBackColor = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(848, 427);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(164, 17);
			this->label3->TabIndex = 13;
			this->label3->Text = L"Num of Detected Circles:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(1033, 427);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(16, 17);
			this->label4->TabIndex = 14;
			this->label4->Text = L"0";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1278, 855);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->radioBCircle);
			this->Controls->Add(this->radioBLine);
			this->Controls->Add(this->textBMaxEdge);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBCircleR);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {


	}
	private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{

			pictureBox1->ImageLocation = openFileDialog1->FileName;

			LPCTSTR input;
			int width, height;
			long Size;

			CString filePathStr;
			
			filePathStr = openFileDialog1->FileName;

			input = (LPCTSTR)filePathStr;

			BYTE* buffer = LoadBMP((int%)width, (int%)height, (long%)Size, input);
			BYTE* raw_intensity = ConvertBMPToIntensity(buffer, width, height);
																							// orjinal image boyutlarini depola
			int imageWidth = width;
			int imageHeight = height;


			//int gaussianFilter[9] = { 1,2,1,2,4,2,1,2,1 };								// -> 1. mert gaussian
			int gaussianFilter[9] = { 2,1,2,1,4,1,2,1,2 };
			int* smoothImage = smoothing(raw_intensity, width, height, gaussianFilter, 3, 16);

			
			// x ve y yonundeki gradient matrisleri 3 * 3
			
			int gradientX[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
			int gradientY[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
																							 
			
			// size = (size - gradient_mask_size + 1)

			int* magnitudeImage = new int[(width - 2) * (height - 2)];						// kenar matrisi
			int* quantizedGradientDir = new int[(width - 2) * (height - 2)];				// [0, 45, 90, 135] acilarina quantize edilmis gradient yon bilgileri
			int* gradientDir = new int[(width - 2) * (height - 2)];							// Quantize yapilmamis gradient yon bilgileri
			
			
			// kenar ve yon bilgileri bulunur
			
			magnitudeAndDirection(smoothImage, width, height, gradientX, gradientY, magnitudeImage, quantizedGradientDir, gradientDir, 3);

			
			// gradient bilgisinden, histogram bilgisini olustur
			
			int* gradientHist = createHistMatris(magnitudeImage, width, height, 1020);

			// draw chart

			chart1->Series["Gradient Hist"]->Points->Clear();
			for (int i = 0; i < 1020; i++) {
				chart1->Series["Gradient Hist"]->Points->AddXY(i, gradientHist[i]);
			}

			// Canny edge detection ///////////////////////
			
			magnitudeImage = nonMaximalSuppression(magnitudeImage, quantizedGradientDir, width, height);

			hysteresisThreashold(magnitudeImage, quantizedGradientDir, width, height, 120, 110);

			///////////////////////////////////////////////

			// display magnitude image

			Bitmap^ surfaceBmp2 = gcnew Bitmap(width, height);
			pictureBox2->Image = surfaceBmp2;
			displayBinaryBitmap(magnitudeImage, width, height, surfaceBmp2);


			int houghWidth = 0;
			int houghHeight = 0;
			int* houghSpace;
			std::vector<int>maxsD;			// maximum distance
			std::vector<int>maxsQ;			// angle

			int numOfMaxEdge = Convert::ToInt16(textBMaxEdge->Text);


			if (radioBLine->Checked)
			{

				houghSpace = houghTransformLine(magnitudeImage, width, height, imageWidth, imageHeight, houghWidth, houghHeight);

				searchMaxPoint(houghSpace, houghWidth, houghHeight, maxsD, maxsQ, numOfMaxEdge);

				markMaxEdge(raw_intensity, imageWidth, magnitudeImage, width, height, maxsD, maxsQ);

				Bitmap^ surfaceBmp4 = gcnew Bitmap(imageWidth, imageHeight);
				pictureBox4->Image = surfaceBmp4;
				displayLineBitmap(raw_intensity, imageWidth, imageHeight, surfaceBmp4);
			}

			else if (radioBCircle->Checked)
			{
				int circleR = Convert::ToInt16(textBCircleR->Text);

				houghSpace = houghTransformCircle(magnitudeImage, gradientDir, width, height, houghWidth, houghHeight, circleR, imageWidth, imageHeight);
				
				searchMaxPoint(houghSpace, houghWidth, houghHeight, maxsD, maxsQ, numOfMaxEdge);
				
				int detectedCircles = drawMaxCircle(raw_intensity, imageWidth, width, maxsD, maxsQ, circleR);
				 
				label4->Text = Convert::ToString(detectedCircles);

				Bitmap^ surfaceBmp4 = gcnew Bitmap(imageWidth, imageHeight);
				pictureBox4->Image = surfaceBmp4;
				displayLineBitmap(raw_intensity, imageWidth, imageHeight, surfaceBmp4);
			}

			// draw hough space

			Bitmap^ surfaceBmp3 = gcnew Bitmap(houghWidth, houghHeight);
			pictureBox3->Image = surfaceBmp3;
			displayHoughBitmap(houghSpace, houghWidth, houghHeight, surfaceBmp3);
		}
	}
	};
}
