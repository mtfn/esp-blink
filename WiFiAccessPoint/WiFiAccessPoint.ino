#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/* Some JS trickery that binds buttons to a fetch request */
const String homepage1 = "<!DOCTYPE html><html><head><meta charset=utf8><title>Test</title><style>button{width:100%;font-size:4em;padding-top:0.5em;padding-bottom:0.5em;}</style></head><body>";
const String homepage2 = "<script>document.querySelectorAll('button').forEach(function(button){button.addEventListener('click',async function(){fetch('http://192.168.4.1/?input='+button.id);});});</script></body></html>";

/* Will be concatenated between homepage1 & homepage2 */
String buttons = "";
void addButton(int id, String label) {
  buttons += "<button id=\"" + String(id) + "\">" + label + "</button>";
}

ESP8266WebServer server(80);

/* Handles the aforementioned fetch request */
void handler() {
  String input = server.arg("input");
  
  if(input == "") {
    /* Serve landing page */
    server.send(200, "text/html", homepage1 + buttons + homepage2);
    
  } else {
    /* Write button ID to serial */
    Serial.write(input.toInt());
    server.send(200, "application/json", "{}");
  }

}

void setup() {
  delay(1000);
  Serial.begin(9600);
  
  /* Connect to Wifi network with this SSID & pass and visit 192.168.4.1 in browser */
  WiFi.softAP("ESP", "password");

  /* Add buttons
   *  Button ID as int
   *  Button label in double quotes
   */
  addButton(1, "On");
  addButton(0, "Off");

  server.on("/", handler);
  server.begin();
}

void loop() {
  server.handleClient();
}
