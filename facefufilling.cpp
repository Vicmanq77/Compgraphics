#include<cstring>
#include<iostream>
#include<tgmath.h>
#include<fstream>
#include<thread>
#include <climits>
#include <bitset>
using namespace std;
#define PI 3.14159265

class FHDRaster {
  unsigned char data[1920][1080][3];
  public:
  FHDRaster(void) {
     memset(data, 0, 1920*1080*3);  
  }
  void setPixel(unsigned int x, unsigned int y,unsigned char r,unsigned char g,unsigned char b) {
      if( x >= 1920 || y >= 1080) {
        return;
      }
      data[x][y][0] = r;
      data[x][y][1] = g;
      data[x][y][2] = b;
  }
  void write(void) {
   int x = 0;
   int y = 0;
   cout<<"P6\n1920 1080 255\n";
   for(y=0;y<1080;y++) {
     for(x=0;x<1920;x++) {
      cout<<data[x][y][0];
      cout<<data[x][y][1];
      cout<<data[x][y][2];
     } 
   }
  }
/*
  void drawLinebresenhampara(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2, unsigned char r,unsigned char g,unsigned char b, FHDRaster* raster){
  unsigned int auxx,auxmx,auxy,auxmy,summ,igu;
  int n;
  n = 7;
  unsigned int ax1[n-1];
  unsigned int ax2[n-1];
  unsigned int ay1[n-1];
  unsigned int ay2[n-1];
  if (x2>x1)
  {
    auxx = (x2-x1)/n;
    auxmx = (x2-x1) % n;
    summ=0;
    igu=0;
    for (int i = 0; i < n; ++i)
    {
      if (auxmx != 0)
      {
        ax1[(n-1)-i] = x1 + (auxx)*(i) + (igu) + summ;
        ax2[(n-1)-i] = x1 + (auxx)*(i+1) + (1) + summ;
        igu=1;
        auxmx--;
        summ++;
      }else{
        ax1[(n-1)-i]= x1 + (auxx*i) + (igu) + summ;
        ax2[(n-1)-i]= x1 + (auxx)*(i+1)  + summ;
        igu=1;
      }
    }
  }else{
    auxx = (x1-x2)/n;
    auxmx = (x1-x2) % n;
    summ=0;
    igu=0;
    for (int i = 0; i < n; ++i)
    {
      if (auxmx != 0)
      {
        ax2[i] = x2 + (auxx)*(i) + (igu) + summ;
        ax1[i] = x2 + (auxx)*(i+1) + (1) + summ;
        igu=1;
        auxmx--;
        summ++;
      }else{
        ax2[i]= x2 + (auxx*i) + (igu)+ summ;
        ax1[i]= x2 + (auxx)*(i+1)  + summ;
        igu=1;
      }
    }
  }
  if (y2>y1)
  {
    auxy = (y2-y1)/n;
    auxmy = (y2-y1) % n;
    summ=0;
    igu=0;
    for (int i = 0; i < n; ++i)
    {
      if (auxmy != 0)
      {
        ay1[(n-1)-i] = y1 + (auxy)*(i) + (igu) + summ;
        ay2[(n-1)-i] = y1 + (auxy)*(i+1) + (1) + summ;
        igu=1;
        auxmy--;
        summ++;
      }else{
        ay1[(n-1)-i]= y1 + (auxy*i) + (igu) + summ;
        ay2[(n-1)-i]= y1 + (auxy)*(i+1)  + summ;
        igu=1;
      }
    }
  }else{
    auxy = (y1-y2)/n;
    auxmy = (y1-y2) % n;
    summ=0;
    igu=0;
    for (int i = 0; i < n; ++i)
    {
      if (auxmy != 0)
      {
        ay2[i] = y2 + (auxy)*(i) + (igu) + summ;
        ay1[i] = y2 + (auxy)*(i+1) + (1) + summ;
        igu=1;
        auxmy--;
        summ++;
      }else{
        ay2[i]= y2 + (auxy*i) + (igu)+ summ;
        ay1[i]= y2 + (auxy)*(i+1)  + summ;
        igu=1;
      }
    }
  }
  thread t[n];
  for(int i=0;i<n;i++){
    t[i] = thread(&FHDRaster::drawLinebresenham,raster ,ax1[i],ay1[i],ax2[i],ay2[i],r,g,b);
  }
  for (int i=0;i<n;++i)
  {
    t[i].join();
  }
}
  void drawLinebresenham(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2, unsigned char r,unsigned char g,unsigned char b) {
      int o;
      o = octant(x1,y1,x2,y2);
      switch(o){
        case 1:
          drawprocessbresenham1(x1,y1,x2,y2,r,g,b);
          break;
        case 2:
          drawprocessbresenham2(y1,x1,y2,x2,r,g,b);
          break;
        case 3:
          drawprocessbresenham3(y1,x1,y2,x2,r,g,b);
          break;
        case 4:
          drawprocessbresenham4(x1,y1,x2,y2,r,g,b);
          break;
        case 5:
          drawprocessbresenham5(x1,y1,x2,y2,r,g,b);
          break;
        case 6:
          drawprocessbresenham6(y1,x1,y2,x2,r,g,b);
          break;
        case 7:
          drawprocessbresenham7(y1,x1,y2,x2,r,g,b);
          break;
        case 8:
          drawprocessbresenham8(x1,y1,x2,y2,r,g,b);
          break;
      }   
   }
  void drawprocessbresenham1(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned char r,unsigned char g,unsigned char b) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y2 - y1;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      setPixel(x1, y1, r, g, b);
      setPixel(x2, y2, r, g, b);
      for(x = x1+1, y = y1; x < x2 ; x++ ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        } 
        setPixel(x, y, r, g, b); 
      } 
  }
  void drawprocessbresenham2(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned char r,unsigned char g,unsigned char b) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y2 - y1;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      setPixel(y1, x1, r, g, b);
      setPixel(y2, x2, r, g, b);
      for(x = x1+1, y = y1; x < x2 ; x++ ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        }
        setPixel(y, x, r, g, b); 
      } 
  }
  void drawprocessbresenham3(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned char r,unsigned char g,unsigned char b) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y1 - y2;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      setPixel(y1, x1, r, g, b);
      setPixel(y2, x2, r, g, b);
      for(x = x2-1, y = y2; x > x1 ; x-- ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        } 
        setPixel(y, x, r, g, b); 
      } 
  }
  void drawprocessbresenham4(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned char r,unsigned char g,unsigned char b) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x1 - x2;
      int dy = y2 - y1;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      setPixel(x1, y1, r, g, b);
      setPixel(x2, y2, r, g, b);
      for(x = x1-1, y = y1; x > x2 ; x-- ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        } 
        setPixel(x, y, r, g, b); 
      } 
  }
  void drawprocessbresenham5(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned char r,unsigned char g,unsigned char b) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x1 - x2;
      int dy = y1 - y2;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      setPixel(x1, y1, r, g, b);
      setPixel(x2, y2, r, g, b);
      for(x = x2+1, y = y2; x < x1 ; x++ ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        } 
        setPixel(x, y, r, g, b); 
      } 
  }
  void drawprocessbresenham6(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned char r,unsigned char g,unsigned char b) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x1 - x2;
      int dy = y1 - y2;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      setPixel(y1, x1, r, g, b);
      setPixel(y2, x2, r, g, b);
      for(x = x1-1, y = y1; x >= x2 ; x-- ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y--;
        }
        setPixel(y, x, r, g, b); 
      } 
  }
  void drawprocessbresenham7(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned char r,unsigned char g,unsigned char b) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x1 - x2;
      int dy = y2 - y1;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      setPixel(y1, x1, r, g, b);
      setPixel(y2, x2, r, g, b);
      for(x = x1-1, y = y1; x >= x2 ; x-- ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        }
        setPixel(y, x, r, g, b); 
      } 
  }
  void drawprocessbresenham8(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned char r,unsigned char g,unsigned char b) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y1 - y2;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      setPixel(x1, y1, r, g, b);
      setPixel(x2, y2, r, g, b);
      for(x = x1+1, y = y1; x < x2 ; x++ ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y--;
        } 
        setPixel(x, y, r, g, b); 
      } 
  }
  int octant(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2){
    float m = 0;
    int dx = x2 - x1;
    int dy = y2 - y1;  
    m = (double)(dy)/(double)(dx);
   
    if (m <= 1 && m >= 0)
    {
      if (x1 < x2)
      {
        return 1;
      }else{
        return 5;
      }

    }else if (m > 1)
    {
      if (y1 < y2)
      {
        return 2;
      }else{
        return 6;
      }
    }else if (m < -1)
    {
      if (y1 < y2)
      {
        return 3;
      }else{
        return 7;
      }
    }else{
      if (x2 < x1)
      {
        return 4;
      }else{
        return 8;
      }
    }
  }
  */
};

