#include "Ultrasonic.h"

//Declarando os LEDs e sensores
const int LED = 4;
const int LED1 = 8;
const int LDR = A5;
Ultrasonic ultrasonic(2, 3); // Trigger na porta 2 e Echo na porta 3

// variaveis de controle
float distanciaCM = 0;
int estado = 0;

void setup() 
{
  //Inicializando saídas, entradas e demais configurações dos componentes
  Serial.begin(9600);
  pinMode(LED, OUTPUT); 
  pinMode(LED1, OUTPUT);
}

void loop() 
{

  ledDistancia();
  ledLuminosidade();
  delay(500);// espera de 500 milissegundos
}

void ledDistancia() 
{
  //Lendo o valor do sensor em centímetros
  distanciaCM = 0;
  distanciaCM = ultrasonic.read(CM);

  Serial.println("-------------------------------------------------------------------");
  Serial.print("Leitura do ultrassonico: ");
  Serial.print(distanciaCM);// mostrar a distancia na porta serial
  Serial.println(" cm");// colocar unidade de medida

  //Desliga o LED
  digitalWrite(LED, LOW);
  
  // criando as condições se a distancia for entre 30 cm e 20 cm
  if (distanciaCM <= 5 and distanciaCM >= 1) 
    digitalWrite(LED, HIGH); //liga o LED
}

void ledLuminosidade()
{
  estado = 0;
  estado = analogRead(LDR);
  Serial.println("-------------------------------------------------------------------");
  Serial.print("Leitura do LDR: ");
  Serial.println(estado);
  delay(30);
  
  if (estado > 700 ) //Se o estado for maior que 700 (pouca luminosidade)
    digitalWrite(LED1, HIGH); //Liga o LED1
  else
    digitalWrite(LED1, LOW);
}
