/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */
#define RELAY1  7   

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
   pinMode(RELAY1, OUTPUT);  
   Serial.begin(9600);
   digitalWrite(RELAY1,LOW); 
   delay(50);
   digitalWrite(RELAY1,HIGH); 
   delay(50);
   digitalWrite(RELAY1,LOW); 
   delay(300);
   Serial.println("\n\nCalibrating Treshold...");
}

int sound;
int treshold = 802;
int filter = 2;

String msg = "";
double sum = 0;
double average = 0;
int count=0;

// the loop function runs over and over again forever
void loop() {

  if(count < 1000){
    sum += analogRead(5);
    count++;
    delay(1);
    
    if(count==1000){
    digitalWrite(RELAY1,HIGH); 
      Serial.println("Average: ");
      average = sum / count;
      Serial.println(average);
      delay(100); 
      treshold = (int)average;
      Serial.println("Treshold: ");
      Serial.println(treshold);
        digitalWrite(RELAY1, LOW);  
      delay(100); 
      Serial.println("Hi-Lo Pass Filter: ");
      Serial.println(filter);
      digitalWrite(RELAY1,HIGH); 
      delay(500); 
    }
  }else{
    sound = analogRead(5); 
    if(sound > treshold + filter || sound < treshold - filter){
      Serial.println(sound);
      digitalWrite(RELAY1,HIGH);
      delay(50); 
      digitalWrite(RELAY1,LOW); 
      delay(20); 
      
      
      
    }
    delay(1); 
  }

/*
  if(sound < tresholdNegative || sound > tresholdPositive){
  
  digitalWrite(RELAY1,LOW);     
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(RELAY1,HIGH);   
  delay(30);              // wait for a second
  }else{
    delay(100);
  }
*/

}