struct vect{
  int nvect;
  double x,y,z;
};

void writepixel(unsigned int x, unsigned int y,unsigned int lines[][2], int& lineaux){
  lines[lineaux][0] = x;
  lines[lineaux][1] = y;
  lineaux++;
}

  void drawprocessbresenham1(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned int lines[][2],int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y2 - y1;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      writepixel(x1, y1,lines,linesaux);
      writepixel(x2, y2,lines,linesaux);
      for(x = x1+1, y = y1; x < x2 ; x++ ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        } 
        writepixel(x, y,lines,linesaux); 
      } 
  }
  void drawprocessbresenham2(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned int lines[][2],int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y2 - y1;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      writepixel(y1, x1,lines,linesaux);
      writepixel(y2, x2,lines,linesaux);
      for(x = x1+1, y = y1; x < x2 ; x++ ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        }
        writepixel(y, x,lines,linesaux); 
      } 
  }
  void drawprocessbresenham3(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned int lines[][2],int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y1 - y2;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      writepixel(y1, x1,lines,linesaux);
      writepixel(y2, x2,lines,linesaux);
      for(x = x2-1, y = y2; x > x1 ; x-- ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        } 
        writepixel(y, x,lines,linesaux); 
      } 
  }
  void drawprocessbresenham4(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned int lines[][2],int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x1 - x2;
      int dy = y2 - y1;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      writepixel(x1, y1,lines,linesaux);
      writepixel(x2, y2,lines,linesaux);
      for(x = x1-1, y = y1; x > x2 ; x-- ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        } 
        writepixel(x, y,lines,linesaux); 
      } 
  }
  void drawprocessbresenham5(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned int lines[][2],int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x1 - x2;
      int dy = y1 - y2;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      writepixel(x1, y1,lines,linesaux);
      writepixel(x2, y2,lines,linesaux);
      for(x = x2+1, y = y2; x < x1 ; x++ ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        } 
        writepixel(x, y,lines,linesaux); 
      } 
  }
  void drawprocessbresenham6(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned int lines[][2],int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x1 - x2;
      int dy = y1 - y2;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      writepixel(y1, x1,lines,linesaux);
      writepixel(y2, x2,lines,linesaux);
      for(x = x1-1, y = y1; x >= x2 ; x-- ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y--;
        }
        writepixel(y, x,lines,linesaux); 
      } 
  }
  void drawprocessbresenham7(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned int lines[][2],int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x1 - x2;
      int dy = y2 - y1;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      writepixel(y1, x1,lines,linesaux);
      writepixel(y2, x2,lines,linesaux);
      for(x = x1-1, y = y1; x >= x2 ; x-- ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        }
        writepixel(y, x,lines,linesaux); 
      } 
  }
  void drawprocessbresenham8(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned int lines[][2],int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y1 - y2;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      writepixel(x1, y1,lines,linesaux);
      writepixel(x2, y2,lines,linesaux);
      for(x = x1+1, y = y1; x < x2 ; x++ ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y--;
        } 
        writepixel(x, y,lines,linesaux); 
      } 
  }
  int octant(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2){
    float m = 0;
    int dx = x2 - x1;
    int dy = y2 - y1;  
    m = (double)(dy)/(double)(dx);
   
    if (m <= 1 && m >= 0)
    {
      if (x1 < x2)
      {
        return 1;
      }else{
        return 5;
      }

    }else if (m > 1)
    {
      if (y1 < y2)
      {
        return 2;
      }else{
        return 6;
      }
    }else if (m < -1)
    {
      if (y1 < y2)
      {
        return 3;
      }else{
        return 7;
      }
    }else{
      if (x2 < x1)
      {
        return 4;
      }else{
        return 8;
      }
    }
  }
