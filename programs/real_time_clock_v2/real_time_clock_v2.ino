

// Timur Maksiomv 2014
//
// A quick demo of how to use DS1302-library to make a quick
// clock using a DS1302 and a 16x2 LCD.
//
// I assume you know how to connect the DS1302 and LCD.
// DS1302:  CE pin    -> Arduino Digital 27
//          I/O pin   -> Arduino Digital 29
//          SCLK pin  -> Arduino Digital 31
//          VCC pin   -> Arduino Digital 33
//          GND pin   -> Arduino Digital 35
//
// LCD:     DB7       -> Arduino Digital 7
//          DB6       -> Arduino Digital 6 
//          DB5       -> Arduino Digital 5
//          DB4       -> Arduino Digital 4
//          E         -> Arduino Digital 9
//          RS        -> Arduino Digital 8

#include <LiquidCrystal.h>
#include <Time.h>
#include <DS1302RTC.h>

#define SCK_PIN 4
#define IO_PIN 3
#define RST_PIN 2  

// Init the DS1302
// Set pins:  CE, IO,CLK
//DS1302RTC RTC(27, 29, 31);
DS1302RTC RTC(RST_PIN, IO_PIN, SCK_PIN);

// Optional connection for RTC module
#define DS1302_GND_PIN 33
#define DS1302_VCC_PIN 35

void setup()
{
  Serial.begin(9600);
  // Setup LCD to 16x2 characters
  

  // Activate RTC module
  digitalWrite(DS1302_GND_PIN, LOW);
  pinMode(DS1302_GND_PIN, OUTPUT);

  digitalWrite(DS1302_VCC_PIN, HIGH);
  pinMode(DS1302_VCC_PIN, OUTPUT);

  Serial.println("RTC activated");

  delay(500);

  // Check clock oscillation  
  /*
  if (RTC.haltRTC())
    Serial.println("Clock stopped!");
  else
    Serial.println("Clock working.");
*/
  // Check write-protection
/*
  if (RTC.writeEN())
    Serial.println("Write allowed.");
  else
    Serial.println("Write protected.");
*/
  delay ( 2000 );

  // Setup Time library 
  /* 
  Serial.println("RTC Sync");
  setSyncProvider(RTC.get); // the function to get the time from the RTC
  if(timeStatus() == timeSet)
    Serial.println(" Ok!");
  else
    Serial.println(" FAIL!");
*/
  delay ( 2000 );

/**
 * SETUP CURRENT TIME:
*/
/*
  time_t t;
  tmElements_t tm;
  tm.Hour=19;
  tm.Minute=40;
  tm.Second=0;
  t = makeTime(tm);
 setTime(t);
  */  
}

void loop(){

  // Display time centered on the upper line
  
 print2digits(hour());
 Serial.print(":");
 print2digits(minute());
 Serial.print(":");
 print2digits(second());
 Serial.println("");

  delay ( 1000 ); // Wait approx 1 sec
}

void print2digits(int number) {
  // Output leading zero
  if (number >= 0 && number < 10) {
    Serial.print('0');
  }
  Serial.print(number);
}
