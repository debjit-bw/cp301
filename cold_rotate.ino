#include <Wire.h>
#include <Adafruit_AMG88xx.h>
#include <stdarg.h>
// DC motor 1 control
#define P1A 2 // define pin 2 as for P1A
#define P2A 4 // define pin 4 as for P2A
// DC motor 2 control
#define P1B 7 // define pin 7 as for P1B
#define P2B 8 // define pin 8 as for P2B

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

char getDirection(float values[3]) {
  float leftAvg = (values[0] + values[1]) / 2.0; // compute average of left values
  float rightAvg = (values[1] + values[2]) / 2.0; // compute average of right values
  if (values[2] > 50  values[2] > (leftAvg + 5.0)) { // right is significantly higher than left and center
    return 'r';
  } else if (values[0] > 50  values[0] > (rightAvg + 5.0)) { // left is significantly higher than right and center
    return 'l';
  } else { // center is the highest or values are not significantly different
    return 'c';
  }
}

char getDirectionInv(float values[3]) {
  float leftAvg = (values[0] + values[1]) / 2.0; // compute average of left values
  float rightAvg = (values[1] + values[2]) / 2.0; // compute average of right values
//  return 'c';
  if (values[1] < 20  (values[1] < (values[0] - 5.0) && values[1] < (values[2] - 5.0))) {
    return 'c';
  } else if (values[2] < 20  values[2] < (leftAvg - 5.0)) { // right is significantly lower than left and center
    return 'r';
  } else if (values[0] < 20 || values[0] < (rightAvg - 5.0)) { // left is significantly lower than right and center
    return 'l';
  } else { // center is the lowest or values are not significantly different
    return 'n';
  }
}

// Function to rotate motor (just a little) in appropriate direction based on input value
void justRotateMotor(char direction) {
  Serial.print("Rotating ");
  if (direction == 'l') { // rotate counterclockwise for 'l'
    Serial.println("left");
    digitalWrite(P1B,HIGH);
    digitalWrite(P2B,LOW);
  } else if (direction == 'r') { // rotate clockwise for 'r'
    Serial.println("right");
    digitalWrite(P1A,HIGH);
    digitalWrite(P2A,LOW);
  } else if (direction == 'c') { // drive both motors for a moment for 'c'
    Serial.println("fwd");
    digitalWrite(P1A,HIGH);
    digitalWrite(P1B,HIGH);
  } else { // do not rotate for any other input
    Serial.println("none");
    return;
  }

  delay(200); // rotate/drive for 200ms
  digitalWrite(P1A,LOW);
  digitalWrite(P1B,LOW);
}

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
float temps[3];

float* readTemps() {
  static float temps[3];
  // Read temperature values from sensor
  amg.readPixels(pixels);
  temps[0] = temps[1] = temps[2] = 0;

  for(int i=0; i<AMG88xx_PIXEL_ARRAY_SIZE; i++){
    if (i%8 < 2) {
      if (pixels[i] > temps[0]) temps[0] = pixels[i];
    } else if (i%8 > 5) {
      if (pixels[i] > temps[2]) temps[2] = pixels[i];
    } else {
      if (pixels[i] > temps[1]) temps[1] = pixels[i];
    }
  }

  return temps;
}

void setup() {
    Serial.begin(9600);

    bool status;
    
    // default settings
    status = amg.begin();
    if (!status) {
        Serial.println("Wrong wiring");
        while (1);
    }

    pinMode(P1A, OUTPUT);// define pin as OUTPUT for P1A
    pinMode(P2A, OUTPUT);// define pin as OUTPUT for P2A

    pinMode(P1B, OUTPUT);// define pin as OUTPUT for P1B
    pinMode(P2B, OUTPUT);// define pin as OUTPUT for P2B

    delay(100); // let sensor boot up
}

void loop() {
  // Read temperature values from sensor
  float* temps = readTemps();
  Serialprintln("[%f\t%f\t%f]\n", temps[0], temps[1], temps[2]);
  // Determine direction to rotate motor
  char direction = getDirectionInv(temps);

  // Rotate motor in appropriate direction
  justRotateMotor(direction);

  // Delay for a second
  delay(100);
}