void drawLinebresenham(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,unsigned int lines[][2], int& lineaux) {
      int o;
      o = octant(x1,y1,x2,y2);
      switch(o){
        case 1:
          drawprocessbresenham1(x1,y1,x2,y2,lines,lineaux);
          break;
        case 2:
          drawprocessbresenham2(y1,x1,y2,x2,lines,lineaux);
          break;
        case 3:
          drawprocessbresenham3(y1,x1,y2,x2,lines,lineaux);
          break;
        case 4:
          drawprocessbresenham4(x1,y1,x2,y2,lines,lineaux);
          break;
        case 5:
          drawprocessbresenham5(x1,y1,x2,y2,lines,lineaux);
          break;
        case 6:
          drawprocessbresenham6(y1,x1,y2,x2,lines,lineaux);
          break;
        case 7:
          drawprocessbresenham7(y1,x1,y2,x2,lines,lineaux);
          break;
        case 8:
          drawprocessbresenham8(x1,y1,x2,y2,lines,lineaux);
          break;
      }  
   }
void createtramat(double mattra[][4], double trax , double tray, double traz){
  mattra[0][0]= 1;
  mattra[0][1]= 0;
  mattra[0][2]= 0;
  mattra[0][3]= trax;
  mattra[1][0]= 0;
  mattra[1][1]= 1;
  mattra[1][2]= 0;
  mattra[1][3]= tray;
  mattra[2][0]= 0;
  mattra[2][1]= 0;
  mattra[2][2]= 1;
  mattra[2][3]= traz;
  mattra[3][0]= 0;
  mattra[3][1]= 0;
  mattra[3][2]= 0;
  mattra[3][3]= 1;
}
void createscalmat(double mattra[][4], double rotx , double roty, double rotz){
  mattra[0][0]= rotx;
  mattra[0][1]= 0;
  mattra[0][2]= 0;
  mattra[0][3]= 0;
  mattra[1][0]= 0;
  mattra[1][1]= roty;
  mattra[1][2]= 0;
  mattra[1][3]= 0;
  mattra[2][0]= 0;
  mattra[2][1]= 0;
  mattra[2][2]= rotz;
  mattra[2][3]= 0;
  mattra[3][0]= 0;
  mattra[3][1]= 0;
  mattra[3][2]= 0;
  mattra[3][3]= 1;
}

