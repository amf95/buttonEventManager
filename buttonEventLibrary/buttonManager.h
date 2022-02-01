#include <Arduino.h>

#ifndef MANAGER
#define MANAGER

//Configs:

//Time
#define BUTTON_DEBONCE_TIME_THRESHOLD 50
#define BUTTON_RELEASE_TIME 50
#define BUTTON_LONG_PRESS_LEASE_TIME_THRESHOLD 1500
#define BUTTON_DOUBLE_CLICK_LEASE_TIME_THRESHOLD 200

//#define D_1

#ifdef D_1 
#define DEBUG(x); Serial.println(x);
#else  
#define DEBUG(x);
#endif

//                    0       1        2          3       4      5          6           7           8
enum BUTTON_STATES {OPEN, DEBOUNCE, PRESS, LONG_PRESS , STUCK, CLICK , DOUBLE_CLICK, RELEASE, TAKE_ACTION};

struct buttonTrackers_t;//Encapsulated.

typedef buttonTrackers_t * buttonEventManager_t;

buttonEventManager_t buttonManagerInit(uint8_t buttonPinNumber, uint8_t pinDirection, uint8_t buttonOnPhysicalState);
void onButtonEvent(buttonEventManager_t button,void (*buttonCallbackFun)(void),byte Event);
uint8_t getButtonEvent(buttonEventManager_t button,byte Event);
void buttonManagerStateUpdate(buttonEventManager_t button, byte buttonPreviousState, byte buttonCurrentState, uint64_t timeTracker);

#endif
