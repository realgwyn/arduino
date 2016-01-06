#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <dht.h>

dht DHT;
#define DHT11_PIN 3


LiquidCrystal_I2C lcd(0x27,16,2);
String MSG_TEMP1 = "Temp: ";
String MSG_TEMP2 = " C    ";
char message0[17] = "                ";

void setup() {
  
  Serial.begin(9600);
  Serial.println("Starting LCD Temperature Detector...");
  
  lcd.init();    
  lcd.backlight();
  lcd.home();
  
  lcd.setCursor(0, 0);
  print16(message0);
  lcd.setCursor(0, 1);
  print16(message0);

}

void loop() {
  int chk = DHT.read11(DHT11_PIN);
  double temperature = DHT.temperature;
  String temperatureStr = String(temperature);
  
  lcd.setCursor(0, 0);
  printString(MSG_TEMP1);
  printString(temperatureStr);
  printString(MSG_TEMP2);
 
  lcd.setCursor(0, 1);
  if(temperature<12){
    print16("KURWA ALE ZIMNO!");
  } else if(temperature<14){
    print16("Napierdala zlem!");
  } else if(temperature<16){
    print16("Ale pizga!      ");
  } else if(temperature<18){
     print16("Zimno mi...     ");
  } else if(temperature<19){
    print16("Troche chlodno  ");
  } else if(temperature<23){
    print16("Jest idealnie =)");
  } else if(temperature<26){
    print16("Ale cieplutko   ");
  } else if(temperature<28){
    print16("Ale grzeje!     ");
  } else {
    print16("KURWA JAKI UPAL!");
  }

  delay(500);
}

void printString(String str){
  int i;
  for(i=0;i<sizeof(str)-1;i++){
    lcd.print(str[i]);
  }
}

void print16(char string[]){
  int i;
  for(i=0;i<16;i++){
    lcd.print(string[i]);
  }
}