void createrotmatx(double mattra[][4], double rotx){
  mattra[0][0]= 1;
  mattra[0][1]= 0;
  mattra[0][2]= 0;
  mattra[0][3]= 0;
  mattra[1][0]= 0;
  mattra[1][1]= cos((rotx*PI)/180);
  mattra[1][2]= -sin((rotx*PI)/180);
  mattra[1][3]= 0;
  mattra[2][0]= 0;
  mattra[2][1]= sin((rotx*PI)/180);
  mattra[2][2]= cos((rotx*PI)/180);
  mattra[2][3]= 0;
  mattra[3][0]= 0;
  mattra[3][1]= 0;
  mattra[3][2]= 0;
  mattra[3][3]= 1;
}

void createrotmaty(double mattra[][4], double roty){
  mattra[0][0]= cos((roty*PI)/180);
  mattra[0][1]= 0;
  mattra[0][2]= -sin((roty*PI)/180);
  mattra[0][3]= 0;
  mattra[1][0]= 0;
  mattra[1][1]= 1;
  mattra[1][2]= 0;
  mattra[1][3]= 0;
  mattra[2][0]= sin((roty*PI)/180);
  mattra[2][1]= 0;
  mattra[2][2]= cos((roty*PI)/180);
  mattra[2][3]= 0;
  mattra[3][0]= 0;
  mattra[3][1]= 0;
  mattra[3][2]= 0;
  mattra[3][3]= 1;
}

