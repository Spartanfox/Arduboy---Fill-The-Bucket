#include <Arduboy2.h>

Arduboy2 arduboy;

struct Particle{
  byte x;
  byte y;
};
//can probably change all of these for booleans honestly
//but modulus is going to come in handy a lot 
int8_t x_vol;
int8_t y_vol;
int8_t x_brownian;
int8_t y_brownian;
byte brown;

struct Particle p[300];

void setup() {
  arduboy.begin();

  startGame();
  arduboy.clear();
}

void loop() {
    if (!(arduboy.nextFrameDEV())){
      brown++;
      return;
    }
    arduboy.pollButtons();

    if(arduboy.pressed(B_BUTTON))startGame();
    
    x_vol = 0;
    y_vol = 127;

    if(arduboy.pressed(LEFT_BUTTON)){
        x_vol = -128;
    }
    if(arduboy.pressed(RIGHT_BUTTON)){
        x_vol = 127;
    }
    if(arduboy.pressed(UP_BUTTON)){
        y_vol = -128;
    }else if(x_vol!=0){y_vol = 0;}
    
    for(int i = 0; i < sizeof(p); i++){
      arduboy.drawPixel(p[i].x,p[i].y,BLACK);
      
      x_brownian = x_vol;
      if(x_vol == 0)
        x_brownian = (brown++%2==0)?-1:1;
      y_brownian = y_vol;
      if(y_vol == 0)
        y_brownian = (brown++%2==0)?-1:1;

      if(x_brownian>0){
        if(canMove(p[i].x+1,p[i].y)){
          p[i].x++;
        }
      }else{
        if(canMove(p[i].x-1,p[i].y)){
          p[i].x--;
        }
      }
      if(y_brownian>0){
        if(canMove(p[i].x,p[i].y+1)){
          p[i].y++;
        }
      }else{
        if(canMove(p[i].x,p[i].y-1)){
          p[i].y--;
        }
      }

      arduboy.drawPixel(p[i].x,p[i].y,WHITE);
    }
    arduboy.clear();
    for(int i = 0; i < sizeof(p); i++){
      arduboy.drawPixel(p[i].x,p[i].y,WHITE);
    }
    
    drawMess(0,0);
    drawMess(30,2);
    drawBucket(0,0);
    drawBucket(104,0);
    
    
    arduboy.display();
}
void startGame(){
  for(int i = 0; i < sizeof(p); i++){
    p[i].x = 10;
    p[i].y = 30;
  }
}
void drawMess(int8_t x,int8_t y){
    arduboy.drawLine(70+x,55+y,30+x,y);
    arduboy.drawLine(40+x,45+y,70+x,55+y);
}
void drawBucket(int8_t x,int8_t y){
    arduboy.drawLine(1+x,35+y,3+x,61+y);
    arduboy.drawLine(23+x,35+y,21+x,61+y);
    arduboy.drawLine(3+x,61+y,21+x,61+y);
}

boolean canMove(byte x, byte y){
  return !(arduboy.getPixel(x,y)==WHITE||x<0||y<0||y>63||x>127);
}
