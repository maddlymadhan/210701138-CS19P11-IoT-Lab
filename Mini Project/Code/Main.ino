#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// Define pin for relay
const int relayPin = 7; // Change to your relay pin
// Define pin for soil moisture sensor
const int soilMoisturePin = A0;
// Define threshold for watering
const int moistureThreshold = 700; // Change the threshold
void setup() {
 // Initialize relay pin
 pinMode(relayPin, OUTPUT);
 // Initialize serial communication
 Serial.begin(9600);
 // Initialize the OLED display
 if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
 Serial.println(F("SSD1306 allocation failed"));
 for (;;); // Don't proceed, loop forever
 }
 display.display();
 delay(2000); // Pause for 2 seconds
 // Clear the buffer
 display.clearDisplay();
 display.setTextSize(1);
 display.setTextColor(SSD1306_WHITE);
 display.setCursor(0, 0);
 display.print("SMART PLANT WATERING SYSTEM");
 display.display();
}
void loop() {
 // Read soil moisture level
 int moistureLevel = analogRead(soilMoisturePin);
 // Clear previous moisture level display
 display.fillRect(0, 16, SCREEN_WIDTH, 16, SSD1306_BLACK);
 display.setCursor(0, 16);
 display.print("Dryness Level: ");
 display.print(moistureLevel);
 // Print moisture level to Serial Monitor
 Serial.print("Dryness Level: ");
 Serial.println(moistureLevel);
 // Check if soil moisture is above threshold
 if (moistureLevel < moistureThreshold) {
 // Turn on motor
 digitalWrite(relayPin, HIGH);
 // Display status on OLED
 display.fillRect(0, 32, SCREEN_WIDTH, 16, SSD1306_BLACK);
 display.setCursor(0, 32);
 display.print("Motor off & No Watering...");
 // Print to Serial Monitor
 Serial.println("Motor off & No Watering...");
 } else {
 // Turn off motor
 digitalWrite(relayPin, LOW);
 // Display status on OLED
 display.fillRect(0, 32, SCREEN_WIDTH, 16, SSD1306_BLACK);
 display.setCursor(0, 32);
 display.print("Motor on & Watering");
 // Print to Serial Monitor
 Serial.println("Motor on & Watering");
 }
 // Update the display
 display.display();
 delay(1000); // Delay for stability
}
