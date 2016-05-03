
//Programm zum Testen der PWM-Module mit Initialisierung des Displays und der Sensoren

//--------------------------Defines-----------------------------------

//Motortreiber
#define stepPin   11
#define dirPin    13
#define ModePin1  8
#define ModePin2  10
#define ModePin3  12

//Themperatursensor Ansschlüsse
#define ktcSO  7
#define ktcCS  6
#define ktcCLK 5

//Button
#define buttonPin 2

//PWM
#define pwmheatPin 3
#define pwmcoolPin 9

//--------------------------Bibliotheken-------------------------------

//PID-Regler Library
#include "PID_v1.h"

//Display Library
#include "Adafruit_GFX.h"
#include "gfxfont.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4

//Temp Sensor Library
#include "max6675.h"

//--------------------------Variablen und Konstanten---------------------

//Display Logo
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

int a = 0;
int b = 0;

// Button Status
int buttonState = 0;  

//Sonstige
int firststart = 1;
//-------------------------Init-----------------------------------------

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,100,1,1, DIRECT);

//Oled Reset
Adafruit_SSD1306 display(OLED_RESET);

//Temperatursensor Initialisierung
MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

//----------------------------Funktionen------------------------------

void stepperstart(){

  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);
  TCCR2B = _BV(CS22);
  OCR2A = 100;
  //OCR2B = 50;

 }

void thempread(){

   
      delay(180);
      display.setTextSize(3);
      display.setTextColor(WHITE);
      display.setCursor(20,0);
      display.clearDisplay();
      display.println(ktc.readCelsius());
      display.setTextSize(1);
      display.setCursor(32,23);
      display.println("Temperatur");
      display.display();
      delay(1);
        
}

void stepperstop(){
  a=0;
 }

int readpin(){

  buttonState = digitalRead(buttonPin);
  return buttonState;
 }

void introtext(void) {
  display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(20,0);
      display.clearDisplay();
      display.println("Happy Chocolate");
      display.setTextSize(2);
      display.setCursor(30,15);
      display.println("Bereit..");
      display.display();
      delay(1);
  
 
}

void starttext(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(40,0);
  display.clearDisplay();
  display.println("Einschalten");
  display.display();
  delay(1);
 
}

void stoptext(void) {

     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(30,0);
     display.clearDisplay();
     display.println("schlafe..");
     display.setTextSize(2);
     display.setCursor(32,15);
     display.println("Bereit");
     display.display();
     delay(1);
 
}

void temptext(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(35,0);
  display.clearDisplay();
  display.println("starting..");
  display.display();
  delay(1);
 
}

void percentwrite (int pwrite){
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.clearDisplay();
  display.println(pwrite);
  display.setTextSize(1);
  display.setCursor(32,23);
  display.println("PWM Prozent");
  display.display();
  delay(1);
}

void setup() {
  
  //Serial begin für den Temp Sensor
  Serial.begin(9600);
  // give the MAX a little time to settle

  //-------Display---------
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
  introtext(); 
  delay(500);

  //-------Motortreiber Init-------
  // Direction & Step Pin als Ausgang
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  // Ports für Microsteps als Ausgang setzen
  pinMode(ModePin1,OUTPUT);
  pinMode(ModePin2,OUTPUT);
  pinMode(ModePin3,OUTPUT);

  // Set Ports für Microsteps
  digitalWrite(ModePin1,HIGH);
  digitalWrite(ModePin2,HIGH);
  digitalWrite(ModePin3,HIGH);

  
  // -------Button Init-------
  pinMode(buttonPin, INPUT);  


}

void loop() 
  {

 // Button Status auslesen
  buttonState = readpin();
   

 //Wenn Knopf gedrückt wirkd
  if(buttonState==HIGH)
  {
    if (firststart == 1)
    {
      firststart = 0;
      
    }
  }
}
