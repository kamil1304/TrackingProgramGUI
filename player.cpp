#include "player.h"

Player::Player(QObject *parent)
 : QThread(parent)
{
    stop = true;
    capture.open(0);
    checkBox1On=false;
    checkBox2On=false;
    saveVideo= false;
    poseMode1.push_back(0);
    poseMode1.push_back(0);
    poseMode2.push_back(0);
    poseMode2.push_back(0);
    circle1=Scalar(222,233,244);
    circle2=Scalar(122,133,44);
    startSaveVideo=false;
    circleRadius=40;
    circleThinckness=8;
    fileName="myTracking.avi" ;
    sizeSave = Size( capture.get(CV_CAP_PROP_FRAME_WIDTH),
                     capture.get(CV_CAP_PROP_FRAME_HEIGHT));

}

void Player::Play()
{
    if (!isRunning()) {
        if (isStopped()){
            stop = false;
        }
        start(LowPriority);
    }
}

void Player::detectRefColor()
{
    int i=0;
    Vec3i avr(0,0,0);

    capture >> frame;

    cv::cvtColor(frame, RGBframe, CV_BGR2RGB);

    for(int y=0;y<RGBframe.rows;y++)
    {
        for(int x=0;x<RGBframe.cols;x++)
        {
            Vec3b color = frame.at<Vec3b>(Point(x,y));
            avr+=color;
            i++;
         }
     }
    avr=avr/i;

    double max=0;
    double actual=0;
    int diff1, diff2, diff3, sumdiff;
    vector<int> pose;
    pose.push_back(0);
    pose.push_back(0);

    for(int x=0;x<RGBframe.cols;x++)
    {
        for(int y=0;y<RGBframe.rows;y++)
        {

            diff1=(avr[0]-RGBframe.at<Vec3b>(Point(x,y))[0]);
            diff2=(avr[1]-RGBframe.at<Vec3b>(Point(x,y))[1]);
            diff3=(avr[2]-RGBframe.at<Vec3b>(Point(x,y))[2]);
            sumdiff=diff1*diff1+diff2*diff2+diff3*diff3;
            actual = std::sqrt((double)sumdiff);

          if (max<actual)
          {
             max=actual;
             pose[0]=x;
             pose[1]=y;
          }
        }
    }

    int r=RGBframe.at<Vec3b>(Point(pose[0], pose[1]))[0];
    int g=RGBframe.at<Vec3b>(Point(pose[0], pose[1]))[1];
    int b=RGBframe.at<Vec3b>(Point(pose[0], pose[1]))[2];

    QColor sendrgb(r,g,b,255);

  emit refColor(sendrgb,pose );
}

void Player::run()
{
    while(!stop)
    {
        if (!capture.isOpened())
        {
            stop = true;
        }
        capture >> frame;
        cv::cvtColor(frame, RGBframe, CV_BGR2RGB);

        // draw a circle for mode1
        if(checkBox1On)
        {
            drawCircle(choosenColormode1, poseMode1, circle1 );
        }
        // draw a circle for mode2
        if(checkBox2On)
        {
              drawCircle(choosenColormode2, poseMode2, circle2);
        }

        img = QImage((const unsigned char*)(RGBframe.data),
                          RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);

        // save a video
        if(startSaveVideo)
        {
            outputVideo.open(fileName, capture.get(CV_CAP_PROP_FOURCC), 1,sizeSave, true);
            startSaveVideo=false;      
        }

        if (saveVideo && outputVideo.isOpened())         
            outputVideo << RGBframe;

        emit processedImage(img);
        waitKey(30);
    }
}

void Player::drawCircle(QColor col, vector<int> pos  , Scalar circolor)
{
    vector<int> finalPose;
    finalPose.push_back(0);
    finalPose.push_back(0);
    finalPose= trackingPixel.trackingPixel(col,pos,RGBframe);

   if (pos==poseMode1)
   {
     poseMode1[0]=finalPose[0];
     poseMode1[1]=finalPose[1];
    }
   if (pos==poseMode2)
   {
     poseMode2[0]=finalPose[0];
     poseMode2[1]=finalPose[1];
    }

    circle(RGBframe, Point(finalPose[0],finalPose[1]), circleRadius,circolor, circleThinckness, 0);

 }

double Player::normValue(int r, int g, int b, int x, int y)
{
    int diff1, diff2, diff3, sumdiff;
    double actual=0;

     if ( x<0 || y<0 || x>RGBframe.rows || y>RGBframe.cols)
          return 1000;

    diff1=(r-RGBframe.at<Vec3b>(Point(x,y))[0]);
    diff2=(g-RGBframe.at<Vec3b>(Point(x,y))[1]);
    diff3=(b-RGBframe.at<Vec3b>(Point(x,y))[2]);
    sumdiff=diff1*diff1+diff2*diff2+diff3*diff3;
    actual = std::sqrt((double)sumdiff);
    return actual;
}

Player::~Player()
{
    mutex.lock();
    stop = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}
void Player::Stop()
{
    stop = true;
}

bool Player::isStopped() const{
    return this->stop;
}

