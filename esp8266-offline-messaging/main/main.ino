#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char *ssid = "xn-2a35-s8.network.teslasoft.org";
const char *password = "dERX8Dh9NNN3r6Ndfp15aQ";

WiFiServer server(80);
String header;
String output5State = "off";

// Assign output variables to GPIO pins
const int output5 = 5; // Blue
const int g = 4;
const int r = 0;
const int s = 2;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

int a = 16;  //Gpio-0 with a of 7 segment display   
int b = 14;  //Gpio-1 with b of 7 segment display    
int c = 10;  //Gpio-2 with c of 7 segment display  
int d = 13;  //Gpio-3 with d of 7 segment display  
int e = 15;  //Gpio-4 with e of 7 segment display   
int f = 3;  //Gpio-5 with f of 7 segment display  
int g1 = 1; //Gpio-16 with g of 7 segment display
int state = 1;

void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g1, OUTPUT);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g1, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(0, LOW);
  digitalWrite(2, LOW);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(5, HIGH);
    digitalWrite(0, LOW);
    delay(200);
    digitalWrite(5, LOW);
    digitalWrite(0, HIGH);
    delay(200);
    Serial.print(".");
  }

  digitalWrite(0, LOW);
  digitalWrite(5, LOW);

  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(4, LOW);
  digitalWrite(2, HIGH);
  delay(50);
  digitalWrite(2, LOW);

  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g1, LOW);
  
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  String url = "";
  int s = 0;
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // client.println(header);
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /home") >= 0) {
              output5State = "main";
            } else if (header.indexOf("GET /controller?command=led&state=on") >= 0) {
              Serial.println("GPIO 5 (LED) on");
              output5State = "sled";
              digitalWrite(output5, HIGH);
              digitalWrite(0, HIGH);
              digitalWrite(4, HIGH);
            } else if (header.indexOf("GET /controller?command=led&state=off") >= 0) {
              Serial.println("GPIO 5 (LED) off");
              output5State = "sled";
              digitalWrite(output5, LOW);
              digitalWrite(0, LOW);
              digitalWrite(4, LOW);
            } else if (header.indexOf("GET /controller?command=notify") >= 0) {
              WiFiClient wifiClient;
              HTTPClient http;

              int pos = 36;

              url = "";

              while (header[pos] != '&') {
                url.concat(header[pos]);
                pos += 1;
              }

              pos += 6;

              url.concat("?command=receiver&data=");

              while (header[pos] != ' ') {
                url.concat(header[pos]);
                pos += 1;
              }

              Serial.println(url);

              
              
              http.begin(wifiClient, url);  //Specify request destination
              int httpCode = http.GET();                                  //Send the request
 
              if (httpCode == 200) { //Check the returning code
                s = 1;
                String payload = http.getString();   //Get the request response payload
                Serial.println(payload);             //Print the response payload
                digitalWrite(5, LOW);
                digitalWrite(0, LOW);
                digitalWrite(4, HIGH);
                delay(100);
                digitalWrite(4, LOW);
                delay(100);
                digitalWrite(4, HIGH);
                delay(100);
                digitalWrite(4, LOW);
              } else {
                Serial.println("An error occured while forwarding command");
                digitalWrite(0, HIGH);
                delay(100);
                digitalWrite(0, LOW);
                delay(100);
                digitalWrite(0, HIGH);
                delay(100);
                digitalWrite(0, LOW);
              }
 
              http.end();
              output5State = "notify";
            } else if (header.indexOf("GET /controller?command=start") >= 0) {
              Serial.println("Executing command /start");
              digitalWrite(5, LOW);
              digitalWrite(4, LOW);
              digitalWrite(0, HIGH);
              delay(100);
              digitalWrite(5, LOW);
              digitalWrite(4, HIGH);
              digitalWrite(0, LOW);
              delay(100);
              digitalWrite(5, HIGH);
              digitalWrite(4, LOW);
              digitalWrite(0, LOW);
              delay(100);
              digitalWrite(5, LOW);
              digitalWrite(4, LOW);
              digitalWrite(0, LOW);
              delay(100);
              
              
              output5State = "start";
            } else if (header.indexOf("GET /controller?command=setstate&data=1") >= 0) {
              digitalWrite(a, LOW);
              digitalWrite(b, HIGH);
              digitalWrite(c, HIGH);
              digitalWrite(d, LOW);
              digitalWrite(e, LOW);
              digitalWrite(f, LOW);
              digitalWrite(g1, LOW);
              output5State = "mod";
              state = 1;
            } else if (header.indexOf("GET /controller?command=setstate&data=2") >= 0) {
              digitalWrite(a, HIGH);
              digitalWrite(b, HIGH);
              digitalWrite(c, LOW);
              digitalWrite(d, HIGH);
              digitalWrite(e, HIGH);
              digitalWrite(f, LOW);
              digitalWrite(g1, HIGH);
              output5State = "mod";
              state = 2;
            } else if (header.indexOf("GET /controller?command=setstate&data=3") >= 0) {
              digitalWrite(a, HIGH);
              digitalWrite(b, HIGH);
              digitalWrite(c, HIGH);
              digitalWrite(d, HIGH);
              digitalWrite(e, LOW);
              digitalWrite(f, LOW);
              digitalWrite(g1, HIGH);
              output5State = "mod";
              state = 3;
            } else if (header.indexOf("GET /controller?command=setstate&data=4") >= 0) {
              digitalWrite(a, LOW);
              digitalWrite(b, HIGH);
              digitalWrite(c, HIGH);
              digitalWrite(d, LOW);
              digitalWrite(e, LOW);
              digitalWrite(f, HIGH);
              digitalWrite(g1, HIGH);
              output5State = "mod";
              state = 4;
            } else if (header.indexOf("GET /controller?command=setstate&data=5") >= 0) {
              digitalWrite(a, HIGH);
              digitalWrite(b, LOW);
              digitalWrite(c, HIGH);
              digitalWrite(d, HIGH);
              digitalWrite(e, LOW);
              digitalWrite(f, HIGH);
              digitalWrite(g1, HIGH);
              output5State = "mod";
              state = 5;
            } else if (header.indexOf("GET /controller?command=setstate&data=6") >= 0) {
              digitalWrite(a, HIGH);
              digitalWrite(b, LOW);
              digitalWrite(c, HIGH);
              digitalWrite(d, HIGH);
              digitalWrite(e, HIGH);
              digitalWrite(f, HIGH);
              digitalWrite(g1, HIGH);
              output5State = "mod";
              state = 6;
            } else if (header.indexOf("GET /controller?command=setstate&data=7") >= 0) {
              digitalWrite(a, HIGH);
              digitalWrite(b, HIGH);
              digitalWrite(c, HIGH);
              digitalWrite(d, LOW);
              digitalWrite(e, LOW);
              digitalWrite(f, LOW);
              digitalWrite(g1, LOW);
              output5State = "mod";
              state = 7;
            } else if (header.indexOf("GET /controller?command=setstate&data=8") >= 0) {
              digitalWrite(a, HIGH);
              digitalWrite(b, HIGH);
              digitalWrite(c, HIGH);
              digitalWrite(d, HIGH);
              digitalWrite(e, HIGH);
              digitalWrite(f, HIGH);
              digitalWrite(g1, HIGH);
              output5State = "mod";
              state = 8;
            } else if (header.indexOf("GET /controller?command=setstate&data=9") >= 0) {
              digitalWrite(a, HIGH);
              digitalWrite(b, HIGH);
              digitalWrite(c, HIGH);
              digitalWrite(d, HIGH);
              digitalWrite(e, LOW);
              digitalWrite(f, HIGH);
              digitalWrite(g1, HIGH);
              output5State = "mod";
              state = 9;
            } else if (header.indexOf("GET /controller?command=setstate") >= 0) {
              output5State = "mod";
            } else if (header.indexOf("GET /controller?command=led&state=red") >= 0) {
              digitalWrite(5, LOW);
              digitalWrite(4, LOW);
              digitalWrite(0, HIGH);
              output5State = "sled";
            } else if (header.indexOf("GET /controller?command=led&state=green") >= 0) {
              digitalWrite(5, LOW);
              digitalWrite(4, HIGH);
              digitalWrite(0, LOW);
              output5State = "sled";
            } else if (header.indexOf("GET /controller?command=led&state=blue") >= 0) {
              digitalWrite(5, HIGH);
              digitalWrite(4, LOW);
              digitalWrite(0, LOW);
              output5State = "sled";
            } else if (header.indexOf("GET /controller?command=led") >= 0) {
              output5State = "sled";
            } else if (header.indexOf("GET /controller?command=reboot") >= 0) {
              output5State = "reboot";
              
            } else {
              digitalWrite(2, HIGH);
              digitalWrite(5, LOW);
              digitalWrite(4, LOW);
              digitalWrite(0, HIGH);
              delay(100);
              digitalWrite(5, LOW);
              digitalWrite(4, LOW);
              digitalWrite(0, LOW);
              delay(100);
              digitalWrite(5, LOW);
              digitalWrite(4, LOW);
              digitalWrite(0, HIGH);
              delay(100);
              digitalWrite(2, LOW);
              digitalWrite(5, LOW);
              digitalWrite(4, LOW);
              digitalWrite(0, LOW);
              delay(100);
              digitalWrite(5, LOW);
              digitalWrite(4, LOW);
              digitalWrite(0, HIGH);
              delay(100);
              digitalWrite(5, LOW);
              digitalWrite(4, LOW);
              digitalWrite(0, LOW);
              
              output5State = "unknown";
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Controller</title>");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: sans-serif; display: inline-block; margin: 0px auto; text-align: center; background-color: #212121; color: #cecece}");
            client.println(".button { background-color: #2e8b57; border: none; border-radius: 8px; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}");
            client.println(".button4 {background-color: #4b0082;}");
            client.println(".button3 {background-color: #db4437;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP8266 controller</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            
            // If the output5State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p>LED - State " + output5State + "</p>");
              client.println("<p><a href=\"/controller?command=led&state=on\"><button class=\"button\">Enable LED</button></a></p>");
            } else if (output5State=="on") {
              client.println("<p>LED - State " + output5State + "</p>");
              client.println("<p><a href=\"/controller?command=led&state=off\"><button class=\"button button2\">Disable LED</button></a></p>");
            } else if (output5State=="start") {
              client.println("<p><a href=\"/controller?command=start\"><button class=\"button button4\">Send /start</button></a></p>");
            } else if (output5State=="reboot") {
              client.println("<p>Waiting 5 sec before reboot...</p>");
              client.println("<script>window.location.replace(\"/controller?command=setstate&data=1\");</script>");
              delay(5000);
              ESP.restart();
            } else if (output5State=="main") {
              client.println("<p>Execute a command by sending GET request</p>");
            } else if (output5State=="notify") {
              if (s == 1) {
                client.println("<p>Message sent successfully. URL:" + url + "</p>");
              } else {
                client.println("<p>Failed to send message. URL:" + url + "</p>");
              }
            } else if (output5State=="mod") {
              client.println("<p>Set mode</p>");
              client.println("<p><a href=\"/controller?command=setstate&data=1\"><button class=\"button button4\">Enter mode 1</button></a></p>");
              client.println("<p><a href=\"/controller?command=setstate&data=2\"><button class=\"button button4\">Enter mode 2</button></a></p>");
              client.println("<p><a href=\"/controller?command=setstate&data=3\"><button class=\"button button4\">Enter mode 3</button></a></p>");
              client.println("<p><a href=\"/controller?command=setstate&data=4\"><button class=\"button button4\">Enter mode 4</button></a></p>");
              client.println("<p><a href=\"/controller?command=setstate&data=5\"><button class=\"button button4\">Enter mode 5</button></a></p>");
              client.println("<p><a href=\"/controller?command=setstate&data=6\"><button class=\"button button4\">Enter mode 6</button></a></p>");
              client.println("<p><a href=\"/controller?command=setstate&data=7\"><button class=\"button button4\">Enter mode 7</button></a></p>");
              client.println("<p><a href=\"/controller?command=setstate&data=8\"><button class=\"button button4\">Enter mode 8</button></a></p>");
              client.println("<p><a href=\"/controller?command=setstate&data=9\"><button class=\"button button4\">Enter mode 9</button></a></p>");
              client.println("<p><a href=\"/controller?command=reboot\"><button class=\"button button3\">Reboot</button></a></p>");
              client.println("<p><a href=\"/controller?command=led\"><button class=\"button button2\">LED</button></a></p>");
            } else if (output5State=="sled") {
              client.println("<p>LED control</p>");
              client.println("<p><a href=\"/controller?command=led&state=red\"><button class=\"button button4\">RED</button></a></p>");
              client.println("<p><a href=\"/controller?command=led&state=green\"><button class=\"button button4\">GREEN</button></a></p>");
              client.println("<p><a href=\"/controller?command=led&state=blue\"><button class=\"button button4\">BLUE</button></a></p>");
              client.println("<p><a href=\"/controller?command=led&state=on\"><button class=\"button button4\">ALL</button></a></p>");
              client.println("<p><a href=\"/controller?command=led&state=off\"><button class=\"button button4\">DISABLED</button></a></p>");
              client.println("<p><a href=\"/controller?command=setstate\"><button class=\"button button4\">MODES</button></a></p>");
            } else {
              // client.println(header);
              client.println("<p><a href=\"/home\"><button class=\"button button3\">Command not recognized</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
