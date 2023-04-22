// DC motor 1 control
#define P1A 8 // define pin 2 as for P1A
#define P2A 7 // define pin 7 as for P2A

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);// setup Serial Monitor to display information
  pinMode(P1A, OUTPUT);// define pin as OUTPUT for P1A
  pinMode(P2A, OUTPUT);// define pin as OUTPUT for P2A
}

// the loop function runs over and over again forever
void loop() {
  Serial.println(" Rotating CW");
  // digitalWrite(EN12 ,HIGH);// Enable 1A and 2A 
  digitalWrite(P1A,LOW);// send + or HIGH singal to P1A
  digitalWrite(P2A,HIGH);// send - or LOW singal to P2A       
  delay(1000);// motor runs for 3 seconds
  // digitalWrite(EN12 ,LOW);// Disable 1A and 2A
  
  digitalWrite(P1A,HIGH);// send + or HIGH singal to P1A
  digitalWrite(P2A,LOW);// send - or LOW singal to P2A   

  // delay(1000);// motor stop for 3 seconds 
  Serial.println(" Motor Stopped"); 

  Serial.println("=========== Loop done"); 
  delay(1000);
}
