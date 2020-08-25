#include <Adafruit_MLX90614.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET  4
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire, OLED_RESET);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define ir 8
#define relay 3

void setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("   SMART     DOORBELL");
  display.display();

  pinMode(ir,INPUT);
  pinMode(relay, OUTPUT);

  mlx.begin();
}

void loop(){
  delay(500);
  if(digitalRead(ir) == LOW){
    float temp = mlx.readObjectTempC() + 4;
    if(temp < 38) {
    display.clearDisplay();
      display.setCursor(0,0);
      display.print("Temp:");display.print(temp);display.print(" !WELCOME!");
      display.display();
      digitalWrite(relay,HIGH);
    } else{
      digitalWrite(relay, LOW);
    display.clearDisplay();
      display.setCursor(0,0);
      display.print("HIGH TEMP! GO AWAY!");
      display.display();
      }
  } else {
    digitalWrite(relay,LOW);
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("   SMART     DOORBELL");
    display.display();
  }
 
}
