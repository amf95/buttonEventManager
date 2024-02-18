/*
**
** Version: 1.0
** Auther: Ahmed Fawzy.
** Created: Mon 31 Jan 2022 04:27:22 PM.
** Last Modification: Tue 08 Feb 2022 10:53:33 AM.
** 
** Description: This file controls time for each event && debug option.
** 
*/

#ifndef BUTTON_MANAGER_CONFIG
#define BUTTON_MANAGER_CONFIG

// Time in milliseconds
#define BUTTON_DEBONCE_TIME_THRESHOLD 50
#define BUTTON_RELEASE_TIME 50
#define BUTTON_LONG_PRESS_LEASE_TIME_THRESHOLD 1500
#define BUTTON_DOUBLE_CLICK_LEASE_TIME_THRESHOLD 200

// #define D_1
// #define D_2 

#ifdef D_1 
#define DEBUG(x); Serial.println(x);
#else  
#define DEBUG(x);
#endif // DEBUG1

#ifdef D_2 
#define DEBUG2(x); Serial.println(x);
#else  
#define DEBUG2(x);
#endif // DEBUG2

#endif // file guard.
