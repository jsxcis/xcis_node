#include <RHRouter.h>
#include <RHMesh.h>
#include <RH_RF95.h>
#include <SoftwareSerial.h>
#include <avr/wdt.h>

RH_RF95 rf95(4, 2);
RHMesh *manager;

SoftwareSerial usonic(A4, A5);//SDA,SCL-  RX, TX
unsigned long delayStart = 0; // the time the delay started
bool delayRunning = 0; // true if still waiting for delay to finish

float distance;
int defaultSwitchPress = 0;
// Analog PIN for Battery input
#define BATTERY_VOLTAGE A0

void setup()
{

   pinMode(A3,INPUT); // D4, PC3 Reset Switch
  
   pinMode(A1,OUTPUT);// A1, PC11 output LOW = ON SENSOR
   digitalWrite(A1,1); 
   pinMode(A2,OUTPUT); // A2, PCI2 output LOW = ON LORA
   digitalWrite(A2,1);
    
   pinMode(5, OUTPUT);
   digitalWrite(5, 1);
  // manual reset
  digitalWrite(5, 0);
  delay(10);
  digitalWrite(5, 1);
  delay(10);

  manager = new RHMesh(rf95, 10); // Node ID - NEED TO SET THIS
  Serial.begin(115200);
  manager->init();
 
  delayStart = millis();   // start delay
  delayRunning = true; // not finished yet
  usonic.begin(9600);
  
  Serial.println(F("Ready"));
  digitalWrite(A1,0);
  digitalWrite(A2,1);
}

void loop()
{
  
  if (digitalRead(A3) == 0)
  {
    Serial.println(F("Default pressed"));
    // restart in 60 milliseconds
    defaultSwitchPress++;
    Serial.println(defaultSwitchPress);
    if (defaultSwitchPress > 3500)
    {
      Serial.println("Defaulting");
      //default();
      defaultSwitchPress = 0;
    }
  }
  // check if delay has timed out after 10sec == DELAY_TIME
  if (delayRunning && ((millis() - delayStart) >= 5000))//unsigned long DELAY_TIME = 5000; // 5 sec
  {
    delayStart += 5000; // 5 secs
    readDataStream();
  }

  // parse for a packet, and call onReceive with the result:
  if (onReceive())
  {
    //String message = "Got Message!";   // send a message
  }
}
