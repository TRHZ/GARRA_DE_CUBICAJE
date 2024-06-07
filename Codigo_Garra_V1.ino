#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define BT_RX 10  // Pin RX del módulo Bluetooth
#define BT_TX 11  // Pin TX del módulo Bluetooth
#define RELAY_PIN 13

SoftwareSerial BTSerial(BT_RX, BT_TX);  // Puerto serie virtual para el Bluetooth
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servoGarra, servoMano1, servoMano2, servoBase, servoCodo, servoHombro;

int anguloInicial = 0;
int anguloInicial1 = 90;
int anguloInicial2 = 180;
char estadoRele = '0';

unsigned long tiempoRele = 0;
const unsigned long duracionRele = 5000;

void setupServos() {
  servoGarra.attach(2);
  servoMano1.attach(3);
  servoMano2.attach(4);
  servoBase.attach(5);
  servoCodo.attach(6);
  servoHombro.attach(7);
}

void setup() {
  lcd.init();
  lcd.backlight();

  setupServos();
  servoGarra.write(60);
  servoMano1.write(anguloInicial);
  servoMano2.write(anguloInicial1);
  servoBase.write(anguloInicial);
  servoCodo.write(50);
  servoHombro.write(anguloInicial2);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Relé apagado al inicio

  BTSerial.begin(9600);
  Serial.begin(9600);  // Para depuración
}

void mostrarPosicionServo(int anguloFinal) {
  lcd.setCursor(0, 1);
  lcd.print("Posicion: ");
  lcd.print(anguloFinal);
}

void moverServo(Servo &servo, int anguloInicial, int anguloFinal, int paso, int retardo) {
  int angulo = anguloInicial;
  while (angulo != anguloFinal) {
    if (anguloInicial < anguloFinal) {
      angulo = min(angulo + paso, anguloFinal);
    } else {
      angulo = max(angulo - paso, anguloFinal);
    }
    servo.write(angulo);
    delay(retardo);
  }
}


