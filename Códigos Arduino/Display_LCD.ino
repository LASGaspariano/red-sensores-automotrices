#include <LiquidCrystal.h>

//Crear el objeto LCD con los números correspondientes (rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(8, 10, 4, 5, 6, 7);
 float lectura ;
 float volTemp ;
 int Temp ;


void setup() {
  // Inicializar el LCD con el número de  columnas y filas del LCD
  lcd.begin(16, 2);
  // Escribimos el Mensaje en el LCD.
  lcd.print("Temperatura:");
}

void loop() {
  //
  lectura = analogRead(A0);
  volTemp = 0.25 * lectura;
  Temp = volTemp / 5.6;
  
  // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.setCursor(0, 1);
  // Escribimos el número de segundos trascurridos
  lcd.print(Temp);
  lcd.print(" grados C");
  delay(100);
}

