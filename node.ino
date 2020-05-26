/*
This sketch sends a string to a TCP server, and prints a one-line response.
You must run a TCP server in your local network.
For example, on Linux you can use this command: nc -v -l 3000
*/

/*
This is slightly modified script
Original script from: https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiClientBasic/WiFiClientBasic.ino

What is changed?
- Everyting that we receive from server just pass to Arduino Mega through serial communication

*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.1.1";
const uint16_t port = 3000;

ESP8266WiFiMulti WiFiMulti;

void setup() {
    // our communication with Mega
    Serial.begin(9600);

    // We start by connecting to a WiFi network
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(ssid, password);

    while (WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    delay(500);
}


void loop() {

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;
    }

    // logic goes here
    while true {
        // Send command to server
        client.println("send_command_1");

        // read back one line from server
        String readCommand = client.readStringUntil('\r');
        Serial.println(readCommand);

        // if server sends end connection command, end the communication
        if(readCommand == "end_connection_command") break;
    }

    Serial.println("end_connection_command");
    client.stop();

    delay(5000);
}