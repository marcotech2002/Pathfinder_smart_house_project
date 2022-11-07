#include "Ultrasonic.h"
#include <Servo.h>
#include <IRremote.h>

//Declarando os LEDs e sensores
const int LED = 4; // Portas digitais para LED's
const int LED1 = 8;
const int LDR = A5;  // Porta analógica para litura do sensor de luz
const int SERVO_PIN = 11; // Precisa ser um pino PWN
int IR_RECEIVE_PIN = 13; // Recebe o sinal do sensor infravermelho
IRrecv infraredReceiver(IR_RECEIVE_PIN);
decode_results results; //valor retornado do decoder 
Servo s; //declaração obj Servo
Ultrasonic ultrasonic(2, 3); // Trigger na porta 2 e Echo na porta 3

// variaveis de controle
float distanciaCM = 0;
int estado = 0;
int sentido = -1;
int ligado = 0;

void setup() 
{
  //Inicializando saídas, entradas e demais configurações dos componentes
  Serial.begin(9600);
  pinMode(LED, OUTPUT); 
  pinMode(LED1, OUTPUT);
  infraredReceiver.enableIRIn();
  s.attach(SERVO_PIN);
  s.write(0);
}

void loop() 
{
  ledDistancia();
  ledLuminosidade();
  controlePortao();
  delay(300);// espera de 300 milissegundos
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
  
  // criando as condições se a distancia for entre 30 cm e 20 cm
  if (distanciaCM <= 10 and distanciaCM >= 1) 
  {
    if(ligado == 0)
    {
      digitalWrite(LED, HIGH); //liga o LED
      ligado = 1;
    }
    else
    {
      digitalWrite(LED, LOW); //desliga o LED
      ligado = 0;
    }
  }

}

void ledLuminosidade()
{
  estado = 0;
  estado = analogRead(LDR);
  Serial.println("-------------------------------------------------------------------");
  Serial.print("Leitura do LDR: ");
  Serial.println(estado);
  
  if (estado > 900) //Se o estado for maior que 700 (pouca luminosidade)
    digitalWrite(LED1, HIGH); //Liga o LED1
  else
    digitalWrite(LED1, LOW);
}

void controlePortao()
{
  results.value = 0; // Zera os registradores
  if (infraredReceiver.decode(&results))// Verificar se algum valor foi recebido 
  {
    Serial.println("-------------------------------------------------------------------");
    Serial.print("Botao: "); // Escreve o código no serial monitor
    Serial.println(results.value, HEX);
    infraredReceiver.resume(); // Reinicializa o receptor
  }
  if(results.value == 0xFFA25D) // Verifica se o botão 1 foi pressionado
  {   
    if(sentido == -1)
    {
      Serial.print("Movimento do portão: ");
      Serial.println("Abriu");
      sentido = 1;
      s.write(90);
    }
    else
    {
      Serial.print("Movimento do portão: ");
      Serial.println("Fechou");
      sentido = -1;
      s.write(0); 
    }
  }
}
