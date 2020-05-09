
#include <Password.h> //http://playground.arduino.cc/uploads/Code/Password.zip //tells to use password library
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip  //tells to use keypad library

Password password = Password( "0000" ); //password to unlock, can be changed

const byte ROWS = 4; // Four rows
const byte COLS = 4; // columns
// Define the Keymap
char keys[ROWS][COLS] ={
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 9, 8, 7, 6 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 5, 4, 3,2 };


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  Serial.write("hello");
  Serial.write(254);
  Serial.write(0x01);
  delay(200);
  pinMode(10, OUTPUT);  //green light
  pinMode(11, OUTPUT);  //red light
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop() {
  keypad.getKey();
}
//take care of some special events
void keypadEvent(KeypadEvent eKey) {
  switch (keypad.getState()) {
    case PRESSED:

      Serial.print("Enter:");
      Serial.println(eKey);
      delay(10);

      Serial.write(254);

      switch (eKey) {
        case '*': checkPassword(); delay(1); break;

        case '#': password.reset(); delay(1); break;

        default: password.append(eKey); delay(1);
      }
  }
}
void checkPassword() {

  if (password.evaluate()) { //if password is right open

    Serial.println("Accepted");
    Serial.write(254); delay(10);
    //Add code to run if it works

    digitalWrite(11, HIGH);//turn on
    delay(5000); //wait 5 seconds
    digitalWrite(11, LOW);// turn off


  } else {
    Serial.println("Denied"); //if passwords wrong keep locked
    Serial.write(254); delay(10);
    //add code to run if it did not work
    digitalWrite(12, HIGH); //turn on
    delay(500); //wait 5 seconds
    digitalWrite(12, LOW);//turn off

  }
}

