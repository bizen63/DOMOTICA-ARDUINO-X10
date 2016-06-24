#include <SPI.h>
#include <x10.h>
#include <x10constants.h> 
#include <Ethernet.h> //Declaración de la direcciones MAC e IP. También del puerto 80 
byte mac[]={0xDE,0xAD,0xBE,0xEF,0xFE,0xED}; //MAC 
IPAddress ip(192, 168, 1, 177); //IP 
EthernetServer servidor(80); 
int PIN_LED0=4;
int PIN_LED1=5;
int PIN_LED2=6;
int PIN_LED3=7; 
String readString=String(30); //lee los caracteres de una secuencia en una cadena.
//Los strings se representan como arrays de caracteres (tipo char) 
String state0=String(3);
String state1=String(3);
String state2=String(3);
String state3=String(3);
String state4=String(8);
/* Configuracion del sistema X10 */
#define zcPin 2         // Pin detector de pasos por cero.
#define dataPin 3       // Pin de salida de datos X10
#define repeatTimes 1   // Veces que se repite el mensaje X10 en instalaciones con
//mucho ruido electrico debemos incrementar este numero

// Ahora creamos una nueva instancia a la libreria X10:
x10 myHouse =  x10(zcPin, dataPin);
/* Fin Configuracion del sistema X10 */

#include <Servo.h>
Servo servo1;  // Crea un Objeto servo
int posicion;    // Variable de la posicion del servo

void setup() {
Ethernet.begin(mac, ip); //Inicializamos con las direcciones asignadas 
servidor.begin(); 
pinMode(PIN_LED0,OUTPUT);
pinMode(PIN_LED1,OUTPUT);
pinMode(PIN_LED2,OUTPUT);
pinMode(PIN_LED3,OUTPUT);
digitalWrite(PIN_LED0,LOW);
digitalWrite(PIN_LED1,LOW);
digitalWrite(PIN_LED2,LOW);
digitalWrite(PIN_LED3,LOW);
state0="OFF";
state1="OFF";
state2="OFF";
state3="OFF";
state4="CERRADA";
servo1.attach(9);  //  Pin donde conectamos el servomotor (pin 9)
 CierraPuerta();
}
void loop() {
  //EthernetClient Crea un cliente que se puede conectar a 
  //una dirección específica de Internet IP
EthernetClient cliente= servidor.available(); 
if(cliente) {
boolean lineaenblanco=true; 
while(cliente.connected()) {
if(cliente.available()) {
char c=cliente.read(); 
if(readString.length()<30) {
readString.concat(c);
//Cliente conectado
//Leemos petición HTTP caracter a caracter
//Almacenar los caracteres en la variable readString
} 
if(c=='\n' && lineaenblanco) //Si la petición HTTP ha finalizado 
{
int LED0 = readString.indexOf("LED0="); 
if(readString.substring(LED0,LED0+6)=="LED0=T") {
digitalWrite(PIN_LED0,HIGH);
encender_A1(); //Encender cocina
state0="ON"; } 
else if (readString.substring(LED0,LED0+6)=="LED0=F") {
digitalWrite(PIN_LED0,LOW);
apagar_A1(); //Apagar cocina 
state0="OFF";
}
int LED1 = readString.indexOf("LED1=");
if(readString.substring(LED1,LED1+6)=="LED1=T") {
digitalWrite(PIN_LED1,HIGH);
encender_A2(); //Encender comedor
state1="ON"; } 
else if (readString.substring(LED1,LED1+6)=="LED1=F") {
digitalWrite(PIN_LED1,LOW);
apagar_A2(); //Apagar comedor 
state1="OFF";
}
int LED2 = readString.indexOf("LED2=");
if(readString.substring(LED2,LED2+6)=="LED2=T") {
digitalWrite(PIN_LED2,HIGH);
encender_A3(); //Encender dormitorio
state2="ON"; } 
else if (readString.substring(LED2,LED2+6)=="LED2=F") {
digitalWrite(PIN_LED2,LOW);
apagar_A3(); //Apagar dormitorio 
state2="OFF";
}
int LED3 = readString.indexOf("LED3=");
if(readString.substring(LED3,LED3+6)=="LED3=T") {
digitalWrite(PIN_LED3,HIGH);
encender_A4(); //Encender horno
state3="ON"; } 
else if (readString.substring(LED3,LED3+6)=="LED3=F") {
digitalWrite(PIN_LED3,LOW);
apagar_A4(); //Apagar horno 
state3="OFF";
}
int TODO = readString.indexOf("TODO=");
if(readString.substring(TODO,TODO+6)=="TODO=T") {
encender_todo(); //Encender todo
state0="ON";
state1="ON";
state2="ON";
state3="ON"; }
else if (readString.substring(TODO,TODO+6)=="TODO=F") {
digitalWrite(PIN_LED3,LOW);
apagar_todo(); 
state0="OFF";
state1="OFF";
state2="OFF";
state3="OFF";
}

int DOOR = readString.indexOf("DOOR=");
if(readString.substring(TODO,TODO+6)=="DOOR=T") {
AbrePuerta(); //ABRIR PUERTA
state4="ABIERTA";
}
else if (readString.substring(TODO,TODO+6)=="DOOR=F") {
CierraPuerta(); //CERRAR PUERTA
state4="CERRADA";
}

//Cabecera HTTP estándar
cliente.println("HTTP/1.1 200 OK"); 
cliente.println("Content-Type: text/html"); 
cliente.println(); //Página Web en HTML 
cliente.println("<html>"); 
cliente.println("<head>"); 
cliente.println("<title>LAMPARAS ON/OFF</title>"); 
cliente.println("</head>");
cliente.println("<body width=100% height=100%>"); 
cliente.println("<center>"); 
cliente.println("<h1>LUZ COCINA ON/OFF</h1>");
cliente.print("<br><br>"); 
cliente.print("Estado LUZ COCINA: "); 
cliente.print(state0); 
cliente.print("<br><br><br><br>"); 
cliente.println("<input type=submit value=ON style=width:200px;height:75px onClick=location.href='./?LED0=T\'>"); 
cliente.println("<input type=submit value=OFF style=width:200px;height:75px onClick=location.href='./?LED0=F\'>"); 
cliente.println("</center>"); 

cliente.println("<center>"); 
cliente.println("<h1>LUZ COMEDOR ON/OFF</h1>");
cliente.print("<br><br>"); 
cliente.print("Estado de LUZ COMEDOR: "); 
cliente.print(state1); 
cliente.print("<br><br><br><br>"); 
cliente.println("<input type=submit value=ON style=width:200px;height:75px onClick=location.href='./?LED1=T\'>"); 
cliente.println("<input type=submit value=OFF style=width:200px;height:75px onClick=location.href='./?LED1=F\'>"); 
cliente.println("</center>"); 

cliente.println("<center>"); 
cliente.println("<h1>LUZ DORMITORIO ON/OFF</h1>");
cliente.print("<br><br>"); 
cliente.print("Estado de LUZ DORMITORIO: "); 
cliente.print(state2); 
cliente.print("<br><br><br><br>"); 
cliente.println("<input type=submit value=ON style=width:200px;height:75px onClick=location.href='./?LED2=T\'>"); 
cliente.println("<input type=submit value=OFF style=width:200px;height:75px onClick=location.href='./?LED2=F\'>"); 
cliente.println("</center>"); 

cliente.println("<center>"); 
cliente.println("<h1>CONEXION HORNO ON/OFF</h1>");
cliente.print("<br><br>"); 
cliente.print("Estado de CONEXION HORNO: "); 
cliente.print(state3); 
cliente.print("<br><br><br><br>"); 
cliente.println("<input type=submit value=ON style=width:200px;height:75px onClick=location.href='./?LED3=T\'>"); 
cliente.println("<input type=submit value=OFF style=width:200px;height:75px onClick=location.href='./?LED3=F\'>"); 
cliente.println("</center>"); 


cliente.println("<h1>ESTADO PUERTA ABIERTA/CERRADA</h1>");
cliente.print("<br><br>"); 
cliente.print("Estado de la PUERTA: "); 
cliente.print(state4); 
cliente.print("<br><br><br><br>"); 
cliente.println("<input type=submit value=ON style=width:200px;height:75px onClick=location.href='./?DOOR=T\'>"); 
cliente.println("<input type=submit value=OFF style=width:200px;height:75px onClick=location.href='./?DOOR=F\'>"); 
cliente.println("</center>"); 


cliente.println("</body>"); 
cliente.println("</html>"); 
cliente.stop();
//Cierro conexión con el cliente 
readString="";
}
}
}
}
}

