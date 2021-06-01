//=====================
//Button press, set LED
//=====================
void setLed(int value, int position)
{
  pinMode(dio, OUTPUT);
  
  //command byte to set single address mode
  digitalWrite(stb, LOW);
  shiftOut(dio, clk, LSBFIRST, 0x44);
  digitalWrite(stb, HIGH);
  
  //turn ON LED due to button press
  digitalWrite(stb, LOW);
  shiftOut(dio, clk, LSBFIRST, 0xC1 + (position<<1));
  shiftOut(dio, clk, LSBFIRST, value);
  digitalWrite(stb, HIGH);
}

//=========================
//Press button, set display
//=========================
void setDisplay(uint8_t value, uint8_t position)
{
  pinMode(dio, OUTPUT);
  //------------------------------------------------
  digitalWrite(stb, LOW);
  shiftOut(dio, clk, LSBFIRST, 0x44);
  digitalWrite(stb, HIGH);
  //------------------------------------------------
  digitalWrite(stb, LOW);
  shiftOut(dio, clk, LSBFIRST, 0xC0 + (position<<1));
  shiftOut(dio, clk, LSBFIRST, value);
  digitalWrite(stb, HIGH);
}

// Timer function
void doTimer()
{
  // Comparing millis() to the time passed makes the timer non-blocking
  // Using delay() for timer would've blocked the Rubik's Cube functionality
  if (millis() - resetTime >= secondsPassed + period) {
    secondsPassed += period;
    long secondsPassedCopy = secondsPassed / 1000;
    for (i=0; i<8; i++) {
      t[i] = 0;
    }
    i = 0;
    while (i != 8 && secondsPassedCopy != 0) {
      t[i] = secondsPassedCopy % 10;
      secondsPassedCopy /= 10;
      i++;
    }
    // Update seconds past on the 8 digit 7 segment display
    setDisplay(digit[t[7]], 0);
    setDisplay(digit[t[6]], 1);
    setDisplay(digit[t[5]], 2);
    setDisplay(digit[t[4]], 3);
    setDisplay(digit[t[3]], 4);
    setDisplay(digit[t[2]], 5);
    setDisplay(digit[t[1]], 6);
    setDisplay(digit[t[0]], 7);
  }
  
}
