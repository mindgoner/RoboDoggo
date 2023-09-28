
int digitalValues[7];
int analogValues[6];
bool debug;

void setup() {
  debug = true;

  // Set the digital pins as inputs
  pinMode(2, INPUT_PULLUP); // Left Joystick Button
  pinMode(3, INPUT_PULLUP); // Right Joystick Button
  pinMode(4, INPUT_PULLUP); // Button 1
  pinMode(5, INPUT_PULLUP); // Button 2
  pinMode(6, INPUT_PULLUP); // Button 3
  pinMode(7, INPUT_PULLUP); // Button 4
  pinMode(8, INPUT_PULLUP); // Switch 1

  // Serial communication for monitoring
  if(debug){
    Serial.begin(9600);
  }
}

void readInputs(){
  // Read and print digital input values
  digitalValues[0] = !digitalRead(2);
  digitalValues[1] = !digitalRead(3);
  digitalValues[2] = !digitalRead(4);
  digitalValues[3] = !digitalRead(5);
  digitalValues[4] = !digitalRead(6);
  digitalValues[5] = !digitalRead(7);
  digitalValues[6] = !digitalRead(8);

  // Read and print analog input values
  analogValues[0] = analogRead(A0);
  analogValues[1] = analogRead(A1);
  analogValues[2] = analogRead(A2);
  analogValues[3] = analogRead(A3);
  analogValues[4] = analogRead(A6);
  analogValues[5] = analogRead(A7);

  if(debug){
    
    // Print digital input values
    Serial.print("Digital Input Values: ");
    for (int i = 0; i < 7; i++) {
      Serial.print("D");
      Serial.print(i + 2);
      Serial.print(": ");
      Serial.print(digitalValues[i]);
      Serial.print(", ");
    }

    // Print analog input values
    Serial.print("Analog Input Values: ");
    for (int i = 0; i < 6; i++) {
      Serial.print("A");
      Serial.print(i);
      Serial.print(": ");
      Serial.print(analogValues[i]);
      Serial.print(", ");
    }

    Serial.println("");
  }
}

void loop() {
  readInputs();
  delay(10); // Delay for 1 second between readings
}
