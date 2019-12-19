/*
g++ -Wall -o lena main.cpp -lpthread -lX11
./lena

Imagenes que se uso:
simpson.jpg
dota.jpg
paisaje.jpg
*/

#include "CImg.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace cimg_library;
using namespace std;

int nodoPadre=0;
int nodoHoja=0;
int nivelBajo=50000;
int nivelAlto=0;

struct Quad_Tree{
    int num;
    Quad_Tree *NW;
    Quad_Tree *NE;
    Quad_Tree *SE;
    Quad_Tree *SW;
};

Quad_Tree *nuevo(int dato){
    Quad_Tree *aux=new Quad_Tree();
    aux->num=dato;
    aux->NE=NULL;    aux->NW=NULL;    aux->SE=NULL;    aux->SW=NULL;
    return aux;
}

int REC(CImg<unsigned char> gray,int a,int b,int x,int y){
    int rec=(int)gray(a,b);
    if (a+1==x && b+1==y)    return rec;
    for(int i=a;i<x;i++){
        for(int j=b;j<y;j++){
            if ((int)gray(i,j)<=(rec-50) || (int)gray(i,j)>=(rec+50))    return -1; //los padres seran 0
        	//EL COLOR VARIA EN 2
            //-1 significa que el nodo en cuestion es padre, si posee otro numero (positivo) es hoja
        }
    }
    return rec;
}


void Create(Quad_Tree *&arbol,CImg<unsigned char> gray,int a,int b,int x,int y){
    if (arbol==NULL){
        arbol=nuevo(REC(gray,a,b,x,y));
        if (arbol->num!=-1){   return;
        }else{
            Quad_Tree *aux=arbol;
            Create(aux->NW,gray,a,b,(a+x)/2,(b+y)/2); //NOROESTE
            Create(aux->NE,gray,a,(b+y)/2,(a+x)/2,y); //NORESTE
            Create(aux->SW,gray,(a+x)/2,b,x,(b+y)/2); //SUROESTE
            Create(aux->SE,gray,(a+x)/2,(b+y)/2,x,y); //SURESTE
            //UNA VEZ TERMINE SALE DE LA RAMA
        }
    }else    return;
}
void Paint(Quad_Tree *arbol,CImg<unsigned char> &grayDISP,int a,int b,int x,int y){
	if (arbol==NULL){
		return;
	}else{
		if (arbol->num==-1){   //si el nodo es padre
            nodoPadre++;
			Paint(arbol->NW,grayDISP,a,b,(a+x)/2,(b+y)/2); //NOROESTE
            Paint(arbol->NE,grayDISP,a,(b+y)/2,(a+x)/2,y); //NORESTE
            Paint(arbol->SW,grayDISP,(a+x)/2,b,x,(b+y)/2); //SUROESTE
            Paint(arbol->SE,grayDISP,(a+x)/2,(b+y)/2,x,y); //SURESTE
		}else{
            nodoHoja++;
			for(int i=a;i<x;i++){
				for(int j=b;j<y;j++){
					grayDISP(i,j,0,0)=arbol->num + '0';
				}
			}return;
		}
	}
}
void complejidad(Quad_Tree *arbol,CImg<unsigned char> &grayDISP,int nivel){
    if (arbol==NULL){
        if (nivel >= nivelAlto)    nivelAlto=nivel;
        if (nivel <= nivelBajo)    nivelBajo=nivel;
        return;
    }else{
        complejidad(arbol->NW,grayDISP,nivel+1); //NOROESTE
        complejidad(arbol->NE,grayDISP,nivel+1); //NORESTE
        complejidad(arbol->SW,grayDISP,nivel+1); //SUROESTE
        complejidad(arbol->SE,grayDISP,nivel+1); 
        
    }
}


int main() {
	Quad_Tree *arbol=NULL;

	CImg<unsigned char> 
	image("simpson.jpg"),
	gray(image.width(), image.height(), 1, 1, 0),
	grayDISP(image.width(), image.height(), 1, 1, 0);
	
	cimg_forXY(image,x,y) {
    	int R = (int)image(x,y,0,0);
    	int G = (int)image(x,y,0,1);
    	int B = (int)image(x,y,0,2);
    	int grayValue = (int)(0.33*R + 0.33*G + 0.33*B);
    	gray(x,y,0,0) = grayValue;
	}
		
    
    Create(arbol,gray,0,0,gray.height()-1,gray.width()-1);
    
    cout<<"Dimensiones de la imagen: "<<gray.height()<<"x"<<gray.width()<<endl;
    Paint(arbol,grayDISP,0,0,gray.height()-1,gray.width()-1);
    cout<<"Cantidad de nodos padre: "<<nodoPadre<<endl;
    cout<<"Cantidad de nodos hoja: "<<nodoHoja<<endl;
    complejidad(arbol,grayDISP,0);
    cout<<"Nivel Minimo: "<<nivelBajo<<endl;
    cout<<"Nivel Maximo: "<<nivelAlto<<endl;

    CImgDisplay
    main_disp(gray,"Gray"),
    draw_disp2(grayDISP,"QUAD_TREE");
 
  	while (!main_disp.is_closed()){
        main_disp.wait();
	}

    return 0;
}
