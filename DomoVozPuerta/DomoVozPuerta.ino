#include <Servo.h>
Servo servo1;  // Crea un Objeto servo
int posicion;    // Variable de la posicion del servo

void setup() {
 Serial.begin(9600);
 servo1.attach(9);  //  Pin donde conectamos el servomotor (pin 9)  
 pinMode(3,OUTPUT); //Cocina
 pinMode(4,OUTPUT); //Pasillo
 pinMode(5,OUTPUT); //Comedor
 
 CierraPuerta();
 

}

void loop() {
  char X = Serial.read();
  if(X=='A')
    digitalWrite(3,HIGH);
  if(X=='B')
    digitalWrite(3,LOW);
  if(X=='C')
    digitalWrite(4,HIGH);
  if(X=='D')
    digitalWrite(4,LOW);
  if(X=='E')
    digitalWrite(5,HIGH);
  if(X=='F')
    digitalWrite(5,LOW);
  if(X=='G') //Apagar todo
  apagar();
  if(X=='H') //Encender todo
  encender();
  if(X=='I') //Encender todo
  secuencia(); //Secuencia
  if(X=='J') //Cerrar puerta
  CierraPuerta();
  if(X=='K') //Abrir puerta
  AbrePuerta();
}

void apagar()
{
 digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
 } 
 
 
void encender()
{
 digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
 } 
 
 void secuencia()
{
 apagar();
 digitalWrite(3,HIGH);
 delay(500);
 digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  delay(500);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  delay(500);
  digitalWrite(5,LOW);
 }

void AbrePuerta()
{

  posicion = 0;            // Establecemos el valor de la posicion a 90º para apertura
  posicion = map(posicion, 0, 255, 0, 179);     // Establecemos la relacion entre los grados de giro y el PWM
  /* Con el mapa de valores anterior establecemos una relacin proporcional */
  /* entre el pulso minimo 0 con el grado minimo, 0 tambien y el pulso maximo*/
  /* 1023 con el grado maximo, 179*/
  servo1.write(posicion);                  // Escribimos la posicion con el mapa de valores al servo
  delay(150);                           // Y le damos un tiempo para que sea capaz de moverse
} 

void CierraPuerta()
{

  posicion = 90;            // Establecemos el valor de la posicion a 179º para cierre
  posicion = map(posicion, 0, 255, 0, 179);     // Establecemos la relacion entre los grados de giro y el PWM
  /* Con el mapa de valores anterior establecemos una relacin proporcional */
  /* entre el pulso minimo 0 con el grado minimo, 0 tambien y el pulso maximo*/
  /* 1023 con el grado maximo, 179*/
  servo1.write(posicion);                  // Escribimos la posicion con el mapa de valores al servo
  delay(150);                           // Y le damos un tiempo para que sea capaz de moverse
}
