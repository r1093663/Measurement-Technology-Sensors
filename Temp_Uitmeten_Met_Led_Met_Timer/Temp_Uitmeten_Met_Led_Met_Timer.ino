const int ledKachel = D1;
const float gewensteTemp = 16.0; 
bool kachelAan = false; 
const float hysterese = 1.0;

const int schakelaar = D3;       
const int timerLeds[5] = {D2, D5, D6, D7, D8}; 
bool timerActief = false;
unsigned long timerStart = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("LM335 Temperatuurmeting gestart...");

  pinMode(ledKachel, OUTPUT);
  digitalWrite(ledKachel, LOW);

  pinMode(schakelaar, INPUT_PULLUP);
  for (int i = 0; i < 5; i++) {
    pinMode(timerLeds[i], OUTPUT);
    digitalWrite(timerLeds[i], LOW);
  }
}

void loop() {
  int rawADC = analogRead(A0);

  float spanningA0 = (rawADC / 1023.0) * 3.2;
  float spanningSensor = spanningA0 * 2.0;
  float tempKelvin = spanningSensor * 100.0;
  float tempCelsius = tempKelvin - 273.15;


  if (tempCelsius < (gewensteTemp - hysterese)) {
    digitalWrite(ledKachel, HIGH);
    kachelAan = true;
  } else {
    digitalWrite(ledKachel, LOW);
    kachelAan = false;
  }

  if (digitalRead(schakelaar) == LOW && !timerActief) {
    timerActief = true;
    timerStart = millis(); 
  }

  if (timerActief) {
    unsigned long verstreken = millis() - timerStart;

    if (verstreken < 10000) {
      int aantalAan = 5 - (verstreken / 2000);
      for (int i = 0; i < 5; i++) {
        if (i < aantalAan) {
          digitalWrite(timerLeds[i], HIGH);
        } else {
          digitalWrite(timerLeds[i], LOW);
        }
      }
    } else {
      timerActief = false;
      for (int i = 0; i < 5; i++) {
        digitalWrite(timerLeds[i], LOW);
      }
    }
  }

  Serial.print("ADC: ");
  Serial.print(rawADC);
  Serial.print(" | Spanning A0: ");
  Serial.print(spanningA0);
  Serial.print(" V | Gewenst: ");
  Serial.print(gewensteTemp);
  Serial.print(" °C | Temp: ");
  Serial.print(tempCelsius);
  Serial.print(" °C | Kachel: ");
  if (kachelAan) {
    Serial.println("AAN");
  } else {
    Serial.println("UIT");
  }

  delay(200);
}