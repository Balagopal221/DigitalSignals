// Mohawk College - COMP-10184
//
// Pulse Width Modulation - Test Program
//
#include <Arduino.h>
int lastButtonState;
int lightState = 0;
unsigned long lastTimeButtonStateChanged = millis();
unsigned long debounceDuration = 50;
void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // set default PWM range
  analogWriteRange(1023);
  // configure pin D5 as digital input - this is the pushbutton
  pinMode(D5, INPUT_PULLUP);

  // configure pin D4 as a digital output - this is the LED
  pinMode(D4, OUTPUT);

  analogWrite(D4, 0);
}

void loop()
{
  float iVal;
  // read digitized value from the D1 Mini's A/D convertor
  iVal = analogRead(A0);
  if (millis() - lastTimeButtonStateChanged >= debounceDuration)
  {

    int buttonState = digitalRead(D5);
    Serial.println(buttonState);
    if (buttonState != lastButtonState)
    {
      lastTimeButtonStateChanged = millis();

      lastButtonState = buttonState;
      if (buttonState == 0)
      {
        if (lightState != 0)
        {
          lightState = 0;
        }
        else
        {
          lightState = iVal;
          analogWrite(D4, lightState);
        }
      }
    }
  }
}