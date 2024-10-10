/*********
  Serhii 
*********/

// TFT Dispaly
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define TFT_GREY 0x5AEB // New colour
// TFT Dispaly

const char* RELEASE_VERSION = "v2024.0";



// Auxiliar variables to store the current output state
String FirePower_1 = "off";
String FireTamper_1 = "off";

// Assign output variables to GPIO pins
const int pinFirePower_1 = 26;
const int pinFireTamper_1 = 27;

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

  Serial.print("Setup end");
}

void loop() {
  // Перевірка вхідних даних із Serial Monitor
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Читання команди до символу нового рядка
    command.trim(); // Видалення пробілів на початку та в кінці команди
    handleSerialCommand(command); // Виклик функції обробки команд
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
// todo: потрібно на екран виводити стан системи, дебаг та помилки
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