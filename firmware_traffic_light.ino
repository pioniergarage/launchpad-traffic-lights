#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid      = "";
const char* password  = "";

const String requestOpen = "http://launchpadapp.pioniergarage.de/api/door/change-status?door=open";
const String requestClosed = "http://launchpadapp.pioniergarage.de/api/door/change-status?door=closed";
String request = "";

const int button = 13;                      //GPIO used to connect the switch
const int redLight = 12;                    //GPIO to control red light

int connectionAttempts = 0;

int buttonState = 0;                 

enum state {
  red = 1,
  green
};

int currentMode = red;                      //false -> red, true -> green

void setup() {
  
  pinMode(button, INPUT_PULLUP);                                             
  pinMode(redLight, OUTPUT);                

  //Setup WiFi Connection
  
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    connectionAttempts++;
    
    if(connectionAttempts > 20) {
      connectionAttempts = 0;
      Serial.print("Starting new connection attempt ...");
      WiFi.begin(ssid, password);
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(redLight, HIGH);
  
  delay(5000);
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.print("Connection lost ... Reconnecting");
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      connectionAttempts++;
    
     if(connectionAttempts > 20) {
      Serial.print("Starting new connection attempt ...");
      connectionAttempts = 0;
      WiFi.begin(ssid, password);
      }
    }
  }
    
  if(digitalRead(button) != buttonState){
    if(currentMode == green) {
      changeRequest(red);
      digitalWrite(redLight, HIGH);
      currentMode = red;       
    }
    else if (currentMode == red) {
      changeRequest(green);
      digitalWrite(redLight, LOW);
      currentMode = green; 
    } 
    else {
      currentMode = red;
    }

    if(buttonState == 0)
      buttonState = 1;
    else
      buttonState = 0;
      
    delay(5000);
  }

  delay(50);
}

int changeRequest(boolean x) {
HTTPClient http;
  
Serial.print("connecting to launchpadapp");

if(x == green) {
  request = requestOpen;
}
else {
  request = requestClosed;
}

http.begin(request);
int httpCode = http.GET();
String payload = http.getString();

Serial.println(httpCode);   //Print HTTP return code
Serial.println(payload);    //Print request response payload

//TODO: decode resopnse payload to determine success of change
 
http.end();  //Close connection
}

