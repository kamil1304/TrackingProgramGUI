#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPoint>
#include <QMessageBox>
#include <QPixmap>
#include <QRect>
#include <QSize>
#include <QImage>
#include <QRgb>
#include <QMessageBox>
#include <QScreen>
#include <QMouseEvent>
#include <QMutex>
#include "vector"
#include <string>

#include "player.h"
#include "methods3d.h"




namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    QImage image;
    QMouseEvent* eve;
    QMutex mutex;
    int cx,cy;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //display video frame in player UI
    void updatePlayerUI(QImage img);
    // slot for the play push button.
    void on_pushButton_2_clicked();
    // turn of/on mode1 using checkBox
    void on_checkBox_stateChanged();
    // turn of/on mode2 using checkBox
    void on_checkBox_2_stateChanged();
    // get color using mode2
    void getColorMode2(QColor getcolor,vector<int> pos);
     // get color by clicking on screen-mode1
    void mousePressEvent(QMouseEvent *event);
    // enables start streaming video
    void on_pushButton_clicked();
    // get the value of cx and cy- principal point
    void setCenter();


signals:
    // sent signal to show, that mode2 is set
    void chceckBox2Change();
    // send a position of pixel (u,v) to estimate angles
    void sendPosetoEstimateAngels( vector<int>);

private:
    //checkBox is On/Off
    bool checkBox1On;
    bool checkBox2On;
    // video should be saved or not
    bool saveVideo;
    // if a saving video is started
    bool startSaveVideo;
    // from witch mode a homography should be computed
    bool homoMode1;
    bool homoMode2;
    Ui::MainWindow *ui;
    Player* myPlayer;
    // is a play button pressd
    bool playButtonPressed;
    // are the vaules of principal point set
    bool principalPointSet;

    // colors of bounding circle  for certian mode
    QColor choosenColormode1;
    QColor choosenColormode2;
    // poses of choosen  pixel in each mode
    vector<int> poseMode1;
    vector<int> poseMode2;
    // object to comupte homography and Y&P angles
    Methods3d anglesPY;

    // set parameters to start computing homography and focals
     void startHomo();
    // set Pitch and Yaw  in label
    QString setAnglesMode(vector<double>);
    // create a ctring for diplay color
    QString setString(QColor myColor);
    void drawCircle();

};
#endif // MAINWINDOW_H
