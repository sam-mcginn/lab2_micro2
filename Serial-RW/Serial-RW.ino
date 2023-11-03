/*
  Serial-WR

  Output hello to Serial
  Read input from Serial. If there is a 'E' detected, flip the LED

  yluo
  
*/
#include<Wire.h>  // Enable I2C communication
#include<math.h>

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t GyX,GyY,joyX, joyY;
int incomingByte = 0;
//char up[3] = {'u', 'p', '\0'};
//char down[5] = {'d', 'o', 'w', 'n', '\0'};
//char left[5] = {'l', 'e', 'f', 't', '\0'};
//char right[5] = {'r', 'i', 'g', 'h', 't', '\0'};
int currDirection = 0;
int buzzer = 2;

void read_gyro () {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  // GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  // Update direction from gyro reading
  if (abs(GyX) > 1000 || abs(GyY) > 1000) {
    // gyro is oriented on board s/t:
    // tilt forward = -x axis, backward = +x axis
    // tilt left = -y axis, right = +y axis
    if (abs(GyX) > abs(GyY)) {
      if (GyX < 0) {
        // up
        if (currDirection != 1) {
          currDirection = 1;
          Serial.println(currDirection);
        }
      }
      else {
        // down
        if (currDirection != 3) {
          currDirection = 3;
          Serial.println(currDirection);
        }
      }
    } 
    else {
      if (GyY < 0) {
        // left
        if (currDirection != 4) {
          currDirection = 4;
          Serial.println(currDirection);
        }
      }
      else {
        // right
        if (currDirection != 2) {
          currDirection = 2;
          Serial.println(currDirection);
        }
      }
    }
  
  }
}

void read_joystick() {
  // FIX - read joystick and set currDirection accordingly
  // Read joystick
  joyX = analogRead(A5);
  joyY = analogRead(A7);
  
  // Update direction from joystick reading
  if (joyX > 650) {
    // right (?)
    if (currDirection != 2) {
      currDirection = 2;
      Serial.println(currDirection);
    }
  }
  else if (joyX < 450) {
    // left ?
    if (currDirection != 4) {
      currDirection = 4;
      Serial.println(currDirection);
    }
  }
  else if (joyY > 650) {
    // up (?)
    if (currDirection != 3) {
      currDirection = 3;
      Serial.println(currDirection);
    }
  }
  else if (joyY < 450) {
    // down (?)
    if (currDirection != 1) {
      currDirection = 1;
      Serial.println(currDirection);
    }
  }
}

// the setup routine runs once when you press reset:
void setup() {
  Wire.begin(); // Adds Arduino to I2C bus as controller

  // Add GYRO to I2C bus
  Wire.beginTransmission(MPU_addr); // begins I2C transmission
  Wire.write(0x6B);  // Queue these bytes to transmit, 0x6B=PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true); // Transmit queued bytes
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);


  // FIX: PIN ASSIGNMENT FOR ACTIVE BUZZER
  // FIX: PIN ASSIGNMENTS FOR JOYSTICK
  pinMode(buzzer, OUTPUT);

  // DEBUG:
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read from the Serial port:
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    // FIX - if incomingByte indicates buzzer, sound buzzer
    if (incomingByte == 'B')
    {
      //tone(buzzer,300,3000);
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
    }
  }
  /*
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  */

  read_gyro();
  read_joystick();
  //Serial.println(currDirection);
}
