
#include <x10.h>
#include <x10constants.h>
#include <SoftwareSerial.h>
SoftwareSerial BT1(7,8); // RX, TX recorder que se cruzan
#define zcPin 2         // the zero crossing detect pin
#define dataPin 3       // the X10 data out pin
#define repeatTimes 3   // how many times each X10 message should repeat
// in an electrically noisy environment, you  
// can set this higher.


// set up a new x10  library instance:
x10 myHouse =  x10(zcPin, dataPin);

#include <Servo.h>
Servo servo1;  // Crea un Objeto servo
int posicion;    // Variable de la posicion del servo

void setup() {
 Serial.begin(9600);
 myHouse.write(HOUSE_A, ALL_UNITS_OFF,repeatTimes);
 Serial.println("ACTIVANDO CASA DOMOTICA:");
 BT1.begin(9600);
 Serial.println("CASA DOMOTICA ACTIVADA EN ESPERA DE ORDENES:");
 
 servo1.attach(6);  //  Pin donde conectamos el servomotor (pin 6)
 CierraPuerta();
 
}

void loop() {
  char X = BT1.read();
  if(X=='A')
    encender_A1();   
  if(X=='B')
    apagar_A1();     
  if(X=='C')
    encender_A2();     
  if(X=='D')
    apagar_A2();     
  if(X=='H')
    encender_todo();     
  if(X=='G')
    apagar_todo();    
  if(X=='J') //Cerrar puerta
  CierraPuerta();
  if(X=='K') //Abrir puerta
  AbrePuerta();
}

void encender_A1()  //Encender cocina
{
  myHouse.write(HOUSE_A, UNIT_1,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);
  Serial.println("LUZ COCINA CONECTADA:");  
 } 
 
 
void apagar_A1()  //Apagar cocina
{
  myHouse.write(HOUSE_A, UNIT_1,repeatTimes);               
  myHouse.write(HOUSE_A, OFF,repeatTimes);
  Serial.println("LUZ COCINA DESCONECTADA:");
 } 
 
 void encender_A2()  //Encender pasillo
{
  myHouse.write(HOUSE_A, UNIT_2,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);
  Serial.println("LUZ PASILLO CONECTADA:");  
 } 
 
 
void apagar_A2()  //Apagar pasillo
{
  myHouse.write(HOUSE_A, UNIT_2,repeatTimes);               
  myHouse.write(HOUSE_A, OFF,repeatTimes);
  Serial.println("LUZ PASILLO DESCONECTADA:");  
 } 
 
 void encender_todo()  //Encender todo
{
  myHouse.write(HOUSE_A, UNIT_1,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);
  myHouse.write(HOUSE_A, UNIT_2,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);
  Serial.println("TODO CONECTADO:");  
 } 
 
 
void apagar_todo()  //Apagar todo
{
  myHouse.write(HOUSE_A, ALL_UNITS_OFF,repeatTimes);
  Serial.println("TODO APAGADO:");
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
