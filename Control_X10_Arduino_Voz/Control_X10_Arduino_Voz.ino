
#include <x10.h>
#include <x10constants.h>

#define zcPin 2         // the zero crossing detect pin
#define dataPin 3       // the X10 data out pin
#define repeatTimes 1   // how many times each X10 message should repeat
// in an electrically noisy environment, you  
// can set this higher.


// set up a new x10  library instance:
x10 myHouse =  x10(zcPin, dataPin);

void setup() {
 Serial.begin(9600);
 myHouse.write(HOUSE_A, ALL_UNITS_OFF,repeatTimes);
}

void loop() {
  char X = Serial.read();
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

void encender_A1()
{
  myHouse.write(HOUSE_A, UNIT_1,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);  
 } 
 
 
void apagar_A1()
{
  myHouse.write(HOUSE_A, UNIT_1,repeatTimes);               
  myHouse.write(HOUSE_A, OFF,repeatTimes);
 } 
 
 void encender_A2()
{
  myHouse.write(HOUSE_A, UNIT_2,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);  
 } 
 
 
void apagar_A2()
{
  myHouse.write(HOUSE_A, UNIT_2,repeatTimes);               
  myHouse.write(HOUSE_A, OFF,repeatTimes);  
 } 
 
 void encender_todo()
{
  myHouse.write(HOUSE_A, UNIT_1,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);
  myHouse.write(HOUSE_A, UNIT_2,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);  
 } 
 
 
void apagar_todo()
{
  myHouse.write(HOUSE_A, ALL_UNITS_OFF,repeatTimes);
 } 
 
 
