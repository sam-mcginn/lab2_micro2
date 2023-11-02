/*
  Serial-WR

  Output hello to Serial
  Read input from Serial. If there is a 'E' detected, flip the LED

  yluo

*/

// LED status
int led_status = HIGH;
int incomingByte = 0;
int buzzer = 25;
// the setup routine runs once when you press reset:
void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  led_status = HIGH;
  pinMode(buzzer, OUTPUT);

}

// the loop routine runs over and over again forever:
void loop()
{
  // read from the Serial port:
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    incomingByte = Serial.read();
    Serial.println(incomingByte);

    if (incomingByte == 'E')
    {
      // flip LED
      led_status = (led_status == HIGH) ? LOW : HIGH;
      digitalWrite(LED_BUILTIN, led_status);
    }
    if (incomingByte == 'B')
    {
      tone(buzzer,300,3000);
    }
  }

  delay(1000);
  Serial.println("Hello");
}

// E not involved in the game-communication between port and python.
// have to make something like that for buzzer.
,