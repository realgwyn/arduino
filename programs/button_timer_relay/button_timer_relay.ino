



#include <LiquidCrystal.h>
#include <Time.h>
#include <DS1302RTC.h>

#define SCK_PIN 4
#define IO_PIN 3
#define RST_PIN 2  

#define RELAY1 7

#define BUTTON 8

// Init the DS1302
// Set pins:  CE, IO,CLK
DS1302RTC RTC(RST_PIN, IO_PIN, SCK_PIN);

// Optional connection for RTC module
#define DS1302_GND_PIN 33
#define DS1302_VCC_PIN 35

void setup()
{
  Serial.begin(9600);

  pinMode(BUTTON, INPUT);
  pinMode(RELAY1, OUTPUT);
  
  // Activate RTC module
  digitalWrite(DS1302_GND_PIN, LOW);
  pinMode(DS1302_GND_PIN, OUTPUT);

  digitalWrite(DS1302_VCC_PIN, HIGH);
  pinMode(DS1302_VCC_PIN, OUTPUT);

  Serial.println("RTC activated");

  

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
  

  // Setup Time library 
  /* 
  Serial.println("RTC Sync");
  setSyncProvider(RTC.get); // the function to get the time from the RTC
  if(timeStatus() == timeSet)
    Serial.println(" Ok!");
  else
    Serial.println(" FAIL!");
*/
 

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

boolean lightChanged;
boolean buttonLightSwitch;
boolean lightOn;
boolean canTimerSwitchOn;
boolean canTimerSwitchOff;
int buttonValue;
int msPassed;

void loop(){

  // Display time centered on the upper line

// Wait approx 1 sec and check for button press action
//delay(1000);

/* 
  //DEBUG BUTTON
  buttonValue = digitalRead(BUTTON);
  if(buttonValue == HIGH){
    Serial.println("BUTTON HIGH");
  }else{
    Serial.println("BUTTON LOW");
  }
*/

    buttonValue = digitalRead(BUTTON);
    if(buttonValue == HIGH && !lightChanged){
      Serial.println("Button pressed!");
      lightChanged = true;
      lightOn = !lightOn;
    }
    
    if(buttonValue == LOW){
      lightChanged = false;
    }
    
   
  

  //If next day passed, timer can switch on and off the light again
  //if(hour() == 0 && minute() == 0 && second() < 2){
  if( second() == 0){
    
    canTimerSwitchOn = true;
    canTimerSwitchOff = true;
  }

  if(second() > 10 && canTimerSwitchOn){
    Serial.println("10 seconds passed, turning light ON!");
    lightOn = true;
    canTimerSwitchOn = false;
  }

  if(second() > 15 && canTimerSwitchOff){
    Serial.println("15 seconds passed, turning light OFF!");
    lightOn = false;
    canTimerSwitchOff = false;
  }
  
  if(lightOn){
    turnLightOn();
  }else{
    turnLightOff();
  }

 delay(10);
 msPassed += 10;
  if(msPassed == 1000){
     print2digits(hour());
 Serial.print(":");
 print2digits(minute());
 Serial.print(":");
 print2digits(second());
 Serial.println("");
    msPassed = 0;
    }

}

void turnLightOn(){

  digitalWrite(RELAY1, 0);
}

void turnLightOff(){

  digitalWrite(RELAY1, 1); 
}

void print2digits(int number) {
  // Output leading zero
  if (number >= 0 && number < 10) {
    Serial.print('0');
  }
  Serial.print(number);
}
