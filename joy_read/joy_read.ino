// Arduino pin numbers
const int SW_pin = 32; // digital pin connected to switch output
const int X_pin = 5; // analog pin connected to X output
const int Y_pin = 7; // analog pin connected to Y output

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
  Serial.print(digitalRead(SW_pin));
  Serial.print(analogRead(X_pin));
  Serial.println(analogRead(Y_pin));
  delay(500);

   // Update direction from joystick reading
  if ( analogRead(X_pin) > 1000 ||analogRead(Y_pin) > 1000) {
    // joystick is oriented on board s/t:
    // tilt forward = -x axis, backward = +x axis
    // tilt left = -y axis, right = +y axis
    if ( analogRead(X_pin) > analogRead(Y_pin)) {
      if (analogRead(X_pin) < 0) {
        // up
        currDirection = 1;
        Serial.println(currDirection);
      }
      else {
        // down
        currDirection = 3;
        Serial.println(currDirection);
      }
    } 
    else {
      if (analogRead(Y_pin) < 0) {
        // left
        currDirection = 4;
        Serial.println(currDirection);
      }
      else {
        // right
        currDirection = 2;
        Serial.println(currDirection);
      }
    }
  
  }
}