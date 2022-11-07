//Bibliotecas
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
//#include <Servo.h>

//Declarando os LEDs e sensores
#define LED 9                  //pino da iluminação interna da casa
#define LED2 10
#define LED3 11
#define LED4 12
#define ONE_WIRE_BUS 2             //pino do sensor de temperatura
//#define ventilador 3               //pino do ventilador
const int b1;
const int LED1 = 8;

// Variáveis de controle
int cont = 0;
int flag = 0;
float tempMin = 999, tempMax = 0;  //temperaturas minima e máxima

//criação das instâncias
SoftwareSerial bt(10, 11);            //bluetooth. Pinos de TX e RX, respectivamente
OneWire oneWire(ONE_WIRE_BUS);        //instância relacionada ao sensor de temperatura.
DallasTemperature sensors(&oneWire);  //instância relacionada ao sensor de temperatura.
DeviceAddress sensorTemp;

void setup() 
{
  Serial.begin(9600);
  bt.begin(9600);   // inicializando o serial do bluetooth
  sensors.begin();  //inicilaizando o sensor de temperatura
  pinMode(ledcasa, OUTPUT);
  pinMode(ventilador, OUTPUT);
  if (!sensors.getAddress(sensorTemp, 0)) {
    Serial.println("Sensores nao encontrados !");
  }
}

void loop() 
{
  iluminacaoInterna();
  sensorTemperatura();
}

//funções
void iluminacaoInterna() 
{
  if (bt.available() > 0) 
  {
    b1 = bt.read();
    if (b1 == 49) 
    {
      cont++;
      flag = cont % 2;
    }
    if (flag == 0) 
      digitalWrite(ledcasa, HIGH); 
    else if (flag == 1) 
      digitalWrite(ledcasa, LOW);
  }
}

void sensorTemperatura() 
{
  sensors.requestTemperatures();  //lê a informação do sensor
  float tempC = sensors.getTempC(sensorTemp);

  if (tempC < tempMin)
    tempMin = tempC;
  if (tempC > tempMax) 
    tempMax = tempC;
  // if (tempC >= 30) 
  // {
  //   analogWrite(ventilador, HIGH);
  //   delay(3000);
  // } 
  // else analogWrite(ventilador, LOW);

  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Min : ");
  Serial.print(tempMin);
  Serial.print(" Max : ");
  Serial.println(tempMax);

  delay(10);
}