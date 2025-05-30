// Definição pinos
const int trigPin = 9;
const int echoPin = 8;
const int pesoPin = A0;

const int ledVerde = 2;
const int ledAmarelo = 3;
const int ledVermelho = 4;
const int buzzer = 5;

// Variáveis medição
long duracao;
float distancia;
int peso;

void setup() {
  Serial.begin(9600);

  // Configurar pinos dos sensores
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pesoPin, INPUT);

  // Configurar LEDs e buzzer
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Leitura nível de água
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH);
  distancia = duracao * 0.034 / 2;  // em cm

  // Ler peso
  peso = analogRead(pesoPin); // valor de 0 a 1023

  // Exibir dados no Serial Monitor
  Serial.print("Distancia (Nivel Agua): ");
  Serial.print(distancia);
  Serial.print(" cm | Peso (Obstrução): ");
  Serial.println(peso);

  // Alerta
  if (distancia < 5 || peso > 800) {  // risco crítico
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, HIGH);
  }
  else if (distancia < 10 || peso > 500) { // atenção
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, LOW);
  }
  else {  // normal
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(buzzer, LOW);
  }

  delay(1000);  // Atualiza a cada segundo
}
