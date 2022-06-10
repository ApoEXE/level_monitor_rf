#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

RH_ASK driver;
unsigned int refresh = 0;
unsigned long start = millis();
unsigned long start2 = millis();
void setup()
{

  Serial.begin(9600);  // Debugging only
  Serial.println("test receiver");
  if (!driver.init())
    Serial.println("init failed");
  lcd.begin(16, 2);
}

void loop()
{

  uint8_t buf[3] = {0, 0, 0};
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    int i;
    // Message with a good checksum received, dump it.
    Serial.print("distancia: ");
    buf[3] = 0;
    Serial.print((char*)buf);
    Serial.print(" cm  ");
    refresh = 0;
    lcd.setCursor(0, 0);
    lcd.print("distance: ");
    lcd.print((char*)buf);
    lcd.print(" cm");

  }
  if (millis() - start >= 1000) {
    
    start = millis();
    refresh += 1;
    Serial.print("link refresh: ");
    Serial.print(refresh);
    Serial.println(" sec ");
    lcd.setCursor(0, 1);

    lcd.print("link: ");
    lcd.print(refresh);
    lcd.print(" sec");
  }

     if (millis() - start2 >= 60000) {
      lcd.clear();
      start2 = millis();
      } 

}
