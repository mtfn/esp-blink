/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const String homepage1 = "<!DOCTYPE html><html><head><meta charset=utf8><title>Test</title><style>button{width:100%;font-size:4em;padding-top:0.5em;padding-bottom:0.5em;}</style></head><body>";
const String homepage2 = "<script>document.querySelectorAll('button').forEach(function(button){button.addEventListener('click',async function(){fetch('http://192.168.4.1/?input='+button.id);});});</script></body></html>";

String buttons = "";

void addButton(int id, String label) {
  buttons += "<button id=\"" + String(id) + "\">" + label + "</button>";
}

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.  
*/
void handler() {
  String input = server.arg("input");
  
  if(input == "") {
    server.send(200, "text/html", homepage1 + buttons + homepage2);
    
  } else {
    Serial.write(input.toInt());
    server.send(200, "application/json", "{}");
  }

}

void setup() {
  delay(1000);
  Serial.begin(9600);
  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP("ESP", "password");

  /* Add buttons
   *  Unique single letter ID in single quotes
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
