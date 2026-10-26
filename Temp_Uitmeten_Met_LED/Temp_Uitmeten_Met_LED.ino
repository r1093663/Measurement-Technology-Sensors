const int ledKachel = D1;
const float gewensteTemp = 16.0; 
const float hysterese = 1.0;
bool kachelAan = false; 

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("LM335 Temperatuurmeting gestart...");

  pinMode(ledKachel, OUTPUT);
  digitalWrite(ledKachel, LOW);
}

void loop() {
  int rawADC = analogRead(A0);

  float spanningA0 = (rawADC / 1023.0) * 3.2;
  float spanningSensor = spanningA0 * 2.0;
  float tempKelvin = spanningSensor * 100.0;
  float tempCelsius = tempKelvin - 273.15;

  if (tempCelsius < (gewensteTemp - hysterese)) {
    kachelAan = true;   // Te koud
  } else if (tempCelsius > (gewensteTemp - hysterese)) {
    kachelAan = false;  // Warm genoeg 
  }

  digitalWrite(ledKachel, kachelAan ? HIGH : LOW);

  Serial.print("ADC: ");
  Serial.print(rawADC);
  Serial.print(" | Spanning A0: ");
  Serial.print(spanningA0);
  Serial.print(" V | Gewenst: ");
  Serial.print(gewensteTemp);
  Serial.print(" °C | Temp: ");
  Serial.print(tempCelsius);
  Serial.print(" °C | Kachel: ");
  Serial.println(kachelAan ? "AAN" : "UIT");

  delay(500);
}