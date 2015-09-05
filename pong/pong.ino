//this pong version for the arduino 2.4" TFTLCD screen is made by robin paret.
//a 12 year old arduino fan. feel free to add new features and remix the sketch!

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h> //touchscreen library

#if defined(__SAM3X8E__) //some weird stuff to setup everything
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

int placeb1 = 110; //position variables for the bars
int placeb2 = 110;
int offset = 1; //the angle where the brick needs to be pushed
int placerectx = 90; //position variables for the brick
int placerecty = 110;
int player = 1; //variable for the indicator of who can control his bar
int point1 = 0; //variables for counting the point each player has scored
int point2 = 0;
//setting up all the pins of the shield
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A1 // must be an analog pin, use "An" notation!
#define YM 6   // can be a digital pin
#define XP 7  // can be a digital pin

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940


TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0xFFFF   
#define	BLUE    0xFFE0   
#define	RED     0x07FF   
#define	GREEN   0xF81F   
#define CYAN    0xF800   
#define MAGENTA 0x07E0   
#define YELLOW  0x001F   
#define WHITE   0x0000   


Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


// variables that time and delay the moving of the brick but not the rest of the program, i had this idea from the blinkwithoutdelay sketch in the examples
int State = LOW;            
unsigned long previousMillis = 0;
// constants won't change :
const long interval = 15;

