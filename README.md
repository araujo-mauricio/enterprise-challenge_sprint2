# Enterprise Challenge – Sprint 2 – Reply

## Continuidade da Sprint 1
Esta entrega dá continuidade ao projeto **AgroGuard**, iniciado na Sprint 1, que visa antecipar falhas em equipamentos de linha de produção agroindustrial (como esteiras, seladoras e sensores de peso). Agora, evoluímos da arquitetura digital teórica para a **simulação prática da coleta de dados em tempo real**, representando um processo industrial digitalizado.

---

## Objetivo da Sprint 2
Simular um circuito funcional com **ESP32 e sensores virtuais** que representem situações reais de falha em equipamentos agroindustriais. A coleta e leitura dos dados permitirão realizar uma primeira análise exploratória do processo, validando a proposta do sistema AgroGuard.

---

## Sensores Utilizados e Justificativas

| Equipamento | Sensor Simulado | Finalidade |
|------------|------------------|------------|
| **Seladora** | DHT22 (Temperatura/Umidade) | Detectar superaquecimento durante operação |
| **Esteira transportadora** | Potenciômetro (Vibração) | Monitorar oscilações anormais que indiquem falha mecânica |
| **Sensor de peso** | LDR (simula ruído/luminosidade) | Simular falha na leitura de peso em embalagem |

---

## Montagem do Circuito
- A montagem foi feita na plataforma **Wokwi** com ESP32.
- Cada sensor foi configurado para simular os comportamentos esperados.
- A leitura dos dados é exibida via Serial.println().

> ![Circuito Simulado](docs/print_circuito.png)

---

## Trecho do Código ESP32

```cpp
#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int vibPin = 34;
const int pesoPin = 35;
const int ledPin = 32;
const int buzzerPin = 25;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  float temp = dht.readTemperature();
  float umid = dht.readHumidity();
  int vibracao = analogRead(vibPin);
  float vib = map(vibracao, 0, 4095, 0, 100);
  int pesoBruto = analogRead(pesoPin);
  float pesoSimulado = map(pesoBruto, 0, 4095, 0, 50);

  Serial.print("Temperatura (C): "); Serial.print(temp);
  Serial.print(" | Umidade (%): "); Serial.print(umid);
  Serial.print(" | Vibração (%): "); Serial.print(vib);
  Serial.print(" | Peso (kg): "); Serial.println(pesoSimulado);

  if (temp > 30 || vib > 70) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  delay(2000);
}

---

## Análise Exploratória Inicial

O gráfico abaixo representa a variação simulada da temperatura ao longo do tempo, coletada virtualmente a partir do sensor DHT22.
Essa visualização permite entender o comportamento do sistema em cenários críticos (ex: temperaturas acima de 30 °C), que disparam os alertas visuais e sonoros.

Foram realizadas 20 simulações de leitura.

Os dados foram salvos em .csv e representados graficamente.

![Gráfico](grafico/analise_inicial.png)


### Insight Inicial:
Durante o monitoramento, foi observado que altos níveis de vibração coincidem com aumentos de temperatura, indicando risco de superaquecimento da seladora. Essa correlação pode alimentar futuros modelos preditivos.

---

## Estrutura do Repositório

enterprise-challenge_sprint2/
├── docs/
│ └── circuito_simulado.png
├── code/
│ └── agroguard_esp32.ino
├── data/
│ └── dados_coletados.csv
├── grafico/
│ └── analise_inicial.png
└── README.md


## Conclusão

A Sprint 2 representa uma evolução concreta do AgroGuard, saindo do planejamento para uma simulação realista da coleta de dados. Esses dados alimentam a etapa futura de análise preditiva com IA, permitindo antecipação de falhas e maior segurança no processo industrial agroalimentar.

---

## Integrantes

- Mauricio Araújo – RM566040
- Igor Herson – RM563980