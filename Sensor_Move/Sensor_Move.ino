#include <DHT.h> //**Lib sensor de temperatura
#include <LCD_I2C.h> //**Lib pantalla led
#define DHTPIN 7 //**sensor temperatura
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); //**inicializar
LCD_I2C lcd(0x27);
//**DECLARAR PUERTO DE SALIDA
int pir_pin = 2;
int led_green = 3;
int led_red = 4;
int buz_pin = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(pir_pin, INPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(buz_pin, OUTPUT);
  lcd.begin(); //**PARA INICIAR LCD
  lcd.backlight();
  lcd.print("Modo:");
  Serial.begin(9600);  //**tiempo de inicio
  
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  float h = dht.readHumidity();
  // Leer temperatura en Celsius (the default)
  float t = dht.readTemperature();
  // Leer temperatura en Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Comprobar funcionamiento del sensor de temperatura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Error al leer de DHT sensor!"));
    return;
  }
  //CONDICION AL ACTIVARSE EL SENSOR PIR-
  if(digitalRead(pir_pin) == HIGH)
  {
    digitalWrite(led_red, HIGH); //**Led red encendido
    digitalWrite(led_green, LOW); //**Led verde apagado
    digitalWrite(buz_pin, HIGH); //**parlante encendido
    lcd.setCursor(6,0);
    lcd.print("!Alerta!"); //**mensaje en pantalla lcd
    lcd.print("         ");
    lcd.setCursor(5,1);
    lcd.print(t); //**mensaje en pantalla lcd
    lcd.setCursor(11,1);
    lcd.print("C"); //**mensaje en pantalla lcd
    Serial.println("¡Intrusos!"); //**mensaje en monitor
    delay(1000);
  }
  //CONDICION AL NO ACTIVARSE EL SENSOR PIR-
  else
  {
    digitalWrite(led_green, HIGH); //**Led verde encendido
    digitalWrite(led_red, LOW); //**Led red apagado
    digitalWrite(buz_pin, LOW); //**parlante red apagado
    lcd.setCursor(6,0);
    lcd.print("Vigilante"); //**mensaje en pantalla lcd
    lcd.setCursor(5,1);
    lcd.print(t); //**mensaje en pantalla lcd
    lcd.setCursor(11,1);
    lcd.print("C");  //**mensaje en pantalla lcd
    Serial.println("Modo vigilante");
    //delay(1000);
  }
  Serial.print(t);
  Serial.print(F("°C "));
}
