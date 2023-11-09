#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 8, 4, 7, 2); // rs, enabled, d4, d5, d6, d7

const int pinSensorHumedad = A1;
const int pinSensorTemperatura = A0;
const int pinSensorLuz = A2;
const int pinRiego = 10;
const int pinVentilacion = 6;
const int pinRojo = 3;
const int pinVerde = 5;
const int pinAzul = 9;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(pinVentilacion, OUTPUT);
  pinMode(pinRiego, OUTPUT);
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
}

void loop() {
  lcd.scrollDisplayLeft();
  float humedad = analogRead(pinSensorHumedad);
  float porcentajeHumedad = map(humedad, 0, 876, 0, 100);

 
  
  lcd.setCursor(0,0);
  lcd.print("H: ");
  lcd.setCursor(4,0);
  lcd.print(porcentajeHumedad);
  lcd.print("% ");
  if(porcentajeHumedad<35){
   digitalWrite(pinRiego,HIGH);
    lcd.setCursor(11,0);
   lcd.print(" Muy seco ");
  } else if (porcentajeHumedad >= 35 && porcentajeHumedad < 60) {
    digitalWrite(pinRiego, LOW);
    lcd.setCursor(11, 0);
    lcd.print(" Suelo seco ");
  } else {
    lcd.setCursor(11, 0);
    lcd.print(" Humedo      ");
  }

  float valorLeidoTMP = analogRead(pinSensorTemperatura);
  //float voltaje = map(valorLeidoTMP, 20, 358, 0, 5);
  float temperatura = (((5 * valorLeidoTMP * 100) / 1024) - 50);
  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print(temperatura);
  lcd.print("C ");
  if (temperatura > 30) {
    digitalWrite(pinVentilacion, HIGH);
    
    lcd.print(" Mucho Calor ");
  }
  else if(temperatura >= 15 && temperatura <= 30)
  {
    lcd.print("  Buen Clima ");
  } 
  else {
    digitalWrite(pinVentilacion, LOW);
    lcd.setCursor(11, 1);
    lcd.print(" Mucho Frio ");
  }

  delay(100);

  int foto = analogRead(pinSensorLuz);
  delay(100);
  Serial.println(foto);
  if (foto > 500) {
    digitalWrite(pinRojo, 255);
    digitalWrite(pinAzul, LOW);
    digitalWrite(pinVerde, LOW);
  } else {
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinAzul, LOW);
    digitalWrite(pinVerde, LOW);
  }
}
