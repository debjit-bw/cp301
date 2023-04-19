#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10); // wait for serial port to connect. Needed for native USB port only
  }

  if (!amg.begin()) {
    Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
    while (1);
  }
}

void loop() {
  float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
  amg.readPixels(pixels);

  Serial.println("Heat map:");
  for (int i = 1; i <= AMG88xx_PIXEL_ARRAY_SIZE; i++) {
    Serial.print(pixels[i - 1]);
    Serial.print(", ");

    if (i % 8 == 0) {
      Serial.println("");
    }
  }

  Serial.println("");
  delay(1000);
}



///////////////////////////

#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10);
  }
  
  bool status;
  
  // Start I2C communication.
  Wire.begin();
  
  // Initialize the sensor.
  status = amg.begin();
  
  if (!status) {
    Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
    while (1);
  }  
}

void loop() {
  float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
  
  // Read the temperature data from the sensor.
  amg.readPixels(pixels);
  
  // Print the temperature data.
  for (int i = 1; i <= AMG88xx_PIXEL_ARRAY_SIZE; i++) {
    Serial.print(pixels[i-1]);
    Serial.print("\t");
    if (i % 8 == 0) {
      Serial.println("");
    }
  }
  
  delay(100);
}