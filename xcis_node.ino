
#include <RHRouter.h>
#include <RHMesh.h>
#include <RH_RF95.h>
#include <SoftwareSerial.h>

RH_RF95 rf95(4, 2);
RHMesh *manager;

//unsigned long delayStart = 0; // the time the delay started
//bool delayRunning = false; // true if still waiting for delay to finish
//unsigned long DELAY_TIME = 5000; // 5 sec
//SoftwareSerial mySerial(2, 3);


void setup()
{
   
   pinMode(5, OUTPUT);
   digitalWrite(5, 1);
  // manual reset
  digitalWrite(5, 0);
  delay(10);
  digitalWrite(5, 1);
  delay(10);

  manager = new RHMesh(rf95, 2);
  Serial.begin(115200);
  if (!manager->init())
  {
    Serial.println(F("init failed"));
  } 
  rf95.setFrequency(915.0);
  Serial.println(F("Lora Mesh Sensor1 Ready"));
}

void loop()
{
  // parse for a packet, and call onReceive with the result:
  if (onReceive())
  {
    //String message = "Got Message!";   // send a message
  }
}
