SYSTEM_THREAD(ENABLED);
#include <blynk.h>
#include "oled-wing-adafruit.h"

OledWingAdafruit display;
void setup()
{
  Blynk.begin("TpZAjVlyQ0UD3kaUtq6YOQsb0eYBptI4", IPAddress(167, 172, 234, 162), 8080);
  display.setup();
  display.clearDisplay();
}
void loop()
{
  bool value = digitalRead(D4);
  Serial.println(value);
  Blynk.run();
  display.loop();
  if (value == TRUE){
  display.clearDisplay();
  uint64_t reading = analogRead(A3);
  double voltage = (reading * 3.3) / 4095.0;
  double temperatureC = (voltage - 0.5) * 100;
  double temperatureF = (temperatureC * 1.8) + 32;
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(temperatureC);
  display.setCursor(0, 18);
  display.println(temperatureF);
  display.display();
  Blynk.virtualWrite(V1, temperatureC);
  Blynk.virtualWrite(V2, temperatureF);
  delay(500);
  }
  else {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Push sent");
    Blynk.notify("Hey, A push here!");
    delay(5000);   
}
}