void createrotmatz(double mattra[][4], double rotz){
  mattra[0][0]= cos((rotz*PI)/180);
  mattra[0][1]= -sin((rotz*PI)/180);
  mattra[0][2]= 0;
  mattra[0][3]= 0;
  mattra[1][0]= sin((rotz*PI)/180);
  mattra[1][1]= cos((rotz*PI)/180);
  mattra[1][2]= 0;
  mattra[1][3]= 0;
  mattra[2][0]= 0;
  mattra[2][1]= 0;
  mattra[2][2]= 1;
  mattra[2][3]= 0;
  mattra[3][0]= 0;
  mattra[3][1]= 0;
  mattra[3][2]= 0;
  mattra[3][3]= 1;
}

void createperstmat (double mattra[][4], double focal){
  mattra[0][0]= 1;
  mattra[0][1]= 0;
  mattra[0][2]= 0;
  mattra[0][3]= 0;
  mattra[1][0]= 0;
  mattra[1][1]= 1;
  mattra[1][2]= 0;
  mattra[1][3]= 0;
  mattra[2][0]= 0;
  mattra[2][1]= 0;
  mattra[2][2]= 1;
  mattra[2][3]= 0;
  mattra[3][0]= 1/focal;
  mattra[3][1]= 0;
  mattra[3][2]= 0;
  mattra[3][3]= 1;
}

void matrixmult(double mattra[][4], vect vec[3][2]){
  for (int i = 0; i < 3; ++i){
    for (int j = 0; j < 2; ++j){
      double temp[]={vec[i][j].x,vec[i][j].y,vec[i][j].z,1};
      double  res[]={0,0,0,0};
      for (int k = 0; k < 4; ++k){
        for (int l = 0; l < 4; ++l){
          res[k] += (mattra[k][l]*temp[l]);
        }
      }
      vec[i][j].x = (res[0])/res[3]; 
      vec[i][j].y = (res[1])/res[3];
      vec[i][j].z = (res[2])/res[3]; 
    }
  } 
}

void caltras(float *maxmin, float& trax,float& tray, float& traz, float& scalx, float& scaly, float& scalz ){
	float difx,dify,difz, tscx, tscy, tscz, scf;
	difx = fabs(maxmin[0]) + fabs(maxmin[1]);
	dify = fabs(maxmin[2]) + fabs(maxmin[3]);
	difz = fabs(maxmin[4]) + fabs(maxmin[5]);
	tscx = 1920/difx;
	tscy = 1080/dify;
	if(tscx < tscy){
		scf = tscx - (tscx/10);
		tray = tray + ((1080-(scf * dify))/2)/scf;
		trax = trax + ((1920-(scf * difx))/2)/scf;
	} else{
		scf = tscy - (tscy/10);
		tray = tray + ((1080-(scf * dify))/2)/scf;
		trax = trax + ((1920-(scf * difx))/2)/scf;
	}

	if (maxmin[0] < 0 ){
		trax =  trax + (fabs(maxmin[0]));
	}
	if (maxmin[2] < 0 ){
		tray =  tray + (fabs(maxmin[2]));
	}
	if (maxmin[4] < 0 ){
		traz =  traz + (fabs(maxmin[4]));
	}
	scalx = scf;
	scaly = scf;
	scalz = scf; 
}

void matrixmult4(double mattra0[][4], double mattra1[][4],double matratemp[][4]){
  for (int i = 0; i < 4; ++i){
    for (int j = 0; j < 4; ++j){
      for (int k = 0; k < 4; ++k){
        matratemp[i][j] += mattra0[i][k] * mattra1[k][j];
      }
    }
  }
}

void findheader(int& nv, int& ne, int& nf, string filename){
  char aux1[32], aux2[32], aux3[32];
  string str;
  ifstream file(filename);
  int i;
  while (getline(file, str)){
    for (i = 0; i < 32; ++i){
      aux1[i] = str[i];
    }
    for (i = 32; i < 64; ++i){
      aux2[i-32] = str[i];
    }
    for (i = 64; i < 96; ++i){
      aux3[i-64] = str[i];
    }
    nv = std::bitset<32>(aux1).to_ulong();
    ne = std::bitset<32>(aux2).to_ulong();
    nf = std::bitset<32>(aux3).to_ulong();
    break;
  }
  file.close();
}

