
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

// Variables de estado

float x1=0, x1n=0;          //Posición        
float x2=0, x2n=0;          //Velocidad  
float Va=0, Van=0;          //Velocidad Aire  
float u=0;                  //Entrada

//Muestreo
int n=0;
int Fs = 200;
float Delta = (float)1/Fs;
long Ts =1000000/Fs;

//Constantes PID
  float ref = 1;
  //Integral
  float I=0, Iant=0; 
  float ki = 1;
  float kib = ki*Delta;
  //Error  
  float e = 0;
  //Proporcional 
  float kp = 2;
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
    if (n % 2500==0){
      if (ref <5){
        ref = 5;
      }else
      ref = 1;
    } 
    
    // Control PI
    e = ref-x1;
    P = kp*e;
    I = Iant+kib*e;
    u = P+I;
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
    
    
    x1=x1n;
    x2=x2n;
    Va=Van;  

    if (n % 5==0){
        Serial.print(ref,3);
        Serial.print('\t');
        //Serial.print(e,3);
        Serial.print('\t');
        Serial.println(x1,3);
        Serial.print('\t');
        //Serial.println(Va,3);
    } 
}

//Main loop no ejecuta ninguna acción
void loop() {
}
