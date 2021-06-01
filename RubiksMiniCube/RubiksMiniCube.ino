int stb=8, clk=9, dio=10;
int i, j, k, l, buttons, timerON, period = 1000;
long aux, cube[6][4], secondsPassed;
unsigned long resetTime;
int digit[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
int t[8];

#include "TM1638_Initialization.h"
#include "readButtons.h"
#include "setLED.h"
#include "rubiksCube.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define button1            A0
#define button2            A1
#define button3            A2
#define button4            A3
#define button5            A4
#define button6            A5
#define PIN_ledPiece0      6
#define PIN_ledPiece1      7
#define NUMPIXELS          12

// A ledPiece is made out of 3 2x2 rgb led matrices serially soldered
Adafruit_NeoPixel ledPiece0 = Adafruit_NeoPixel(NUMPIXELS, PIN_ledPiece0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ledPiece1 = Adafruit_NeoPixel(NUMPIXELS, PIN_ledPiece1, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(stb, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(dio, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(button6, INPUT);
  
  TM1638_Initialization();
  timerON = 0;
  secondsPassed = 0;
  resetTime = 0;

  Serial.begin(9600); // initiate serial communication, open the serial port at 9600 bps (baud rate)
  initCube();
  ledPiece0.begin();
  ledPiece1.begin();
}

void loop()
{
  int mask;
  int button1rev = digitalRead(button1);
  int button2rev = digitalRead(button2);
  int button3rev = digitalRead(button3);
  int button4rev = digitalRead(button4);
  int button5rev = digitalRead(button5);
  int button6rev = digitalRead(button6);
  
  if (button1rev == HIGH)
  {
    move1rev();
    delay(250);
  }
  if (button2rev == HIGH)
  {
    move2rev();
    delay(250);
  }
  if (button3rev == HIGH)
  {
    move3rev();
    delay(250);
  }
  if (button4rev == HIGH)
  {
    move4rev();
    delay(250);
  }
  if (button5rev == HIGH)
  {
    move5rev();
    delay(250);
  }
  if (button6rev == HIGH)
  {
    move6rev();
    delay(250);
  }

  buttons = readButtons();
  for(int pos=0; pos<=7; pos++)
  {
    mask = 0b00000001 << pos;
    setLed(buttons & mask ? 1 : 0, pos);
    if (buttons == mask) {
      if (pos == 0) {
        move1();
      } else if (pos == 1) {
        move2();
      } else if (pos == 2) {
        move3();
      } else if (pos == 3) {
        move4();
      } else if (pos == 4) {
        move5();
      } else if (pos == 5) {
        move6();
      } else if (pos == 6) {
        if (timerON == 0) {
          timerON = 1;
          secondsPassed = 0;
          resetTime = millis();
        } else {
          timerON = 0;
          secondsPassed = 0;
          resetTime = millis();
        }
      } else if (pos == 7) {
        initCube();
      }
      delay(250);
    }
  }

  if (timerON == 1) {
    doTimer();
  }
  

  ledPiece0.clear();
  ledPiece0.setBrightness(10);
  // Is green on initialization
  ledPiece0.setPixelColor(0, ledPiece0.Color(getR(cube[0][0]), getG(cube[0][0]), getB(cube[0][0])));
  ledPiece0.setPixelColor(1, ledPiece0.Color(getR(cube[0][1]), getG(cube[0][1]), getB(cube[0][1])));
  ledPiece0.setPixelColor(2, ledPiece0.Color(getR(cube[0][2]), getG(cube[0][2]), getB(cube[0][2])));
  ledPiece0.setPixelColor(3, ledPiece0.Color(getR(cube[0][3]), getG(cube[0][3]), getB(cube[0][3])));

  // Is orange on initialization
  ledPiece0.setPixelColor(4, ledPiece0.Color(getR(cube[3][0]), getG(cube[3][0]), getB(cube[3][0])));
  ledPiece0.setPixelColor(5, ledPiece0.Color(getR(cube[3][1]), getG(cube[3][1]), getB(cube[3][1])));
  ledPiece0.setPixelColor(6, ledPiece0.Color(getR(cube[3][2]), getG(cube[3][2]), getB(cube[3][2])));
  ledPiece0.setPixelColor(7, ledPiece0.Color(getR(cube[3][3]), getG(cube[3][3]), getB(cube[3][3])));

  // Is blue on initialization
  ledPiece0.setPixelColor(8, ledPiece0.Color(getR(cube[4][0]), getG(cube[4][0]), getB(cube[4][0])));
  ledPiece0.setPixelColor(9, ledPiece0.Color(getR(cube[4][1]), getG(cube[4][1]), getB(cube[4][1])));
  ledPiece0.setPixelColor(10, ledPiece0.Color(getR(cube[4][2]), getG(cube[4][2]), getB(cube[4][2])));
  ledPiece0.setPixelColor(11, ledPiece0.Color(getR(cube[4][3]), getG(cube[4][3]), getB(cube[4][3])));
  
  ledPiece0.show();

  ledPiece1.clear();
  ledPiece1.setBrightness(10);
  // Is yellow on initialization
  ledPiece1.setPixelColor(0, ledPiece1.Color(getR(cube[5][0]), getG(cube[5][0]), getB(cube[5][0])));
  ledPiece1.setPixelColor(1, ledPiece1.Color(getR(cube[5][1]), getG(cube[5][1]), getB(cube[5][1])));
  ledPiece1.setPixelColor(2, ledPiece1.Color(getR(cube[5][2]), getG(cube[5][2]), getB(cube[5][2])));
  ledPiece1.setPixelColor(3, ledPiece1.Color(getR(cube[5][3]), getG(cube[5][3]), getB(cube[5][3])));

  // Is red on initialization
  ledPiece1.setPixelColor(4, ledPiece1.Color(getR(cube[1][3]), getG(cube[1][3]), getB(cube[1][3])));
  ledPiece1.setPixelColor(5, ledPiece1.Color(getR(cube[1][0]), getG(cube[1][0]), getB(cube[1][0])));
  ledPiece1.setPixelColor(6, ledPiece1.Color(getR(cube[1][1]), getG(cube[1][1]), getB(cube[1][1])));
  ledPiece1.setPixelColor(7, ledPiece1.Color(getR(cube[1][2]), getG(cube[1][2]), getB(cube[1][2])));

  // Is white on initialization
  ledPiece1.setPixelColor(8, ledPiece1.Color(getR(cube[2][3]), getG(cube[2][3]), getB(cube[2][3])));
  ledPiece1.setPixelColor(9, ledPiece1.Color(getR(cube[2][0]), getG(cube[2][0]), getB(cube[2][0])));
  ledPiece1.setPixelColor(10, ledPiece1.Color(getR(cube[2][1]), getG(cube[2][1]), getB(cube[2][1])));
  ledPiece1.setPixelColor(11, ledPiece1.Color(getR(cube[2][2]), getG(cube[2][2]), getB(cube[2][2])));
  
  ledPiece1.show();
}
