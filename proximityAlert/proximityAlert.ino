#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // Biblioteca utilizada para fazer a comunicação com o display 16x2

#define col 16     // Define o numero de colunas do display
#define lin 2      // Define o numero de linhas do display
#define ende 0x3F  // Endereço do display

LiquidCrystal_I2C lcd(ende, col, lin);  // Chamada da função LiquidCrystal para ser usada com o I2C

// Define os pinos do sensor ultrassônico e do buzzer
const int triggerPin = 9;
const int echoPin = 10;
const int buzzerPin = 8;

// Variáveis para armazenar o tempo de ida e volta do ultrassom
long duration;
int distance;

// Distância limite para acionar o buzzer.
int max_distance = 5;

void setup() {

  Serial.begin(9600);

  // Define os pinos como saída ou entrada
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Desliga o buzzer no início
  digitalWrite(buzzerPin, LOW);

  lcd.init();       // Inicia a comunicação com o display
  lcd.backlight();  // Liga a luz do display
  lcd.clear();      // Limpa a tela do display
}

void loop() {
  // Aciona um pulso no pino Trigger do sensor ultrassônico
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Mede a duração do pulso Echo
  duration = pulseIn(echoPin, HIGH);

  // Calcula a distância em centímetros
  distance = duration * 0.034 / 2;

  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Distancia:");
  lcd.setCursor(6, 1);
  lcd.print(distance);
  lcd.setCursor(12, 1);
  lcd.print("cm");

  // Verifica se a distância é menor que um valor de limite (por exemplo, 20 cm)
  if (distance < max_distance) {
    // Se a distância for menor que 20 cm, ativa o buzzer
    digitalWrite(buzzerPin, HIGH);
  } else {
    // Caso contrário, desliga o buzzer
    digitalWrite(buzzerPin, LOW);
  }

  // Aguarda um curto período de tempo antes de fazer a próxima leitura
  delay(1000);
  lcd.clear();
}
