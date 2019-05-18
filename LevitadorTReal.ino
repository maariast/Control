
#include "TimerOne.h"

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

// Valores Nominales
float VaNom=sqrt(m*g/alpha); 
float uNom = sqrt(m*g/alpha/k);
float x1Nom = 0.25;                    //Valor de referencia
// Valores Nominales
float Va=VaNom, Van=0, VaD=0;        //Velocidad Aire  
float u=uNom,  uD=0;                 //Entrada 
float x1=0,x1n=0, x1D=-x1Nom;        //Posición        
float x2=0,x2n=0, xD=0;              //Velocidad 

//Muestreo
int n=0;
int Fs = 200;
float Delta = (float)1/Fs;
long Ts =1000000/Fs;
//long trigg=Ts/2;

//Constantes PID
  //Error  
  float e = 0;
  //Integral
  float I=0, Iant=0; 
  float ki = 4.4;
  float kib = ki*Delta;
  //Proporcional 
  float kp = 5;
  float P=0; 

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
    
    //Señal de referencia
    n+=1;
    if (n % (Ts/2)==0){
      if (x1Nom <.5){
        x1Nom = .5;
      }else
      x1Nom = .25;
    } 
    
    // Control PI
    x1D=x1-x1Nom;
    e = 0-x1D;
    P = kp*e;
    I = Iant+kib*e;   
    uD =P+I;
    u=uD+uNom;
    
    /*
    if(u>11){
      u=12;
    }else{
      u = P+I; //P+I;
    }
    */
    
    //Actualización de variables
    Iant = I; 

    // Modelo de la planta
    x1n=x1+Delta*x2;
    x2n=x2+Delta*alpha/m*(Va-x2)*(Va-x2)-Delta*g; 
    Van=Va*(1-Delta/Thao)+u*Delta*k/Thao; 

    //Variables de desviación 
    x1=x1n;
    x2=x2n;
    Va=Van;

    if (n % 5==0){
       //Serial.print(x1Nom,3);
       Serial.print('\t');
      //Serial.print(e,3);
       Serial.print('\t');
       Serial.print(x1D,3);
       Serial.print('\t');
       Serial.println(u,3);
    } 
}

//Main loop no ejecuta ninguna acción
void loop() {
}
