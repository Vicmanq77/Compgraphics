#include<cstring>
#include<iostream>
#include<tgmath.h>
#include<thread>
using namespace std;

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
  void drawLinenaive(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2, unsigned char r,unsigned char g,unsigned char b){
    double m = (double)(y2-y1)/(double)(x2-x1);
    double be = (double)y1 - (m*x1) ;
    unsigned int x = 0;
    unsigned int y = 0;
    setPixel(x1, y1, r, g, b);
    setPixel(x2, y2, r, g, b);
    y = m*x1 + be;
    for( x=x1+1 ; x<x2 ; x++){
      y = m*x + be; 
      setPixel(x, y, r, g, b);
    } 
  }
  void drawLineDDA(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2, unsigned char r,unsigned char g,unsigned char b){
    double m = (double)(y2-y1)/(double)(x2-x1);
    double be = (double)y1 - (m*x1) ;
    unsigned int x = 0;
    unsigned int y = 0;
    setPixel(x1, y1, r, g, b);
    setPixel(x2, y2, r, g, b);
    y = m*x1 + be;
    for( x=x1+1 ; x<x2 ; x++){
      y = y + (unsigned int)m; 
      setPixel(x, y, r, g, b);
    } 
  }
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
};

int main(void) {
  FHDRaster * raster = new FHDRaster();
  /*
  raster->drawLinebresenham(600, 600 , 600 , 1000 , 255, 255, 255);
  raster->drawLinebresenham(600, 1000 , 1000 , 1000 , 255, 255, 255);
 raster->drawLinebresenham(1000, 1000 , 1000 , 600 , 255, 255, 255);
  raster->drawLinebresenham(600, 600 , 1000 , 600 , 255, 255, 255);
  */
  raster->drawLinebresenhampara(960, 520 , 480 , 675 , 255, 255, 255,raster);
  raster->drawLinebresenhampara(960, 520 , 720 , 810 , 255, 255, 255,raster);
  raster->drawLinebresenhampara(960, 520 , 1200 , 810 , 255, 255, 255,raster);
  raster->drawLinebresenhampara(960, 520 , 1440 , 675 , 255, 255, 255,raster);
  
  raster->write();

  return 0;
}