/*
**
** Version: 1.0
** Auther: Ahmed Fawzy.
** Created: Mon 31 Jan 2022 04:27:22 PM.
** Last Modification: Tue 08 Feb 2022 10:53:33 AM.
** 
**
** Description: This library is used to debounce push button click/press and detect other evenets.
** Events of interest: ( PRESS, LONG_PRESS, CLICK , DOUBLE_CLICK, RELEASE ).
** Use:
**  1- Create buttonEventManager_t instance.
**  2- Init with buttonManagerInit().
**  3- Use onButtonEvent() and give it button object, callback function and event to listen to.
**
*/


#include <Arduino.h>
#include "buttonManager.h"


typedef struct buttonTrackers_t {  //Encapsulated.
  byte buttonCurrentState;
  byte buttonPreviousState;
  uint64_t timeTracker;
  byte on;
  byte off;
  byte buttonPinNumber;
} buttonTrackers_t;


void onButtonEvent(buttonEventManager_t button,void (*buttonCallbackFun)(void),byte Event){

  if(button == NULL) { return; }
  
  switch (button->buttonCurrentState){
    
    case OPEN:
      if(digitalRead(button->buttonPinNumber) == button->on){
        buttonManagerStateUpdate(button, OPEN, DEBOUNCE, millis());
      }
      break;

    case DEBOUNCE:
      if(digitalRead(button->buttonPinNumber) == button->off){
        buttonManagerStateUpdate(button, DEBOUNCE, OPEN, millis());
      }
      else if(millis() - button->timeTracker >= BUTTON_DEBONCE_TIME_THRESHOLD){
        buttonManagerStateUpdate(button, DEBOUNCE, PRESS, millis());
      }
      break;

    case PRESS:
      if(Event  == PRESS){
        buttonManagerStateUpdate(button, PRESS, TAKE_ACTION, millis()); 
      }else if((digitalRead(button->buttonPinNumber) == button->off)){
        DEBUG("Pressed!");
        buttonManagerStateUpdate(button, PRESS, CLICK, millis());
      }else if ((digitalRead(button->buttonPinNumber) == button->on) 
          && (millis() - button->timeTracker >= BUTTON_LONG_PRESS_LEASE_TIME_THRESHOLD)){
        DEBUG("Pressed!");
        buttonManagerStateUpdate(button, PRESS, LONG_PRESS, millis());
      }
      break;

    case LONG_PRESS:
      DEBUG("Long_Pessed!");
      if(Event == LONG_PRESS){
        buttonManagerStateUpdate(button, LONG_PRESS, TAKE_ACTION, millis()); 
      }
      if(digitalRead(button->buttonPinNumber) == button->off){
        buttonManagerStateUpdate(button, LONG_PRESS, RELEASE, millis()); 
      }
      break;

    case STUCK:
      DEBUG("STUCK!");
      if(digitalRead(button->buttonPinNumber) == button->off){
        buttonManagerStateUpdate(button, STUCK, RELEASE, millis());
      }
      break;

    case CLICK:
      if((digitalRead(button->buttonPinNumber) == button->off) 
          && (millis() - button->timeTracker >= BUTTON_DOUBLE_CLICK_LEASE_TIME_THRESHOLD)){
        DEBUG("Clicked!");
        buttonManagerStateUpdate(button, CLICK, TAKE_ACTION, millis());
      }else if((digitalRead(button->buttonPinNumber) == button->on) 
          && (millis() - button->timeTracker < BUTTON_DOUBLE_CLICK_LEASE_TIME_THRESHOLD) 
          && (millis() - button->timeTracker >= BUTTON_DEBONCE_TIME_THRESHOLD)){ //debounce second click.
        buttonManagerStateUpdate(button, CLICK, DOUBLE_CLICK, millis());
      }
      break;

    case DOUBLE_CLICK:
      DEBUG("Double_Clicked!");
      buttonManagerStateUpdate(button, DOUBLE_CLICK, TAKE_ACTION, millis());
      break;

    case RELEASE:
      DEBUG("Released!");
      buttonManagerStateUpdate(button, RELEASE, TAKE_ACTION, millis());
      break;

    case TAKE_ACTION:
      if(millis() - button->timeTracker > BUTTON_RELEASE_TIME){
        DEBUG("Take_Action");
        if(button->buttonPreviousState == Event){
          DEBUG("-----callback Called-----");
          buttonCallbackFun();
        }
        if(digitalRead(button->buttonPinNumber) == button->on){ 
          buttonManagerStateUpdate(button, TAKE_ACTION, STUCK, millis()); 
        }else{
          buttonManagerStateUpdate(button, TAKE_ACTION, OPEN, millis());
        }
      }
      break;

    default:
      DEBUG("Default!");
      break;
  }
}


buttonEventManager_t buttonManagerInit(uint8_t buttonPinNumber,
    uint8_t pinDirection, uint8_t buttonOnPhysicalState){
 
  buttonEventManager_t button = (buttonEventManager_t)malloc(sizeof(buttonTrackers_t));

  if(button == NULL){ return NULL; }

  pinMode(buttonPinNumber, pinDirection);
  button->buttonCurrentState = OPEN;
  button->buttonPreviousState = OPEN;
  button->timeTracker = millis();
  button->buttonPinNumber = buttonPinNumber;
  if(buttonOnPhysicalState == LOW){
    button->on = buttonOnPhysicalState; 
    button->off = HIGH; 
  }else if(buttonOnPhysicalState == HIGH){
    button->on = buttonOnPhysicalState;
    button->off = LOW;
  }
  return button;
}


void buttonManagerStateUpdate(buttonEventManager_t button,
    byte buttonPreviousState, byte buttonCurrentState, uint64_t timeTracker){
      
  if(button == NULL) { return; }
  button->buttonCurrentState = buttonCurrentState;
  button->buttonPreviousState = buttonPreviousState;
  if(timeTracker != NULL){ button->timeTracker = timeTracker;}
}

