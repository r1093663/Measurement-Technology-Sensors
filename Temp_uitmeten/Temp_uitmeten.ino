void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("LM335 Temperatuurmeting gestart...");
}

void loop() {
  int rawADC = analogRead(A0);

  float spanningA0 = (rawADC / 1023.0) * 3.2;
  float spanningSensor = spanningA0 * 2.0;
  float tempKelvin = spanningSensor * 100.0;
  float tempCelsius = tempKelvin - 273.15;

  Serial.print("ADC: ");
  Serial.print(rawADC);
  Serial.print(" | Spanning A0: ");
  Serial.print(spanningA0, 2);
  Serial.print(" V | Temp: ");
  Serial.print(tempCelsius, 1);
  Serial.println(" °C");

  delay(500);
}