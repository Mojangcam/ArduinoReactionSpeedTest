#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int g_beforeData = 0;
unsigned long startTime, endTime;
bool isRun = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(7, INPUT);
  pinMode(2, INPUT);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long randTime = random(3, 6) * 1000;
  lcd.setCursor(0, 0);
  lcd.print("Press Right BTN");
  Serial.println(digitalRead(7));
  if (digitalRead(7)){
    isRun = true;
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 0);
    lcd.print("Ready?");
    delay(2000);
    lcd.clear();
    unsigned long asyncStartTime = millis();
    while (true){
      unsigned long asyncEndTime = millis();
      if (asyncEndTime - asyncStartTime > randTime){
        break;
      }
      else{
        if (digitalRead(2)){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("YOU LOSE");
          delay(3000);
          isRun = false;
        }
      }
    }
    if (isRun){
      lcd.setCursor(0, 0);
      lcd.print("NOW!!!!!");
      startTime = millis();
      while (isRun){
        if (digitalRead(2)){
          endTime = millis();
          unsigned long result = endTime - startTime;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(String() + F("Your Time : ") + result);
          lcd.setCursor(0, 1);
          if (result < 150){
            lcd.print("YOU ARE GOD!");
          }
          else if(result < 200){
            lcd.print("YOU ARE PRO!");
          }
          else if(result < 300){
            lcd.print("YOU ARE NORMAL");
          }
          else {
            lcd.print("ARE YOU BABY?");
          }
          delay(5000);
          lcd.clear();
          break;
        }
      }
    }
  }
}
