#include<cstring>
#include<iostream>
#include<tgmath.h>
#include<fstream>
#include<thread>
#include <climits>
#include <bitset>
#include <cfloat>
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
};

struct vect{
  int nvect;
  double x,y,z;
};

struct list{
  int lines2[10000][2] = {0};
  double z[10000] = {0};
};

void writepixel(unsigned int x, unsigned int y,double z,  list& lines, int& lineaux){
  lines.lines2[lineaux][0] = x;
  lines.lines2[lineaux][1] = y;
  lines.z[lineaux] = z;
  lineaux++;
}

void drawprocessbresenham1(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2, double z1,  double z2,  list& lines,int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y2 - y1;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      double auxz = z1;
      int xdif;
      double deltaz;
      if (x2-x1 == 0 || x1-x2 == 0){
        deltaz = 0;
      }else{
        if ((int )z1 == (int )z2){
          deltaz = 0;
        } else{
          deltaz = (z2-z1) / ((double) x2 - (double) x1); 
        }  
      }
      //cout << "111111111111111111111111111111111111111111111111111111111111111111111111111" << endl;
      //cout << z1 << endl;
      //cout << deltaz << endl;
      writepixel(x1, y1,z1,lines,linesaux);
      writepixel(x2, y2,z2,lines,linesaux);
      for(x = x1+1, y = y1; x < x2 ; x++ ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        } 
        auxz = auxz + deltaz;
        //cout << auxz << endl; 
        writepixel(x, y,auxz,lines,linesaux); 
      }
      //cout << z2 << endl;
      //cout << "---------------------------------------------------------" << endl;
  }
  void drawprocessbresenham2(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2, double z1,  double z2, list& lines,int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y2 - y1;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      double auxz = z1;
      double deltaz;
      int xdif;
      if (x2-x1 == 0 || x1-x2 == 0){
        deltaz = 0;
      }else{
        if ((int )z1 == (int )z2){
          deltaz = 0;
        } else{
          deltaz = (z2-z1) / ((double) x2 - (double) x1); 
        }  
      }
      //cout << "222222222222222222222222222222222222222222222222222222222222222222222" << endl;
      //cout << z1 << endl;
      //cout << deltaz << endl;
      writepixel(y1, x1,z1,lines,linesaux);
      writepixel(y2, x2,z2,lines,linesaux);
      for(x = x1+1, y = y1; x < x2 ; x++ ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        }
        auxz = auxz + deltaz; 
        //cout << auxz << endl;
        writepixel(y, x,auxz,lines,linesaux); 
      } 
      //cout << z2 << endl;
      //cout << "---------------------------------------------------------" << endl;
  }
  void drawprocessbresenham3(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2, double z1,  double z2,  list& lines,int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y1 - y2;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      double auxz = z1;
      double deltaz;
      int xdif;
      if (x2-x1 == 0 || x1-x2 == 0){
        deltaz = 0;
      }else{
        if ((int )z1 == (int )z2){
          deltaz = 0;
        } else{
          deltaz = (z2-z1) / ((double) x2 - (double) x1); 
        }  
      }
      //cout << "333333333333333333333333333333333333333333333333333333333333333333333" << endl;
      //cout << z1 << endl;
      //cout << deltaz << endl;
      writepixel(y1, x1,z1,lines,linesaux);
      writepixel(y2, x2,z2,lines,linesaux);
      for(x = x2-1, y = y2; x > x1 ; x-- ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        } 
        auxz = auxz + deltaz;
        //cout << auxz << endl;  
        writepixel(y, x,auxz,lines,linesaux); 
      }
      //cout << z2 << endl;
      //cout << "---------------------------------------------------------" << endl;
  }
  void drawprocessbresenham4(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2, double z1,  double z2,  list& lines,int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x1 - x2;
      int dy = y2 - y1;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      double auxz = z1;
      double deltaz;
      int xdif;
      if (x2-x1 == 0 || x1-x2 == 0){
        deltaz = 0;
      }else{
        if ((int )z1 == (int )z2){
          deltaz = 0;
        } else{
          deltaz = (z2-z1) / ((double) x1 - (double) x2); 
        }  
      }
      //cout << "4444444444444444444444444444444444444444444444444444444444444444444444" << endl;
      //cout << z1 << endl;
      //cout << deltaz << endl;
      writepixel(x1, y1,z1,lines,linesaux);
      writepixel(x2, y2,z2,lines,linesaux);
      for(x = x1-1, y = y1; x > x2 ; x-- ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        } 
        auxz = auxz + deltaz;
        //cout << auxz << endl;  
        writepixel(x, y,auxz,lines,linesaux); 
      } 
      //cout << z2 << endl;
      //cout << "---------------------------------------------------------" << endl;
  }
  void drawprocessbresenham5(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2, double z1,  double z2,  list& lines,int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x1 - x2;
      int dy = y1 - y2;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      double auxz = z1;
      double deltaz;
      int xdif;
      if (x2-x1 == 0 || x1-x2 == 0){
        deltaz = 0;
      }else{
        if ((int )z1 == (int )z2){
          deltaz = 0;
        } else{
          deltaz = (z2-z1) / ((double) x1 - (double) x2); 
        }  
      }
      //cout << "55555555555555555555555555555555555555555555555555555555555555555" << endl;
      //cout << z1 << endl;
      //cout << deltaz << endl;
      writepixel(x1, y1,z1,lines,linesaux);
      writepixel(x2, y2,z2,lines,linesaux);
      for(x = x2+1, y = y2; x < x1 ; x++ ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        } 
        auxz = auxz + deltaz;
        //cout << auxz << endl;  
        writepixel(x, y,auxz,lines,linesaux); 
      } 
      //cout << z2 << endl;
      //cout << "---------------------------------------------------------" << endl;
  }
  void drawprocessbresenham6(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2, double z1,  double z2, list& lines,int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x1 - x2;
      int dy = y1 - y2;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      double auxz = z1;
      double deltaz;
      int xdif;
      if (x2-x1 == 0 || x1-x2 == 0){
        deltaz = 0;
      }else{
        if ((int )z1 == (int )z2){
          deltaz = 0;
        } else{
          deltaz = (z2-z1) / ((double) x1 - (double) x2); 
        }  
      }
      //cout << "6666666666666666666666666666666666666666666666666666666666666666666" << endl;
      //cout << z1 << endl;
      //cout << deltaz << endl; 
      writepixel(y1, x1,z1,lines,linesaux);
      writepixel(y2, x2,z2,lines,linesaux);
      for(x = x1-1, y = y1; x > x2 ; x-- ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y--;
        }
        auxz = auxz + deltaz;
        //cout << auxz << endl;  
        writepixel(y, x,auxz,lines,linesaux); 
      } 
      //cout << z2 << endl;
      //cout << "---------------------------------------------------------" << endl;
  }
  void drawprocessbresenham7(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2, double z1,  double z2, list& lines,int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x1 - x2;
      int dy = y2 - y1;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      double auxz = z1;
      double deltaz;
      int xdif;
      if (x2-x1 == 0 || x1-x2 == 0){
        deltaz = 0;
      }else{
        if ((int )z1 == (int )z2){
          deltaz = 0;
        } else{
          deltaz = (z2-z1) / ((double) x1 - (double) x2); 
        }  
      }
      //cout << "777777777777777777777777777777777777777777777777777777777777777777777777777" << endl;
      //cout << deltaz << endl; 
      //cout << z1 << endl;
      writepixel(y1, x1,z1,lines,linesaux);
      writepixel(y2, x2,z2,lines,linesaux);
      for(x = x1-1, y = y1; x > x2 ; x-- ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y++;
        }
        auxz = auxz + deltaz;
        //cout << auxz << endl;  
        writepixel(y, x,auxz,lines,linesaux); 
      } 
      //cout << z2 << endl;
      //cout << "---------------------------------------------------------" << endl;
  }
  void drawprocessbresenham8(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2, double z1,  double z2, list& lines,int& linesaux) {
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y1 - y2;  
      int p = 2*dy-dx;
      int updateUp = 2*dy - 2*dx;
      int updateRight = 2*dy;
      double auxz = z1;
      double deltaz;
      int xdif;
      if (x2-x1 == 0 || x1-x2 == 0){
        deltaz = 0;
      }else{
        if ((int )z1 == (int )z2){
          deltaz = 0;
        } else{
          deltaz = (z2-z1) / ((double) x2 - (double) x1); 
        }  
      }
      //cout << "8888888888888888888888888888888888888888888888888888888888888888" << endl;
      //cout << z1 << endl;
      //cout << deltaz << endl;
      writepixel(x1, y1,z1,lines,linesaux);
      writepixel(x2, y2,z2,lines,linesaux);
      for(x = x1+1, y = y1; x < x2 ; x++ ) {
        if(p <= 0) {
          p += updateRight;
        } else {
          p += updateUp;
          y--;
        } 
        auxz = auxz + deltaz;
        //cout << auxz << endl;  
        writepixel(x, y,auxz,lines,linesaux); 
      }
      //cout << z2 << endl;
      //cout << "---------------------------------------------------------" << endl;
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
void drawLinebresenham(unsigned int x1, unsigned int y1 , unsigned int x2, unsigned int y2,  double z1, double z2,  list& lines, int& lineaux) {
      int o;
      o = octant(x1,y1,x2,y2);
      /*
      cout << "1x1 "<< x1 << endl;
      cout << "1x2 "<< x2 << endl;
      cout << "1y1 "<< y1 << endl;
      cout << "1y2 "<< y2 << endl;
      cout << "1z1 "<< z1 << endl;
      cout << "1z2 "<< z2 << endl;
      */
      switch(o){
        case 1:
          drawprocessbresenham1(x1,y1,x2,y2,z1,z2,lines,lineaux);
          break;
        case 2:
          drawprocessbresenham2(y1,x1,y2,x2,z1,z2,lines,lineaux);
          break;
        case 3:
          drawprocessbresenham3(y1,x1,y2,x2,z1,z2,lines,lineaux);
          break;
        case 4:
          drawprocessbresenham4(x1,y1,x2,y2,z1,z2,lines,lineaux);
          break;
        case 5:
          drawprocessbresenham5(x1,y1,x2,y2,z1,z2,lines,lineaux);
          break;
        case 6:
          drawprocessbresenham6(y1,x1,y2,x2,z1,z2,lines,lineaux);
          break;
        case 7:
          drawprocessbresenham7(y1,x1,y2,x2,z1,z2,lines,lineaux);
          break;
        case 8:
          drawprocessbresenham8(x1,y1,x2,y2,z1,z2,lines,lineaux);
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

void findemaxmin (double maxmin[6] ,int vn, string filename){
  double temp1[3];
  int aux = 0 ;
  string str; 
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

void caltras(double tem[6], double& trax,double& tray, double& traz, double& scalx, double& scaly, double& scalz ){
  double difx,dify,difz, tscx, tscy, tscz, scf;
  double maxmin[6];
  for (int i = 0; i < 6; ++i){
    maxmin[i] = tem[i];
  }
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

void mezclar(list& datos,  int l,  int m,  int n){
     int n1 = m - l + 1;
     int n2 = n - m;
     int tem1[n1][2], tem2[n2][2];
    double d1[n1], d2 [n2];
    for(int i = 0; i < n1; i++){
        tem1[i][0] = datos.lines2[l + i][0];
        tem1[i][1] = datos.lines2[l + i][1];
        d1[i] = datos.z[l + i];
    }
    for(int j = 0; j < n2; j++){
        tem2[j][0] = datos.lines2[m + 1 + j][0];
        tem2[j][1] = datos.lines2[m + 1 + j][1];
        d2[j] = datos.z[m + 1 + j];
    }
    int a = 0,b = 0, c = l;
    while (a < n1 && b < n2)
    {
        if (tem1[a][0] <= tem2[b][0]) {
            datos.lines2[c][0] = tem1[a][0];
            datos.lines2[c][1] = tem1[a][1];
            datos.z[c] = d1[a];
            a++;
        }else{
            datos.lines2[c][0] = tem2[b][0];
            datos.lines2[c][1] = tem2[b][1];
            datos.z[c] = d2[b];
            b++;
        }
        c++;
    }
    while (a < n1) {
        datos.lines2[c][0] = tem1[a][0];
        datos.lines2[c][1] = tem1[a][1];
        datos.z[c] = d1[a];
        a++;
        c++;
    }
    while (b < n2){
        datos.lines2[c][0] = tem2[b][0];
        datos.lines2[c][1] = tem2[b][1];
        datos.z[c] = d2[b];
        b++;
        c++;
    }
}

void dividir(list& datos,int l, int n){
  if (l<n)
  {
    int m = l + (n - l)/2;
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

void facemaxmin(list& lines, int linesaux, int& max, int& min,double& zmax,double& zmin){
  int i = linesaux;
  int aux = lines.lines2[i][0];
  int maxlocal = -INT_MAX, minlocal = INT_MAX;
  double zmaxlocal = -DBL_MAX , zminlocal = DBL_MAX;
  while(aux == lines.lines2[i][0]){
    if (lines.lines2[i][1] > maxlocal){
      maxlocal = lines.lines2[i][1];
      zmaxlocal = lines.z[i];
    }
    if (lines.lines2[i][1] < minlocal)
    {
      minlocal = lines.lines2[i][1];
      zminlocal = lines.z[i];
    }
    i++;
  }
  max = maxlocal;
  min = minlocal;
  zmax = zmaxlocal;
  zmin = zminlocal;
}

int main(void){
  FHDRaster * raster = new FHDRaster();
  string filename = {"Monkey5.vlf"};
  string str;
  ifstream file(filename);
  int nv = 0, ne = 0, nf = 0, aux = 0; 
  double maxmin[6];
  maxmin[0] = DBL_MAX;
  maxmin[1] = 0;
  maxmin[2] = DBL_MAX;
  maxmin[3] = 0;
  maxmin[4] = DBL_MAX;
  maxmin[5] = 0;
  int linesaux = 0;
  double trax = 10, tray= 5.75 ,traz= 10;
  double scalx = 95 , scaly = 95, scalz = 95;
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
  double **zbuffer;
  zbuffer = (double**)malloc(1920*sizeof(double*));
  for (int i = 0; i < 1920; ++i){
    zbuffer[i] = (double*)malloc(1080*sizeof(double));
  }
  for (int i = 0; i < 1920; ++i){
    for (int j = 0; j < 1080; ++j){
      zbuffer[i][j] = DBL_MAX;
    }
  }
  findheader(nv,ne,nf,filename);
  findemaxmin(maxmin,nv,filename);
  //caltras(maxmin,trax,tray,traz,scalx,scaly,scalz);
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
          //cout << "1" << vec[0][j].x << endl;
          //cout << "1" << vec[0][j].y << endl;
          cout << "1" << vec[0][j].z << endl;
          cout << "1" << "---------------------" << endl;
        }
        for (int j = 0; j < 3; ++j)
        {
          //cout << "1" << vec[1][j].x << endl;
          //cout << "1" << vec[1][j].y << endl;
          cout << "1" << vec[1][j].z << endl;
          cout << "---------------------" << endl;
        }
        */
      linesaux = 0;
      list lines;
      
      drawLinebresenham(vec[0][0].x, vec[0][0].y , vec[0][1].x , vec[0][1].y, vec[0][0].z , vec[0][1].z , lines, linesaux);
      drawLinebresenham(vec[1][0].x, vec[1][0].y , vec[1][1].x , vec[1][1].y, vec[1][0].z , vec[1][1].z , lines, linesaux);
      drawLinebresenham(vec[2][0].x, vec[2][0].y , vec[2][1].x , vec[2][1].y, vec[2][0].z , vec[2][1].z , lines, linesaux);
      dividir(lines, 0, linesaux-1);
      /*
      for (int i = 0; i < linesaux; ++i){
          cout << "x" <<lines.lines2[i][0] ;
          cout << "  y" <<lines.lines2[i][1] << endl;
          //cout << "z" <<lines.z[i] << endl;
      }
      cout << "------------------------------------------------" << endl; 
      */
      
      int range = 255 - 1 + 1;
      int num = rand() % range + 1;
      int num1 = rand() % range + 1;
      int num2 = rand() % range + 1;
      /*
      for (int i = 0; i < linesaux; ++i){
        unsigned int x = lines.lines2[i][0]; 
        unsigned int y = lines.lines2[i][1];
        //cout << x << endl;
        //cout << y << endl;
        raster->setPixel(x,y,255, 255, 255);
      }
      */
      int auxface = 0, tempface = 100000000, maxface, minface, auxfacewhile = 0;
      double zmax, zmin,daux,zaux;

      for (int i = 0; i < linesaux; ++i){
        //if (tempface != lines.lines2[i][0]){
          tempface = lines.lines2[i][0];
          facemaxmin(lines,i,maxface,minface,zmax,zmin);
          if (maxface - minface == 0 || zmax == zmin){
            daux = 0;
            zaux = zmin;
          } else {
            zaux = zmin;
            daux = (zmax - zmin)/((double)maxface - (double)minface);
          }
          for (int j = minface; j <= maxface; ++j){
            if (zaux < zbuffer[tempface][j])
            {
              zbuffer[tempface][j] = zaux;
              raster->setPixel((unsigned int)tempface,(unsigned int) j ,255,num1,num2);
            }
            zaux = zaux + daux;            
          }
        }
        //unsigned int x = lines.lines2[i][0]; 
        //unsigned int y = lines.lines2[i][1];
      //}       
    }
    aux++;    
  }
  raster->write();
  file.close();
  return 0; 
}