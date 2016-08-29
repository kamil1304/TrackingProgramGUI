/* CLass gives  differen posiibilities to track  objects
*/
#ifndef TRACKINGMETHODS_H
#define TRACKINGMETHODS_H

#include <QColor>
#include <QDebug>
#include <QObject>

#include <vector>
#include <math.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>

using namespace cv;
using namespace std;

class TrackingMethods
{
public:
    TrackingMethods();

    // track a point- method: knowing a value of pixel and a previous position of pixel
    //  new position is looked for around previous one looking for the  nearest positions,
    // which has the most similar value of  pixel
   vector<int> trackingPixel(QColor col, vector<int> po, Mat frame);
   //compute a norm
   double normValue(int r, int g, int b, int x, int y);
   // Mat to store a frame from camera
   Mat RGBframe;
   // how big should be a quare, that   trackingPixel() is looki for  next position of pixel
   int howBigSquare;
};

#endif // TRACKINGMETHODS_H
