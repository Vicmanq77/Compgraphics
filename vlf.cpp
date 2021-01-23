#include<cstring>
#include<iostream>
#include<tgmath.h>
#include<fstream>
#include <bitset>
#include <string>

using namespace std;

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

void getheader(unsigned int& n0,unsigned int& n1,unsigned int& nv,unsigned int& ne,unsigned int& nf,string fileo){
  ifstream file(fileo);
  string str , v = "v ", vt = "vt",temp[5] ={"0","0","0","0","0"};
  int vec[4];
  while (getline(file,str)){
      if (!str.find(v))
      {
        break;
      }
      n0++;
    }
  file.clear();
  file.seekg(0);
  nv -= n0;
  while (getline(file,str)){
      if (!str.find(vt))
      {
        break;
      }
      nv++;
      n1++;
    }
  file.clear();
  file.seekg(0);
  while (getline(file, str)) {
      if(!str.find('f')){
        findelef(str, temp);
      for (int i = 0; i < 4; ++i){
        findeslash(temp[i+1]);
        vec[i]= stoi(temp[i+1]);
      }    
      if(vec[3]!=0){
          ne += 5;
          nf += 2;
        }
        else{
          ne += 3;
          nf += 1;
        }       
      }
    }
    file.close();
}

union udouble {
  double d;
  uint64_t u;
};

void writenv(unsigned int nv,string fileo,ofstream& MyFile){
  ifstream file(fileo);
  string str , v = "v ", vt = "vt",temp[5] ={"0","0","0","0","0"};
  double temp2[3];
  udouble a,b,c;
  while (getline(file,str)){
    if (!str.find(v)){
      findelef(str, temp);
      temp2[0] = stod(temp[1]);
      temp2[1] = stod(temp[2]);
      temp2[2] = stod(temp[3]);
      a.d = temp2[0];
      b.d = temp2[1];
      c.d = temp2[2];
      MyFile << bitset<64>(a.u);
      MyFile << bitset<64>(b.u);
      MyFile << bitset<64>(c.u) << endl;
    } else if (!str.find(vt)){
        break;
    }
  }
  file.close();
}

void writeheader(unsigned int nv, unsigned int ne, unsigned int nf, ofstream& MyFile){
  MyFile << bitset<32>(nv);
  MyFile << bitset<32>(ne);
  MyFile << bitset<32>(nf) << endl;
}

void finde(unsigned int& ne,unsigned int nv,int e1,int e2,ofstream& MyFile,string filev){
  string temp1 = to_string(e1);
  string temp2 = to_string(e2);
  string str;
  string tempf,tempf1,tempf2;
  int a;
  char aux1[32], aux2[32];
  int aux = 0;
  int comp,ind;
  ifstream file(filev);
  if (e1 < e2){
    ind = 0;
    tempf = temp1 + temp2;
  }else{
    ind = 1;
    tempf = temp2 + temp1;
  }
  while (getline(file, str)){
    a = str.length();
    if(a == 64){
      for (int i = 0; i < 32; ++i){
        aux1[i] = str[i];
      }
      for (int i = 32; i < 64; ++i){
        aux2[i-32] = str[i];
      }
      tempf1 = to_string(std::bitset<32>(aux1).to_ulong());
      tempf2 = to_string(std::bitset<32>(aux2).to_ulong());
      str = tempf1 + tempf2;
    }
    
    if(aux >= nv){  
      comp = str.compare(tempf);
      if (comp == 0){
        return;
      }
    }
    aux++;
  }
  if (ind == 1){
    MyFile << bitset<32>(e2);
    MyFile << bitset<32>(e1)<< endl;
    ne++;
  }else if(ind == 0){
    MyFile << bitset<32>(e1);
    MyFile << bitset<32>(e2)<< endl;
    ne++;
  }
  file.close();
}

