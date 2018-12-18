# Feeling Blue
What shade of blue are you feeling?

## About the Project
Behance link

## How it works

3 needles move over the colour the user selects on a website, with a slider. Each needle has its own site and is theoretically designed to be used by a different user. 

### The Website

The website consits of a slider changing the HUE value 

Due to time limitations

### ESP8266

The ESP acts as a WiFi web server, using the code provided as an [example by Arduino](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiManualWebServer/WiFiManualWebServer.ino)

The server isolates and stores in a string the value received via request from each hand website, then adds a number to identify from which hand it came, and sends it via software serial to the arduino.

´´´
  if (req.indexOf("/hand1/") != -1) {
    Serial.print("Hand 1: ");
    int end = req.indexOf("HTTP") - 1;
    String s = req.substring(11, end); 
    s = "1" + s;
    val = s.toInt();
    Serial.println(val);
    Serial.println(s);
  }
´´´

### Arduino

### Mecanical Specifics

https://lecarles.github.io/moodclock/
