#pragma once
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <string>
#include <msclr\marshal_cppstd.h>


namespace detekcija_lica_GUI {
	using namespace std;
	using namespace cv;

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for PocetnaForma
	/// </summary>
	public ref class PocetnaForma : public System::Windows::Forms::Form
	{
	public:
		PocetnaForma(void)
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
		~PocetnaForma()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  odabirSlike;
	private: System::Windows::Forms::Button^  detektuj;
	private: System::Windows::Forms::PictureBox^  slika;

	protected:




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->odabirSlike = (gcnew System::Windows::Forms::Button());
			this->detektuj = (gcnew System::Windows::Forms::Button());
			this->slika = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->slika))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// odabirSlike
			// 
			this->odabirSlike->Location = System::Drawing::Point(208, 288);
			this->odabirSlike->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->odabirSlike->Name = L"odabirSlike";
			this->odabirSlike->Size = System::Drawing::Size(82, 30);
			this->odabirSlike->TabIndex = 0;
			this->odabirSlike->Text = L"Odaberi sliku";
			this->odabirSlike->UseVisualStyleBackColor = true;
			this->odabirSlike->Click += gcnew System::EventHandler(this, &PocetnaForma::odabirSlike_Click);
			// 
			// detektuj
			// 
			this->detektuj->Location = System::Drawing::Point(303, 288);
			this->detektuj->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->detektuj->Name = L"detektuj";
			this->detektuj->Size = System::Drawing::Size(82, 30);
			this->detektuj->TabIndex = 1;
			this->detektuj->Text = L"Detektuj lica";
			this->detektuj->UseVisualStyleBackColor = true;
			this->detektuj->Click += gcnew System::EventHandler(this, &PocetnaForma::detektuj_Click);
			// 
			// slika
			// 
			this->slika->Location = System::Drawing::Point(20, 15);
			this->slika->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->slika->Name = L"slika";
			this->slika->Size = System::Drawing::Size(364, 255);
			this->slika->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->slika->TabIndex = 2;
			this->slika->TabStop = false;
			// 
			// PocetnaForma
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(402, 328);
			this->Controls->Add(this->slika);
			this->Controls->Add(this->detektuj);
			this->Controls->Add(this->odabirSlike);
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"PocetnaForma";
			this->Text = L"Detekcija lica";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->slika))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		System::String^ path = gcnew System::String("");
	private: System::Void odabirSlike_Click(System::Object^  sender, System::EventArgs^  e) {
				 openFileDialog1->Filter = "Podržani tipovi|*.jpg;*.jpeg;*.png|" +
					 "JPEG (*.jpg;*.jpeg)|*.jpg;*.jpeg|" +
					 "Portable Network Graphic (*.png)|*.png";
				 openFileDialog1->Title = "Odaberi sliku";
				 if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 slika->Image = Image::FromFile(openFileDialog1->FileName);
					 path = openFileDialog1->FileName;
					// label1->Text = path;
				 }
	}
			 
			/* string* lice_kaskada = new string("d:/ETF/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");
			 string* oci_kaskada = new string("d:/ETF/opencv/sources/data/haarcascades/haarcascade_eye.xml");*/
			 string* lice_kaskada = new string("c:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");
			 string* oci_kaskada = new string("c:/opencv/sources/data/haarcascades/haarcascade_eye.xml");
			 CascadeClassifier* lice = new CascadeClassifier();
			 CascadeClassifier* oci = new CascadeClassifier();
			 string* prozor = new string("Detekcija lica");
			// RNG rng(12345);

	private: System::Void detektuj_Click(System::Object^  sender, System::EventArgs^  e) {
					 
					 Mat slikaDet;
					 System::String^ s = gcnew System::String(path);
					 std::string sl = msclr::interop::marshal_as<std::string>(s);
					 //loadanje kaskada
					if (!lice->load(*lice_kaskada)){
						 MessageBox::Show("Greska");
					 };
					 if (!oci->load(*oci_kaskada)){
						 MessageBox::Show("Greska");
					 };

					 //ucitavanje slike
					 slikaDet = imread(sl);
					 
					 if (!slikaDet.empty())
					 {
						 nadjiFacu(slikaDet);
					 }
					 else
					 {
						 MessageBox::Show("Nema slike");
					 }

					 int c = waitKey(10000);



	}

			 void nadjiFacu(Mat slika1){
				 std::vector<Rect> faces;
				 Mat slika_grayscale;
				 System::String^ s = gcnew System::String(path);
				 std::string put = msclr::interop::marshal_as<std::string>(s);
				 cvtColor(slika1, slika_grayscale, CV_BGR2GRAY);
				 equalizeHist(slika_grayscale, slika_grayscale);

				 //prepoznaj lica
				 lice->detectMultiScale(slika_grayscale, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

				 for (size_t i = 0; i < faces.size(); i++)
				 {
					 cv::Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
					 ellipse(slika1, center, cv::Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 0), 3, 8, 0);

					 Mat faceROI = slika_grayscale(faces[i]);
					 std::vector<Rect> eyes;

					 //-- In each face, detect eyes
					 oci->detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

					 for (size_t j = 0; j < eyes.size(); j++)
					 {
						 cv::Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
						 int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
						 circle(slika1, center, radius, Scalar(23, 255, 25), 1, 8, 0);
					 }
				 }
				 //krajnji rez
				// imshow(*prozor, slika);
				 vector<int> parametri;
				 parametri.push_back(CV_IMWRITE_JPEG_QUALITY);
				 parametri.push_back(90);
				 put += "-detected.jpg";
				 imwrite(put, slika1, parametri);
				 System::String^ putS = gcnew System::String("");
				 MessageBox::Show("Slika je saèuvana!");
				 putS = msclr::interop::marshal_as<System::String^>(put);
				 slika->ImageLocation = putS;
			 }
};
}
