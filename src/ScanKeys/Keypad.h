#ifndef KEYPAD_H
#define KEYPAD_H
#include <Arduino.h>
#include "Key.h"

#ifndef KEY_MAP_sIZE
#define KEY_MAP_sIZE(R, C)   ((R) * (C))
#endif


class KeyPad{
  
  public:   
      
      
      KeyPad(char* keyMap_, int nRows_, int nCols_, int* keyRowPins_, int* keyColPins_);  //constructor declaration
      void init(char sCanType = 'C',char _pinMode = 'U');
      void showKeys();
      bool isPressed();
      bool pressed(char* btn, bool* pressed, bool* lPressed );

     

private: 
      
      char* keyMap;
      int nRows;
      int nCols;
      
      int debounceTime;
      int waitTime;
      
      int keyMapSize;    // rXC
      char* sCanType;   // by rows or by cols
      int* keyRowPins; 
      int* keyColPins;
      bool defaultPinState;   // pulled High or LOW
      bool isInit; 
      bool iskeyCreated;
      int* pins2Scan;
      int* pins2Set;
      int longPressDur;
      
      

      
      void scan();
      void createKeys(int* size_);
      
  
      KeyC keys[];
  
  };

#endif