void getvector(int e,int& v1,int& v2,int nv,string filename){
  ifstream file(filename);
  string str;
  int aux = 0 - nv,i;
  char aux1[32], aux2[32];
  while (getline(file, str)){
    if(aux == e){
      for (i = 0; i < 32; ++i){
        aux1[i] = str[i];
      }
      for (i = 32; i < 64; ++i){
        aux2[i-32] = str[i];
      }
      v1 = std::bitset<32>(aux1).to_ulong();
      v2 = std::bitset<32>(aux2).to_ulong();
      file.close();
      return;
    }
    aux++;
  }
  file.close();
}

template<typename InputIterator>
double bitstring_to_double(InputIterator begin, InputIterator end)
{
    unsigned long long x = 0;
    for (; begin != end; ++begin)
    {
        x = (x << 1) + (*begin - '0');
    }
    double d;
    memcpy(&d, &x, 8);
    return d;
}

void findemaxmin (double *maxmin ,int vn, string filename){
  double temp1[3];
  int aux = 0 ;
  string str, temp2[5] ={"0","0","0","0","0"};   
  ifstream file(filename);
  char auxi1[64], auxi2[64], auxi3[64];
  int i, j ,k;
  while (getline(file, str)){
    if (aux < vn){
      for (k = 0; k < 64; ++k){
         auxi1[k] = str[k];
      }
      for (k = 64; k < 128; ++k){
        auxi2[k - 64] = str[k];
      }
      for (k = 128; k < 192; ++k){
        auxi3[k - 128] = str[k];
      }
      temp1[0] = bitstring_to_double(auxi1 + 0, auxi1 + 64);
      temp1[1] = bitstring_to_double(auxi2 + 0, auxi2 + 64);
      temp1[2] = bitstring_to_double(auxi3 + 0, auxi3 + 64);
      if (temp1[0] < maxmin[0]){
        maxmin[0] = temp1[0];
      }
      if (temp1[0] > maxmin[1]){
        maxmin[1] = temp1[0];
      }
      if (temp1[1] < maxmin[2]){
        maxmin[2] = temp1[1];
      }
      if (temp1[1] > maxmin[3]){
        maxmin[3] = temp1[1];
      }
      if (temp1[2]< maxmin[4]){
        maxmin[4] = temp1[2];
      }
      if (temp1[2] > maxmin[5]){
        maxmin[5] = temp1[2];
      }   
    }
    else if(aux > vn){
      return;
    }
    aux++;          
  } 
  file.close();
}

void caltras(double *maxmin, double& trax,double& tray, double& traz, double& scalx, double& scaly, double& scalz ){
  double difx,dify,difz, tscx, tscy, tscz, scf;
  difx = fabs(maxmin[0]) + fabs(maxmin[1]);
  dify = fabs(maxmin[2]) + fabs(maxmin[3]);
  difz = fabs(maxmin[4]) + fabs(maxmin[5]);
  tscx = 1920/difx;
  tscy = 1080/dify;
  if(tscx < tscy){
    scf = tscx - (tscx/10);
    tray = tray + ((1080-(scf * dify))/2)/scf;
    trax = trax + ((1920-(scf * difx))/2)/scf;
  } else{
    scf = tscy - (tscy/10);
    tray = tray + ((1080-(scf * dify))/2)/scf;
    trax = trax + ((1920-(scf * difx))/2)/scf;
  }

  if (maxmin[0] < 0 ){
    trax =  trax + (fabs(maxmin[0]));
  }
  if (maxmin[2] < 0 ){
    tray =  tray + (fabs(maxmin[2]));
  }
  if (maxmin[4] < 0 ){
    traz =  traz + (fabs(maxmin[4]));
  }
  scalx = scf;
  scaly = scf;
  scalz = scf; 
}

