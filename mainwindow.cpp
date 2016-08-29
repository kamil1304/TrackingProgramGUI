#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    myPlayer = new Player();
    poseMode1.push_back(0);
    poseMode1.push_back(0);
    poseMode2.push_back(0);
    poseMode2.push_back(0);
    checkBox1On=false;
    checkBox2On=false;
    saveVideo=false;
    startSaveVideo=true;
    playButtonPressed=false;
    principalPointSet=false;

    homoMode1=false;
    homoMode2=false;

    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),
                              this, SLOT(updatePlayerUI(QImage)));

    QObject::connect(this, SIGNAL(chceckBox2Change()),myPlayer, SLOT(detectRefColor()));

    QObject::connect(myPlayer,&Player::refColor, this, &MainWindow::getColorMode2);

    QObject::connect( this,&MainWindow::sendPosetoEstimateAngels,&anglesPY, &Methods3d::getPoints);

}

void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        if (!principalPointSet)
               startHomo();


        ui->label->setAlignment(Qt::AlignCenter);

        ui->label->setPixmap(QPixmap::fromImage(img).scaled (ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));


        if(myPlayer->poseMode1[0]!=0 && myPlayer->poseMode1[1]!=0 && homoMode1 ){
            emit sendPosetoEstimateAngels(myPlayer->poseMode1);}


        if(myPlayer->poseMode2[0]!=0 && myPlayer->poseMode2[1]!=0 && homoMode2 )
            emit sendPosetoEstimateAngels(myPlayer->poseMode2);


        if(anglesPY.isReady() && checkBox1On  )
        {
             vector<double> temp;
             temp= anglesPY.computeAngles(myPlayer->poseMode1);
              qDebug()<<temp[0]<<" "<<temp[1];

             ui->label_7->setText(setAnglesMode(temp));
        }else
            ui->label_7->setText("Pitch and Yaw");


        if(anglesPY.isReady()&& checkBox2On )
        {
            qDebug()<<"INN  2 chatterBox";
             vector<double> temp;
             temp= anglesPY.computeAngles(myPlayer->poseMode2);
             ui->label_8->setText(setAnglesMode(temp));
        }else
            ui->label_8->setText("Pitch and Yaw");
        if((checkBox1On || checkBox2On) &&  !anglesPY.isReady())
            ui->label_9->setText(" homogrpahy in progress...");
        else
             ui->label_9->setText("  ");


    }
}
void MainWindow::startHomo()
{

       setCenter();

      anglesPY.setCenter(this->cx,this->cy);

      if (checkBox1On)
           homoMode1=true;

      if (checkBox2On)
           homoMode2=true;

      if( homoMode2 && homoMode1)
          homoMode2=false;

       if( homoMode2 || homoMode1)
           principalPointSet=true;


}

MainWindow::~MainWindow()
{
    delete myPlayer;
    delete ui;
  }

void MainWindow::on_pushButton_2_clicked()
{
    if (myPlayer->isStopped())
    {
        myPlayer->Play();
        ui->pushButton_2->setText(tr("Stop"));
        myPlayer->checkBox2On=this->checkBox2On;
        playButtonPressed=true;

    }else
    {
        myPlayer->Stop();
        ui->pushButton_2->setText(tr("Play"));
        myPlayer->checkBox2On=this->checkBox2On;
        playButtonPressed=false;
    }
}

void MainWindow::on_checkBox_stateChanged()
{
    if(!checkBox1On)
    {
         ui->checkBox->setText("Mode 1 Running");
         this->checkBox1On=true;
    }
    else
    {
        ui->checkBox->setText("Mode 1");
        this->checkBox1On=false;
        ui->label_5->setText("Choose color");
        myPlayer->checkBox1On=this->checkBox1On;
    }
}
void MainWindow::on_checkBox_2_stateChanged()
{
    if(!checkBox2On)
    {
      emit chceckBox2Change();
      this->checkBox2On=true;
      ui->checkBox_2->setText("Mode 2 Running");
    }
    else
    {
      ui->checkBox_2->setText("Mode 2");
      this->checkBox2On=false;
      ui->label_6->setText("Choose color");
      myPlayer->checkBox2On=this->checkBox2On;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){

    if(checkBox1On )
    {
        poseMode1[0]=event->pos().x();
        poseMode1[1]=event->pos().y();
        image=ui->label->grab(QRect( QPoint(0, 0), QSize( -1, -1 ) )).toImage();
        QRgb rgb=image.pixel(poseMode1[0],poseMode1[1]);
        choosenColormode1.setRgb(rgb);

        myPlayer->choosenColormode1=this->choosenColormode1;
        myPlayer->poseMode1=this->poseMode1;
        myPlayer->checkBox1On=this->checkBox1On;

        ui->checkBox->setText("Mode 1 Running");
        ui->label_5->setText(setString(choosenColormode1));
        QMessageBox::information(this,"You get it!",setString(choosenColormode1));
    }
    else
    {
      checkBox1On=false;
     }
}

void MainWindow::getColorMode2(QColor getcolor, vector<int> pos)
{
    choosenColormode2=getcolor;
    poseMode2[0]=pos[0];
    poseMode2[1]=pos[1];

     this->checkBox2On=true;
    myPlayer->choosenColormode2=this->choosenColormode2;
    myPlayer->poseMode2=this->poseMode2;
    myPlayer->checkBox2On=this->checkBox2On;

    ui->label_6->setText(setString(choosenColormode2));
    QMessageBox::information(this,"You get it!", setString(choosenColormode2));
}
QString MainWindow::setString(QColor myColor)
{
    QString color="R:";
    color.append(QString::number(myColor.toRgb().red()));
    color.append("  G:");
    color.append(QString::number(myColor.toRgb().green()));
    color.append("  B:");
    color.append(QString::number(myColor.toRgb().blue()));
    return color;
}

void MainWindow::on_pushButton_clicked()
{
    if ( playButtonPressed)
    {
        if (!saveVideo)
        {
          if(this->startSaveVideo)
          {
              this->startSaveVideo=false;
              myPlayer->startSaveVideo=true;
          }

          ui->pushButton->setText("Stop save");
          this->saveVideo=true;
          myPlayer->saveVideo=this->saveVideo;

        }
        else
        {
            ui->pushButton->setText("Save video");
            this->saveVideo=false;
            myPlayer->saveVideo=this->saveVideo;
        }
    }
    else
        QMessageBox::information(this,"Warning!"," Cannot save Video, first start streaming");

}

void MainWindow::setCenter()
{
    this->cx=myPlayer->RGBframe.rows/2;
    this->cy=myPlayer->RGBframe.cols/2;
}

QString MainWindow::setAnglesMode(vector<double> angles)
{
    QString ang="P:";
    ang.append(QString::number(angles[0]));
    ang.append("  Y:");
    ang.append(QString::number(angles[1]));

    return ang;
}
