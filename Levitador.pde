

// Graphing sketch


// This program takes ASCII-encoded strings
// from the serial port at 9600 baud and graphs them. It expects values in the
// range 0 to 1023, followed by a newline, or newline and carriage return
// Created 19 Jan 2016
// Updated 20 Jan 2016
// by Sarath Babu
// This example code is in the public domain.

import processing.serial.*;

Serial myPort;        // The serial port
int x1=0;    // horizontal position t
int x2=0;   // horizontal position 
int x3=0;   // horizontal position 
int x4=0;   // horizontal position
int Tam=370; //Tamaño graficas
int Dist=30; //separación graficas
float inByte1=0;
float inByte2=0;
float inByte3=0;
float inByte4=0;
float inByte5=0;
float inByte6=0;
PFont F;
PFont f1;
void setup () {
  // set the window size:
  size(1200, 800);
  F = createFont("Times New Roman", 20);
  f1 = createFont("Times New Roman", 17);

  // List all the available serial ports
  // if using Processing 2.1 or later, use Serial.printArray()
  //println(Serial.list());

  //From the available ports, select the port to which your arduino is connected
  //If the connected port is the first port  then the code is Serial.list()[0]
  //Since I am using the second port the code is written as Serial.list()[1]
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[0], 2000000);

  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');  
  // set inital background:
  background(0);
  strokeWeight(3);
  //Gráfico1 error
  Graf1(0, 0, Tam, Dist, "-50", "-30", "-10", "10", "30", "50");   
  text("error(cm)", 20, 20);
  //Gráfico2 ki
  Graf(0, Tam+Dist, Tam, Dist, "0", "1.6", "3.2", "4.8", "6.4", "8");   
  text("k_i", 20, Tam+Dist+20);
  //Gráfico3 kp
  Graf(Tam+Dist, Tam+Dist, Tam, Dist, "0", "2", "4", "6", "8", "10");   
  text("k_p", Tam+Dist+20, Tam+Dist+20);
  //Gráfico4 tensión
  Graf(Tam+Dist, 0, Tam, Dist, "0", "2.4", "4.8", "7.2", "9.6", "12");   
  text("Tensión(v)", Tam+Dist+20, 20);
}

void draw () {
  //strokeWeight(4);
  // draw the line of the first sensor:
  stroke(0, 200, 0);//define color de línea
  line(x1+Dist, Tam-inByte1, x1+Dist, Tam-inByte1);
  // at the half length of the screen, go back to the beginning:
  if (x1 >= Tam-Dist) {
    x1= 0;    
    Graf1(0, 0, Tam, Dist, "0.2", "10", "20", "30", "40", "50"); 
    text("error(cm)", 20, 20);
  }
  // increment the horizontal position:
  x1++;
  //draw the line of the second sensor  
  stroke(0, 0, 200);
  line(x2+Dist, 2*Tam+Dist-inByte2, x2+Dist, 2*Tam+Dist - inByte2);
  // at the edge of the screen, go back to the beginning:
  if (x2 >= Tam-Dist) {
    x2= 0;
    Graf(0, Tam+Dist, Tam, Dist, "0", "1.6", "3.2", "4.8", "6.4", "8");   
    text("k_i", 20, Tam+Dist+20);
  }
  // increment the horizontal position:
  x2++;   
  //draw the line of the third sensor  
  stroke(0, 0, 200);
  line(x3+Tam+Dist*2, 2*Tam+Dist-inByte3, x3+Tam+Dist*2, 2*Tam+Dist - inByte3);
  // at the edge of the screen, go back to the beginning:
  if (x3 >= Tam-Dist) {
    x3= 0;
    Graf(Tam+Dist, Tam+Dist, Tam, Dist, "0", "2", "4", "6", "8", "10");   
    text("k_p", Tam+Dist+20, Tam+Dist+20);
  }
  // increment the horizontal position:
  x3++;
  //draw the line of the third sensor  
  stroke(0, 0, 200);
  line(x4+Tam+Dist*2, Tam-inByte4, x3+Tam+Dist*2, Tam-inByte4);
  // at the edge of the screen, go back to the beginning:
  if (x4 >= Tam-Dist) {
    x4= 0;
    Graf(Tam+Dist, 0, Tam, Dist, "0", "2.4", "4.8", "7.2", "9.6", "12");   
    text("Tensión(v)", Tam+Dist+20, 20);
  }
  // increment the horizontal position:
  x4++;

  fill(150);
  stroke(150);
  rect(2.8*Tam-37, Tam/3-35, 74, 4*Tam/3+70);
  rect(2.8*Tam-47, 5*Tam/3+35, 94, 10);
  fill(255);
  stroke(255);
  circle(Tam*2.8, Tam/3+inByte6, 70); 
  fill(0,200,0);
  stroke(0,200,0);
  line(2.8*Tam-37, Tam/3+inByte5,2.8*Tam+37,Tam/3+inByte5);
 }



