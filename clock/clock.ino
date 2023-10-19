#include <stdio.h>
#include <stdlib.h>
#include <Keypad.h>
#include <LinkedList.h>

class clk{
    public:
      void print_time(){
        // *** \\
      }
    private:
        int m_second{};
        int m_minute{};
        int m_hour{};
    
};

const byte ROWS = 4;
const byte COLS = 3;

const int pin_hr_1D = 52;   //X0:00
const int pin_hr_1C = 50;
const int pin_hr_1B = 48;
const int pin_hr_1A = 46;

const int pin_hr_2D = 53;   //0X:00
const int pin_hr_2C = 51;
const int pin_hr_2B = 49;
const int pin_hr_2A = 47;

const int pin_min_1D = 36;  //00:X0
const int pin_min_1C = 34;
const int pin_min_1B = 32;
const int pin_min_1A = 30;

const int pin_min_2D = 37;   //00:0X
const int pin_min_2C = 35;
const int pin_min_2B = 33;
const int pin_min_2A = 31;

int time_out;
int s = 0;
int m;
int h;

void print_num(int num, int pin4, int pin3, int pin2, int pin1){
  if(num == 0){  //0
    digitalWrite(pin4, LOW);  //D = pin4
    digitalWrite(pin3, LOW);  //C = pin3
    digitalWrite(pin2, LOW);   //B = pin2
    digitalWrite(pin1, LOW);   //A = pin1
  }
  if(num == 1){  //1
    digitalWrite(pin4, LOW);  //D = pin4
    digitalWrite(pin3, LOW);  //C = pin3
    digitalWrite(pin2, LOW);   //B = pin2
    digitalWrite(pin1, HIGH);   //A = pin1
  }
  if(num == 2){  //2
    digitalWrite(pin4, LOW);  //D = pin4
    digitalWrite(pin3, LOW);  //C = pin3
    digitalWrite(pin2, HIGH);   //B = pin2
    digitalWrite(pin1, LOW);   //A = pin1
  }
  if(num == 3){  //3
    digitalWrite(pin4, LOW);  //D = pin4
    digitalWrite(pin3, LOW);  //C = pin3
    digitalWrite(pin2, HIGH);   //B = pin2
    digitalWrite(pin1, HIGH);   //A = pin1
  }
  if(num == 4){  //4
    digitalWrite(pin4, LOW);  //D = pin4
    digitalWrite(pin3, HIGH);  //C = pin3
    digitalWrite(pin2, LOW);   //B = pin2
    digitalWrite(pin1, LOW);   //A = pin1
  }
  if(num == 5){  //5
    digitalWrite(pin4, LOW);  //D = pin4
    digitalWrite(pin3, HIGH);  //C = pin3
    digitalWrite(pin2, LOW);   //B = pin2
    digitalWrite(pin1, HIGH);   //A = pin1
  }
  if(num == 6){  //6
    digitalWrite(pin4, LOW);  //D = pin4
    digitalWrite(pin3, HIGH);  //C = pin3
    digitalWrite(pin2, HIGH);   //B = pin2
    digitalWrite(pin1, LOW);   //A = pin1
  }
  if(num == 7){  //7
    digitalWrite(pin4, LOW);  //D = pin4
    digitalWrite(pin3, HIGH);  //C = pin3
    digitalWrite(pin2, HIGH);   //B = pin2
    digitalWrite(pin1, HIGH);   //A = pin1
  }
  if(num == 8){  //8
    digitalWrite(pin4, HIGH);  //D = pin4
    digitalWrite(pin3, LOW);  //C = pin3
    digitalWrite(pin2, LOW);   //B = pin2
    digitalWrite(pin1, LOW);   //A = pin1
  }
  if(num == 9){  //9
    digitalWrite(pin4, HIGH);  //D = pin4
    digitalWrite(pin3, LOW);  //C = pin3
    digitalWrite(pin2, LOW);   //B = pin2
    digitalWrite(pin1, HIGH);   //A = pin1
  }
  if(num == 10){  //10 for case when X0:00 where X = 0, we want to print nothing, not 0
    digitalWrite(pin4, HIGH);  //D = pin4
    digitalWrite(pin3, HIGH);  //C = pin3
    digitalWrite(pin2, HIGH);   //B = pin2
    digitalWrite(pin1, HIGH);   //A = pin1
  }
}

