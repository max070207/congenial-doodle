#include <LiquidCrystal.h>
#include <math.h>
#include <FastLED.h>

#define FIRST_KEY_PIN 6
#define KEY_COUNT 3
#define NUM_LEDS 16
#define DATA_PIN 7
#define DIODE_DROP 0.7
int LEDS_COUNT = 0;
long unsigned int time_in = 0;
long unsigned int time_in2 = 0;

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
CRGB leds[NUM_LEDS];

void setup() {
 lcd.clear();
 clearLed();
 int a = ReciveIntFromSerial();
 pinMode(4, INPUT_PULLUP);
 pinMode(5, INPUT_PULLUP);
 pinMode(6, INPUT_PULLUP);
 lcd.begin(16, 2);
 lcd.setCursor(0, 0);
 lcd.print("Press any button");
 lcd.setCursor(0, 1);
 lcd.print("to start");
 LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds, NUM_LEDS);
 LEDS.setBrightness(100);
 Serial.begin(115200);
 Serial.println("Press any button to start");
 clearLed();
}

void loop() {
 for (int i = 0; i < KEY_COUNT; ++i){
  int keyPin = i + FIRST_KEY_PIN;
 }
 if(digitalRead(4) == 0){
  double voltage = 0;
  for(register unsigned int i = 0; i < 100; i++){
   voltage += analogRead(A0) * 5.0 / 1023.0;
  }
  voltage /= 100;
  int volts = map(voltage*10, 240, 260, 255, 85);
  Serial.print("Voltage: "); Serial.println(voltage);
  show1screen(voltage, volts);
 }
 if(digitalRead(5) == 0){
  double temperature = 0;
  for(register unsigned int i = 0; i < 100; i++){
   float voltage = analogRead(A0) * 5.0 / 1023.0;
   temperature += 1.0 / (log(voltage / 2.5) / 4300.0 + 1.0 / 298.0) - 273.0;
  }
  temperature /= 100;
  int temp = map(temperature*10, 220, 300, 255, 85);
  Serial.print("Temperature: "); Serial.println(temperature);
  show2screen(temperature, temp);
 }
 if(digitalRead(6) == 0){
  double lightness = 0;
  for(register unsigned int i = 0; i < 100; i++){
   lightness += analogRead(A1);
  }
  lightness /= 100;
  int light = map(lightness, 500, 1023, 255, 85);
  Serial.print("Lightness: "); Serial.println(lightness);
  show3screen(lightness, light);
 }
 /*if (time_in < millis() + 6200){
  if (LEDS_COUNT > 2){
    LEDS_COUNT = 0;
  }
  switch (LEDS_COUNT)
  {
   case 0:
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Voltage: ");     
    lcd.setCursor(0, 1);
    lcd.print(voltage);    lcd.print(" V");
    AnimatedLed(volts, 200);
    break;
   case 1:
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature: ");     
    lcd.setCursor(0, 1);
    lcd.print(temperature);    lcd.print(" C");
    AnimatedLed(temp, 200);
    break;
   case 2:
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lightness: ");     
    lcd.setCursor(0, 1);
    lcd.print(lightness);    lcd.print(" L");
    AnimatedLed(light, 200);
    break;
  }
  time_in += 6200;
  LEDS_COUNT++;
 }*/
}
 
void clearLed(){
  for (int i = 0; i < NUM_LEDS; i++) leds [i] = CHSV(0, 0, 0);
}

void show1screen(float voltage, int volts){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");     
  lcd.setCursor(0, 1);
  lcd.print(voltage);    lcd.print(" V");
  SetStatusBarLed(volts, 20);
}

void show2screen(float temperature, int temp){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");     
  lcd.setCursor(0, 1);
  lcd.print(temperature);    lcd.print(" C");
  SetStatusBarLed(temp, 20);
}

void show3screen(float lightness, int light){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lightness: ");     
  lcd.setCursor(0, 1);
  lcd.print(lightness);    lcd.print(" L");
  SetStatusBarLed(light, 20);
}

void SetStatusBarLed(int color, int decay){
  clearLed();
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CHSV(color, 255, 255);
    delay(decay);
    FastLED.show();
  }
}

int ReciveIntFromSerial(){
  while(!Serial.available());
  int tmp = Serial.parseInt();
  if(Serial.read() == "\n");
  return tmp;
}
