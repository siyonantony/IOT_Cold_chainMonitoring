#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------------- WiFi Details ----------------------
const char* ssid = "Amk3";
const char* password = "amk12345";

// ---------------------- ThingSpeak ------------------------
unsigned long channelNumber = ;
const char* writeAPIKey = "";

// ---------------------- DHT11 Setup -----------------------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ---------------------- OLED Setup ------------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// I2C pins (explicit for safety)
#define SDA_PIN 21
#define SCL_PIN 22

WiFiClient client;

unsigned long exposureStart = 0;
bool highTemp = false;

void setup() {
  Serial.begin(115200);

  dht.begin();

  // Initialize I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while(true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // WiFi Connection
  display.setCursor(0,0);
  display.println("Connecting WiFi...");
  display.display();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  
  display.clearDisplay();
  display.println("WiFi Connected!");
  display.display();
  delay(1500);

  ThingSpeak.begin(client);
}

void loop() {

  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT Error");
    return;
  }

  String status = "SAFE";

  // Cold Chain Logic (Threshold = 8°C)
  if(temp > 8) {

    if(!highTemp) {
      exposureStart = millis();
      highTemp = true;
    }

    unsigned long exposureMinutes = (millis() - exposureStart) / 60000;

    if(exposureMinutes > 60)
      status = "DISPOSE!";
    else if(exposureMinutes > 30)
      status = "WARNING";
    else
      status = "ALERT";

  } else {
    highTemp = false;
    status = "SAFE";
  }

  // OLED Display
  display.clearDisplay();
  display.setCursor(0,0);

  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  display.print("Hum : ");
  display.print(hum);
  display.println(" %");

  display.print("Status:");
  display.println(status);

  display.display();

  // Send data to ThingSpeak
  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, hum);
  ThingSpeak.writeFields(channelNumber, writeAPIKey);

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C | Hum: ");
  Serial.print(hum);
  Serial.print(" % | Status: ");
  Serial.println(status);

  delay(20000);  // 20 seconds (ThingSpeak limit)
}
