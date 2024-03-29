#include <Arduino.h>
#include "buttonManager.h"

//Pins:
#define BUTTON1_PIN D1
#define BUTTON2_PIN D2
#define LED1 D3 

buttonEventManager_t button1ClickEventTracker;
buttonEventManager_t button1DoubleClickEventTracker;
buttonEventManager_t button1LongPressEventTracker;
buttonEventManager_t button2PressEventTracker;

void clickAction(void);
void pressAction(void);
void longPressAction(void);
void doubleClickAction(void);
void blink(int delayTime);
void blink2(int delayTime);

//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);

  Serial.begin(9600);

  button1ClickEventTracker = buttonManagerInit(BUTTON1_PIN, INPUT_PULLUP, LOW);
  button1DoubleClickEventTracker = buttonManagerInit(BUTTON1_PIN, INPUT_PULLUP, LOW);
  button1LongPressEventTracker = buttonManagerInit(BUTTON1_PIN, INPUT_PULLUP, LOW);
  button2PressEventTracker = buttonManagerInit(BUTTON2_PIN, INPUT_PULLUP, LOW);
}

//------------------------------------------------------------------------------------------

void loop() 
{
  onButtonEvent(button1ClickEventTracker, clickAction, CLICK);
  onButtonEvent(button1DoubleClickEventTracker, doubleClickAction, DOUBLE_CLICK);
  onButtonEvent(button1LongPressEventTracker, longPressAction, LONG_PRESS);
  
  onButtonEvent(button2PressEventTracker, pressAction, PRESS);
}

//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------

void blink(int delayTime)
{
  digitalWrite(LED_BUILTIN, LOW);
  delay(delayTime);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(delayTime);
}

void blink2(int delayTime)
{
  digitalWrite(LED1, HIGH);
  delay(delayTime);
  digitalWrite(LED1, LOW);
  delay(delayTime);
}

void longPressAction(void)
{
  blink(500);
}

void pressAction(void)
{
  blink(200);
}

void clickAction()
{
  blink(50);
}

void doubleClickAction()
{
  blink(100);
  blink(100);
}
