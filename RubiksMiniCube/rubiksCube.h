// Converts 3 long variables for red, green and blue in a single rgb long variable
long rgbToInt(long r, long g, long b)
{
  long result = (r << 16) + (g << 8) + b;
  return result;
}

// Gets red component from rgb variable
long getR(long colorInt)
{
  return (0b00000000111111110000000000000000 & colorInt) >> 16;
}

// Gets green component from rgb variable
long getG(long colorInt)
{
  return (0b00000000000000001111111100000000 & colorInt) >> 8;
}

// Gets blue component from rgb variable
long getB(long colorInt)
{
  return 0b00000000000000000000000011111111 & colorInt;
}

// Initializes the cube faces with the correct colors
void initCube()
{
  for (i=0; i<4; i++) {
    cube[0][i] = rgbToInt(0, 255, 0); //green
    cube[1][i] = rgbToInt(255, 0, 0); //red
    cube[2][i] = rgbToInt(255, 255, 255); //white
    cube[3][i] = rgbToInt(236, 128, 0); //orange
    cube[4][i] = rgbToInt(0, 0, 255); //blue
    cube[5][i] = rgbToInt(255, 255, 0); //yellow
  }
}

// moveX provides the 6 possible moves in a Rubik's Cube
// moveXrev provides the 6 possible reverse moves in a Rubik's Cube
void move1()
{
  for (i=0; i<2; i++) {
    aux = cube[0][0];
    cube[0][0] = cube[0][1];
    cube[0][1] = cube[3][0];
    cube[3][0] = cube[3][1];
    cube[3][1] = cube[4][0];
    cube[4][0] = cube[4][1];
    cube[4][1] = cube[1][0];
    cube[1][0] = cube[1][1];
    cube[1][1] = aux;
  }
  aux = cube[2][1];
  cube[2][1] = cube[2][0];
  cube[2][0] = cube[2][3];
  cube[2][3] = cube[2][2];
  cube[2][2] = aux;
}

void move1rev()
{
  for (i=0; i<2; i++) {
    aux = cube[0][0];
    cube[0][0] = cube[1][1];
    cube[1][1] = cube[1][0];
    cube[1][0] = cube[4][1];
    cube[4][1] = cube[4][0];
    cube[4][0] = cube[3][1];
    cube[3][1] = cube[3][0];
    cube[3][0] = cube[0][1];
    cube[0][1] = aux;
  }
  aux = cube[2][1];
  cube[2][1] = cube[2][2];
  cube[2][2] = cube[2][3];
  cube[2][3] = cube[2][0];
  cube[2][0] = aux;
}

void move2()
{
  for (i=0; i<2; i++) {
    aux = cube[0][3];
    cube[0][3] = cube[0][2];
    cube[0][2] = cube[3][3];
    cube[3][3] = cube[3][2];
    cube[3][2] = cube[4][3];
    cube[4][3] = cube[4][2];
    cube[4][2] = cube[1][3];
    cube[1][3] = cube[1][2];
    cube[1][2] = aux;
  }
  aux = cube[5][1];
  cube[5][1] = cube[5][2];
  cube[5][2] = cube[5][3];
  cube[5][3] = cube[5][0];
  cube[5][0] = aux;
}

void move2rev()
{
  for (i=0; i<2; i++) {
    aux = cube[0][3];
    cube[0][3] = cube[1][2];
    cube[1][2] = cube[1][3];
    cube[1][3] = cube[4][2];
    cube[4][2] = cube[4][3];
    cube[4][3] = cube[3][2];
    cube[3][2] = cube[3][3];
    cube[3][3] = cube[0][2];
    cube[0][2] = aux;
  }
  aux = cube[5][1];
  cube[5][1] = cube[5][0];
  cube[5][0] = cube[5][3];
  cube[5][3] = cube[5][2];
  cube[5][2] = aux;
}

void move3()
{
  for (i=0; i<2; i++) {
    aux = cube[2][3];
    cube[2][3] = cube[2][2];
    cube[2][2] = cube[0][0];
    cube[0][0] = cube[0][3];
    cube[0][3] = cube[5][2];
    cube[5][2] = cube[5][1];
    cube[5][1] = cube[4][2];
    cube[4][2] = cube[4][1];
    cube[4][1] = aux;
  }
  aux = cube[1][1];
  cube[1][1] = cube[1][2];
  cube[1][2] = cube[1][3];
  cube[1][3] = cube[1][0];
  cube[1][0] = aux;
}