void print_hr(int h){
  int h1 = h / 10;
  int h2 = h % 10;

  if(h1 == 0)
    print_num(10, pin_hr_1D, pin_hr_1C, pin_hr_1B, pin_hr_1A);
  else
    print_num(h1, pin_hr_1D, pin_hr_1C, pin_hr_1B, pin_hr_1A);
  print_num(h2, pin_hr_2D, pin_hr_2C, pin_hr_2B, pin_hr_2A);
}

void print_min(int m){
  int m1 = m / 10;
  int m2 = m % 10;

  print_num(m1, pin_min_1D, pin_min_1C, pin_min_1B, pin_min_1A);
  print_num(m2, pin_min_2D, pin_min_2C, pin_min_2B, pin_min_2A);
}

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = {5, 4, 3}; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void set_time(int time_in){
  time_out = time_in;
  m = time_in % 100;
  h = time_in / 100;
}

void setup(){
  //Serial.begin(9600);

  char customKey;
  char playTime[4];
  bool valid_time = false;

  //X0:00
  pinMode(pin_hr_1D, OUTPUT); //D
  pinMode(pin_hr_1C, OUTPUT); //C
  pinMode(pin_hr_1B, OUTPUT); //B
  pinMode(pin_hr_1A, OUTPUT); //A

  //0X:00
  pinMode(pin_hr_2D, OUTPUT); //D
  pinMode(pin_hr_2C, OUTPUT); //C
  pinMode(pin_hr_2B, OUTPUT); //B
  pinMode(pin_hr_2A, OUTPUT); //A

  //00:X0
  pinMode(pin_min_1D, OUTPUT); //D
  pinMode(pin_min_1C, OUTPUT); //C
  pinMode(pin_min_1B, OUTPUT); //B
  pinMode(pin_min_1A, OUTPUT); //A

  //00:0X
  pinMode(pin_min_2D, OUTPUT); //D
  pinMode(pin_min_2C, OUTPUT); //C
  pinMode(pin_min_2B, OUTPUT); //B
  pinMode(pin_min_2A, OUTPUT); //A
 
  LinkedList<char> myList = LinkedList<char>(); //create linkedlist

  while(!valid_time){
    //Serial.println("Please enter play time in minutes: ");
    //* = 42
    //# = 35
    int len = 0;
  
    for(int i = 0; i < 4; i++){
        customKey = customKeypad.waitForKey();
        //customKey = customKeypad.getKey();
        if(customKey == '*'){     //CLEAR
          i = -1;
          myList.clear();
          continue;
        }
        if(customKey == '#'){     //ENTER
          //playTime[i+1] = '\0';
          break;
        }
        //Serial.print("Entered #: ");
       
        //Serial.println(customKey);            //TEST
        //Serial.println();
        //playTime[i] = customKey;                  
        myList.add(customKey);
        //Serial.println(playTime[i]);         //TEST
    
        //Serial.print("Current list size: ");
        //Serial.print(myList.size());
        //Serial.println();
        //Serial.print("Current list: ");            //TEST
        for(int j = 0; j < myList.size(); j++){
          //Serial.print(myList.get(j));
        }
        delay(1000); //This delay is necessary
    }
  
    char final[myList.size()];
    String str_final = "";
    //Serial.println();
    //Serial.print("Final: ");
    for(int k = 0; k < myList.size(); k++){
        //Serial.print(myList.get(k));
        final[k] = myList.get(k);
        //Serial.print(final[k]);
    }
    final[myList.size()] = '\0';
    int int_final = atoi(final);
    
    if(int_final <= 2359 && int_final >= 100){
      valid_time = true;
      set_time(int_final);
    } else {
      //Serial.print("Enter a valid time please.");
      valid_time = false;
      myList.clear();
    }
  }
}


void loop(){
  s++;
  //update hour, minute and second
  if(s==60){
    m += 1;
    s = 0;
  }
  if(m==60){
    h += 1;
    m = 0;
  }
  if(h==24){
    h = 0;
    m = 0;
    s = 0;
  }
  delay(1000);
  print_hr(h);
  print_min(m);
}
