#include "HX711.h"
#define DOUT  A2
#define CLK  A1

HX711 balanza(DOUT, CLK);

void setup() {
Serial.begin(9600);
  Serial.print("Lectura del valor del ADC:  ");
  Serial.println(balanza.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  Serial.println("...");
  balanza.set_scale(439430.25); // Establecemos la escala
  balanza.tare(5);  //El peso actual es considerado Tara.
  
  Serial.println("Listo para pesar");  
}

void loop() {
  Serial.print("Peso: ");
  Serial.print(balanza.get_units(5),3);
  Serial.println(" kg");
  //delay(500);
}
