
#include <EthernetUdp.h>

#include <aJSON.h>
#include <IoTkit.h>

//Sensors
//Motion Sensor
int Motion = 2;
int Motion_Light = 3;

//Availability Status Light
int Available_Light = 8;

//Light Sensor
int Light = A2;
int Light_Light = 7;


IoTkit iotkit;

int count = 0;

bool flagSent_1 = false;
bool flagSent_0 = false;

void setup() {

  pinMode(Motion, INPUT);
  pinMode(Light, INPUT);

  pinMode(Motion_Light, OUTPUT);
  pinMode(Available_Light, OUTPUT);
  pinMode(Light_Light, OUTPUT);
  Serial.begin(9600);
  iotkit.begin();
}

  void loop() {

  int motionValue = digitalRead(Motion);
  if (motionValue)
  {
      digitalWrite(Motion_Light, HIGH);
  }
  else
  {
    digitalWrite(Motion_Light, LOW);
  }
  
  int lightValue = analogRead(Light);
  if(lightValue > 500)
  {
    digitalWrite(Light_Light, HIGH);
  }
  else
  {
    digitalWrite(Light_Light, LOW);
  }
  
//If motion detected or light intensity is greater than threshold value (light is on in the room)  
  if(motionValue || lightValue > 500) 
  {
    count=0;
    if(!flagSent_1)
    {
                
      flagSent_1 = true;
      flagSent_0 = false;
  
      //Serial.println("MeetingRoom is Occupied");
      iotkit.send("meetingroom",1);
      iotkit.send("Room1",1);
      
      digitalWrite(Available_Light, LOW);

    }//if
      
  } //if
  else
  {
    count++;
    if (count > 10 && !flagSent_0)
    {
      count = 0;    
      flagSent_1 = false;
      flagSent_0 = true;
  
      //Serial.println("MeetingRoom is Available");
      iotkit.send("meetingroom",0);
      iotkit.send("Room1",0);
      digitalWrite(Available_Light, HIGH);
    } //if
  } //else
delay(1000);
}
