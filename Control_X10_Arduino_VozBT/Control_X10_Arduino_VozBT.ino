
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

void setup() {
 Serial.begin(9600);
 myHouse.write(HOUSE_A, ALL_UNITS_OFF,repeatTimes);
 Serial.println("ACTIVANDO CASA DOMOTICA:");
 BT1.begin(9600);
 Serial.println("CASA DOMOTICA ACTIVADA EN ESPERA DE ORDENES:");
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
 
 
