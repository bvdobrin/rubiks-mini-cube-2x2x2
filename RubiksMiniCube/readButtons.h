//===================
//read TM1638 buttons
//===================
int readButtons()
{
  int buttons = 0;
  
  //command byte to read buttons
  digitalWrite(stb, LOW);
  shiftOut(dio, clk, LSBFIRST, 0x42);

  //set dio pin as input
  pinMode(dio, INPUT);

  //get 4 bytes and store pressed button(s)
  for (int i=0; i<4; i++)
  {
    int val = shiftIn(dio, clk, LSBFIRST) << i;
    buttons |= val;
  }

  //set dio pin as output and return pressed button(s)
  pinMode(dio, OUTPUT);
  digitalWrite(stb, HIGH);
  return buttons;
}
