#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PG0 8
#define PG1 9
#define PG2 10
#define PG3 11
#define ARST 12

#define OLED_RESET 2
Adafruit_SSD1306 display(OLED_RESET);

int terminal_1  = 2;
int terminal_2  = 4;
volatile int encorder_val = 0;
volatile int mode_set = 0;
volatile int band_mode = LOW;
volatile char old_state = 0;
boolean event = 0;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //    Serial.begin(9600);
  pinMode(PG0, OUTPUT);
  pinMode(PG1, OUTPUT);
  pinMode(PG2, OUTPUT);
  pinMode(PG3, OUTPUT);
  pinMode(ARST, OUTPUT);
  pinMode(terminal_1, INPUT);
  pinMode(terminal_2, INPUT);
  Wire.begin() ;
  attachInterrupt(0, Rotary_encorder, CHANGE);
  // attachInterrupt(1,mode_setting,CHANGE);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  //  display.setCursor(32,32);
  //  display.print("FM");
  //  display.display();

  //setting Internal setting mode

  //initial reset
  reset_dsp();
  //setting 1010;
  //  digitalWrite(ARST,HIGH);
  //  digitalWrite(PG3, 1);
  //  digitalWrite(PG2, 1);
  //  digitalWrite(PG1, 1);
  //  digitalWrite(PG0, 0);
  //reset_dsp();
  encorder_val = 8;
  display.clearDisplay();
  display.setCursor(32, 32);
  display.print("Phaser");
  display.setCursor(32, 40);
  writestate(encorder_val);
  display.display();

}

// the loop function runs over and over again forever
void loop() {


  if (event == 1) {
    reset_dsp();
    switch (encorder_val) {
      case 0:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Reverb");
        display.setCursor(32, 40);
        display.print("small hall");
        display.display();
        writestate(encorder_val);
        break;
      case 1:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Reverb");
        display.setCursor(32, 40);
        display.print("big hall");
        display.display();
        writestate(encorder_val);
        break;
      case 2:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Reverb");
        display.setCursor(32, 40);
        display.print("room");
        display.display();
        writestate(encorder_val);
        break;
      case 3:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Reverb");
        display.setCursor(32, 40);
        display.print("Church");
        display.display();
        writestate(encorder_val);
        break;
      case 4:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Reverb");
        display.setCursor(32, 40);
        display.print("reverse");
        display.display();
        writestate(encorder_val);
        break;
      case 5:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Reverb");
        display.setCursor(32, 40);
        display.print("Gated");
        display.display();
        writestate(encorder_val);
        break;
      case 6:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Reverb");
        display.setCursor(32, 40);
        display.print("Chapel");
        display.display();
        writestate(encorder_val);
        break;
      case 7:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Reverb");
        display.setCursor(32, 40);
        display.print("Spring");
        display.display();
        writestate(encorder_val);
        break;
      case 8:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Phaser");
        display.setCursor(32, 40);
        //display.print("small hall");
        display.display();
        writestate(encorder_val);
        break;
      case 9:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Flanger");
        display.setCursor(32, 40);
        //display.print("big hall");
        display.display();
        writestate(encorder_val);
        break;
      case 10:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Echo");
        display.setCursor(32, 40);
        //display.print("room");
        display.display();
        writestate(encorder_val);
        break;
      case 11:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Chorus");
        display.setCursor(32, 40);
        display.print("Church");
        display.display();
        writestate(encorder_val);
        break;
      case 12:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Early");
        display.setCursor(32, 40);
        display.print("Reflection");
        display.display();
        writestate(encorder_val);
        break;
      case 13:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Big");
        display.setCursor(32, 40);
        display.print("Ambience");
        display.display();
        writestate(encorder_val);
        break;
      case 14:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("Stereo");
        display.setCursor(32, 40);
        display.print("Delay");
        display.display();
        writestate(encorder_val);
        break;
      case 15:
        display.clearDisplay();
        display.setCursor(32, 32);
        display.print("slap-back");
        display.setCursor(32, 40);
        display.print("Delay");
        display.display();
        writestate(encorder_val);
        break;
    }


    event = 0;
  }
}

void reset_dsp(void) {
  digitalWrite(ARST, LOW);
  digitalWrite(ARST, HIGH);
}


void Rotary_encorder(void)
{
  if (!digitalRead(terminal_1)) {
    if (digitalRead(terminal_2)) {
      old_state = 'R';
    } else {
      old_state = 'L';
    }
  } else {
    if (digitalRead(terminal_2)) {
      if (old_state == 'L') {
        encorder_val++;
      }
    } else {
      if (old_state == 'R') {
        encorder_val--;
      }
    }

    if (encorder_val < 0) {
      encorder_val = 15;
    }
    if (encorder_val > 15) {
      encorder_val = 0;
    }
    old_state = 0;
    event = 1;
  }

}

void writestate(int i) {
  boolean bit0, bit1, bit2, bit3;
  bit3 = (i & 0b1000) >> 3;
  bit2 = (i & 0b100) >> 2;
  bit1 = (i & 0b10) >> 1;
  bit0 = i & 0b1;
  digitalWrite(PG3, bit3);
  digitalWrite(PG2, bit2);
  digitalWrite(PG1, bit1);
  digitalWrite(PG0, bit0);
}

