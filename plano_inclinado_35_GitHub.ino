/******************************************************
#
#  PROYECTO - CAPSTONE
#
#  Diplomado SAMNSUNG INNOVATION CAMPUS _ Codigo IoT
#
#  Programa para manejar secuencias de posicionamiento del
#  Plano Inclinado mediante el control de un servomotor
#
#  ARDUINO UNO
#
#  - Version de prueba
#
#  Eduardo Rodriguez
3  Fernando Ramírez
#                                 7 - diciembre - 2021
#
#*******************************************************/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo


int angulo_actual = 1;
int angulo_objetivo = 1;
int inicio_secuencia = 1;
int retardo_angulo = 100;

String msg_enviado;
char option;
String data;

int pinLED = 13;

void setup() {

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  
  Serial.begin(9600);

  /*******************************
   * Interruptores manuales *
   *******************************/
  pinMode(2, INPUT);         // Angulo de 1 grado. Captura de canica
  digitalWrite(2, HIGH);     // turn on pullup resistors
  pinMode(3, INPUT);          // Angulo de 20 grados. Posicion HORIZONTAL
  digitalWrite(3, HIGH);     // turn on pullup resistors
  pinMode(4, INPUT);          // Angulo de 40 grados. [30 grados EFECTIVOS]
  digitalWrite(4, HIGH);     // turn on pullup resistors
  pinMode(5, INPUT);          // Angulo de 60 grados [50 grados EFECTIVOS]
  digitalWrite(5, HIGH);     // turn on pullup resistors

  pinMode(7, OUTPUT);       // Manejo del solenoide de liberacion

  myservo.write(1);
}

int entrada_2;

void loop() {

  /*******************************
   * SIMULACIONES DE ANGULOS DE 
   * INCLINACION
   *******************************/
  if(!digitalRead(2)){
    angulo_objetivo = 1;  // Angulo de 1 grado. Captura de canica
    inicio_secuencia = 1;
  }

  if(!digitalRead(3)){
    angulo_objetivo = 20; // Angulo de 20 grados. Posicion HORIZONTAL
    inicio_secuencia = 1;
  }

  if(!digitalRead(4)){
    angulo_objetivo = 40; // Angulo de 40 grados. [30 grados EFECTIVOS]
    inicio_secuencia = 1;
  }

  if(!digitalRead(5)){
    angulo_objetivo = 60; // Angulo de 60 grados [50 grados EFECTIVOS]
    inicio_secuencia = 1;
  }
  
  if (angulo_objetivo != 1 && inicio_secuencia){
    ejecuta_secuencia_posicionamiento();
    inicio_secuencia = 0;
  } else {
    posiciona_plano_inclinado();
  }

}

void posiciona_plano_inclinado(){
  
 if (angulo_actual < angulo_objetivo) {
    for(int i=angulo_actual; i<=angulo_objetivo; i++){
      myservo.write(i);
      delay(retardo_angulo);
    }
  }

  if (angulo_actual > angulo_objetivo) {
    for(int i=angulo_actual; i>=angulo_objetivo; i--){
      myservo.write(i);
      delay(retardo_angulo);
    }
  }
  angulo_actual = angulo_objetivo;
}

void ejecuta_secuencia_posicionamiento(){

  int temp = angulo_objetivo;
  angulo_objetivo = 1;
  posiciona_plano_inclinado();
  delay(100);
  
  angulo_objetivo = 20;
  posiciona_plano_inclinado();
  delay(2000);
  
  angulo_objetivo = temp;
  posiciona_plano_inclinado();
  delay(2000);

  libera_esfera();
}

void libera_esfera(){
  digitalWrite(7, HIGH);
  delay(100);
  digitalWrite(7, LOW);
}
