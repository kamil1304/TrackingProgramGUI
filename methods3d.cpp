#include "methods3d.h"

Methods3d::Methods3d(QObject *parent)
 : QThread(parent)
{
    minRadius=12;
    homoPoints=30;
    homoMinPoints=8;
    homoReady=false;
    f0Good=false;
    f1Good=false;
}

void Methods3d::getPoints(vector<int> newPose)
{
    qDebug()<<"in homography";
    qDebug()<<homoReady;
     this->newValue= Point2f(newPose[0],newPose[1]);

   if(!firstPoints.empty() && !secondPoints.empty() && !homoReady)
   {
        if(farEnough(this->newValue,secondPoints.back()))
        {
            firstPoints.push_back(secondPoints.back());
            secondPoints.push_back(this->newValue);

             // compute homography
             if( secondPoints.size()>homoMinPoints)
            {
                homography=findHomography(cv::Mat(firstPoints),cv::Mat(secondPoints),CV_RANSAC);
                computeHomo();
            }
         }
   }
   else if(firstPoints.empty() && !homoReady)
   {
       firstPoints.push_back(this->newValue);
   }
     else if (!firstPoints.empty()&& secondPoints.empty() && farEnough(newValue,firstPoints.back()))
   {
       secondPoints.push_back(this->newValue);
   }

   if(secondPoints.size()>homoPoints && f1Good &&f0Good)
       homoReady=true;
}
void Methods3d::computeHomo(){

    if(!homography.empty() )
    {
        if(!homoReady)
        focalsFromHomography(homography,f0, f1,f0Good, f1Good);
    }
}

vector<double> Methods3d::computeAngles(vector<int> value)
{
    double temp;

    //Pitch
    temp= f0/(value[0]- cx );
    pitch=atan(temp)*180/PI;

    //Yaw
    temp= f1/(value[1]- cy );
    yaw=atan(temp)*180/PI;

    vector<double> angels;
    angels.push_back(pitch);
    angels.push_back(yaw);

    return  angels;
}

bool Methods3d::farEnough(Point a, Point b)
{
    double result=sqrt(pow((a.x-b.x),2)+ pow((a.y-b.y),2));

    if (result<minRadius)
        return false;
    else
        return true;
}
void Methods3d::setCenter( int x, int y)
{
    this->cx=x;
    this->cy=y;
}
bool Methods3d::isReady()
{
    return homoReady;
}

void Methods3d::focalsFromHomography(const Mat& H, double &f0, double &f1, bool &f0_ok, bool &f1_ok)
{
    CV_Assert(H.type() == CV_64F && H.size() == Size(3, 3));

    const double* h = H.ptr<double>();

    double d1, d2; // Denominators
    double v1, v2; // Focal squares value candidates

    f1_ok = true;
    d1 = h[6] * h[7];
    d2 = (h[7] - h[6]) * (h[7] + h[6]);
    v1 = -(h[0] * h[1] + h[3] * h[4]) / d1;
    v2 = (h[0] * h[0] + h[3] * h[3] - h[1] * h[1] - h[4] * h[4]) / d2;
    if (v1 < v2) std::swap(v1, v2);
    if (v1 > 0 && v2 > 0) f1 = std::sqrt(std::abs(d1) > std::abs(d2) ? v1 : v2);
    else if (v1 > 0) f1 = std::sqrt(v1);
    else f1_ok = false;

    f0_ok = true;
    d1 = h[0] * h[3] + h[1] * h[4];
    d2 = h[0] * h[0] + h[1] * h[1] - h[3] * h[3] - h[4] * h[4];
    v1 = -h[2] * h[5] / d1;
    v2 = (h[5] * h[5] - h[2] * h[2]) / d2;
    if (v1 < v2) std::swap(v1, v2);
    if (v1 > 0 && v2 > 0) f0 = std::sqrt(std::abs(d1) > std::abs(d2) ? v1 : v2);
    else if (v1 > 0) f0 = std::sqrt(v1);
    else f0_ok = false;
}
