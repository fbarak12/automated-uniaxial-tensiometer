/*
  Based on this examples:
   http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld
   https://www.addicore.com/v/vspfiles/downloadables/Product%20Downloadables/Project_Interface_Kit/Joystick_2Axis_with_Switch.txt
*/

// Include the library code:
#include <LiquidCrystal.h>
#include "HX711.h"
#include <AccelStepper.h>
#include <MultiStepper.h>

//STEPPER MOTOR PINS
AccelStepper stepper(1, 13, 12); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

#define DOUT  10
#define CLK  11
HX711 scale;
float calibration_factor = 20; // this calibration factor must be adjusted according to your load cell
float units;
float currentPos;

//Arduino pins attached to joystick
#define joystick_switch_pin  9
#define joystick_x_pin       A0
#define joystick_y_pin       A1

//Joystick values
#define up    0
#define right 1
#define down  2
#define left  3
#define enter 4
#define none  5

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Menus
// TODO: Submenus
String main_menu[] = {"1.Begin Test", "2.Calibrate", "3.Lower/Raise"};
String subMenu1[] = {"<- Back  Yes? ->", "CANCELLING...", "Beginning Test...","TEST COMPLETE"};
String subMenu2[] = {"sub12", "Zeroing Load Cell...", "sub32"};
String subMenu3[] = {"sub13", "<- LWR    RSE ->", "sub33"};

// Current menu and item to be displayed
int current_menu_item;
String *current_menu;
String *prevMenu;
// Used to check joystick state
int last_joy_read;

int read_joystick() {
  int output = none;
  // read all joystick values
  int X_Axis = analogRead(joystick_x_pin);     // read the x axis value
  int Y_Axis = analogRead(joystick_y_pin);     // read the y axis value
  Y_Axis = map(Y_Axis, 0, 1023, 1023, 0);      // invert the input from the y axis so that pressing the stick forward gives larger values
  int SwitchValue = digitalRead(joystick_switch_pin);  // read the state of the switch
  SwitchValue = map(SwitchValue, 0, 1, 1, 0);  // invert the input from the switch to be high when pressed

  if (SwitchValue == 1) {
    output = enter;
  } else if (X_Axis >= 900) {
    output = right;
  } else if (X_Axis <= 100) {
    output = left;
  } else if (Y_Axis >= 900) {
    output = up;
  } else if (Y_Axis <= 100) {
    output = down;
  }
  return output;
}

void print_line(int line, String text) {
  lcd.setCursor(0, line);
  lcd.print("               ");
  lcd.setCursor(0, line);
  lcd.print(text);
}

void move_up() {
  if (current_menu_item <= 0) {
    current_menu_item = sizeof(current_menu);
  } else {
    current_menu_item--;
  }
}

void move_down() {
  if (current_menu_item >= sizeof(current_menu)) {
    current_menu_item = 0;
  } else {
    current_menu_item++;
  }
}

void move_right() {
  if (current_menu == main_menu) {
    if (current_menu_item == 0) {
      current_menu = subMenu1;
      current_menu_item = 0;
      prevMenu = 0;
    }
    else if (current_menu_item == 1) {
      current_menu = subMenu2;
      current_menu_item = 0;
      prevMenu = 1;
    }
    else if (current_menu_item == 2) {
      current_menu = subMenu3;
      current_menu_item = 0;
      prevMenu = 2;
    }
    else {
      current_menu = main_menu;
      current_menu_item = 0;
    }
  }
  // TODO: enter submenu
  // TODO: change selected value
  // TODO: increase selected value (ex: defaut temp, timers, etc..)
}
void move_left() {
  current_menu = main_menu;
  current_menu_item = prevMenu;
  // TODO: go back mainmenu
  // TODO: go back submenu
  // TODO: decrease selected value (ex: defaut temp, timers, etc..)
}

int moveMenu() {
  int current_joy_read = read_joystick();

  if (current_joy_read != last_joy_read) {
    last_joy_read = current_joy_read;

    switch (current_joy_read) {
      case up:
        move_up();
        break;
      case down:
        move_down();
        break;
      case right:
        move_right();
        break;
      case left:
        move_left();
        break;
      default: break;
    }
  } return current_joy_read;
}

void setup() {
  // arduino default once time function
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // set up joy pins
  pinMode(joystick_switch_pin, INPUT_PULLUP);

  // Print template on lcd.
  lcd.setCursor(0, 0);
  lcd.print("Main Menu:");
  lcd.setCursor(0, 1);
  lcd.print(main_menu[current_menu_item]);

  // Init vars
  current_menu_item = 0;
  last_joy_read = none;
  current_menu = main_menu;

  // BEGIN STEPPER PROGRAMMING
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(120);
  stepper.setSpeed(100);
  stepper.setAcceleration(80);
  stepper.moveTo(500);

  //LOAD CELL VALUES
  scale.begin(DOUT, CLK);
  Serial.begin(9600);
  //Serial.println("Remove all weight from scale");
  //Serial.println("After readings begin, place known weight on scale");

  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  scale.tare();  //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {
  //Serial.print("\nReading - ,");
  units = scale.get_units(), 5;

  //Serial.print(",Weight: ,");

  Serial.print(units);
  Serial.print("\t");

  //Serial.print(", grams");
  //Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();
  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if (temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }
  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp == 't' || temp == 'T')
      scale.tare();  //Reset the scale to zero
  }


  // "main" arduino program

  int currentJoyVal = moveMenu();

  // clear line and print values to lcd
  if (current_menu == main_menu) { //PRINT HEADER
    print_line(0, "Main Menu:");
  }
  else {
    print_line(0, "Sub Menu:");
  }

  if (current_menu == subMenu1) { //BEGIN TEST
    if (currentJoyVal == down) {
      //scale.tare();
      current_menu_item = 2;
      //stepper.runToNewPosition(2750);
      //stepper.move(2750);
      //stepper.run();
     for (int i = 0; i <= 2750; i++) {
        stepper.move(100);
        stepper.run();
        currentPos = (240.0*stepper.currentPosition())/2750.0;
        //Serial.println("Current Position: ,");
        Serial.print(currentPos);
        Serial.print("\t");
        units = scale.get_units(), 5;

        //Serial.print("Weight: ,");
        Serial.print(units);
        Serial.println();
        //Serial.print(", grams");
        if (currentJoyVal == up){
          i=2750;
          stepper.runToNewPosition(0);
          current_menu_item = 1;
        }
        if (currentPos>50 && units<100){
          i=2750;
          current_menu_item = 3;
        }
      }

    }
    if (currentJoyVal == up) {
      //scale.tare();
      current_menu_item = 2;
      stepper.runToNewPosition(0);
    }
  }
  //currentPos = stepper.currentPosition();
  //Serial.print(" Current Position: ");
  //Serial.print(currentPos);

  if (current_menu == subMenu3) { //LOWER OR RAISE CLAMPS
    current_menu_item = 1; //set display to 2nd value
    if (currentJoyVal == down) {
      stepper.move(10);
      stepper.runToPosition();
    }
    else if (currentJoyVal == up) {
      stepper.move(-10);
      stepper.runToPosition();
    }
  }

  print_line(1, current_menu[current_menu_item]);
  delay(100);
}
