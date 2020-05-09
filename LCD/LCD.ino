#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 8, 7, 4); //RS,E,D4,D5,D6,D7LiquidCrystal lcd(9, 8 , 7, 4, 3, 2); //RS,E,D4,D5,D6,D7
int time;

void setup()

{
  lcd.begin(16, 2); //LCD begins. dimension: 16x2(Coluns x Rows)
  lcd.setCursor(0, 0); // Positions the cursor in the first column (0) and the firt row (1) at LCD
  lcd.print("Hello World"); //LCD write comand"LiquidCrystal.h"
  lcd.setCursor(0, 1); // Positions the cursor in the first column (0) and the second row (1) at LCD
  lcd.print("GarageLab"); // LCD write command "GarageLab"
}

void loop()
{ /*
    lcd.setCursor(13, 1); // Positions the cursor on the fourteenth column (13) and the second line (1) LCD
    lcd.print(time); // Write the current value of the count variable in the LCD
    delay(1000); // Waits for 1 second
    time++; // Increment count variable
    if (time == 600) // If the variable temp get to 600 (10 minutes), ...
    {
     time = 0; //... resets the count variable
    }*/
}
