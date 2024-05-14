#include <ESP32Servo.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN    8    // Pin connected to the data input of the LED strip
#define LED_COUNT  12   // Number of LEDs in the strip
#define SERVO_PIN  9    // Pin connected to the continuous rotation servo motor
#define PIR_PIN    10   // Pin connected to the SR501 PIR motion sensor

Servo myServo;  // Create a servo object to control the continuous rotation servo motor
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Define LED strip

unsigned long previousMillisLED = 0;   // Variable to store time since last LED update
const long intervalLED = 2000;  // Interval between LED updates in milliseconds
unsigned long previousMillisServo = 0;   // Variable to store time since last servo update
const long intervalServo = 5000;  // Interval for each rotation cycle in milliseconds
int servoSpeed = 90; // Variable to store servo speed, 90 = stop, 180 and 0 for both directions
int servoDirection = 1; // Variable to store servo rotation direction
int servoLimit = 10; // Variable to count servo rotations

void setup() {
  myServo.attach(SERVO_PIN);  // Attach the servo to the defined GPIO pin
  strip.begin(); // Initialize the LED strip
  strip.show();  // Initialize all pixels to 'off'
  //pinMode(PIR_PIN, INPUT); // Set PIR sensor pin as input
  pinMode(PIR_PIN, INPUT); // Set PIR sensor pin as input
  Serial.begin(9600); // Initialize serial communication
}

void loop() {  
  // Read PIR sensor status
  int pirStatus = digitalRead(PIR_PIN);
  //Serial.print("PIR Sensor Status: ");
  //Serial.println(pirStatus);

  // If motion detected, turn on LED strip to yellow
  if (pirStatus == LOW) {
    setColor(strip.Color(255, 255, 0)); // Set LED color to yellow
  } else {
    setColor(strip.Color(75, 0, 130)); // Set LED color to purple
  }


  if (millis() - previousMillisServo >= intervalServo) {
    /*if((servoDirection == 1 && servoSpeed - 90 >= servoLimit) || (servoDirection == -1 && 90 - servoSpeed >= servoLimit)) {
      servoDirection = -servoDirection; // reverse direction when speed reaches limit
    }
    if((servoDirection == 1 && servoSpeed - 90 <= 4) || (servoDirection == -1 && 90 - servoSpeed <= 4))
      servoSpeed += 3*servoDirection;
    Serial.println("trigger servo");
    Serial.println(servoSpeed);
    
    myServo.write(servoSpeed); // Set servo position
    previousMillisServo = millis(); // Update time*/

    servoDirection = -servoDirection;
    Serial.println(servoDirection);
    if(servoDirection == 1) {
      myServo.write(97);
    }
    else {
      myServo.write(85);
    }

    previousMillisServo = millis(); // Update time
  }

    // Delay before next iteration
    delay(100); 
}
// Function to set the color of the entire LED strip
void setColor(uint32_t color) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show(); // Send the updated color to the LEDs
}