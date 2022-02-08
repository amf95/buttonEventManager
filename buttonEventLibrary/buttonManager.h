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

#ifndef BUTTON_MANAGER
#define BUTTON_MANAGER

//Configs:

//Time
#define BUTTON_DEBONCE_TIME_THRESHOLD 50
#define BUTTON_RELEASE_TIME 50
#define BUTTON_LONG_PRESS_LEASE_TIME_THRESHOLD 1500
#define BUTTON_DOUBLE_CLICK_LEASE_TIME_THRESHOLD 200

//#define D_1
#define D_2 

#ifdef D_1 
#define DEBUG(x); Serial.println(x);
#else  
#define DEBUG(x);
#endif

#ifdef D_2 
#define DEBUG2(x); Serial.println(x);
#else  
#define DEBUG2(x);
#endif

struct buttonTrackers_t;//Encapsulated.

typedef buttonTrackers_t * buttonEventManager_t;

enum BUTTON_STATES {OPEN, DEBOUNCE, PRESS, LONG_PRESS ,
STUCK, CLICK , DOUBLE_CLICK, RELEASE, TAKE_ACTION};

buttonEventManager_t buttonManagerInit(uint8_t buttonPinNumber, 
    uint8_t pinDirection, uint8_t buttonOnPhysicalState);

void onButtonEvent(buttonEventManager_t button,
    void (*buttonCallbackFun)(void),byte Event);
    
uint8_t getButtonEvent(buttonEventManager_t button,byte Event);

void buttonManagerStateUpdate(buttonEventManager_t button,
    byte buttonPreviousState, byte buttonCurrentState, uint64_t timeTracker);

#endif
