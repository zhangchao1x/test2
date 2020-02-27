#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include <string.h>

//test
unsigned int getRand();
unsigned int CircleLeftShift(unsigned int x,unsigned int N);
unsigned int calulY(unsigned int d0,unsigned int d1,unsigned int d2,unsigned int d3,unsigned int d4,int num,unsigned int m);
unsigned int ONZ(unsigned int x,unsigned int y,unsigned int z);
int adjust(unsigned int num);

unsigned int getRand(){
    unsigned int retNum = 0;
    retNum = rand();
    retNum <<=16;
    retNum ^= rand();
    retNum ^= CircleLeftShift(retNum,17);
    return retNum;
}

unsigned int CircleLeftShift(unsigned int x,unsigned int N)
{
    return (x << N) | (x >> (32 - N));
}

int adjust(unsigned int num){
    if(num == 0x4800009 || num == 0x4800007 || num == 0x47ffff9 || num == 0x3800009
       || num == 0x47ffff7 || num == 0x3800007 || num == 0x37ffff9 || num == 0x37ffff7){
       return 1;
    }else{
       return 0;
    }
}

unsigned int calulY(unsigned int d0,unsigned int d1,unsigned int d2,unsigned int d3,unsigned int d4,int num,unsigned int m){
  unsigned int d5 =(unsigned int)(CircleLeftShift(d1,10) + CircleLeftShift((unsigned int)((CircleLeftShift(d0,10) + (ONZ(d4,d3,CircleLeftShift(d2,10))) + m + 0x544dd124)% (unsigned int)pow(2,32)),num))% (unsigned int) pow(2,32);
  return d5;
}

unsigned int ONZ(unsigned int x,unsigned int y,unsigned int z){
      return (x|~y)^z;
}

int main()
{
      srand((unsigned int)time(NULL));
      int count = 0;
      for(int i =0 ;i < 0x40000000; i++){
      unsigned int y30 = getRand();
      y30 = y30 | (1<<22);
      y30 = y30 | (1<<19);
      unsigned int y31 = getRand();
      y31 = y31 | (1<<29);
      y31 = y31 | 1;
      unsigned int y32 = getRand();
      unsigned int y32_d = y32;
      y32 = (y32 | (1<<29))^(1<<29);
      y32 = y32 | 1;
      y32_d = y32_d | (1<<29);
      y32_d = (y32_d | 1)^1 ;
      unsigned int y33  = getRand();
      y33 = y33 | (1<<29);
      y33 = y33 | 1 ;
      unsigned int y34 = getRand();
      y34 = y34 | (1<<29);
      y34 = y34 | 1 ;
      y34 = (y34 | (1<<25))^(1<<25);
      y34 = (y34 | (1<<22))^(1<<22);

      unsigned int m = getRand();
      // compute y35,y35',y36,y36',y37,y37',y38,y38',y39,y39'.
      unsigned int y35d = calulY(y30,y31,y32,y33,y34,15,m);
      unsigned int y35_d = calulY(y30,y31,y32_d,y33,y34,15,m);
      m = getRand();
      unsigned int y36d = calulY(y31,y32,y33,y34,y35d,11,m);
      unsigned int y36_d = calulY(y31,y32_d,y33,y34,y35_d,11,m);
      m = getRand();
      unsigned int y37d = calulY(y32,y33,y34,y35d,y36d,8,m);
      unsigned int y37_d = calulY(y32_d,y33,y34,y35_d,y36_d,8,m);
      m = getRand();
      unsigned int y38d = calulY(y33,y34,y35d,y36d,y37d,6,m);
      unsigned int y38_d = calulY(y33,y34,y35_d,y36_d,y37_d,6,m);
      m = getRand();
      unsigned int y39d = calulY(y34,y35d,y36d,y37d,y38d,6,m);
      unsigned int y39_d = calulY(y34,y35_d,y36_d,y37_d,y38_d,6,m);

      if(((y35d^y35_d) == 0x2400000) && (y35d&(1<<10)) && (y35d&(1<<7))
         &&((y36d^y36_d) == 0x480)  && (y36d&(1<<25)) && (y36d&(1<<22)) && (y36d&(1<<10)) && (y36_d&(1<<7))
         &&((y37d^y37_d) == 0)&& (y37d&(1<<10)) &&(y37d&(1<<7)) && (~(y37d&(1<<6)))&& (~(y37d&(1<<9)))
         &&((y38d^y38_d) == 0x240)
         && (adjust(abs(y39d - y39_d)))
         && ((y39d&(1<<3)) == (y35d&(1<<25))>>22) && ((y39d&1) == ((y35d)&(1<<22)>>22))
         ){
            count ++;
         }
      }
        printf("%x\n",count);
}


