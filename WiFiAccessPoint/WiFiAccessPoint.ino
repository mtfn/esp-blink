#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/* Some JS trickery that binds inputs to a fetch request */
const String homepage1 = "<!DOCTYPE html><html><head><meta charset=utf8><title>Panel</title>"
  "<style>button,input,h2{display:block;font-family:sans-serif;width:100%;font-size:4em;}"
  "button{padding-top:0.5em;padding-bottom: 0.5em;}h2{text-align:center;margin-bottom:0;}</style></head><body>";

const String homepage2 = "<script>async function r(a){fetch('http://192.168.4.1/?input='+a);}</script></body></html>";

/* Will be concatenated between homepage1 & homepage2 */
String ui = "";

void addButton(int id, String label) {
  ui += "<button id=\"" + String(id) + "\" onclick=\"r(this.id)\">" + label + "</button>";
}

void addSlider(int min, int max, String label) {
  ui += "<h2>" + label + "</h2><input name=\"" + label + "\" type=\"range\" min=\"" + String(min)
    + "\" max=\"" + String(max) + "\"oninput=\"r(this.value)\" onchange=\"r(this.value)\">";
}

void addBox(int min, int max) {
  ui += "<input type=\"number\" min=\"" + String(min) + "\" max=\"" + String(max) + "\" onchange=\"r(this.value)\">";
}

ESP8266WebServer server(80);

/* Handles the aforementioned fetch request */
void handler() {
  String input = server.arg("input");
  
  if(input == "") {
    /* Serve landing page */
    server.send(200, "text/html", homepage1 + ui + homepage2);
    
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

  addButton(1, "On");
  addButton(0, "Off");
  /*addSlider(0, 1, "Switch");
  addBox(0, 10);*/

  server.on("/", handler);
  server.begin();
}

void loop() {
  server.handleClient();
}
