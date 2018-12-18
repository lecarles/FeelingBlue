# Feeling Blue
What shade of blue are you feeling?

## About the Project
This is an artistic-experimental IoT prejoect developed as part as the "easy pieces" MP Project "On The Internet Nobody Knows you0re a toaster", at KISD. 
More about the project and it's narrative can be found at its Behance Page.

## How it works

3 needles move over the colour the user selects on a website, with a slider. Each needle has its own site and is theoretically designed to be used by a different user. The value received by the slider at the web, hosted locally, went to a ESP8266 , that passed the value via Software Serial Com to an Arduino, in charge of mapping this values and making three stepper motors move. 

![Data Flow](https://github.com/lecarles/FeelingBlue/blob/master/Images/greatscheme.PNG)

I'll overview all of this and highlight some code snippets now.

### The Website

The website consits of a slider with values ranging from 0 to 359 changing the HUE value of the background. That same HUE is sent in the GET request every time the user releases his mouse button or stops touching the screen.

```
	slider.oninput = function() {
	  var value = 360 - this.value; //Quick fix: the slider shows colours on the opposite direction as the clock. 
	  document.body.style.backgroundColor = `hsl(${value},65%,60%)`;
	}

	slider.onmouseup = function() {
	  var xhr = new XMLHttpRequest();
		xhr.open('GET', `http://192.168.0.101/hand1/${this.value}`);
		xhr.send();
	}
```

Due to time limitations the website was simply copy pasted three times, one for each needle.

It was hosted on a local server powered by node.js. As WiFi network we used a little TP-LINK hotspot. 


### ESP8266

The ESP acts as a WiFi web server, using the code provided as an [example by Arduino](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiManualWebServer/WiFiManualWebServer.ino) as a basis.

The server isolates and stores in a string the value received via request from each hand website, then adds a number so the Arduino can  identify from which hand it came (as I will clarify later), and sends it via software serial to the arduino.

```
  if (req.indexOf("/hand1/") != -1) {
    Serial.print("Hand 1: ");
    int end = req.indexOf("HTTP") - 1;
    String s = req.substring(11, end); 
    s = "1" + s;
    val = s.toInt();
    Serial.println(val);
    Serial.println(s);
  }
```

### Arduino

The Arduino has to receive move three stepper motors from 0 to 360 degrees. The needles are supposed to be set on red manually (our reference hue = 0  value). These stepper motors are controlled by [One EasyDriver each](http://www.schmalzhaus.com/EasyDriver/Examples/EasyDriverExamples.html).

To control each motor separately and more easily, the [AccelStepper Library](http://www.airspayce.com/mikem/arduino/AccelStepper/) is used.

```
  ss1.listen();
  delay(2);
  if ( ss1.available() ) {
    Serial.print("received value:  ");
    String inString = ss1.readString();
    char hand = inString.charAt(0); //1, 2 or 3; depending on the needle.

    if ( hand == '1') {
      string1 = inString.substring( 1 );
      value1 = string1.toInt();
      Serial.println(value1);
      value1 = map(value1, 0, 359, 0, 1600);
      Serial.println("I have mapped:");
      Serial.println(value1);
    }
    
    if ( hand == '2') {
    ...
```

The code inside the loop function checks for software serial communication, gets the string and separates the first character from the rest: it contains the added number identifying the needle that should change its positions. This number gets stored in a variable that gets checked with an if condition.

Inside the if, the string is converted to an integer and mapped - a 360 degree turn in a stepper motor working at 1/8 is 1600. The hue value is therefore transformed to be used properly by the motors, that move to the specified value. 

```
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

```


### Mechanical Overview

The clock is moved by three stepper motors. Three concentric little metal tubes, each smaller than the other, are put together holding one needle each. The motors have a smaller wheel attached to them and bigger one is attached to these small metal tubes, creating, with the aid of rubberbands, a polley transmiting the movement to the needles.  

The clock ended up being much wider than expected, and also heating up considerably (because of the stepper motors) - almost enough to guarantee liquid cooling as a feature if a second version was created.


