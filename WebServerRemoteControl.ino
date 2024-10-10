/*********
  Serhii 
  Example - https://randomnerdtutorials.com/esp32-web-server-arduino-ide/
*********/

// Load Wi-Fi library
#include <WiFi.h>


// TFT Dispaly
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define TFT_GREY 0x5AEB // New colour
// TFT Dispaly

const char* ssid = "WIFI network name";
const char* password = "password wifi network";

const char* RELEASE_VERSION = "v2024.0";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String FirePower_1 = "off";
String FireTamper_1 = "off";

// Assign output variables to GPIO pins
const int pinFirePower_1 = 26;
const int pinFireTamper_1 = 27;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
// TFT Dispaly
  tft.init();
  tft.setRotation(1);
    clear_display();                     // Очищення екрану
// TFT Dispaly

  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(pinFirePower_1, OUTPUT);
  pinMode(pinFireTamper_1, OUTPUT);
  // Set outputs to LOW
  digitalWrite(pinFirePower_1, LOW);
  digitalWrite(pinFireTamper_1, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  String url = String(WiFi.localIP());
  showMainMenu(url);// todo: не виводиться на дисплей строка урла за якою можна відкрити вебінтерфейс
  Serial.println(url);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  // Перевірка вхідних даних із Serial Monitor
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Читання команди до символу нового рядка
    command.trim(); // Видалення пробілів на початку та в кінці команди
    handleSerialCommand(command); // Виклик функції обробки команд
  }

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
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
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("CH 1 Power on (26 gpio)");
              FirePower_1 = "on";
              digitalWrite(pinFirePower_1, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("CH 1 Power off (26 gpio)");
              FirePower_1 = "off";
              digitalWrite(pinFirePower_1, LOW);
            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("CH 1 Tamper on (27 gpio)");
              FireTamper_1 = "on";
              digitalWrite(pinFireTamper_1, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("CH 1 Tamper off (27 gpio)");
              FireTamper_1 = "off";
              digitalWrite(pinFireTamper_1, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state CH 1 Power, and ON/OFF buttons for GPIO 26  
            client.println("<p>CH 1 Power (26 gpio) - State " + FirePower_1 + "</p>");
            // If the FirePower_1 is off, it displays the ON button       
            if (FirePower_1=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state CH 1 Tamper, and ON/OFF buttons for GPIO 27  - Tamper
            client.println("<p>CH 1 Tamper (27 gpio)- State " + FireTamper_1 + "</p>");
            // If the FireTamper_1 is off, it displays the ON button       
            if (FireTamper_1=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
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

// Функція для обробки команд із Serial Monitor
void handleSerialCommand(String command) {
  if (command == "request_ch_1_power_on") {
    digitalWrite(pinFirePower_1, HIGH);
    Serial.println("response_ch_1_power_on");
  } else if (command == "request_ch_1_power_off") {
    digitalWrite(pinFirePower_1, LOW);
    Serial.println("response_ch_1_power_off");
  } else if (command == "request_ch_1_tamper_on") {
    digitalWrite(pinFireTamper_1, HIGH);
    Serial.println("response_ch_1_tamper_on");
  } else if (command == "request_ch_1_tamper_off") {
    digitalWrite(pinFireTamper_1, LOW);
    Serial.println("response_ch_1_tamper_off");
  } else if (command == "release_version") {
    Serial.println(RELEASE_VERSION);
  } else {
    Serial.println("Unknown command: " + command);
  }
}

// -------------------------------------------------------------------------------
// Показати головне меню 
// todo: потрібне щоб на екран виводити стан системи, урл в якому відкривати, дебаг та помилки системи
// поки не виводиться урл, треба розібратись
// -------------------------------------------------------------------------------
void showMainMenu(String text){
  tft.fillScreen(TFT_GREY);
  tft.setCursor(0, 4, 4);  // Встановлюємо курсор для виводу тексту
  tft.println("Menu:");    // Виводимо заголовок меню
  tft.println();

  tft.setTextColor(TFT_WHITE);  // Білий колір для тексту
  tft.print("URL ");
  tft.setTextColor(TFT_YELLOW);         // Жовтий колір для температури
  tft.println(text);  // Виводимо початкову температуру
}

// -------------------------------------------------------------------------------
// Очищення екрану
// -------------------------------------------------------------------------------
void clear_display() {
  tft.fillScreen(TFT_BLACK);  // Заповнюємо екран чорним кольором
}













