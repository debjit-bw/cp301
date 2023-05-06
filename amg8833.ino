#include <Wire.h>
#include <Adafruit_AMG88xx.h>
#include <stdarg.h>

void Serialprintln(const char* input...) {
  va_list args;
  va_start(args, input);
  for(const char* i=input; *i!=0; ++i) {
    if(*i!='%') { Serial.print(*i); continue; }
    switch(*(++i)) {
      case '%': Serial.print('%'); break;
      case 's': Serial.print(va_arg(args, char*)); break;
      case 'd': Serial.print(va_arg(args, int), DEC); break;
      case 'b': Serial.print(va_arg(args, int), BIN); break;
      case 'o': Serial.print(va_arg(args, int), OCT); break;
      case 'x': Serial.print(va_arg(args, int), HEX); break;
      case 'f': Serial.print(va_arg(args, double), 2); break;
    }
  }
  Serial.println();
  va_end(args);
}

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
float temps[3];

void setup() {
    Serial.begin(9600);
    Serial.println(F("AMG88xx pixels"));

    bool status;
    
    // default settings
    status = amg.begin();
    if (!status) {
        Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Pixels Test --");

    Serial.println();

    delay(100); // let sensor boot up
}


void loop() { 
    //read all the pixels
    amg.readPixels(pixels);
    temps[0] = temps[1] = temps[2] = 0;

    for(int i=0; i<AMG88xx_PIXEL_ARRAY_SIZE; i++){
      // Serial.print(pixels[i]);
      if (i%8 < 2) {
        // Serial.println(pixels[i])
        if (pixels[i] > temps[0]) temps[0] = pixels[i];
      } else if (i%8 > 5) {
        if (pixels[i] > temps[2]) temps[2] = pixels[i];
      } else {
        if (pixels[i] > temps[1]) temps[1] = pixels[i];
      }
      // Serial.println(temps[0]);
      // temps[0] /= 24;
      // temps[1] /= 16;
      // temps[2] /= 24;
    }
    Serialprintln("[%f\t%f\t%f]\n", temps[0], temps[1], temps[2]);

    //delay a second
    delay(100);
}
