/* ARDUINO KEYPAD LIBRARY BY TAM ANADERSON 
 *  28-16-2023
 *  tamandersonmav@gmail.com
 * 
 */

#include <Keypad.h>

int nRows = 4; int nCols = 4;                                //define number of rows and cols
const int kSize = 16;                                        // Define number of keys
                                                             //Create keymap
char keys[kSize] = {
                 '1', '2', '3', 'A',    
                 '4', '5', '6', 'B',
                 '7', '8', '9', 'C',
                 '*', '0', '#', 'D'
                  };
                                    
int keyRowPins[4] = {4,5,6,7 };                              //define row pins
int keyColPins[4] = {8,9,10,11};                             // define column pins

KeyPad keypad(keys, 4, 4, keyRowPins, keyColPins);           //create keypad object


//Function and vars for searching and holding keypad results
void checkKeypad();                             
 char button = ' ';
 bool pressed = false, lPressed = false;

           
void setup(){
  Serial.begin(9600);
  keypad.init();                                               //initialize keypad
  keypad.showKeys();                                           //Display keyMap
  
}
void loop(){
  checkKeypad();
  delay(50);
  
}

void checkKeypad(){
   button = ' ';
   pressed = false, lPressed = false;
//  delay(10000);
//  keypad.showKeys();
  //keypad.isPressed();
  if(keypad.pressed(&button,&pressed, &lPressed)){
    if(pressed) {
      Serial.println("Button pressed: ");
      Serial.println(button);
    }
    else{
      Serial.println("Button Long pressed: ");
      Serial.println(button);
    }
    
  }

   button = ' ';
   pressed = false, lPressed = false;
}