void writene(unsigned int& ne,unsigned int nv,string fileo,string filev,ofstream& MyFile){
  ifstream file(fileo);
  string str ,temp[5] ={"0","0","0","0","0"};
  int vec[4];
  while (getline(file, str)) {
      if(!str.find('f')){
        findelef(str, temp);
      for (int i = 0; i < 4; ++i){
        findeslash(temp[i+1]);
        vec[i]= stoi(temp[i+1]);
      }    
      if(vec[3]!=0){
        finde(ne,nv,vec[0],vec[1],MyFile,filev);
        finde(ne,nv,vec[1],vec[2],MyFile,filev);
        finde(ne,nv,vec[2],vec[3],MyFile,filev);
        finde(ne,nv,vec[3],vec[0],MyFile,filev);
        finde(ne,nv,vec[0],vec[2],MyFile,filev);
      }else{
        finde(ne,nv,vec[0],vec[1],MyFile,filev);
        finde(ne,nv,vec[1],vec[2],MyFile,filev);
        finde(ne,nv,vec[2],vec[0],MyFile,filev);
      }       
    }
  }
  file.close();
}

void finde2(unsigned int nv,int e1,int e2,ofstream& MyFile,string filev){
  string temp1 = to_string(e1);
  string temp2 = to_string(e2);
  string str;
  string tempf,tempf1,tempf2;
  int a;
  char aux1[32], aux2[32];
  int aux = 0;
  int comp,ind;
  ifstream file(filev);
  if (e1 < e2){
    ind = 0;
    tempf = temp1 + temp2;
  }else{
    ind = 1;
    tempf = temp2 + temp1;
  }
  while (getline(file, str)){
    a = str.length();
    if(a == 64){
      for (int i = 0; i < 32; ++i){
        aux1[i] = str[i];
      }
      for (int i = 32; i < 64; ++i){
        aux2[i-32] = str[i];
      }
      tempf1 = to_string(std::bitset<32>(aux1).to_ulong());
      tempf2 = to_string(std::bitset<32>(aux2).to_ulong());
      str = tempf1 + tempf2;
    }
    if(aux >= nv){  
      comp = str.compare(tempf);
      if (comp == 0){
        MyFile << bitset<32>(aux-nv);
        return;
      }
    }
    aux++;
  }
  file.close();
}

void writeheader1(unsigned int nv, unsigned int ne, unsigned int nf, ofstream& MyFile){
  MyFile << bitset<32>(nv);
  MyFile << bitset<32>(ne);
  MyFile << bitset<32>(nf) << endl;
}


void writenf(unsigned int nv,string fileo,string filev,ofstream& MyFile){
  ifstream file(fileo);
  string str ,temp[5] ={"0","0","0","0","0"};
  int vec[4],aux = 1;
  while (getline(file, str)) {
      if(!str.find('f')){
        findelef(str, temp);
      for (int i = 0; i < 4; ++i){
        findeslash(temp[i+1]);
        vec[i]= stoi(temp[i+1]);
      }    
      if(vec[3]!=0){
        finde2(nv,vec[0],vec[1],MyFile,filev);
        finde2(nv,vec[1],vec[2],MyFile,filev);
        finde2(nv,vec[0],vec[2],MyFile,filev);
        MyFile << endl;
        finde2(nv,vec[2],vec[3],MyFile,filev);
        finde2(nv,vec[3],vec[0],MyFile,filev);
        finde2(nv,vec[0],vec[2],MyFile,filev);
        MyFile << endl;
      }else{
        finde2(nv,vec[0],vec[1],MyFile,filev);
        finde2(nv,vec[1],vec[2],MyFile,filev);
        finde2(nv,vec[2],vec[0],MyFile,filev);
        MyFile << endl;
      }       
    }
  }
  file.close();
}

int main(void){
  string filev = {"Monkey5.vlf"};
  string fileo = {"Monkey.obj"};
  ofstream MyFile(filev);
  unsigned int n0 = 0, n1 = 0 , nv = 0,ne = 0, nf = 0;
  getheader(n0,n1,nv,ne,nf,fileo);
  writeheader(nv,ne,nf,MyFile);
  writenv(nv,fileo,MyFile);
  ne = 0;
  writene(ne,nv,fileo,filev,MyFile);
  writenf(nv,fileo,filev,MyFile);
  MyFile.clear();
  MyFile.seekp(0, ios::beg);
  writeheader1(nv,ne,nf,MyFile);
  MyFile.close();
}