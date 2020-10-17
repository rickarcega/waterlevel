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


  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();

}

void loop() {

  int cmMsec;
  long perc;
  long litersAvailable = 0;

  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);


  perc = ((50 - cmMsec ) * 100) / 40;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Caixa AG:   ");
  lcd.setCursor(0, 1);
  lcd.print("Litros Dis: ");

  //litersAvailable = (660 * int(perc)) / 100; //660 total ammount of two water boxes.

  litersAvailable = (perc * 660) / 100;

  long litersAvailableAux = 660 - ((litersAvailable - 660) * -1);

  lcd.print(litersAvailableAux);
  lcd.print("L");

  if (perc > 300 || perc < 0
  && litersAvailableAux > 660 || litersAvailableAux < 0) {
    lcd.setCursor(9, 0);
    lcd.print(" - - -");

    lcd.setCursor(11, 1);
    lcd.print(" - -  ");
    
  } else {
    lcd.setCursor(9, 0);
    lcd.print("   ");
    lcd.print(perc);
    lcd.print("%" );
  }

  delay(2000);

}
