// NODO 0 MONITOR

#include <SPI.h>
#include "mcp_can.h"
#include <LiquidCrystal.h>

long j = 0;
const int incremento = 100;
const int SPI_CS_PIN = 10;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
MCP_CAN CAN(SPI_CS_PIN);                                   

void setup()
{ 
    Init:  
    while (CAN_OK != CAN.begin(CAN_125KBPS))              
    {
     lcd.print(":(");
    }  
  lcd.begin(16, 2);
  lcd.print("Leyendo Nodo:");  
}

void loop()
{   long inicio = millis();
    unsigned char len;
    unsigned char buf[8]; 
    lcd.setCursor(14, 0);   
    if(CAN_MSGAVAIL == CAN.checkReceive())            
    {   
        CAN.readMsgBuf(&len, buf); 
        unsigned int canId = CAN.getCanId();
        lcd.print(canId);
        lcd.setCursor(0, 1);  
        for (int i = 0; i<8; i=i+2)
        {
           lcd.print(buf[i]);
            lcd.print(" ");
        }
             lcd.print("   ");
             j = 0;
      }    
   
    if (CAN.checkReceive() == CAN_NOMSG)
    { 
      j++;
      if (j >= 3000){ 
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      }  
    }
}