void mezclar(unsigned int  datos[][2], unsigned int l, unsigned int m, unsigned int n){
    unsigned int n1 = m - l + 1;
    unsigned int n2 = n - m;
    unsigned int tem1[n1][2], tem2[n2][2];
    for(int i = 0; i < n1; i++){
        tem1[i][0] = datos[l + i][0];
        tem1[i][1] = datos[l + i][1];
    }
    for(int j = 0; j < n2; j++){
        tem2[j][0] = datos[m + 1 + j][0];
        tem2[j][1] = datos[m + 1 + j][1];
    }
    int a = 0,b = 0, c = l;
    while (a < n1 && b < n2)
    {
        if (tem1[a][0] <= tem2[b][0]) {
            datos[c][0] = tem1[a][0];
            datos[c][1] = tem1[a][1];
            a++;
        }else{
            datos[c][0] = tem2[b][0];
            datos[c][1] = tem2[b][1];
            b++;
        }
        c++;
    }
    while (a < n1) {
        datos[c][0] = tem1[a][0];
        datos[c][1] = tem1[a][1];
        a++;
        c++;
    }
    while (b < n2){
        datos[c][0] = tem2[b][0];
        datos[c][1] = tem2[b][1];
        b++;
        c++;
    }
}

void dividir(unsigned int datos[][2], unsigned int l, unsigned int n){
  if (l<n)
  {
    unsigned int m = l + (n - l)/2;
    dividir(datos,l,m);
    dividir(datos,m+1,n);
    mezclar(datos,l,m,n);
  }
}


void getcordinates(vect vec[3][2],int nv,string filename){
  ifstream file(filename);
  string str;
  int aux = 0 ,i,j,k;
  char auxi1[64], auxi2[64], auxi3[64];
  while (getline(file, str)){
    for (i = 0; i < 3; ++i)
    { 
      for (int j = 0; j < 2; ++j)
      {
        if(aux == vec[i][j].nvect){
          for (k = 0; k < 64; ++k){
            auxi1[k] = str[k];
          }
          
          for (k = 64; k < 128; ++k){
            auxi2[k - 64] = str[k];
          }
          for (k = 128; k < 192; ++k){
            auxi3[k - 128] = str[k];
          }
          vec[i][j].x = bitstring_to_double(auxi1 + 0, auxi1 + 64);
          vec[i][j].y = bitstring_to_double(auxi2 + 0, auxi2 + 64);
          vec[i][j].z = bitstring_to_double(auxi3 + 0, auxi3 + 64);
        }          
      }
    }
    aux++;
  }
  file.close();
}

void facemaxmin(unsigned int lines[][2], int linesaux, int& max, int& min){
  unsigned int aux = lines[linesaux][0];
  int maxlocal = 0 ,auxwhile = 0;
  int minlocal = INT_MAX;
  while(auxwhile == 0){
    if (lines[linesaux][0] ==  aux){
      if(lines[linesaux][1] > maxlocal){
        maxlocal = lines[linesaux][1];
      }
      if(lines[linesaux][1] < minlocal){
        minlocal = lines[linesaux][1];
      }
      linesaux++;
    } else {
      auxwhile = 10;
    }
    max = maxlocal;
    min = minlocal;
  }
}

