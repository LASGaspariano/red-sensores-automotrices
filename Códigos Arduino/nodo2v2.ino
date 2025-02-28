// CÓDIGO PARA NODO 2

#include <SPI.h>
#include "mcp_can.h"

// El pin para CS de comunicación SPI para el shield es D10
const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN);                                    // Se setea el pin de CS
void MCP2515_ISR();                                         // Se declara la función de interrupción

unsigned char flagRecv = 0;                                 // Se inicia con la bandera de recepción abajo  
unsigned char len = 0;                                      // Se inicia la longitud del mensaje en 0
unsigned char buf[8];                                       // Se crea el vector del buffer con longitud de 8 bytes
unsigned char datos[8] = {0,0,1,1,0,0,1,1};   
// Inicialización de variables, funciones y puerto serial

void setup()
{
    Serial.begin(9600);

    while (CAN_OK != CAN.begin(CAN_250KBPS))              // Velocidad del CAN = 500KBPS
    {
        Serial.println("CAN BUS Shield fallo en iniciar");
        Serial.println(" Iniciando CAN BUS Shield otra vez");
        delay(100);
    }
    Serial.println("CAN BUS Shield inicio con exito");

    attachInterrupt(0, MCP2515_ISR, FALLING);             // Establecimiento de la función de la interrupción 
  
}

// Rutina de interrupción
void MCP2515_ISR()
{   
    flagRecv = 1;                                        // Se alza la bandera de recepción     
    
}

// Rutina de lectura de mensaje
void loop()
{   //Declaración de trama de datos 
    unsigned char datos[8] = {0,0,1,1,0,0,1,1}; 
    // Envío del mensaje
    if(flagRecv) 
    {                                   // Se revisa si la bandera de recepción está alzada y se inicia la rutina de lectura

        flagRecv = 0;                   // Se vuelve a bajar la bandera para reiniciar el proceso de lectura de mensaje

        // iterate over all pending messages
        // If either the bus is saturated or the MCU is busy,
        // both RX buffers may be in use and reading a single
        // message does not clear the IRQ conditon.

           while (CAN_MSGAVAIL == CAN.checkReceive()) {
          CAN.readMsgBuf (&len, buf);
          delay(200);
         // Impresión de los mensaje
            Serial.print("Mensaje recibido: ");
            for(int i = 0; i<len; i++){
            {
                Serial.print(buf[i]); Serial.print("\t");
            }
           }
            Serial.println();
            Serial.print("Mensaje enviado: ");
            for(int i = 0; i<len; i++){
            {
                Serial.print(datos[i]); Serial.print("\t");
            }
           }
            Serial.println();
            Serial.println();  
            }
    
      }
    
    CAN.sendMsgBuf(0x01, 0, 8, datos);
    delay(200);
    Serial.println("No se ha podido leer un mensaje");
}