void secuencia1() {
  // Pasos
  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(130);
  moverServo(servoHombro, anguloInicial2, 130, 1, 40);
  delay(100);

  // Codo baja
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Codo");
  mostrarPosicionServo(120);
  moverServo(servoCodo, anguloInicial1, 120, 1, 40);
  delay(100);

  // Baja Mano 1
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mano1");
  mostrarPosicionServo(37);
  moverServo(servoMano1, anguloInicial, 37, 1, 40);
  delay(100);

  // Cerramos Garra
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garra");
  mostrarPosicionServo(15.5);
  moverServo(servoGarra, 60, 15.5, 1, 40);
  delay(100);

  // Hombro sube
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(anguloInicial2);
  moverServo(servoHombro, 130, anguloInicial2, 1, 40);
  delay(100);

  // Gira la base
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Base");
  mostrarPosicionServo(45);
  moverServo(servoBase, anguloInicial, 45, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(130);
  moverServo(servoHombro, anguloInicial2, 130, 1, 40);
  delay(100);

  // Codo baja
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Codo");
  mostrarPosicionServo(100);
  moverServo(servoCodo, 120, 100, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(120);
  moverServo(servoHombro, 130, 120, 1, 40);
  delay(100);

  // Abre Garra
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garra");
  mostrarPosicionServo(60);
  moverServo(servoGarra, 15.5, 60, 1, 40);
  delay(100);

  // Hombro sube
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(anguloInicial2);
  moverServo(servoHombro, 130, anguloInicial2, 1, 40);
  delay(100);

  // Gira la base
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Base");
  mostrarPosicionServo(anguloInicial);
  moverServo(servoBase, 45, anguloInicial, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(120);
  moverServo(servoHombro, anguloInicial2, 120, 1, 40);
  delay(100);

  // Codo baja
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Codo");
  mostrarPosicionServo(80);
  moverServo(servoCodo, anguloInicial1, 80, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(110);
  moverServo(servoHombro, 120, 110, 1, 40);
  delay(100);

  // Baja Mano 1
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mano1");
  mostrarPosicionServo(20);
  moverServo(servoMano1, 37, 20, 1, 40);
  delay(100);

  // Cerramos Garra
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garra");
  mostrarPosicionServo(15.5);
  moverServo(servoGarra, 60, 15.5, 1, 40);
  delay(100);

  // Hombro sube
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(140);
  moverServo(servoHombro, 110, 140, 1, 40);
  delay(100);

  // Gira la base
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Base");
  mostrarPosicionServo(45);
  moverServo(servoBase, anguloInicial, 45, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(130);
  moverServo(servoHombro, 140, 130, 1, 40);
  delay(100);

  // Codo baja
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Codo");
  mostrarPosicionServo(100);
  moverServo(servoCodo, anguloInicial1, 100, 1, 40);
  delay(100);

  // Baja Mano 1
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mano1");
  mostrarPosicionServo(35);
  moverServo(servoMano1, 20, 35, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(127);
  moverServo(servoHombro, 130, 127, 1, 40);
  delay(100);

  // Abre Garra
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garra");
  mostrarPosicionServo(60);
  moverServo(servoGarra, 15.5, 60, 1, 40);
  delay(100);

  // Hombro sube
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(anguloInicial2);
  moverServo(servoHombro, 127, anguloInicial2, 1, 40);
  delay(100);

  // Gira la base
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Base");
  mostrarPosicionServo(anguloInicial);
  moverServo(servoBase, 45, anguloInicial, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(120);
  moverServo(servoHombro, anguloInicial2, 120, 1, 40);
  delay(100);

  // Codo sube
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Codo");
  mostrarPosicionServo(65);
  moverServo(servoCodo, 100, 65, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(105);
  moverServo(servoHombro, 120, 105, 1, 40);
  delay(100);

  // Baja Mano 1
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mano1");
  mostrarPosicionServo(43);
  moverServo(servoMano1, 35, 43, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(100);
  moverServo(servoHombro, 105, 100, 1, 40);
  delay(100);

  // Cerramos Garra
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garra");
  mostrarPosicionServo(15.5);
  moverServo(servoGarra, 60, 15.5, 1, 40);
  delay(100);

  // Hombro sube
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(140);
  moverServo(servoHombro, 100, 140, 1, 40);
  delay(100);

  // Gira la base
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Base");
  mostrarPosicionServo(45);
  moverServo(servoBase, anguloInicial, 45, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(135);
  moverServo(servoHombro, 140, 135, 1, 40);
  delay(100);

  // Codo baja
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Codo");
  mostrarPosicionServo(105);
  moverServo(servoCodo, 65, 105, 1, 40);
  delay(100);

  // Abre Garra
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garra");
  mostrarPosicionServo(60);
  moverServo(servoGarra, 15.5, 60, 1, 40);
  delay(100);
  digitalWrite(RELAY_PIN, HIGH);
  estadoRele = '1';
  tiempoRele = millis();  // Marca el tiempo en el que se encendió el relé
}

void secuencia2() {
  // Pasos
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(120);
  moverServo(servoHombro, anguloInicial2, 120, 1, 40);
  delay(100);

  // Codo baja
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Codo");
  mostrarPosicionServo(65);
  moverServo(servoCodo, anguloInicial1, 65, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(105);
  moverServo(servoHombro, 120, 105, 1, 40);
  delay(100);

  // Baja Mano 1
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mano1");
  mostrarPosicionServo(43);
  moverServo(servoMano1, anguloInicial, 43, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(100);
  moverServo(servoHombro, 105, 100, 1, 40);
  delay(100);

  // Cerramos Garra
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garra");
  mostrarPosicionServo(15.5);
  moverServo(servoGarra, 60, 15.5, 1, 40);
  delay(100);

  // Hombro sube
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(140);
  moverServo(servoHombro, 100, 140, 1, 40);
  delay(100);

  // Gira la base
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Base");
  mostrarPosicionServo(45);
  moverServo(servoBase, anguloInicial, 65, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(120);
  moverServo(servoHombro, 140, 120, 1, 40);
  delay(100);

  // Codo baja
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Codo");
  mostrarPosicionServo(100);
  moverServo(servoCodo, 65, 100, 1, 40);
  delay(100);

  // Abre Garra
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garra");
  mostrarPosicionServo(60);
  moverServo(servoGarra, 15.5, 60, 1, 40);
  delay(100);

  // Hombro sube
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(140);
  moverServo(servoHombro, 115, 140, 1, 40);
  delay(100);

  // Gira la base
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Base");
  mostrarPosicionServo(anguloInicial);
  moverServo(servoBase, 65, anguloInicial, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(130);
  moverServo(servoHombro, 140, 130, 1, 40);
  delay(100);

  // Codo baja
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Codo");
  mostrarPosicionServo(120);
  moverServo(servoCodo, 100, 120, 1, 40);
  delay(100);

  // Baja Mano 1
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mano1");
  mostrarPosicionServo(37);
  moverServo(servoMano1, 43, 37, 1, 40);
  delay(100);

  // Cerramos Garra
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garra");
  mostrarPosicionServo(15.5);
  moverServo(servoGarra, 60, 15.5, 1, 40);
  delay(100);

  // Hombro sube
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(anguloInicial2);
  moverServo(servoHombro, 130, anguloInicial2, 1, 40);
  delay(100);

  // Gira la base
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Base");
  mostrarPosicionServo(65);
  moverServo(servoBase, anguloInicial, 65, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(135);
  moverServo(servoHombro, anguloInicial2, 135, 1, 40);
  delay(100);

  // Codo baja
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Codo");
  mostrarPosicionServo(100);
  moverServo(servoCodo, 120, 100, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(125);
  moverServo(servoHombro, 135, 125, 1, 40);
  delay(100);

  // Abre Garra
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garra");
  mostrarPosicionServo(60);
  moverServo(servoGarra, 15.5, 60, 1, 40);
  delay(100);

  // Hombro sube
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(anguloInicial2);
  moverServo(servoHombro, 135, anguloInicial2, 1, 40);
  delay(100);

  // Gira la base
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Base");
  mostrarPosicionServo(anguloInicial);
  moverServo(servoBase, 65, anguloInicial, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(120);
  moverServo(servoHombro, anguloInicial2, 120, 1, 40);
  delay(100);

  // Codo baja
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Codo");
  mostrarPosicionServo(80);
  moverServo(servoCodo, 100, 80, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(110);
  moverServo(servoHombro, 120, 110, 1, 40);
  delay(100);

  // Baja Mano 1
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mano1");
  mostrarPosicionServo(20);
  moverServo(servoMano1, 37, 20, 1, 40);
  delay(100);

  // Cerramos Garra
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garra");
  mostrarPosicionServo(15.5);
  moverServo(servoGarra, 60, 15.5, 1, 40);
  delay(100);

  // Hombro sube
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(140);
  moverServo(servoHombro, 110, 140, 1, 40);
  delay(100);

  // Gira la base
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Base");
  mostrarPosicionServo(45);
  moverServo(servoBase, anguloInicial, 65, 1, 40);
  delay(100);

  // Baja hombro
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(125);
  moverServo(servoHombro, 140, 125, 1, 40);
  delay(100);

  // Codo baja
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Codo");
  mostrarPosicionServo(85);
  moverServo(servoCodo, 80, 85, 1, 40);
  delay(100);

  // Abre Garra
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Garra");
  mostrarPosicionServo(60);
  moverServo(servoGarra, 15.5, 60, 1, 40);
  delay(100);

  // Hombro sube
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hombro");
  mostrarPosicionServo(anguloInicial2);
  moverServo(servoHombro, 125, anguloInicial2, 1, 40);
  delay(100);

  // Gira la base
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Base");
  mostrarPosicionServo(anguloInicial);
  moverServo(servoBase, 65, anguloInicial, 1, 40);
  delay(100);

  digitalWrite(RELAY_PIN, HIGH);
  estadoRele = '1';
  tiempoRele = millis();  // Marca el tiempo en el que se encendió el relé
}

void secuencia3() {
  // Pasos

  digitalWrite(RELAY_PIN, HIGH);
  estadoRele = '1';
  tiempoRele = millis();  // Marca el tiempo en el que se encendió el relé
}

void loop() {
  if (BTSerial.available()) {
    char dato = BTSerial.read();
    Serial.print("Dato recibido: ");  // Imprime el dato recibido por Bluetooth
    Serial.println(dato);
    while (BTSerial.available()) {
      BTSerial.read();
    }
    // Control del brazo robótico
    switch (dato) {
      case '1':
        Serial.println("Ejecutando secuencia 1");  // Mensaje de depuración
        secuencia1();
        break;
      case '2':
        Serial.println("Ejecutando secuencia 2");  // Mensaje de depuración
        secuencia2();
        break;
      case '3':
        Serial.println("Ejecutando secuencia 3");  // Mensaje de depuración
        secuencia3();
        break;
    }
    delay(10);

    // Control manual del relé (opcional)
    if (dato == 'R') {
      estadoRele = (estadoRele == '0') ? '1' : '0';
      digitalWrite(RELAY_PIN, estadoRele == '1' ? HIGH : LOW);
      BTSerial.print("Estado del relé: ");
      BTSerial.println(estadoRele);
    }
  }

  // Apagar el relé después de un tiempo (opcional)
  if (estadoRele == '1' && (millis() - tiempoRele >= duracionRele)) {
    digitalWrite(RELAY_PIN, LOW);
    estadoRele = '0';
  }
}
