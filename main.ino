/*
  MIT License

  Copyright (c) 2025 Bruno Santos

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "devices.h"


Devices devices;
/*
  Código para a esp32, caso deseje rodar em uma placa arduino, desejo sorte,
  ter memória para esse código é um desafio.
  i2c no esp32 -> pinos:
    vcc-> 3v3
    sda-> 21
    scl-> 22
/----\
LCD  20X4 i2c
*/


void setup(){
  /*Setando GPIOs*/
  devices.SetServoPin(16);
  //esquerdo, centro,  direito
  devices.SetBtnPin(27,14,26);
  //ponto inicial, ponto final 1, ponto final 2, ponto final 3
  devices.SetIrPin(23,34,25,28);
  
  devices.SetGteorico(9.81);/*setando o valor teórico da gravidade*/
  devices.SetTlimite(30);/*30 segundos para o experimento terminar após dado o início*/
  devices.Setup();
  Serial.begin(9600);
  
  devices.Animar();//animação inicial
  delay(1000);
  
  devices.Imprime(6,1,"BEM VINDO");
  devices.Imprime(8,2,"BRUNO");
  delay(1000);
  
}

void loop(){
  
  devices.Run();
  
}
