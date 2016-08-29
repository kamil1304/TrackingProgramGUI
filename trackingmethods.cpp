#include "trackingmethods.h"

TrackingMethods::TrackingMethods()
{
    howBigSquare=50;
}

vector<int> TrackingMethods::trackingPixel(QColor col, vector<int> po, Mat frame)
{
    RGBframe=frame;
    //just big number, a pose which is beyond a frame
    double max=1000;

    vector<int> finalPose;
    finalPose.push_back(0);
    finalPose.push_back(0);
    int x=po[0];
    int y=po[1];
    int x2,y2;
    int r=col.toRgb().red();
    int g=col.toRgb().green();
    int b=col.toRgb().blue();
    double actual;

   for (int i=0; i< this->howBigSquare; i++)
   {
       //first side of a square
        y2=y+i;
        for(int x2=x-i; x2<x+i;x2++)
        {
          actual =normValue(r,g,b,x2,y2);

          if (max>actual)
          {
             max=actual;
             finalPose[0]=x2;
             finalPose[1]=y2;
          }
         }
        //second side of a square
         y2=y-i;
         for(int x2=x-i; x2<x+i;x2++)
         {
           actual =normValue(r,g,b,x2,y2);
           if (max>actual)
           {
              max=actual;
              finalPose[0]=x2;
              finalPose[1]=y2;
           }
          }
         //third side of a square
          x2=x+i;
          for(int y2=y-i; y2<y+i;y2++)
          {
            actual =normValue(r,g,b,x2,y2);
            if (max>actual)
            {
               max=actual;
               finalPose[0]=x2;
               finalPose[1]=y2;
            }
           }
          //fourth side of a square
           x2=x-i;
           for(int y2=y-i; y2<y+i;y2++)
           {
             actual =normValue(r,g,b,x2,y2);
             if (max>actual)
             {
                max=actual;
                finalPose[0]=x2;
                finalPose[1]=y2;
             }
            }
        }

   return finalPose;
}

double TrackingMethods::normValue(int r, int g, int b, int x, int y)
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
