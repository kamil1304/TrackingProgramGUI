/*  Class enables to play and save video  from camera
  and also find a most distinctive pixel and follow it drawing 
  circle around
*/
#ifndef PLAYER_H
#define PLAYER_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <QMessageBox>
#include <QDebug>
#include <QColor>
#include <string>

#include <vector>
#include <math.h>
#include "trackingmethods.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>

using namespace cv;
class Player : public QThread
{    Q_OBJECT
 private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    QImage img;
    VideoCapture capture;
    Mat frame;
    VideoWriter outputVideo;
    Size sizeSave ;
    String fileName;
    TrackingMethods  trackingPixel;

    // fucntion follow a point on a next frame and draw a circle around it
    void drawCircle(QColor col, vector<int> pos, Scalar circolor);
    // compute a norm to find out the pixel which is the closest to a choosen value by mode1 or mode2
    double normValue(int r, int g,int b,int x,int y);

 signals:
    //signal to output frame to be displayed
    void processedImage(const QImage &image);
    // signal sends a most distinctive pixel on an image
    void refColor(QColor a, vector<int>);

 private slots:
    // find out a the most distinctive pixel
    void detectRefColor();

 protected:
     // streaming frames from camera
    void run();

 public:

    Player(QObject *parent = 0);
    ~Player();
    //play the video
    void Play();
    //stop the video
    void Stop();
    //check if the player has been stopped
    bool isStopped() const;

    QColor choosenColormode1;
    QColor choosenColormode2;
    vector<int> poseMode1;
    vector<int> poseMode2;
    Mat RGBframe;
    bool checkBox1On;
    bool checkBox2On;
    bool saveVideo;
    bool startSaveVideo;
    Scalar circle1;
    Scalar circle2;
    int circleRadius;
    int circleThinckness;

};
#endif // PLAYER_H
