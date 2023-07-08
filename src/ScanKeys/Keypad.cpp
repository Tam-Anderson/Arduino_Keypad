#include "KeyPad.h"
//#include "Key.h"

//KeyC KeyPad::keys[16] = {};

KeyPad::KeyPad(char* keyMap_, int nRows_, int nCols_, int* keyRowPins_, int* keyColPins_) {  //constructor definition
  keyMap = keyMap_;
  nRows = nRows_;
  nCols = nCols_;
  keyRowPins = keyRowPins_;
  keyColPins = keyColPins_;
  debounceTime = 10;
  waitTime = 1000;
  longPressDur = 500;
  isInit = false;
  iskeyCreated = false;
  defaultPinState = HIGH;

  keyMapSize = KEY_MAP_sIZE(nRows, nCols);
  //for (int i = 0; i< keyMapSize ; i++){
  //  keys[i] = NULL;
  //}




}

bool KeyPad::isPressed(){
  bool state = false;
  for (int i = 0; i<keyMapSize; i++){
    if(keys[i].isPressed() == true){
      state = true;
      Serial.print("Key press Detected: Key = "); Serial.println(keys[i].keyVal);
      return state;
    }
  }
}

bool KeyPad::pressed(char* btn, bool* pressed, bool* lPressed ){
  bool state = false;
  for (int k = 0; k<keyMapSize; k++){
    if(keys[k].isPressed( pressed,lPressed)) {
      if(*lPressed) *pressed = false;
      state = true;
      *btn = keys[k].keyVal;
      break;
    }
  }
  return state;
}

void KeyPad::init(char sCanType = 'C',char _pinMode = 'U') {
  Serial.println("At init");
  pins2Scan = (sCanType == 'C') ? keyColPins : keyRowPins; // pins to scan in the key function
  pins2Set  = (pins2Scan == keyColPins) ? keyRowPins : keyColPins;
  if(_pinMode == 'U'){   //pull up
    for (int i = 0; i < nRows; i++){
      pinMode(*(pins2Set + i), OUTPUT);
      pinMode(*(pins2Scan + i) , INPUT_PULLUP);
    }
  }
  else{                //pull down ( no pullDown available on arduino
     for (int i = 0; i < nCols; i++){
      pinMode(*(pins2Set + i), OUTPUT);
      pinMode(*(pins2Scan + i) , INPUT);
    }
    
  }
    //Serial.println("Setting isInit to True");
    isInit = true;
     //Serial.print("isInit: "); Serial.print(isInit); Serial.print("  iskeyCreated: "); Serial.println(iskeyCreated);

    createKeys(&keyMapSize);
}

void KeyPad::createKeys(int* size_) {
  //Serial.println("Creating Keys");
  //Serial.print("isInit: "); Serial.print(isInit); Serial.print("  iskeyCreated: "); Serial.println(iskeyCreated);
  if (isInit && !iskeyCreated) {
    //Serial.print("isInit: "); Serial.print(isInit); Serial.print("  iskeyCreated: "); Serial.println(iskeyCreated);
    int k = 0;
    if (pins2Set == keyRowPins){
      for(int i = 0; i < nRows; i++){
        for (int j = 0; j< nCols; j++){
          //Serial.print("key val for key creation: "); Serial.println(*(keyMap + k) );
          keys[k] = KeyC( (keyMap + k) , pins2Scan + j, pins2Set +i , !defaultPinState, longPressDur, debounceTime);
          k++;
        }
      }
      Serial.println(" ");
      
    }
    else{
      //Serial.print("isInit: "); Serial.print(isInit); Serial.print("  iskeyCreated: "); Serial.println(iskeyCreated);
       for(int i = 0; i < nCols; i++){
        for (int j = 0; j< nRows; j++){
          keys[k] = KeyC( (keyMap + k) , pins2Scan + j, pins2Set +i , !defaultPinState, longPressDur, debounceTime);
          k++;
        }
      }
      
    }

    //Serial.println("Setting iskeycreated to true");
    iskeyCreated = true;     // keys created.
    //Serial.print("isInit: "); Serial.print(isInit); Serial.print("  iskeyCreated: "); Serial.println(iskeyCreated);
  }
  else {
    //Serial.println("Couldn't create keys");
  }

}

void KeyPad::showKeys() {
  //Serial.println("SHOW KEYS");
  //Serial.print("isInit: "); Serial.print(isInit); Serial.print("  iskeyCreated: "); Serial.println(iskeyCreated);
  if (isInit && iskeyCreated) {
    int k = 0;
    for (int i = 0; i < nRows; i++) {
      for (int j = 0; j < nCols; j++) {
        Serial.print(keys[k].keyVal);
        k++;
        Serial.print("   ");
      }
      Serial.println(" "); 
    }
 //Serial.println("Keys Shown");
  }
  else {
//    if(!isInit) Serial.println("Keypad::Showkeys ->> keypad not well init");
//    else if(!iskeyCreated) Serial.println("Keypad::Showkeys ->> keys not created");
//    else Serial.print("Keypad::Showkeys --> Something went wrong!!");
   
  }
}
