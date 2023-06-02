#include <LiquidCrystal_I2C.h>//incluye la libreria de la LCD
#include <Wire.h>		// incluye libreria para interfaz I2C


#define trig 8 // se realizan las configuraciones del sensor ultrasonico
#define echo 9
const float velocidad = 0.0343;
float time;
float distancia;

#define direccion_lcd 0x27 //configuracion del LCD
#define filas 2
#define columnas 16
LiquidCrystal_I2C lcd(direccion_lcd, columnas, filas);

#define buzzer 5 /*definimos los nombres de los nuevos codigos*/
#define buzzer_2 6
#define bomba 15
#define led 11
#define buzzon() tone(buzzer, 1950)
#define buzzoff() noTone(buzzer)
#define buzzon_2() tone(buzzer_2, 1900)
#define buzzoff_2() noTone(buzzer_2)
#define ence() digitalWrite(bomba,HIGH)
#define apag() digitalWrite(bomba,LOW)
#define buzzon_3() tone(buzzer, 2200)
#define buzzoff_3() noTone(buzzer)
#define buzzon_4() tone(buzzer_2, 2300)
#define buzzoff_4() noTone(buzzer_2)
#define time() delay(50)/**/

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT); //Se configura el trig como salida
  pinMode(echo, INPUT);  //Se configura eñ echo como entrada
  Serial.begin(9600); //Se activa el monitor serial
  
  lcd.init();       //iniciamos la lcd
  lcd.backlight();  //encendemos las luces backlight

  pinMode(bomba,OUTPUT);  //la bomba como salida

  attachInterrupt(digitalPinToInterrupt(2), vaciado, HIGH); //Se configuraciones las interrupciones
  attachInterrupt(digitalPinToInterrupt(3), alarma2, HIGH);
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(trig,HIGH);  /*Se realiza toda la configuracion para usar el modulo ultrasonico*/
    delay(1);
    digitalWrite(trig,LOW);
    time = pulseIn(echo,HIGH);
    distancia = (time)*velocidad/2;
    Serial.print(distancia);
    Serial.println("cm");
    delay(200);
    secuencia();
    alarma();
    digitalWrite(bomba,HIGH);/**/

}

void secuencia(){//creamos una secuencia para mostrar el porcentaje de agua
  
  if (distancia > 7.12){
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Agua al 0%");
      lcd.setCursor(0,0);
      lcd.print("llenar de agua");

      }
  else if (distancia > 6.02  && distancia < 6.13){ 
      lcd.clear();
      lcd.setCursor(0,1);  
      lcd.print("Agua al 10%");
        
      }
  else if (distancia > 6.50  && distancia < 6.90){
      lcd.clear(); 
      lcd.setCursor(0,1);  
      lcd.print("Agua al 20%");
        
      } 
  else if (distancia > 5.02  && distancia < 5.13){
      lcd.clear(); 
      lcd.setCursor(0,1);  
      lcd.print("Agua al 30%");
        
      }
  else if (distancia > 4.02  && distancia < 4.13){
      lcd.clear(); 
      lcd.setCursor(0,1);  
      lcd.print("Agua al 40%");
        
      }
  else if (distancia > 3.41 && distancia <3.58) {
      lcd.clear();      
      lcd.setCursor(0,1);
      lcd.print("Agua al 50%");
        
      }
  else if (distancia > 3.90  && distancia < 3.59){ 
      lcd.clear();
      lcd.setCursor(0,1);  
      lcd.print("Agua al 60%");
        
      }
  else if (distancia > 2.90  && distancia < 4.13){ 
      lcd.clear();
      lcd.setCursor(0,1);  
      lcd.print("Agua al 70%");
        
      }
  else if (distancia > 2.02  && distancia < 2.13){ 
      lcd.clear();
      lcd.setCursor(0,1);  
      lcd.print("Agua al 80%");
        
      }
  else if (distancia > 2.45 && distancia < 2.56) {
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Agua al 90%");

      }
  else if (distancia > 1.78 && distancia < 1.90) {
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Agua al 100%");
      lcd.setCursor(0,0);
      lcd.print("vacie pronto");

      }
  
}

void alarma() {//Creo una alarma para cuando alcanze el maximo
  if (distancia < 1.91){
    buzzon();
    time();
    buzzoff();
    buzzon_2();
    time();
    buzzoff_2();
    buzzon();
    time();
    buzzoff();
    buzzon_2();
    time();
    buzzoff_2();
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("alerta");
    lcd.setCursor(0,1);
    lcd.print("maxima capacidad");

  }else {
    buzzoff();
    buzzoff_2();
  }
}

void vaciado(){//una funcion para que se vacie al usar el boton
  Serial.println("se realiza interrupcion 1");
  digitalWrite(bomba,LOW);
  
  delay(1);
}

void alarma2() {//la alarma para el otro boton
  Serial.println("se realiza interrupcion 2");
    buzzon_3();
    delay(10000);

}




