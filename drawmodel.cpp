#include<cstring>
#include<iostream>
#include<tgmath.h>
#include<fstream>
#include<thread>
#include <climits>
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

struct vect{
  int tv;
  int nv;
  float x,y,z;
};

void createtramat(float mattra[][4], float trax , float tray, float traz){
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
void createscalmat(float mattra[][4], float rotx , float roty, float rotz){
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

void createrotmatx(float mattra[][4], float rotx){
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

void createrotmaty(float mattra[][4], float roty){
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

void createrotmatz(float mattra[][4], float rotz){
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

void createperstmat (float mattra[][4], float focal){
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


void matrixmult(float mattra[][4], vect *vec,int n){
  float temp[4];
  float  res[4];
  for (int w = 0; w < n; ++w)
  {
    float temp[]={vec[w].x,vec[w].y,vec[w].z,1};
    float  res[]={0,0,0,0};
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        res[i] += (mattra[i][j]*temp[j]);
      }
    }
    vec[w].x = (res[0])/res[3]; 
    vec[w].y = (res[1])/res[3];
    vec[w].z = (res[2])/res[3];
  }
}


void findelef(string str, string *temp){
  temp[4]="0";
    string ele = "";
    int aux= 0;
    for (auto x : str) 
    {
        if (x == ' ' )
        {
          temp[aux] = ele;
            ele = "";
            aux ++;
        }
        else {
            ele = ele + x;
        }
        temp[aux] = ele; 
    } 
}
void findeslash(string slash){
    string ele = "";
    for (auto x : slash) 
    {
        if (x == '/' )
        {
          slash = ele;
            return;
        }
        else {
            ele = ele + x;
        }
    } 
}

void findelev (vect *vec,int v0, int v1,int n){
  ifstream file1("Monkey.obj");
  string word = "";
  int b = 0;
  int aux= 0;
  string str, temp2[5] ={"0","0","0","0","0"};    
  b -= v0-1;
  while(getline(file1,str)){
    for (int i = 0; i < n; ++i)
    {
      if(vec[i].nv == b){
          aux=0;
          findelef(str, temp2);
            vec[i].x= stof(temp2[1]);
            vec[i].y= stof(temp2[2]);
            vec[i].z= stof(temp2[3]);
        }
    }
    if(v1 == b){
      file1.close();
      return;
    }
    b++;
  }
}

void findemaxmin (float *maxmin ,int v0,int v1){
  float temp1[3];
  int aux = 0 ;
 	string v = "v ", vt = "vt";
  	string str, temp2[5] ={"0","0","0","0","0"};   
  	ifstream file1("Monkey.obj");
  	while (getline(file1,str)){
      	if (aux >= v0 && aux < v1){
        	findelef(str, temp2);	
            temp1[0]= stof(temp2[1]);
            temp1[1]= stof(temp2[2]);
            temp1[2]= stof(temp2[3]);
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
    	aux ++; 	
	}
	file1.close();
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

void matrixmult4(float mattra0[][4], float mattra1[][4],float matratemp[][4]){
  for (int i = 0; i < 4; ++i){
    for (int j = 0; j < 4; ++j){
      for (int k = 0; k < 4; ++k){
        matratemp[i][j] += mattra0[i][k] * mattra1[k][j];
      }
    }
  }
}

int main(void){
	FHDRaster * raster = new FHDRaster();
	ifstream file("Monkey.obj");
	float maxmin[5];
	maxmin[0] = INT_MAX;
	maxmin[1] = 0;
	maxmin[2] = INT_MAX;
	maxmin[3] = 0;
	maxmin[4] = INT_MAX;
	maxmin[5] = 0;
	float trax = 0, tray= 0 ,traz= 0;
	float scalx = 0 , scaly = 0, scalz = 0;
	float rotx = 180;
	float roty = 0;
	float rotz = 0;
	float focal = 900;
	float mattra [4][4];
	float matscal[4][4];
	float matrotx[4][4];
	float matroty[4][4];
	float matrotz[4][4];
	float matperst[4][4];
	float matrafin[4][4] = {0};
	//matrixmult4(mattra,matrot,matrafin);
	  
	string str , v = "v ", vt = "vt",temp[5] ={"0","0","0","0","0"};
	vect vec[4];
	unsigned int v0=0 ,v1=0, aux=0,n;
	while (getline(file,str)){
	    if (!str.find(v))
	    {
	      break;
	    }
	      v0++;
	    }
	file.clear();
	file.seekg(0);
	while (getline(file,str)){
	    if (!str.find(vt)){
	    	break;
	    	}
	    v1++;
	 	}
	file.clear();
	file.seekg(0);
	findemaxmin(maxmin,v0,v1);
	/* 
	for (int i = 0; i < 6; ++i)
	{
		cout << maxmin[i] <<endl;
	}
	*/
	caltras(maxmin,trax,tray,traz,scalx,scaly,scalz);

  /*
	cout << trax << endl;
	cout << tray << endl;
	cout << traz << endl;
	cout << scalx << endl; 
	cout << scaly << endl;
	cout << scalz << endl; 
	*/
	createtramat (mattra, trax, tray, traz);
	createscalmat (matscal, scalx , scaly, scalz);
	createrotmatx (matrotx,rotx);
	createrotmaty (matroty,roty);
	createrotmatz (matrotz,rotz);
	createperstmat (matperst, focal);
  	while (getline(file, str)) {
      	if(!str.find('f')){
        //cout << str << "\n";
        findelef(str, temp);
      for (int i = 0; i < 4; ++i){
        findeslash(temp[i+1]);
        vec[i].nv= stoi(temp[i+1]);
      }
      if(vec[3].nv!=0){
          n=4;
        }
        else{
          n=3;
        }

        findelev(vec,v0,v1,n);
      
        /*
        for (int w = 0; w < 4; ++w)
        {
          cout << vec[w].nv << "\n";
          cout << vec[w].x << "\n";
          cout << vec[w].y << "\n";
          cout << vec[w].z << "\n";
        }
        */
        matrixmult(matrotx,vec,n);
        matrixmult(matroty,vec,n);
        matrixmult(matrotz,vec,n);
        matrixmult(mattra,vec,n);
        /*
        for (int w = 0; w < 4; ++w)
        {
          cout << vec[w].nv << "\n";
          cout << vec[w].x << "\n";
          cout << vec[w].y << "\n";
          cout << vec[w].z << "\n";
        }
        */
        matrixmult(matscal,vec,n);
       // matrixmult(matperst,vec,n);
        
        /* 
        for (int w = 0; w < 4; ++w)
        {
          cout << vec[w].nv << "\n";
          cout << vec[w].x << "\n";
          cout << vec[w].y << "\n";
          cout << vec[w].z << "\n";
        }

        */
        
        if(n == 4){
        	raster->drawLinebresenham(vec[0].x, vec[0].y , vec[1].x , vec[1].y , 255, 255, 255);
        	raster->drawLinebresenham(vec[1].x, vec[1].y , vec[2].x , vec[2].y , 255, 255, 255);  
          	raster->drawLinebresenham(vec[2].x, vec[2].y , vec[3].x , vec[3].y , 255, 255, 255);
        	raster->drawLinebresenham(vec[3].x, vec[3].y , vec[0].x , vec[0].y , 255, 255, 255);   
          /*
          raster->drawLinebresenhampara(vec[0].x, vec[0].y , vec[1].x , vec[1].y , 255, 255, 255,raster);
          raster->drawLinebresenhampara(vec[1].x, vec[1].y , vec[2].x , vec[2].y , 255, 255, 255,raster);  
          raster->drawLinebresenhampara(vec[2].x, vec[2].y , vec[3].x , vec[3].y , 255, 255, 255,raster);
          raster->drawLinebresenhampara(vec[3].x, vec[3].y , vec[0].x , vec[0].y , 255, 255, 255,raster);    
        */
        	
       	}
       	if(n == 3){
          	raster->drawLinebresenham(vec[0].x, vec[0].y , vec[1].x , vec[1].y , 255, 255, 255);
          	raster->drawLinebresenham(vec[1].x, vec[1].y , vec[2].x , vec[2].y , 255, 255, 255);  
       		raster->drawLinebresenham(vec[2].x, vec[2].y , vec[0].x , vec[0].y , 255, 255, 255);  
          /*
          raster->drawLinebresenhampara(vec[0].x, vec[0].y , vec[1].x , vec[1].y , 255, 255, 255,raster);
          raster->drawLinebresenhampara(vec[1].x, vec[1].y , vec[2].x , vec[2].y , 255, 255, 255,raster);  
          raster->drawLinebresenhampara(vec[2].x, vec[2].y , vec[0].x , vec[0].y , 255, 255, 255,raster);     
        */
        }
      }
    }
    /*
      for (int i = 0; i < 6; ++i)
        {
        	cout << maxmin[i] << endl;
        }
        */
    file.close();
    raster->write(); 
    return 0; 
}