# Button Event Detector for Arduino

# Description:
This library allows you to detect push button events.

Debounce without the need of external hardware.

No Blocking as no Delays are used.

# Notes:
Better not to use delays nor blocking code in loop() as onButtonEvent() function depends on main loop() to detect events based on time.

If you use "PRESS" event, other events wont work on the same button.

# Events that can be detected:
**PRESS, LONG_PRESS, CLICK, DOUBLE_CLICK, RELEASE.**


# Use:

After adding the library to your project(lib folder for PlatformIO).

Create buttonEventManager_t instance for each event that you want to listen to per button:
```c++
buttonEventManager_t button1ClickEventTracker;
buttonEventManager_t button1DoubleClickEventTracker;

buttonEventManager_t button2PressEventTracker;
```

# In setup():

Initialize the instance with **buttonManagerInit(buttonPinNumber, pinDirection, buttonOnPhysicalState)**

- **buttonPinNumber:** physical pin number
- **pinDirection:** **INPUT** | **INPUT_PULLUP** | **INPUT_PULLDOWN**.
- **buttonOnPhysicalState:** Active **HIGH** | **LOW**.

*returns*: **buttonEventManager_t** pointer.

```c++
void setup(){   
  //all buttons are active LOW here.   
  button1ClickEventTracker = buttonManagerInit(BUTTON1_PIN, INPUT_PULLUP, LOW);
  button1DoubleClickEventTracker = buttonManagerInit(BUTTON1_PIN, INPUT_PULLUP, LOW);
  
  button2PressEventTracker = buttonManagerInit(BUTTON2_PIN, INPUT_PULLUP, LOW);
}
```

# In loop():

Use **onButtonEvent(buttonEventTracker, buttonCallbackFun, Event)** to set action for each desired event.

- **buttonEventTracker:** the instance that has been initialized in setup().
- **buttonCallbackFun:** fuction to be called when desired even is detected.
- **Event:** enum { PRESS, LONG_PRESS, CLICK , DOUBLE_CLICK, RELEASE }.

```c++
void loop() {
  onButtonEvent(button1ClickEventTracker, clickAction, CLICK);
  onButtonEvent(button1DoubleClickEventTracker, doubleClickAction, DOUBLE_CLICK);
  
  onButtonEvent(button2PressEventTracker, pressAction, PRESS);
}
```

# Note:
buttonCallbackFun template takes void parameter and returns void.

```c++
void myCallbackFunction(void){
    //some code here or another funtion... .  
}

void clickAction(void){
    //some code here or another funtion... .
}

void doubleClickAction(void){
    //some code here or another funtion... .
}
```
