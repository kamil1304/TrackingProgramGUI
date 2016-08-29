#ifndef METHODS3D_H
#define METHODS3D_H

#include <QMutex>
#include <QThread>
#include <QDebug>

#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define PI 3.14159265

class Methods3d: public QThread
{ Q_OBJECT
public:
    QMutex mutex;
    Methods3d(QObject *parent = 0);
    double pitch,yaw;
    int cx,cy;
    // amount of points that we can trust computed  homography
    int homoPoints;
    // minimum amount to compute homography
    int homoMinPoints;

    //Set a center point cx and xy
    void setCenter( int x, int y);
     // compute angles Pitch and Yaw
    vector<double> computeAngles(vector<int> value);
    // are  f0 and f1 ready to use
    bool  isReady();


  public slots:
     // get information about  current possino of tracking pixel
     void getPoints(vector<int> newPose);

protected:
    // source points to computing homogrpahy
    vector<Point2f> firstPoints;
    // destination points to computing homogrpahy
    vector<Point2f> secondPoints;
    //min radius, that we claim, that our reference point has moved
    double minRadius;
    Mat homography;
    Point2f newValue;

    // check if new point is far enough from previous one- check if  object has moved
    bool farEnough(Point a, Point b);
    // compute homography
    void computeHomo();

private:
    //focals dimmenion in x and y
    double f0,f1;
    bool f0Good, f1Good;
    bool homoReady;
    // estimate focal dimension from homography
    void focalsFromHomography(const Mat& H, double &f0, double &f1, bool &f0_ok, bool &f1_ok);
};

#endif // METHODS3D_H
