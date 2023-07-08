#include "Key.h"

KeyC::KeyC(char* val_, int* pin2Scan_,int* pin2Set_, bool lookOutState_, int longPressDur_ , int debounceTime_ ) {
  keyVal = *val_;
  waitTime = 5;
  pin2Scan = pin2Scan_;
  pin2Set = pin2Set_;
  lookOutState = lookOutState_;
  newKeyState = false;
  oldKeyState = false;
  longPressDur = longPressDur_;
  debounceTime = debounceTime_;
  pressStartTime = 0;
  ongoingEvent = false;
  Serial.print("Created Key: "); Serial.println(keyVal);

}

bool KeyC::isPressed(bool* pressedVar, bool* longPressedVar) {
  newKeyState = debounce();

  if (newKeyState)                                    //if pressed
  {
    *pressedVar = true;
    if (oldKeyState != newKeyState) {
      pressStartTime = millis();        //Start timing Key press
      ongoingEvent = true;              //start Key monitoring event
    }
    else {                             //old state is pressed, new is is pressed, check if longpressed
      *longPressedVar =  ((millis() - pressStartTime) >= longPressDur) ? true : false;

    }
    oldKeyState = newKeyState;                          //update old Key State
    return true ;                                      //yes Key is pressed
  }

  else {
    pressStartTime = millis();  //reset
    *pressedVar = false;
    *longPressedVar = false;
    return false;
  }
}


bool KeyC::isPressed() {
  newKeyState = debounce();

  if (newKeyState)                                    //if pressed
  {
    if (oldKeyState != newKeyState) {
      pressStartTime = millis();        //Start timing Key press
      ongoingEvent = true;              //start Key monitoring event
    }
    else {                             //old state is pressed, new is is pressed, check if longpressed
        //do nothing
    }
    oldKeyState = newKeyState;                          //update old Key State
    return true ;                                      //yes Key is pressed
  }

  else {
    pressStartTime = millis();  //reset
    return false;
  }
}


bool KeyC::isLongPressed(bool* pressedVar, bool* longPressedVar) {
  newKeyState = debounce();

  if (newKeyState)                                    //if pressed
  {
    *pressedVar = true;
    if (oldKeyState != newKeyState) {
      pressStartTime = millis();        //Start timing Key press
      ongoingEvent = true;              //start Key monitoring event
    }
    else {                             //old state is pressed, new is is pressed, check if longpressed
      *longPressedVar =  ((millis() - pressStartTime) >= longPressDur) ? true : false;
      return *longPressedVar;

    }
    oldKeyState = newKeyState;                          //update old Key State
                                     //yes Key is pressed
  }

  else {
    pressStartTime = millis();  //reset
    *pressedVar = false;
    *longPressedVar = false;
    return false;
  }
}

bool KeyC::isLongPressed() {
  newKeyState = debounce();

  if (newKeyState)                                    //if pressed
  {
    if (oldKeyState != newKeyState) {
      pressStartTime = millis();        //Start timing Key press
      ongoingEvent = true;              //start Key monitoring event
    }
    else {                             //old state is pressed, new is is pressed, check if longpressed
      bool state =  ((millis() - pressStartTime) >= longPressDur) ? true : false;
      return state;

    }
    oldKeyState = newKeyState;                          //update old Key State
                                     //yes Key is pressed
  }

  else {
    pressStartTime = millis();  //reset
    return false;
  }
}




bool KeyC::debounce() {
   digitalWrite (*pin2Set,lookOutState);
   delay(waitTime);                       // wait for signal to rise/fall to desired state
   bool newState = logic(digitalRead(*pin2Scan));
  if (oldKeyState == newState) {
    digitalWrite (*pin2Set, !lookOutState);
    return newState;
  }
  else {
    delay(debounceTime);
    newState = logic(digitalRead(*pin2Scan));
    digitalWrite (*pin2Set, !lookOutState);
    return newState;
  }

}

bool KeyC::logic(bool state) {
  if (state == lookOutState) return true;
  else return false;
}

void KeyC::destroy(){
  
}