void setup() {
 
  Serial.begin(9600);
  
  
  tft.reset();
  
  uint16_t identifier = 0x9341;
  //weird stuff for the setup, dont delete all of this, or it wont work
  if(identifier == 0x9325) {
   
  } else if(identifier == 0x9328) {
   
  } else if(identifier == 0x7575) {
   
  } else if(identifier == 0x9341) {
  
  } else if(identifier == 0x8357) {
   
  } else {
    
    return;
  }

  tft.begin(identifier);
  //fill the screen black
  tft.fillScreen(BLACK);
  pinMode(13, OUTPUT);
  //setup the pallets, brick and indicators
  tft.fillRect(0, 0, 30, 30, RED);
  tft.fillRect(210, 0, 30, 30, RED);
  tft.fillRect(0, 290, 30, 30, GREEN);
  tft.fillRect(210, 290, 30, 30, GREEN);
  tft.fillRect(placeb1, 0, 40, 10, WHITE); 
  tft.fillRect(placeb2, 310, 40, 10, WHITE);
}
//this is for the touchscreen, you can change the pressure preferences to whatever you like
#define MINPRESSURE 10
#define MAXPRESSURE 1000
void loop()
{
 
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  
  
    
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) { //an if statement that runs when the touchscreen is pressed
    Serial.println("delaydelaydelay"); //a weird way of delaying stuff but if it wasnt here, the bar movement would be incontrollable
    
    
    if (p.x >= 500 && p.y >= 500 && player == 2){ // code for the pallet movements
      
      tft.fillRect(placeb1, 0, 40, 10, BLACK);
      if (placeb1 > 42){
      placeb1 = placeb1 - 3;
      }
     tft.fillRect(placeb1, 0, 40, 10, WHITE);  
      }
    if (p.x <= 500 && p.y >= 500 && player == 2){
      
      tft.fillRect(placeb1, 0, 40, 10, BLACK);
      if (placeb1 < 158){
      placeb1 = placeb1 + 3;
      }
     tft.fillRect(placeb1, 0, 40, 10, WHITE);  
      }
    if (p.x >= 500 && p.y <= 500 && player == 1){
      
      tft.fillRect(placeb2, 310, 40, 10, BLACK);
      if (placeb2 > 42){
      placeb2 = placeb2 - 3;
      }
     tft.fillRect(placeb2, 310, 40, 10, WHITE);  
      }
    if (p.x <= 500 && p.y <= 500 && player == 1){
      
      tft.fillRect(placeb2, 310, 40, 10, BLACK);
      if (placeb2 < 158){
      placeb2 = placeb2 + 3;
      }
      tft.fillRect(placeb2, 310, 40, 10, WHITE);
      }
    }
  if(placerecty <= 3){ //if the brick is too far away to push back from the pallet, end the game and tell the score
    tft.fillRect(placerectx, placerecty, 10, 10, BLACK);
    point2 = point2 + 1;
    Serial.print("points: ");
    Serial.print(point1);
    Serial.print(" | ");
    Serial.println(point2);
    placerectx = 90;
    placerecty = 110;
    offset = 1;
    player = 1;
    tft.fillRect(0, 0, 30, 30, RED); //change the indicators for who is controlling his pallet
     tft.fillRect(210, 0, 30, 30, RED);
     tft.fillRect(0, 290, 30, 30, GREEN);
     tft.fillRect(210, 290, 30, 30, GREEN);
    delay(2500);
    }
  if(placerecty >= 317){ //if the brick is too far away to push back from the pallet, end the game and tell the score
    tft.fillRect(placerectx, placerecty, 10, 10, BLACK);
    point1 = point1 + 1;
    Serial.print("points: ");
    Serial.print(point1);
    Serial.print(" | ");
    Serial.println(point2);
    placerectx = 90;
    placerecty = 110;
    offset = 1;
    player = 1;
    tft.fillRect(0, 0, 30, 30, RED); //change the indicators for who is controlling his pallet
     tft.fillRect(210, 0, 30, 30, RED);
     tft.fillRect(0, 290, 30, 30, GREEN);
     tft.fillRect(210, 290, 30, 30, GREEN);
    delay(2500);
    
    }
    
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) { //code for moving the brick and delaying it without delaying the rest of the sketch, it uses a function called millis() and tells the sketch how many milliseconds the arduino board was started ago
    previousMillis = currentMillis;
    if (State == LOW)
      State = HIGH;
    else
      State = LOW;
    if(offset == 1 ){ // all the code for moving the brick
     
     tft.fillRect(placerectx, placerecty, 10, 10, BLACK);
     placerectx = placerectx + 2;
     placerecty = placerecty + 1;
     tft.fillRect(placerectx, placerecty, 10, 10, WHITE);
     
     }
    if(offset == 2){
      tft.fillRect(placerectx, placerecty, 10, 10, BLACK);
      placerectx = placerectx - 2;
      placerecty = placerecty + 2;
      tft.fillRect(placerectx, placerecty, 10, 10, WHITE);
      }
    if(offset == 5){
      tft.fillRect(placerectx, placerecty, 10, 10, BLACK);
      placerectx = placerectx + 2;
      placerecty = placerecty - 2;
      tft.fillRect(placerectx, placerecty, 10, 10, WHITE);
      }
    if(offset == 6){
      tft.fillRect(placerectx, placerecty, 10, 10, BLACK);
      placerectx = placerectx - 2;
      placerecty = placerecty - 2;
      tft.fillRect(placerectx, placerecty, 10, 10, WHITE);
      }
    if(placerectx >= 200){ //code for the bouncing of the bars
      if (offset == 1){
        offset = 2;
        }
      if (offset == 5){
        offset = 6;
        }
    }
    if(placerectx <= 40 && placerecty){
      if (offset == 2){
        offset = 1;
        }
      if (offset == 6){
        offset = 5;
        }
    }
    if(placerectx >= placeb2 - 9 && placerectx <= placeb2 + 48 && placerecty >= 300 && placerecty <= 313){ //code for seeing if the brick hit the pallet and then changes the offset of the brick
     if(offset == 1){
       offset = 5;
       }
     if(offset == 2){
       offset = 6;
       }
     player = 2;
     tft.fillRect(0, 0, 30, 30, GREEN);//change the indicators for who is controlling his pallet
     tft.fillRect(210, 0, 30, 30, GREEN);
     tft.fillRect(0, 290, 30, 30, RED);
     tft.fillRect(210, 290, 30, 30, RED);
     }
    if(placerectx >= placeb1 - 9 && placerectx <= placeb1 + 48 && placerecty <= 10 && placerecty >= 7){
     if(offset == 5){
       offset = 1;
       }
     if(offset == 6){
       offset = 2;
       }
     tft.fillRect(0, 0, 30, 30, RED); //change the indicators for who is controlling his pallet
     tft.fillRect(210, 0, 30, 30, RED);
     tft.fillRect(0, 290, 30, 30, GREEN);
     tft.fillRect(210, 290, 30, 30, GREEN);
     player = 1;
     }

  }
 
 }

