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

// Define os pinos dos botões que vao incrementar e decrementar a distância.

// Variáveis para armazenar o tempo de ida e volta do ultrassom
long duration;
int distance;

// Distância limite para acionar o buzzer.
int max_distance = 10;

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

  // Mede a duração do pulso.
  duration = pulseIn(echoPin, HIGH);

  // Calcula a distância em centímetros
  distance = duration * 0.034 / 2;

  // Display LCD.
  // Dist: xxcm
  // Limite: xxcm
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("cm");
  lcd.setCursor(0, 1);
  lcd.print("Limit: ");
  lcd.print(max_distance);
  lcd.print("cm");

  // Lê o valor do potenciômetro e o usa como o novo valor de max_distance
  int potValue = analogRead(A5);
  max_distance = map(potValue, 0, 1023, 0, 100);

  // De acordo com a distância muda a frequência dos bips.
  int num_bips = 0;
  if (distance < max_distance) {
    int frequency = 528;
    if (distance < max_distance / 4) {
      num_bips = 1;
    } 
    else if (distance < max_distance / 2) {
      num_bips = 3;
      frequency = 392;
    } 
    else {
      num_bips = 5;
      frequency = 100;
    }
      tone(buzzerPin, frequency);
  } 
  else {
    noTone(buzzerPin);
  }

  // Emitir o som com base no número de bips
  for (int i = 0; i < num_bips; i++) {
    delay(25);
    noTone(buzzerPin);
    delay(25);
  }

  delay(200);
  lcd.clear();
}
