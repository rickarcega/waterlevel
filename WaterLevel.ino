#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
#include <Ultrasonic.h>

#define pino_trigger 9
#define pino_echo 8
Ultrasonic ultrasonic(pino_trigger, pino_echo);

#define endereco  0x3F // Endereços comuns: 0x27, 0x3F
#define colunas   16
#define linhas    2

LiquidCrystal_I2C lcd(endereco, colunas, linhas);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear(); 
}

void loop() {

  int cmMsec;
  int perc;
 
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

 
 // 16  - 0
 // 22  - 10
 // 33  - 50
 // 83  - 100
  
  perc = ((50 - cmMsec ) * 100) / 40;

  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("C.A 01: " );
  lcd.setCursor(0, 1); 
  lcd.print("C.A 02: " );
  lcd.print(" -- - --");
  
  lcd.setCursor(9, 0); 
                
    
  if(perc > 300 || perc < 0){
    lcd.print("-- - --");
  }else{

    lcd.print("- ");
    lcd.print(perc);
    lcd.print("%" );
    lcd.print(" -");
  }
  
  
  delay(3000); 

}
