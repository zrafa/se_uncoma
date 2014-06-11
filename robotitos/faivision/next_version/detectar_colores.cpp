// Cristóbal Carnero Liñán <grendel.ccl@gmail.com>

#include <iostream>
#include <iomanip>

#if (defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || (defined(__APPLE__) & defined(__MACH__)))
#include <cv.h>
#include <highgui.h>
#else
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif

#include <iostream>
using namespace std;


#include <cvblob.h>
using namespace cvb;


int rojox = 0;
int rojoy = 0;
int cuantorojo = 0;

static int detectar( char *archivo )

{
  CvTracks tracks;

  cvNamedWindow("red_object_tracking", CV_WINDOW_AUTOSIZE);
  IplImage* img = cvLoadImage(archivo);
  CvSize imgSize = cvGetSize(img);
  IplImage* frame = cvLoadImage(archivo);

  IplConvKernel* morphKernel = cvCreateStructuringElementEx(5, 5, 1, 1, CV_SHAPE_RECT, NULL);

  unsigned int blobNumber = 0;

  bool quit = false;
//  while (!quit)
 // {

enum escala_de_colores {rojo, verde, azul, blanco, negro}; 

unsigned char f;
int color;
for (color=rojo;color<=negro;color++) {

    IplImage *segmentated = cvCreateImage(imgSize, 8, 1);
    
    for (unsigned int j=0; j<imgSize.height; j++)
      for (unsigned int i=0; i<imgSize.width; i++)
      {
	CvScalar c = cvGet2D(frame, j, i);

	double b = ((double)c.val[0])/255.;
	double g = ((double)c.val[1])/255.;
	double r = ((double)c.val[2])/255.;
	switch(color) {
		case (rojo):
			f = 255*((r>0.2+g)&&(r>0.2+b));
			break;
		case (azul):
			f = 255*((b>0.2+g)&&(b>0.2+r));
			break;
		case (verde):
			f = 255*((g>0.2+b)&&(g>0.2+r));
			break;
		case (blanco):
			f = 255*((r>0.9)&&(g>0.9)&&(b>0.9));
			break;
		case (negro):
			f = 255*((r<0.2)&&(g<0.2)&&(b<0.2));
			break;
	}

	cvSet2D(segmentated, j, i, CV_RGB(f, f, f));
      }

    cvMorphologyEx(segmentated, segmentated, NULL, morphKernel, CV_MOP_OPEN, 1);

    IplImage *labelImg = cvCreateImage(cvGetSize(frame), IPL_DEPTH_LABEL, 1);

    CvBlobs blobs;
    unsigned int result = cvLabel(segmentated, labelImg, blobs);
    cvFilterByArea(blobs, 500, 1000000);
    cvRenderBlobs(labelImg, blobs, frame, frame, CV_BLOB_RENDER_BOUNDING_BOX);

	cuantorojo=0;
	rojox=0;
	rojoy=0;
/* Nos informa donde esta el centro */
for (CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it)
{
//  cout << "Blob #" << it->second->label << ": Area=" << it->second->area << ", Centroid=(" << it->second->centroid.x << ", " << it->second->centroid.y << ")" << endl;
	if (cuantorojo < it->second->area) {
		cuantorojo = it->second->area;
		rojox = it->second->centroid.x;
		rojoy = it->second->centroid.y;
	}
};
	switch(color) {
		case (rojo):
			printf("COLOR ROJO ");
			break;
		case (azul):
			printf("COLOR AZUL ");
			break;
		case (verde):
			printf("COLOR VERDE ");
			break;
		case (blanco):
			printf("COLOR BLANCO ");
			break;
		case (negro):
			printf("COLOR NEGRO ");
			break;
	}
	printf("AREA = %i, x=%i, y=%i \n\n", cuantorojo, rojox, rojoy);
	fflush(stdout);

    cvShowImage("red_object_tracking", frame);

    cvReleaseImage(&labelImg);
    cvReleaseImage(&segmentated);
    cvReleaseBlobs(blobs);

}

  //}

  cvReleaseStructuringElement(&morphKernel);
  cvReleaseImage(&frame);
  cvReleaseImage(&img);

  cvDestroyWindow("red_object_tracking");

  return 0;
}

int main( int argc, char** argv ) {
	detectar(argv[1]);
	return 0;
}
