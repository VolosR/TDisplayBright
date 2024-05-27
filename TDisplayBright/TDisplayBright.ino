#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

//buttons
int right=14;
int left=0;
bool leftPressed=0;
bool rightPressed=0;
unsigned short colors[2]={TFT_MAGENTA,TFT_PURPLE};

int bright=40;
int bar=0;

void setup() {
  pinMode(left,INPUT_PULLUP);
  pinMode(right,INPUT_PULLUP);

  tft.init();
  tft.fillScreen(TFT_BLACK);
  sprite.createSprite(170,320);

     //brightness
     ledcSetup(0, 10000, 8);
     ledcAttachPin(38, 0);
     ledcWrite(0, bright);
}

void draw()
  {
    sprite.fillSprite(TFT_BLACK); 
    sprite.setTextDatum(4);
    sprite.setTextColor(TFT_WHITE,TFT_BLACK);
    sprite.drawString("BRIGHTNESS",85,20,2);
    sprite.drawRect(30,35,110,65,TFT_WHITE);
    sprite.drawString(String(bright),85,70,7);

    //draw graph
    sprite.drawRect(30,110,110,150,TFT_WHITE);
    for(int i=0;i<15;i++)
    {
      if(i<bar)
       sprite.fillRect(40,246-(i*9),90,5,TFT_MAGENTA);
      else
       sprite.fillRect(40,246-(i*9),90,5,TFT_PURPLE);;
    }

    //draw Buttons
    sprite.fillSmoothRoundRect(10, 280, 70, 34,3, colors[leftPressed]);
    sprite.setTextColor(TFT_WHITE,colors[leftPressed]);
    sprite.drawString("DEC",45,300,4);

    sprite.fillSmoothRoundRect(90, 280, 70, 34,3, colors[rightPressed]);
    sprite.setTextColor(TFT_WHITE,colors[rightPressed]);
    sprite.drawString("INC",125,300,4);

    sprite.pushSprite(0,0);
  }

void loop() {

  bar=map(bright,0,255,0,15);
 
  if(digitalRead(right)==0 && bright<255)
    {
      bright++;
      ledcWrite(0, bright);
      rightPressed=1;
    } else {rightPressed=0;}

    if(digitalRead(left)==0 && bright>1)
    {
      bright--;
      ledcWrite(0, bright);
      leftPressed=1;
    } else {leftPressed=0;}

  draw();
}
