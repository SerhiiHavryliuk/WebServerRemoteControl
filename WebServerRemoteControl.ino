/*********
  Serhii 
  RELEASE_VERSION = "v2024.2"
  Serial monitor controls
*********/

// TFT Dispaly
#include <TFT_eSPI.h>  // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define TFT_GREY 0x5AEB  // New colour
// TFT Dispaly

const char* RELEASE_VERSION = "v2024.3";

// Assign output variables to GPIO pins
// Device 1
const int pinDevicePower_1 = 13;
const int pinDeviceTamper_1 = 12;

// Device 2
const int pinDevicePower_2 = 27;
const int pinDeviceTamper_2 = 26;

// Device 3
const int pinDevicePower_3 = 33;
const int pinDeviceTamper_3 = 32;

void setup() {
  Serial.begin(115200);

  Serial.println("Start setup");
  Serial.println(RELEASE_VERSION);

  showMainMenu("Start setup");
  delay(1000);
  showMainMenu(RELEASE_VERSION);
  delay(1000);

  // TFT Dispaly
  tft.init();
  tft.setRotation(1);
  clear_display();  // Очищення екрану
                    // TFT Dispaly

  // Initialize the output variables as outputs
  // Device 1
  pinMode(pinDevicePower_1, OUTPUT);
  pinMode(pinDeviceTamper_1, OUTPUT);
  // Device 2
  pinMode(pinDevicePower_2, OUTPUT);
  pinMode(pinDeviceTamper_2, OUTPUT);
  // Device 3
  pinMode(pinDevicePower_3, OUTPUT);
  pinMode(pinDeviceTamper_3, OUTPUT);

  // Set outputs to LOW
  // Device 1
  digitalWrite(pinDevicePower_1, LOW);
  digitalWrite(pinDeviceTamper_1, LOW);
  // Device 2
  digitalWrite(pinDevicePower_2, LOW);
  digitalWrite(pinDeviceTamper_2, LOW);
  // Device 3
  digitalWrite(pinDevicePower_3, LOW);
  digitalWrite(pinDeviceTamper_3, LOW);

  Serial.println("Setup end");
  showMainMenu("Setup end");
  delay(1000);
}

void loop() {
  // Перевірка вхідних даних із Serial Monitor
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // Читання команди до символу нового рядка
    command.trim();                                 // Видалення пробілів на початку та в кінці команди
    handleSerialCommand(command);                   // Виклик функції обробки команд
  }
}

// Функція для обробки команд із Serial Monitor
void handleSerialCommand(String command) {
  if (command == "request_ch_1_power_on") {
    digitalWrite(pinDevicePower_1, HIGH);
    Serial.println("response_ch_1_power_on");
  } else if (command == "request_ch_1_power_off") {
    digitalWrite(pinDevicePower_1, LOW);
    Serial.println("response_ch_1_power_off");
  } else if (command == "request_ch_1_tamper_on") {
    digitalWrite(pinDeviceTamper_1, HIGH);
    Serial.println("response_ch_1_tamper_on");
  } else if (command == "request_ch_1_tamper_off") {
    digitalWrite(pinDeviceTamper_1, LOW);
    Serial.println("response_ch_1_tamper_off");
  } else if (command == "request_ch_2_power_on") {
    digitalWrite(pinDevicePower_2, HIGH);
    Serial.println("response_ch_2_power_on");
  } else if (command == "request_ch_2_power_off") {
    digitalWrite(pinDevicePower_2, LOW);
    Serial.println("response_ch_2_power_off");
  } else if (command == "request_ch_2_tamper_on") {
    digitalWrite(pinDeviceTamper_2, HIGH);
    Serial.println("response_ch_2_tamper_on");
  } else if (command == "request_ch_2_tamper_off") {
    digitalWrite(pinDeviceTamper_2, LOW);
    Serial.println("response_ch_2_tamper_off");
  } else if (command == "request_ch_3_power_on") {
    digitalWrite(pinDevicePower_3, HIGH);
    Serial.println("response_ch_3_power_on");
  } else if (command == "request_ch_3_power_off") {
    digitalWrite(pinDevicePower_3, LOW);
    Serial.println("response_ch_3_power_off");
  } else if (command == "request_ch_3_tamper_on") {
    digitalWrite(pinDeviceTamper_3, HIGH);
    Serial.println("response_ch_3_tamper_on");
  } else if (command == "request_ch_3_tamper_off") {
    digitalWrite(pinDeviceTamper_3, LOW);
    Serial.println("response_ch_3_tamper_off");
  } else if (command == "release_version") {
    Serial.println(RELEASE_VERSION);
  } else {
    Serial.println("Unknown command: " + command);
    showMainMenu("Unknown command: " + command);
  }
  showMainMenu(command);
}

// -------------------------------------------------------------------------------
// Показати головне меню
// todo: потрібно на екран виводити стан системи, дебаг та помилки
// -------------------------------------------------------------------------------
void showMainMenu(String text) {
  tft.fillScreen(TFT_GREY);
  tft.setCursor(0, 4, 4);  // Встановлюємо курсор для виводу тексту
  tft.println("Menu:");    // Виводимо заголовок меню
  tft.println();

  tft.setTextColor(TFT_WHITE);  // Білий колір для тексту
  tft.print("State: ");
  tft.setTextColor(TFT_YELLOW);  // Жовтий колір для температури
  tft.println(text);             // Виводимо початкову температуру
}

// -------------------------------------------------------------------------------
// Очищення екрану
// -------------------------------------------------------------------------------
void clear_display() {
  tft.fillScreen(TFT_BLACK);  // Заповнюємо екран чорним кольором
}