void encender_A1() //Encender cocina
{
  myHouse.write(HOUSE_A, UNIT_1,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);  
 } 
 
 
void apagar_A1() //Apagar cocina
{
  myHouse.write(HOUSE_A, UNIT_1,repeatTimes);               
  myHouse.write(HOUSE_A, OFF,repeatTimes);
 } 
 
 void encender_A2() //Encender comedor
{
  myHouse.write(HOUSE_A, UNIT_2,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);  
 } 
 
 
void apagar_A2() //Apagar comedor
{
  myHouse.write(HOUSE_A, UNIT_2,repeatTimes);               
  myHouse.write(HOUSE_A, OFF,repeatTimes);  
 } 

void encender_A3() //Encender dormitorio
{
  myHouse.write(HOUSE_A, UNIT_3,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);  
 } 
void apagar_A3() //Apagar dormitorio
{
  myHouse.write(HOUSE_A, UNIT_3,repeatTimes);               
  myHouse.write(HOUSE_A, OFF,repeatTimes);
 } 
 
 void encender_A4() //Encender horno
{
  myHouse.write(HOUSE_A, UNIT_4,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);  
 } 
 
 
void apagar_A4() //Apagar horno
{
  myHouse.write(HOUSE_A, UNIT_4,repeatTimes);               
  myHouse.write(HOUSE_A, OFF,repeatTimes);  
 } 
  
 void encender_todo() //Encender todo
{
  myHouse.write(HOUSE_A, UNIT_1,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);
  myHouse.write(HOUSE_A, UNIT_2,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);
  myHouse.write(HOUSE_A, UNIT_3,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);
  myHouse.write(HOUSE_A, UNIT_4,repeatTimes);               
  myHouse.write(HOUSE_A, ON,repeatTimes);
  digitalWrite(PIN_LED0,HIGH);
  digitalWrite(PIN_LED1,HIGH);
  digitalWrite(PIN_LED2,HIGH);
  digitalWrite(PIN_LED3,HIGH);  
 } 
 
 void apagar_todo() //Apagar todo
{
  myHouse.write(HOUSE_A, ALL_UNITS_OFF,repeatTimes);
  digitalWrite(PIN_LED0,LOW);
  digitalWrite(PIN_LED1,LOW);
  digitalWrite(PIN_LED2,LOW);
  digitalWrite(PIN_LED3,LOW); 
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
