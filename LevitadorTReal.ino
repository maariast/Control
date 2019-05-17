
#include "TimerOne.h"


// constantes del PID


float u=0;
float x1=0, x1n=0;
float x2=0, x2n=0;
float Va=0, Van=0;
int n=0;
int Fs = 200;
float D = (float)1/Fs;
long Ts =1000000/Fs; 


float alpha = 0.02356;
float g= 9.8;
float m =0.04;
float k=1;
float Thao=0.1;

float r = 1;
float I=0, Iant=0;
float kp = 2;
float ki = 1;
float kib = ki*D;
float e = 0;
float P=0;

// filtro diseñado para wp = 0.1 en frecuencia normalizada 

void setup() {
   Serial.begin(2000000);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
    }
    // timer para ajustar la interrupcion
    Timer1.initialize(Ts);        
    Timer1.attachInterrupt(control);

}




void control()
{
    n+=1;

   if (n % 2500==0){
    if (r <5){
      r =5 ;
    }
    else
      r = 1;
   } 
    // Control 
      
    
    e = r-x1;
    P = kp*e;
    I = Iant+kib*e;
    u = P+I; //P+I;
    
    Iant = I; 
        
    // planta en lazo abierto
    
    x1n = x2*D+x1; 
    x2n = x2+D*alpha/m*(Va-x2)*(Va-x2)-D*g; 
    Van = Va+D*k/Thao*u-Va*D/Thao;   
    x1=x1n;
    x2=x2n;
    Va=Van; 
 
if (n % 5==0){

Serial.print(r,3);
Serial.print('\t');
Serial.println(x1,3);
} 

}


// main loop no hace nada
void loop(){
  }
