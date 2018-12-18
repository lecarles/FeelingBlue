#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
*/

SoftwareSerial ss1(4, 16, false, 256);

const char* ssid = "";
const char* password = "";

int gpio = 5;

int val = 0;
int val2 = 0;
int val3 = 0;


// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(38400);
  ss1.begin(38400);
  delay(10);

  // prepare GPIO2
  pinMode(gpio, OUTPUT);
  digitalWrite(gpio, 0);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {

  if (Serial.available() ) {
    String inString = Serial.readString();
    Serial.println(inString);
    ss1.print(inString);
  }


  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  /*  if (req.indexOf("/gpio/0") != -1)
      val = 0;
    else if (req.indexOf("/gpio/1") != -1)
      val = 1;
    else {
      Serial.println("invalid request");
      client.stop();
      return;
    }
  */
  if (req.indexOf("/hand1/") != -1) {
    Serial.print("Hand 1: ");
    int end = req.indexOf("HTTP") - 1;
    String s = req.substring(11, end);
    s = "1" + s;
    val = s.toInt();
    Serial.println(val);
    Serial.println(s);
    ss1.print(val);
  }

  if (req.indexOf("/hand2/") != -1) {
    Serial.print("Hand 2: ");
    int end2 = req.indexOf("HTTP") - 1;
    String s2 = req.substring(11, end2);
    s2 = "2" + s2;
    val2 = s2.toInt();
    Serial.println(val2);
    Serial.println(s2);
    ss1.print(val2);
  }

  if (req.indexOf("/hand3/") != -1) {
    Serial.print("Hand 3: ");
    int end3 = req.indexOf("HTTP") - 1;
    String s3 = req.substring(11, end3);
    s3 = "3" + s3;
    val3 = s3.toInt();
    Serial.println(val3);
    Serial.println(s3);
    ss1.print(val3);
  }



  // Set GPIO2 according to the request
  digitalWrite(gpio, val);

  client.flush();

  // Prepare the response
  client.println("HTTP/1.1 200 OK");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Content-Type: text/html");
  client.println();
  client.println("<!DOCTYPE HTML>\r\n <html>\r\nGPIO is now CHANGED.</html>");
  //  client.println("Connection: close");

  /*
    s += (val) ? "high" : "low";
    s += "";

    // Send the response to the client
    client.println(s); */
  delay(5);
  Serial.println("Client disonnected");



  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}

