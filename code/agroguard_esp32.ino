#include <DHT.h>

// === CONFIGURAÇÃO DO SENSOR DHT22 ===
#define DHTPIN 15         // Pino conectado ao DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// === PINOS DOS SENSORES E ATUADORES ===
const int vibPin     = 34;  // Potenciômetro simula vibração
const int pesoPin    = 35;  // LDR simula peso
const int ledPin     = 32;  // LED de alerta visual
const int buzzerPin  = 25;  // Buzzer de alerta sonoro (simulado)

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // === LEITURA DO SENSOR DHT22 ===
  float temp = dht.readTemperature();
  float umid = dht.readHumidity();

  Serial.print("Temperatura (°C): ");
  if (isnan(temp)) Serial.println("Erro na leitura!");
  else Serial.println(temp);

  Serial.print("Umidade (%): ");
  if (isnan(umid)) Serial.println("Erro na leitura!");
  else Serial.println(umid);

  // === SIMULAÇÃO DA VIBRAÇÃO DA ESTEIRA ===
  int vibracao = analogRead(vibPin);
  float vib = map(vibracao, 0, 4095, 0, 100);
  Serial.print("Vibração (%): ");
  Serial.println(vib);

  // === SIMULAÇÃO DO PESO NA BALANÇA ===
  int pesoBruto = analogRead(pesoPin);
  float pesoSimulado = map(pesoBruto, 0, 4095, 0, 50);
  Serial.print("Peso simulado (kg): ");
  Serial.println(pesoSimulado);

  // === ALERTA AUTOMÁTICO COM LED E BUZZER ===
  if (temp > 30 || vib > 70) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);  // 🔊 (sem som real no Wokwi)
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  delay(2000); // Aguarda 2 segundos antes da próxima leitura
}