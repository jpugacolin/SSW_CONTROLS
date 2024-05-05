// Automated Seatbelt Restraint System - SSW CONTROLS
// Code Written by Jose Puga
// Senior Design Project - ME195B 

#include "Nextion.h"
#define dirPin 8                                                              // Pin que nos indicara el sentido de giro.
#define pulsoPin 9                                                            // Pin para cada uno de los pulsos que hace girar el motor.

NexText t0 = NexText(0, 1, "t0");                                             // Definimos etiqueta Texto.
NexSlider h0 = NexSlider(0, 2, "h0");                                         // Definimos un nuebo Objeto slider.
NexDSButton bt0 = NexDSButton(0, 3, "bt0");                                   // Boton marcha.
NexDSButton bt1 = NexDSButton(0, 4, "bt1");                                   // Boton cambio giro.

char buffer[100] = {0};
int delayPasos = 9000;                                                        // Variable para temporizar los pasos.
int valorSlider = 0;                                                          // Variable para almacenar el valor del slider que se lee.
int disparo=500;
uint32_t botonMotorON;
uint32_t botonSentidoGiro;
boolean  puestaMarchaMotor = false;
boolean  sentidoGiro = false;


NexTouch *nex_listen_list[] =                                                       // Lista de escucha, solo el slider.
{
    &bt0,
    &bt1,
    &h0,
    NULL
};

void h0PopCallback(void *ptr)                                                      // Funcion que se ejecuta al cambiar el slider.       
{
    uint32_t number = 0;
    char temp[10] = {0};
   // dbSerialPrintln("h0PopCallback");                                             // Mostramos por el puerto de deputacion que se activo la funcion hopopcallback.
    h0.getValue(&number);                                                         // Recuperamos el valor del slider.
    valorSlider=number; 
    //dbSerialPrintln(valorSlider);
     delayPasos=map(valorSlider,0,100,9000,500);                             // Mapeamos para sacar la escala que desamos.  
    //dbSerialPrintln(delayPasos);
    utoa(number, temp, 10);                                                       // Lo pasamos a texto.
    t0.setText(temp);                                                             // Ponemos la etiqueta con el valor del slider.
                           
}

void bt0Funcion(void *ptr)  {
     bt0.getValue(&botonMotorON);
    if(botonMotorON) puestaMarchaMotor = true; else puestaMarchaMotor = false;
     }

void bt1Funcion(void *ptr)  {
    bt1.getValue(&botonSentidoGiro);
    if(botonSentidoGiro)    {
       sentidoGiro = true;
       digitalWrite(dirPin, HIGH);                                               // Activamos la direccion del motor ( giro antihorario).  
    } else  {
      digitalWrite(dirPin, LOW);                                                // Activamos la direccion del motor ( giro antihorario).
       sentidoGiro = false;
    }
  }

void setup(void)
{
   pinMode(dirPin, OUTPUT);                                                   // definimos dirPin como salida.
   pinMode(pulsoPin, OUTPUT);                                                 // definimos pulsoPin como salida.
   digitalWrite(dirPin, LOW);                                                 // Activamos la direccion del motor ( giro antihorario).
   nexInit();                                                                 // Iniciamos la comunicacion con la nextion.
   bt0.attachPop(bt0Funcion);                                                 // Registra la funcion que de desencadena al pulsar el boton de texto.
   bt1.attachPop(bt1Funcion);                                                 // Registra la funcion que de desencadena al pulsar el boton de texto.
   h0.attachPop(h0PopCallback);                                               // Indicamos la funcion a la que saltara con el evento h0.AttachPop
   dbSerialPrintln("Arduino funcionando ...");                                // Inprimimos por el puerto de depuracion saliendo del setup.  
}

void loop(void)
{
   nexLoop(nex_listen_list);                                                     // Escuchando eventos provenientes de la pantalla.
   //delayPasos=3000;
       
    
    if(puestaMarchaMotor) 
    {
         digitalWrite(pulsoPin, HIGH);                                         // Ponemos en valor alto la salida del pin del pulsos.
         delayMicroseconds(delayPasos);                                        // temporizamos el valor resultante del mapeo.
         digitalWrite(pulsoPin, LOW);                                          // Bajamos el pin de pulsos.
         delayMicroseconds(delayPasos);                                        // temporizamos el valor resultante del mapeo.
      }
    }    



