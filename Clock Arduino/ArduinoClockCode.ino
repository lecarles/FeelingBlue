#include <SoftwareSerial.h>
#include <AccelStepper.h>

SoftwareSerial ss1(10, 13); // RX, TX //A0


// Define a stepper and the pins it will use
AccelStepper hand1(AccelStepper::DRIVER, 9, 8);
AccelStepper hand2(AccelStepper::DRIVER, 6, 7);
AccelStepper hand3(AccelStepper::DRIVER, 4, 5);


String string1 = "";
String string2 = "";
String string3 = "";
int value1 = 0;
int value2 = 0;
int value3 = 0;


void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(38400);
  ss1.begin(38400);


    hand1.setMaxSpeed(3000);
    hand2.setMaxSpeed(2000);
    hand3.setMaxSpeed(2000);
  
    hand1.setAcceleration(2000);
    hand2.setAcceleration(800);
    hand3.setAcceleration(500);
  

  //PHYSICAL 0 POSITION IS HANDS POINTING AT RED O'CLOCK -> MAKE SURE ALL NEEDLES ARE IN THAT POSITION WHEN STARTING

}

void loop()
{

  ss1.listen();
  delay(2);
  if ( ss1.available() ) {
    Serial.print("received value:  ");
    String inString = ss1.readString();
    char hand = inString.charAt(0);

    if ( hand == '1') {
      string1 = inString.substring( 1 );
      value1 = string1.toInt();
      Serial.println(value1);
      value1 = map(value1, 0, 359, 0, 1600);
      Serial.println("I have mapped:");
      Serial.println(value1);
    }

    if ( hand == '2') {
      string2 = inString.substring( 1 );
      value2 = string2.toInt();
      Serial.println(value2);
      value2 = map(value2, 0, 359, 0, 1600);
      Serial.println("I have mapped:");
      Serial.println(value2);
    }

    if ( hand == '3') {
      string3 = inString.substring( 1 );
      value3 = string3.toInt();
      Serial.println(value3);
      value3 = map(value3, 0, 359, 0, 1600);
      Serial.println("I have mapped:");
      Serial.println(value3);
    }
  }


  if (hand1.distanceToGo() == 0)
  {
    delay(5);
    hand1.moveTo(value1);
  }
  if (hand2.distanceToGo() == 0)
  {
    delay(5);
    hand2.moveTo(value2);
  }
  if (hand3.distanceToGo() == 0)
  {
    delay(5);
    hand3.moveTo(value3);
  }
  hand1.run();
  hand2.run();
  hand3.run();
}


