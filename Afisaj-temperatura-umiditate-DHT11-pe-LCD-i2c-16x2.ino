/*
 * DHT11 PINOUT (vazut din fata cu grilajul spre tine):
 * pin1 - VCC (5v)
 * pin2 - data
 * pin3 - nefolosit
 * pin4 - GND
 *
 * CONECTARE SENZOR DHT11:
 * - o rezistenta 10K intre pinii 1 si 2 al lui DHT11
 * - pinul 1 VCC la Arduino 5V
 * - pinul 2 data la Arduino D2 (daca modificati schimbati valoarea si in sketch)
 * - pinul 4 GND la Arduino GND
 *
 * CONECTARE LCD I2C Display
 * - LCD GND la Arduino GND
 * - LCD VCC la Arduino 5V
 * - LCD SDA la Arduin A4
 * - LCD SCL la Arduino A5
 *
 * PENTRU A GASI ADRESA LCD-ULUI RULEAZA PRIMA DATA SKETCH-UL DE AICI
 * http://playground.arduino.cc/Main/I2cScanner
 */
 
 
#include <DHT.h> // Include libraria pentru senzorul temperatura si umiditate DHT11
#include <Wire.h> // Include libraria pentru I2C
#include <LiquidCrystal_I2C.h> // Include libraria pentru LCD prin I2C
 
#define DHTPIN 2     // defineste PIN la care e legat DHT11
#define DHTTYPE DHT11   // defineste tipul de senzor DHT - DHT11 sau DHT12
 
DHT dht(DHTPIN, DHTTYPE); // initializeaza senzorul DHT
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // initializeaza LCD prin I2C la adresa 0x3F (adresa se gaseste folosind un I2C scanner)
 
//***************************************************************
 
void setup(void) {
  lcd.begin(16, 2); // pornim lcd definit cu 16 coloane si 2 linii
  lcd.print("Citesc date");
  lcd.setCursor(0,1);  // start linia 2
  lcd.print("senzor ...");
  dht.begin(); // pornim senzor DHT11
}
 
//****************************************************************
 
void loop() {
 
  float temperatura, umiditate; // declaram variabilele temperatura si umiditate ca float
 
  umiditate = dht.readHumidity(); // citesc valoare umiditate de pe DHT11
  temperatura = dht.readTemperature(); // citesc valoare temperatura de pe DHT11
  delay(2000); // delay 2 secunde intre citiri
 
 lcd.clear(); // stergere ecran
 
 char tempF[6];
 char humF[6];
 dtostrf(temperatura, 5, 1, tempF); // convert float tempF in string
 dtostrf(umiditate, 2, 0, humF); // convert float humF in string
 
 /*incepe afisarea datelor pe ecran*/
 lcd.print("Temp:");
 lcd.print(tempF);
 lcd.print((char)223);
 lcd.print("C");
 lcd.setCursor(0,1);  // start linia 2 coloana 1
 lcd.print("Umiditate: ");
 lcd.print(humF);
 lcd.print("%");
}
