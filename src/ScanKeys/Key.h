#ifndef KEY_H
#define KEY_H

#include <Arduino.h>

class KeyC{
  private:
      long int pressStartTime;
      bool lookOutState;
      int* pin2Scan;
      int* pin2Set;
      int waitTime;
      
      
      bool oldKeyState;
      bool newKeyState;
      int debounceTime;
      int longPressDur;
      bool ongoingEvent;

      bool logic(bool state);
      bool debounce();
      
  public:
      char keyVal;
      KeyC(char* val_, int* pin2Scan_,int* pin2Set_, bool lookOutState_, int longPressDur_ , int debounceTime_ );
      bool isPressed(bool* pressedVar, bool* longPressedVar);
      bool isPressed();
      bool isLongPressed(bool* pressedVar, bool* longPressedVar);
      bool isLongPressed();
      void destroy();
      
  
  };

#endif