void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    //Split the string value dot as delimiter
    float[] nums=float(split(inString, "\t"));
    //nums[0]=first sensor value
    println("First sensor value="+nums[0]);
    //nums[1]=second sensor value
    println("Second Sensor value="+nums[1]);
    // convert to an int and map to the screen height:
    inByte1 = float(inString);
    println(inByte1);
    //map the first sensor value
    inByte1 = map(nums[0], -500, 500, 0, Tam-Dist);
    //map the second sensor value
    inByte2=map(nums[1], 0, 800, 0, Tam-Dist-10);
    //map the third sensor value
    inByte3=map(nums[2], 0, 1000, 0, Tam-Dist-10);
    //map the fourth sensor value
    inByte4=map(nums[3], 0, 1200, 0, Tam-Dist-10);
    //map the sixt sensor value
    inByte5=map(nums[4], 0, 500, 0, 4*Tam/3);
    //map the sixt sensor value
    inByte6=map(nums[5], 0, 500, 0, 4*Tam/3);
  }
}

void Graf(int Refx, int Refy, int Tam, int Dist, String b, String c, String d, String e, String f, String g) {
  stroke(0);
  fill(0);
  rect(Refx, Refy, Tam+Dist, Tam+Dist);
  stroke(255);
  fill(255);
  line(Refx+Dist, Refy+Dist+10, Refx+Dist, Refy+Tam);
  line(Refx+Dist, Refy+Tam, Refx+ Tam, Refy+ Tam);
  textFont(F);
  text("t", Refx+Tam+10, Refy+Tam+10);    
  textFont(f1);
  text(b, Refx+4, Refy+Tam+10);
  text(c, Refx+4, Refy+4*Tam/5+10);
  text(d, Refx+4, Refy+3*Tam/5+10);
  text(e, Refx+4, Refy+2*Tam/5+10);
  text(f, Refx+4, Refy+Tam/5+10);
  text(g, Refx+4, Refy+Dist+10);
}

void Graf1(int Refx, int Refy, int Tam, int Dist, String b, String c, String d, String e, String f, String g) {
  stroke(0);
  fill(0);
  rect(Refx, Refy, Tam+Dist, Tam+Dist);
  stroke(255);
  fill(255);
  line(Refx+Dist, Refy+Dist+10, Refx+Dist, Refy+Tam);
  line(Refx+Dist, (Refy+Tam+Dist)/2, Refx+ Tam, Refy+(Refy+Tam+Dist)/2);
  textFont(F);
  text("t", Refx+Tam+10, (Refy+Tam+Dist)/2+10);    
  textFont(f1);
  text(b, Refx+4, Refy+Tam+10);
  text(c, Refx+4, Refy+4*Tam/5+10);
  text(d, Refx+4, Refy+3*Tam/5+10);
  text(e, Refx+4, Refy+2*Tam/5+10);
  text(f, Refx+4, Refy+Tam/5+10);
  text(g, Refx+4, Refy+Dist+10);
}
