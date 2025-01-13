#include <Keypad.h>
#include <Servo.h>.
#include <Wire.h>.
#include <LiquidCrystal_I2C.h>.

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define Password_Lenght 7 // Give enough room for six chars + NULL char

char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "333333";     //Change PASSWORD here
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
bool door = true;

byte rowPins[ROWS] = {53, 51, 49,47}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {45, 43, 41}; //connect to the column pinouts of the keypad

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad

#define trig 9  
#define echo 10

int touch = 7;
int vib = 6;
int mr = 4;
int flame = 3;
int mic = 8;
int pir = 11;
int ledg = 13;
int ledr = 12;
int ir = A0;
int data;

void setup() {
  pinMode(flame, INPUT);
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT);
  pinMode(mr, INPUT);
  pinMode(vib, INPUT);
  pinMode(touch, INPUT);
  pinMode(pir, INPUT);
  pinMode(mic, INPUT);
  pinMode(ir, INPUT);
  pinMode(ledg, OUTPUT);
  pinMode(ledr, OUTPUT);
  myServo.attach(23);
  lcd.begin();
  lcd.backlight(); 
  Serial.begin(9600);
  // put your setup code here, to run once:
}

void loop() {
  lcd.clear();
  lcd.setCursor(1,0); 
  lcd.print("Hello Krishna!");
  long duration, distance;
  digitalWrite(trig, LOW);  
  delay(0);                  
  digitalWrite(trig, HIGH);
  delay(0);         
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration/2) / 29.1;


  if(digitalRead(touch)==HIGH){
    digitalWrite(ledr, HIGH);
    digitalWrite(ledg, LOW);
    lcd.clear();
    lcd.setCursor(1,0); 
    lcd.print("Touch!");
    delay(1000);
  }
  else{
    if(digitalRead(vib)==HIGH){
      digitalWrite(ledg, LOW);
      digitalWrite(ledr, HIGH); 
      lcd.clear();
      lcd.setCursor(1,0); 
      lcd.print("Vibration!");
      delay(1000);
    }
    else{
      if(distance<=5){
      digitalWrite(ledg, LOW);
      digitalWrite(ledr, HIGH);
      lcd.clear();
      lcd.setCursor(1,0); 
      lcd.print("Ultrasonic!");
      delay(1000);
    }
     else{
      if(digitalRead(mr)==LOW){
          digitalWrite(ledg, LOW);
          digitalWrite(ledr, HIGH);
          lcd.clear();
          lcd.setCursor(1,0); 
         lcd.print("Magnetic Reed!");
         delay(1000);
      }
      else{
        if(digitalRead(flame)==LOW){
          digitalWrite(ledg, LOW);
          digitalWrite(ledr, HIGH);  
          lcd.clear();
          lcd.setCursor(1,0); 
          lcd.print("Flame!");
          delay(1000);
        }
        else{
          if(digitalRead(mic)==HIGH){
            digitalWrite(ledg, LOW);
            digitalWrite(ledr, HIGH);
            lcd.clear();
            lcd.setCursor(1,0); 
            lcd.print("Voice");
            delay(1000);

          }
          else{
            if (door == 0) {
              customKey = customKeypad.getKey();

              if (customKey == '7'){
      
                lcd.clear();
                lcd.setCursor (3,0);
                lcd.print("LOCKING");
                delay(1000);
                lcd.setCursor (10,0);
                lcd.print(".");
                delay(1000);
                lcd.setCursor (11,0);  
                lcd.print(".");
                delay(1000);
                lcd.setCursor (12,0);
                lcd.print(".");
                delay(1000);
                lcd.clear();
                delay(1000);
                lcd.setCursor (5,0);
                lcd.print("LOCKED");
                door = 1;
               }
             }
            else { 
              customKey = customKeypad.getKey();
             if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
               {
                lcd.clear();
               lcd.setCursor(3, 1); 
                lcd.print("PASSCODE!");    //To hide your PASSWORD, make sure its the same lenght as your password
                Data[data_count] = customKey; // store char into data array // move cursor to show each new char // print char at said cursor
               data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
                }

              if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
                {
                 if (!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
                    {
                      lcd.clear();
                      lcd.print(" ACCESS GRANTED");
                      lcd.setCursor(0,1);
                      lcd.print("press * to close");
                      door = 0;
                     digitalWrite(ledg, HIGH);
                     digitalWrite(ledr, LOW);
                     delay(1000);
                   }
                 else
                    {
                     lcd.clear();
                     lcd.setCursor(1,0); 
                     lcd.print("ACCESS DENIED!");
                     delay(1000);
                     door = 1;
                     digitalWrite(ledg, LOW);
                     digitalWrite(ledr, HIGH);
                     delay(1000);
                   }
                      clearData();
                 }
                 else{
                  // if(digitalRead(pir)==HIGH){
                  //   digitalWrite(ledg, LOW);
                  //   digitalWrite(ledr, HIGH); 
                  //   lcd.clear();
                  //   lcd.setCursor(1,0); 
                  //   lcd.print("PIR!");
                  //   delay(1000);
                  // }
                  // else{
                    if(digitalRead(ir)==LOW){
                    digitalWrite(ledg, LOW);
                    digitalWrite(ledr, HIGH); 
                    lcd.clear();
                    lcd.setCursor(1,0); 
                    lcd.print("IR!");
                    delay(1000);
                    }
                    else{
                      // if(Serial.available() > 0){
                      //   data = Serial.read();

                      //   if(data == 'A'){
                      //     delay(1000); 
                      //     lcd.clear();
                      //     lcd.setCursor(4,0); 
                      //     lcd.print("Bluetooth");
                      //     lcd.setCursor(5,1); 
                      //     lcd.print("UNLOCK");
                      //     delay(1000);
                      //     digitalWrite(ledg, HIGH);
                      //     digitalWrite(ledr, LOW);
                      //   }
                      //   if(data == 'B'){
                      //     digitalWrite(ledg, LOW);
                      //     // delay(1000);
                      //     digitalWrite(ledr, HIGH);
                      //     delay(1000); 
                      //     lcd.clear();
                      //     lcd.setCursor(4,0); 
                      //     lcd.print("Bluetooth");
                      //     lcd.setCursor(6,1); 
                      //     lcd.print("LOCK");
                      //     delay(1000);
                      //     digitalWrite(ledg, LOW);
                      //     digitalWrite(ledr, HIGH);
                      //   }

                      // }
                      // else{
                        digitalWrite(ledg, HIGH);
                        digitalWrite(ledr, LOW);
                        Serial.println('A');
                        // delay(10000);
                      // }
                    }
                  }
                 }
              //  }            
             }
           }
          }
        }
      }
    }
  }
  // put your main code here, to run repeatedly:



void clearData()
{
  while (data_count != 0)
  { // This can be used for any array size,
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}