int main(void){
	FHDRaster * raster = new FHDRaster();
  string filename = {"Monkey3.vlf"};
  string str;
	ifstream file(filename);
  int nv = 0, ne = 0, nf = 0, aux = 0; 
	double maxmin[5];
	maxmin[0] = INT_MAX;
	maxmin[1] = 0;
	maxmin[2] = INT_MAX;
	maxmin[3] = 0;
	maxmin[4] = INT_MAX;
	maxmin[5] = 0;
  int linesaux = 0;
	double trax = 0, tray= 0 ,traz= 0;
	double scalx = 0 , scaly = 0, scalz = 0;
	double rotx = 180;
	double roty = 0;
	double rotz = 0;
	double focal = 900;
	double mattra [4][4];
	double matscal[4][4];
	double matrotx[4][4];
	double matroty[4][4];
	double matrotz[4][4];
	double matperst[4][4];
	double matrafin[4][4] = {0};
  findheader(nv,ne,nf,filename);
  findemaxmin(maxmin,nv,filename);
  caltras(maxmin,trax,tray,traz,scalx,scaly,scalz);
  createtramat(mattra, trax, tray, traz);
  createscalmat(matscal, scalx , scaly, scalz);
  createrotmatx(matrotx,rotx);
  createrotmaty(matroty,roty);
  createrotmatz(matrotz,rotz);
  createperstmat(matperst, focal);  
	matrixmult4(mattra,matscal,matrafin);
  char auxi[3][32];
  int i;
  int e[3],v[3][2];
  vect vec[3][2];
  while (getline(file, str)) {
    if (aux > nv + ne){
      for (i = 0; i < 32; ++i){
        auxi[0][i] = str[i];
      }
      for (i = 32; i < 64; ++i){
        auxi[1][i-32] = str[i];
      }
      for (i = 64; i < 96; ++i){
        auxi[2][i-64] = str[i];
      }
      for (i = 0; i < 3; ++i)
      {
        e[i] = std::bitset<32>(auxi[i]).to_ulong();
        getvector(e[i],vec[i][0].nvect,vec[i][1].nvect,nv,filename); 
      }
      getcordinates(vec,nv,filename);
      matrixmult(matrotx,vec);
      matrixmult(matroty,vec);
      matrixmult(matrotz,vec);
      matrixmult(mattra,vec);
      matrixmult(matscal,vec);
      //matrixmult(matrafin,vec);
      /*
        for (int j = 0; j < 3; ++j)
        {
          cout << vec[0][j].x << endl;
          cout << vec[0][j].y << endl;
          cout << vec[0][j].z << endl;
          cout << "---------------------" << endl;
        }
        for (int j = 0; j < 3; ++j)
        {
          cout << vec[1][j].x << endl;
          cout << vec[1][j].y << endl;
          cout << vec[1][j].z << endl;
          cout << "---------------------" << endl;
        }
        */
      linesaux = 0;
    unsigned int lines[100000][2] = {9000};
    int auxface = 0, tempface = 5000, maxface, minface, auxfacewhile = 0;
    drawLinebresenham(vec[0][0].x, vec[0][0].y , vec[0][1].x , vec[0][1].y,lines,linesaux);
    drawLinebresenham(vec[1][0].x, vec[1][0].y , vec[1][1].x , vec[1][1].y,lines,linesaux);
    drawLinebresenham(vec[2][0].x, vec[2][0].y , vec[2][1].x , vec[2][1].y,lines,linesaux);
    dividir(lines, 0, linesaux-1);
    /*
    for (int i = 0; i < linesaux; ++i)
    {
      cout << lines[i][0] << endl;
      cout << lines[i][1] << endl;
    }
    cout << "------------------------------------------------" << endl;
    */
    int range = 255 - 1 + 1;
    int num = rand() % range + 1;
    int num1 = rand() % range + 1;
    int num2 = rand() % range + 1;
    while(auxface < linesaux){
        if(tempface != lines[auxface][0]){
          tempface = lines[auxface][0];
          facemaxmin(lines,auxface,maxface,minface);
          for (int i = minface; i <= maxface; ++i){
            raster->setPixel(tempface, i, 255, 255, 255);
          }
          /*
          cout << "////"<<tempface << endl;
          cout << "----"<<maxface << endl;
          cout << "----"<<minface << endl;
          */
        } 
      auxface++;
    }
    }
    aux++;
    
    /*
    raster->setPixel(vec[0][0].x, vec[0][1].x , 255, 255, 255);
    raster->setPixel(vec[1][0].y, vec[1][1].y , 255, 255, 255);
    raster->setPixel(vec[2][0].x, vec[2][1].x , 255, 255, 255);
    raster->setPixel(vec[0][0].y, vec[0][1].y , 255, 255, 255);
    raster->setPixel(vec[1][0].x, vec[1][1].x , 255, 255, 255);
    raster->setPixel(vec[2][0].y, vec[2][1].y , 255, 255, 255);
    */
    /*
    for (int i = 500; i < 1000; ++i)
    {
      raster->setPixel(i, i, 15, 10, 255);
    }
    */
  }
  raster->write();
  file.close();
  return 0; 
}