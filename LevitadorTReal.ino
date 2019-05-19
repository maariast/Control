
#include "TimerOne.h"

// Puertos

int PtoRef=0;
int PtoInt=1;
int PtoProp=2;

//Muestreo
int n=0;
int Fs = 200;
float Delta = (float)1/Fs;
long Ts =1000000/Fs;

//Constantes PID
  //Error   
  float e = 0;
  //Integral
  float I=0, Iant=0; 
  float ki=1;
  float kib = ki*Delta;
  //Proporcional
  float kp=1; 
  float P=0; 
  
// Constantes físicas

float g=9.8;                 //kg*m/s^2
float Rho=1.2;               //kg/m^3
float A=0.00196;             //para r=0.025m
float Cd=20;                 //Coeficiente de Arrastre
float m=0.04;                //masa=40g
float alpha=0.5*Cd*Rho*A; 

// Constantes Ventilador
float k=1;
float Thao=0.1;

// Valores de saturación.

float uLimSup=12;
float uLimInf=0;
float yLimSup=0.5;
float yLimInf=0;

// Valores Nominales
float VaNom=sqrt(m*g/alpha); 
float uNom = sqrt(m*g/alpha/k);
float x1Nom=0;

// Variables sistema
float Va=VaNom, Van=0, VaD=0;        //Velocidad Aire  
float u=uNom,  uD=0;                 //Entrada 
float x1=0,x1n=0, x1D=-x1Nom;        //Posición        
float x2=0,x2n=0, xD=0;              //Velocidad 

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
   
    //Señal de referencia 0 a 0.5m
     x1Nom=analogRead(PtoRef);
     x1Nom=x1Nom/1023*.5;

     //Señal Proporcional   0 a 10
     kp=analogRead(PtoProp);
     kp=kp/1023*10;

     //Señal Integral   0 a 8
     ki=analogRead(PtoInt);
     ki=ki/1023*8;
       
    // Control PI
    x1D=x1-x1Nom;
    e = 0-x1D;
    P = kp*e;
    I = Iant+kib*e;   
    uD =P+I;
    Iant = I; 
    
    //Valores de saturación    
    if(uD>(uLimSup-uNom)){
       uD=uLimSup-uNom;
    }
    if (uD<(uLimInf-uNom)){
       uD=uLimInf-uNom;
    } 
    u=uD+uNom;
    
    // Modelo de la planta
    x1n=x1+Delta*x2;
    x2n=x2+Delta*alpha/m*(Va-x2)*(Va-x2)-Delta*g; 
    Van=Va*(1-Delta/Thao)+u*Delta*k/Thao; 

    //Límites de desplazamiento
    if(x1n>yLimSup){
      x1n=yLimSup;
    }
    if(x1n<yLimInf){
      x1n=yLimInf;
    }
    //actualización de variables
    x1=x1n;
    x2=x2n;
    Va=Van;


   // if (n % 5==0){  
       Serial.print(e*1000);
       Serial.print('\t');  
       Serial.print(ki*100);       
       Serial.print('\t');       
       Serial.print(kp*100);
       Serial.print('\t');
       Serial.print(u*100); 
       Serial.print('\t');      
       Serial.print(x1Nom*1000);
       Serial.print('\t');
       Serial.print(x1*1000);
       Serial.print("\n");
    //} 
}

//Main loop no ejecuta ninguna acción
void loop() {
}
