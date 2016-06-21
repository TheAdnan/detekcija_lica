#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

String lice_kaskada = "c:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
String oci_kaskada = "c:/opencv/sources/data/haarcascades/haarcascade_eye.xml";
CascadeClassifier lice;
CascadeClassifier oci;
string prozor = "Detekcija lica";
RNG rng(12345);


void nadjiFacu(Mat slika){
	std::vector<Rect> faces;
	Mat slika_grayscale;

	cvtColor(slika, slika_grayscale, CV_BGR2GRAY);
	equalizeHist(slika_grayscale, slika_grayscale);

	//prepoznaj lica
	lice.detectMultiScale(slika_grayscale, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(slika, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 0), 3, 8, 0);

		Mat faceROI = slika_grayscale(faces[i]);
		std::vector<Rect> eyes;

		//-- In each face, detect eyes
		oci.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(slika, center, radius, Scalar(23, 255, 25), 1, 8, 0);
		}
	}
	//krajnji rez
	imshow(prozor, slika);
	cvWaitKey(10000);
}





int main(int argc, const char** argv)
{
	Mat slika;

	//loadanje kaskada
	if (!lice.load(lice_kaskada)){ 
		printf("--(!)Greska\n"); 
		return -1; 
	};
	if (!oci.load(oci_kaskada)){ 
		printf("--(!)Greska\n"); 
		return -1; 
	};

	//ucitavanje slike
	slika = imread("D:/Moji podaci/Desktop/sheikh_isa_qassim_ap.jpg");
			if (!slika.empty())
			{
				nadjiFacu(slika);
			}
			else
			{
				printf(" --(!) Nema slike!");
			}

			int c = waitKey(10000);
			

	return 0;
}































//#include <opencv\cv.h>
//#include <opencv\highgui.h>
//#include <opencv\ml.h>
//
//void nadjiLice(IplImage* ulaz, int x0, int y0,
//	int width, int visina, int dimenzije)
//{
//	int b, g, r, col, row;
//
//	int xMin = dimenzije*(int)floor((double)x0 / dimenzije);
//	int yMin = dimenzije*(int)floor((double)y0 / dimenzije);
//	int xMax = dimenzije*(int)ceil((double)(x0 + width) / dimenzije);





//	int yMax = dimenzije*(int)ceil((double)(y0 + visina) / dimenzije);
//
//	for (int y = yMin; y<yMax; y += dimenzije){
//		for (int x = xMin; x<xMax; x += dimenzije){
//			b = g = r = 0;
//			for (int i = 0; i<dimenzije; i++){
//				if (y + i > ulaz->height){
//					break;
//				}
//				row = i;
//				for (int j = 0; j<dimenzije; j++){
//					if (x + j > ulaz->width){
//						break;
//					}
//					b += (unsigned char)ulaz->imageData[ulaz->widthStep*(y + i) + (x + j) * 3];
//					g += (unsigned char)ulaz->imageData[ulaz->widthStep*(y + i) + (x + j) * 3 + 1];
//					r += (unsigned char)ulaz->imageData[ulaz->widthStep*(y + i) + (x + j) * 3 + 2];
//					col = j;
//				}
//			}
//			row++;
//			col++;
//			for (int i = 0; i<row; i++){
//				for (int j = 0; j<col; j++){
//					ulaz->imageData[ulaz->widthStep*(y + i) + (x + j) * 3] = cvRound((double)b / (row*col));
//					ulaz->imageData[ulaz->widthStep*(y + i) + (x + j) * 3 + 1] = cvRound((double)g / (row*col));
//					ulaz->imageData[ulaz->widthStep*(y + i) + (x + j) * 3 + 2] = cvRound((double)r / (row*col));
//				}
//			}
//		}
//	}
//}
//
////Cv haar klasifikator
// const char *lokacijaXML = "?c:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
// CvHaarClassifierCascade *kaskada = (lokacijaXML, 0, 0, 0);
// CvMemStorage *memorija = 0;
// CvSeq *lica = 0;
//
//
//int main(){
//	IplImage* slika = cvLoadImage("D:/Moji podaci/Desktop/detekcija_lica/test_slike/2.jpg");
//	IplImage* src_sivo = 0;
//	src_sivo = cvCreateImage(cvGetSize(slika), IPL_DEPTH_8U, 1);
//
//
//
//
//	memorija = cvCreateMemStorage(0);
//	cvClearMemStorage(memorija);
//	cvCvtColor(slika, src_sivo, CV_BGR2GRAY);
//	cvEqualizeHist(src_sivo, src_sivo);
//	lica = cvHaarDetectObjects (src_sivo, kaskada, memorija, 1.11, 3, 0, cvSize(40,40));
//	for (int i = 0; i < (lica ? lica->total : 0); i++) {
//		CvRect *r = (CvRect *)cvGetSeqElem(lica, i);
//		nadjiLice(slika, r->x, r->y, r->width, r->height, 20);
//	}
//
//	
//	//prikaz slike
//	cvNamedWindow("Prikaz slike", CV_WINDOW_AUTOSIZE);
//	cvShowImage("Prikaz slike", slika);
//	cvWaitKey(0);
//	cvReleaseImage(&src_sivo);
//	cvReleaseImage(&slika);
//	cvDestroyWindow("Prikaz slike");
//
//
//	/*cvNamedWindow("Prikaz slike", CV_WINDOW_AUTOSIZE);
//	cvShowImage("Prikaz slike", src_sivo);
//	cvWaitKey(0);
//	cvReleaseImage(&src_sivo);
//	cvDestroyWindow("Prikaz slike");*/
//	return 0;
//
//}