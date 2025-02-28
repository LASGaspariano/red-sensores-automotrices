// NODO 3 - SIN SENSORES

//Se incluyen las librerías para la comunicación Serial entre el arduino y el shield Can bus
//y la librería de este último
#include <SPI.h>
#include "mcp_can.h"                               
  
// Declaración de funciones
void MCP2515_ISR();
void enviar();
void leer();


// Declaración de variables 
unsigned char flagRecv = 0;                     // Bandera de recepción del mensaje
unsigned char len = 8;                          // Longitud de la trama de datos; bytes
unsigned char buf[8]; 
const int SPI_CS_PIN = 10;                      // Es el pin CS para la comunicación del shield con Arduino                  
MCP_CAN CAN(SPI_CS_PIN);                        // para esta versión de CAN (v1.2) se usa el pin D10


void setup()
{
    Serial.begin(9600);

    while (CAN_OK != CAN.begin(CAN_125KBPS))              // velocidad del CAN = 125 Kbps
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");
    attachInterrupt(0, MCP2515_ISR, FALLING);           // Se establece una rutina de interrupción activada 
}                                                       // por el flanco de bajada del pin D0 (Rx)

void MCP2515_ISR()
{
    flagRecv = 1;                                      // Durante la rutina de interrupción se alza la 
}                                                      // bandera de recepción

unsigned char datos[8]={3, 3, 3, 3, 3, 3, 3, 3};              // Valor inicial de la trama de datos

void loop()
{   
    
  
    if(flagRecv) 
    {                                  
        flagRecv = 0;                                 // Se resetea la bandera de recepción
        while (CAN_MSGAVAIL == CAN.checkReceive())    // Si se comprueba que hay un mensaje en el buffer
        {                                             // se llama a la función de lectura del mensaje
         leer();
        }
    }
        
enviar();                                            // Una vez bajada la bandera de recepción se aprovecha
delay(1000);                                         // para enviar un mensaje cada segundo
}

// FUNCIÓN PARA ENVIAR MENSAJE
void enviar(){
   // Enviar mensaje
    CAN.sendMsgBuf(0x03,0,8,datos);

  // Impresión de datos
  Serial.println("------------------------------------------------------------------------");
    Serial.print("Mensaje enviado: ");
    for (int i = 0; i<8; i++){
      Serial.print(datos[i]); Serial.print("\t");
    }
    Serial.println();
}

// FUNCIÓN PARA LEER MENSAJE
void leer(){
   
  // Lectura del mensaje
  CAN.readMsgBuf(&len, buf);
              
   // Impresión del mensaje 
   Serial.print("Mensaje recibido: ");
    for(int i = 0; i<len; i++)
      {
       Serial.print(buf[i]);Serial.print("\t");
      }
       Serial.println();     
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
