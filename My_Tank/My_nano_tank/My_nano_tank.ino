//#include <TimerOne.h> // this library has to be installed

#include "SerialDataLib.hpp"

#define WHEEL "m"

//Command format {wheel speed}: (m)Lspeed,Rspeed)
SerialData serial_data(1);
String mark, data;


/////////////////////////////MOTOR CONTROL ////////////////////////////////////////
int  Lmotorspeed = 0;
int  Rmotorspeed = 0;
int  Lspeed = 0;
int  Rspeed = 0;



volatile int state = LOW;
long LED_count = 0;


void setup()
{ 
  
  Serial.begin(115200);
  serial_data.setCommand(WHEEL);

  pinMode(13, OUTPUT);
  
  
}
void loop()
{ 
    
  if(Serial.available()){
    if(serial_data.ReadData(Serial.read(), mark, data)){
      if(mark == WHEEL){
        //Serial.println("<WHEEL>received>");
        Lspeed = serial_data.StringToInt(data, 0);
        Rspeed = serial_data.StringToInt(data, 1);
      }
    }
  }

  Speed_cal();    
  
  
  LED_count++;
  if(LED_count >= 25000){
    state=~state;
    digitalWrite(13, state); //blink every second
    LED_count = 0;
/*         Serial.print("m ");
        Serial.print(Rspeed);
        Serial.print(",");
        Serial.print(Lspeed);
        Serial.print("\n"); */
  }
       
}

void Speed_cal(){
  
  Rmotorspeed = Rspeed;
  Lmotorspeed = Lspeed;  
  
  if(Rmotorspeed>=0 && Lmotorspeed>=0 ){
    analogWrite(6, 0 );
    analogWrite(9, Rmotorspeed );
    analogWrite(10, 0 );
    analogWrite(11, Lmotorspeed );
  }
  else if(Rmotorspeed>=0 && Lmotorspeed<=0){
    Lmotorspeed=-Lmotorspeed;
    analogWrite(6, 0 );
    analogWrite(9, Rmotorspeed );
    analogWrite(10, Lmotorspeed );
    analogWrite(11, 0 );
  }  
  else if(Rmotorspeed<=0 && Lmotorspeed>=0){
    Rmotorspeed=-Rmotorspeed;
    analogWrite(6, Rmotorspeed );
    analogWrite(9, 0 );
    analogWrite(10, 0 );
    analogWrite(11, Lmotorspeed );
  }
  else if(Rmotorspeed<=0 && Lmotorspeed<=0){
    Rmotorspeed=-Rmotorspeed;
    Lmotorspeed=-Lmotorspeed;
    analogWrite(6, Rmotorspeed );
    analogWrite(9, 0 );
    analogWrite(10, Lmotorspeed );
    analogWrite(11, 0 );
  }
  else{
    analogWrite(6, 0 );
    analogWrite(9, 0 );
    analogWrite(10,0 );
    analogWrite(11, 0 );
  }   

}



