void move3rev()
{
  for (i=0; i<2; i++) {
    aux = cube[2][3];
    cube[2][3] = cube[4][1];
    cube[4][1] = cube[4][2];
    cube[4][2] = cube[5][1];
    cube[5][1] = cube[5][2];
    cube[5][2] = cube[0][3];
    cube[0][3] = cube[0][0];
    cube[0][0] = cube[2][2];
    cube[2][2] = aux;
  }
  aux = cube[1][1];
  cube[1][1] = cube[1][0];
  cube[1][0] = cube[1][3];
  cube[1][3] = cube[1][2];
  cube[1][2] = aux;
}

void move4()
{
  for (i=0; i<2; i++) {
    aux = cube[2][0];
    cube[2][0] = cube[2][1];
    cube[2][1] = cube[0][1];
    cube[0][1] = cube[0][2];
    cube[0][2] = cube[5][3];
    cube[5][3] = cube[5][0];
    cube[5][0] = cube[4][3];
    cube[4][3] = cube[4][0];
    cube[4][0] = aux;
  }
  aux = cube[3][1];
  cube[3][1] = cube[3][0];
  cube[3][0] = cube[3][3];
  cube[3][3] = cube[3][2];
  cube[3][2] = aux;
}

void move4rev()
{
  for (i=0; i<2; i++) {
    aux = cube[2][0];
    cube[2][0] = cube[4][0];
    cube[4][0] = cube[4][3];
    cube[4][3] = cube[5][0];
    cube[5][0] = cube[5][3];
    cube[5][3] = cube[0][2];
    cube[0][2] = cube[0][1];
    cube[0][1] = cube[2][1];
    cube[2][1] = aux;
  }
  aux = cube[3][1];
  cube[3][1] = cube[3][2];
  cube[3][2] = cube[3][3];
  cube[3][3] = cube[3][0];
  cube[3][0] = aux;
}

void move5()
{
  for (i=0; i<2; i++) {
    aux = cube[2][3];
    cube[2][3] = cube[2][0];
    cube[2][0] = cube[3][1];
    cube[3][1] = cube[3][2];
    cube[3][2] = cube[5][0];
    cube[5][0] = cube[5][1];
    cube[5][1] = cube[1][3];
    cube[1][3] = cube[1][0];
    cube[1][0] = aux;
  }
  aux = cube[4][1];
  cube[4][1] = cube[4][0];
  cube[4][0] = cube[4][3];
  cube[4][3] = cube[4][2];
  cube[4][2] = aux;
}

void move5rev()
{
  for (i=0; i<2; i++) {
    aux = cube[2][3];
    cube[2][3] = cube[1][0];
    cube[1][0] = cube[1][3];
    cube[1][3] = cube[5][1];
    cube[5][1] = cube[5][0];
    cube[5][0] = cube[3][2];
    cube[3][2] = cube[3][1];
    cube[3][1] = cube[2][0];
    cube[2][0] = aux;
  }
  aux = cube[4][1];
  cube[4][1] = cube[4][2];
  cube[4][2] = cube[4][3];
  cube[4][3] = cube[4][0];
  cube[4][0] = aux;
}

void move6()
{
  for (i=0; i<2; i++) {
    aux = cube[2][2];
    cube[2][2] = cube[2][1];
    cube[2][1] = cube[3][0];
    cube[3][0] = cube[3][3];
    cube[3][3] = cube[5][3];
    cube[5][3] = cube[5][2];
    cube[5][2] = cube[1][2];
    cube[1][2] = cube[1][1];
    cube[1][1] = aux;
  }
  aux = cube[0][1];
  cube[0][1] = cube[0][2];
  cube[0][2] = cube[0][3];
  cube[0][3] = cube[0][0];
  cube[0][0] = aux;
}

void move6rev()
{
  for (i=0; i<2; i++) {
    aux = cube[2][2];
    cube[2][2] = cube[1][1];
    cube[1][1] = cube[1][2];
    cube[1][2] = cube[5][2];
    cube[5][2] = cube[5][3];
    cube[5][3] = cube[3][3];
    cube[3][3] = cube[3][0];
    cube[3][0] = cube[2][1];
    cube[2][1] = aux;
  }
  aux = cube[0][1];
  cube[0][1] = cube[0][0];
  cube[0][0] = cube[0][3];
  cube[0][3] = cube[0][2];
  cube[0][2] = aux;
}
