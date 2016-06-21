#include <opencv\cv.h>
#include <opencv\highgui.h>

int main(){
	IplImage* slika = cvLoadImage("D:/20151218_144421-1-1.jpg");
	cvNamedWindow("ImgDisp", CV_WINDOW_AUTOSIZE);
	cvShowImage("ImgDisp", slika);
	cvWaitKey(0);
	cvReleaseImage(&slika);
	cvDestroyWindow("ImgDisp");
	return 0;

}