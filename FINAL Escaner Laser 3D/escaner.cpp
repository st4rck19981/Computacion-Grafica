#include <iostream>
#include "escaner.h"
using namespace std;

escaner::escaner()
{
   iMinH = 50;
   iMinS = 90;
   iMinV = 250;

   iMaxH = 255;
   iMaxS = 255;
   iMaxV = 255;

   rotacion = 0.0;
   angulo = 1.3;
}

void escaner::triangulacion(int x, int y, int &_X, int &_Z){
    x = (240-x)*0.4;
    _X = x*cos(rotacion);
    _Z = x*sin(rotacion);
}

void escaner::media_puntos(vector<vector<Point> > contornos, map<int,int> &mPuntos){
    if(contornos.size()){
        map<int,int>::iterator it;

        for(int i=0; i<contornos.size(); ++i){
            for(int j =0; j < contornos[i].size(); ++j){

                it = mPuntos.find( contornos[i][j].y );
                if( it != mPuntos.end() ){
                    mPuntos[contornos[i][j].y ] = ( mPuntos[ contornos[i][j].y ] + contornos[i][j].x )/2;
                }else{
                    mPuntos[ contornos[i][j].y ] = contornos[i][j].x;
                }
            }
        }
    }
}

void escaner::calibrar(Mat &imgOriginal){
    CvPoint mid_bottom , mid_top ;
    mid_bottom . x = 1920/2;
    mid_bottom . y = 0;
    mid_top . x = 1920/2;
    mid_top . y = 1080;
    IplImage frame_ipl = imgOriginal ;

    cvLine (& frame_ipl , mid_bottom , mid_top , CV_RGB (0 ,255 ,0) , 2) ;
}

void escaner::guardar(){
    ofstream archivo("objeto.obj");
    string ver = "v ";

    for(int i=0;i<nube_puntos.size();++i){
       archivo << "v "<<nube_puntos[i][0]<<" "<<nube_puntos[i][1]<<" "<<nube_puntos[i][2]<<endl;
    }
    archivo.close();
}

void escaner::ejecutar(){

    videocapture.open("muneco.mp4");
    if( !videocapture.isOpened()){
        cout<<"Camera Not Open"<<endl;
        return;
    }
    int cont = 0;
    int x,y;
    char key = 0;

    while(key != 27){
        Mat imgOriginal;
        bool Success = videocapture.read(imgOriginal);

        if(!Success){
            cout<<"Video Stream Not Open"<<endl;
            continue;
        }

        Mat imgHSV;
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

        Mat imgThresholded;
        calibrar(imgOriginal);

        inRange(imgHSV, Scalar(iMinH, iMinS,iMinV),Scalar(iMaxH,iMaxS,iMaxV), imgThresholded);

        dilate(imgThresholded,imgThresholded,Mat(), Point(-1, -1), 2, 1, 1);
        erode(imgThresholded,imgThresholded,Mat(), Point(-1, -1), 2, 1, 1);

        imshow("linea_laser",imgThresholded);

        Mat salida = imgThresholded.clone();
        Canny(imgThresholded, salida, 100, 200);
        vector< vector< Point> > contornos;
        map<int,int> mPuntos;
        findContours(salida, contornos, RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
        media_puntos(contornos,mPuntos);

        vector<Point> mp;
        int _X,_Z;


        cout<<"angulo:  "<<angulo<<" "<<imgOriginal.cols<<" "<<salida.rows<<endl;
        for(const auto &dist : mPuntos){
            if(dist.first < 990 and dist.first>120){
                triangulacion(dist.second,dist.first,_X,_Z);
                vector<int> test;
                test.push_back(_X);
                test.push_back(dist.first);
                test.push_back(_Z);
                nube_puntos.push_back(test);
            }
        }

        rotacion = angulo*((22/7)/180.0);
        angulo+=1.33;

        guardar();
        if(angulo > 400) break;

        imshow("canny",salida);
        key = 0;
        key=waitKey(20);
    }
}

