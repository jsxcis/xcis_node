#include <RHRouter.h>
#include <RHMesh.h>
#include <RH_RF95.h>
#include <SoftwareSerial.h>

RH_RF95 rf95(4, 2);
RHMesh *manager;

//unsigned long delayStart = 0; // the time the delay started
//bool delayRunning = false; // true if still waiting for delay to finish
//unsigned long DELAY_TIME = 5000; // 5 sec
SoftwareSerial usonic(A4, A5);//SDA,SCL-  RX, TX
unsigned long delayStart = 0; // the time the delay started
bool delayRunning = 0; // true if still waiting for delay to finish

float distance;

void setup()
{
   pinMode(5, OUTPUT);
   digitalWrite(5, 1);
  // manual reset
  digitalWrite(5, 0);
  delay(10);
  digitalWrite(5, 1);
  delay(10);

  manager = new RHMesh(rf95, 4); // Node ID
  Serial.begin(115200);
  manager->init();
 
  delayStart = millis();   // start delay
  delayRunning = true; // not finished yet
  Serial.println(F("Ready"));
  usonic.begin(9600);
}

void loop()
{
  // check if delay has timed out after 10sec == DELAY_TIME
  if (delayRunning && ((millis() - delayStart) >= 5000))
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
