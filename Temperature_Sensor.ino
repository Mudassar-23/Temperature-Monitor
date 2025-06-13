#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DHT_U.h>
// Replace 0x27 with 0x3F if I2C scanner shows a different address
LiquidCrystal_I2C lcd(0x27, 16, 2); 


#define DHTPIN 3     // what pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  lcd.init();          // Initialize the LCD
  lcd.backlight();     // Turn on backlight
  lcd.setCursor(0, 0);
  lcd.print(" Simple Circuits ");
  delay(2000);         // Splash screen for 2 seconds
  lcd.clear();
}

void loop() {
  float h = dht.readHumidity();      // Read humidity
  float t = dht.readTemperature();   // Read temperature in Celsius

  // Check if reading is successful
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Sensor Error! ");
    delay(2000);
    return;
  }

  // Print to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %, Temp: ");
  Serial.print(t);
  Serial.println(" *C");

  // Print to LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp =");
  lcd.print(t,2);
  lcd.print((char)223);  // Degree symbol
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity= ");
  lcd.print(h,2);
  lcd.print("%");

  delay(2000); // Wait 2 seconds before refreshing
}
