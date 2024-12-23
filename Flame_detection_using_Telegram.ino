/Welcome to The IoT Projects
//IoT Based Fire Alarm Notification and control system using ESP8266
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


int LED = D2;
int RELAY = D4;
int Flame_sensor = D1;
int Flame_detected;

BlynkTimer timer;
char auth[] = "jovd0wly3APhqOwX6XJzwN4j0m6wpTwR"; //Auth code sent via Email
char ssid[] = "Alsan";
char pass[] = "12345678";

void notifyOnFire()
{
  Flame_detected = digitalRead(Flame_sensor);
  Serial.println(Flame_detected);
  //delay(100);
  if (Flame_detected == 0) {
    Serial.println("Flame detected...! take action immediately.");
    Blynk.notify("Alert : Fire detected...! take action immediately.");
    digitalWrite(LED, HIGH);
    digitalWrite(RELAY, LOW);
    delay(500);
  }
  else
  {
    Serial.println("No Fire detected. stay cool");
    digitalWrite(LED, LOW);
    digitalWrite(RELAY, HIGH);
  }
}
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  pinMode(Flame_sensor, INPUT_PULLUP);
  timer.setInterval(1000L, notifyOnFire);
}
void loop()
{
  Blynk.run();
  timer.run();
}
