/*
  MIT License

  Copyright (c) 2025 Bruno da Silva Santos

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

/*
    @Bruno da silva santos - 2025
    Este código faz parte do projeto queda livre utilizando arduino
    desenvolvido como parte do Pibid na universidade estadual do Maranhão
*/
#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>
#include <cstdlib>
#include "devices.h"

Devices::Devices(){

}
void Devices::SetServoPin(const int servoPin){
  servo_pin = servoPin;
}
void Devices::SetBtnPin(const int left, const int center, const int right){
  btn_esquerdo = left;
  btn_centro = center;
  btn_direito = right;
}
void Devices::SetIrPin(const int ir1, const int ir2, const int ir3, const int ir4){
  ir_1 = ir1;
  ir_2 = ir2;
  ir_3 = ir3;
  ir_4 = ir4;
  IR[0] = ir_1;
  IR[1] = ir_2;
  IR[2] = ir_3;
  IR[3] = ir_4;
}

void Devices::SetGteorico(const float gt){
  Gt =  gt;/*valor teórico da gravidade*/
  ge = 0;
  vf = 0;
  dt = 0;
  ep = 0;
}
void Devices::SetTlimite(const int time){
  if(time > 10  && time <= 60){
    t_limite = time * 1000; /* para milissegundos*/
  }else{
    t_limite = 15*1000; /* valor padrão*/
  }
 }
void Devices::Setup(){

  pinMode(btn_esquerdo, INPUT_PULLUP);
  pinMode(btn_centro, INPUT_PULLUP);
  pinMode(btn_direito,  INPUT_PULLUP);
 
  for(int i = 0; i < 4; i++) {
    pinMode(IR[i], INPUT);
  }
  
  ant.attach(servo_pin);

  lcd.Setup(); /*Inicia o lcd*/

}

void Devices::Run(){
  ControleBotoes();
  if (dentro_m_principal){
    if (anterior_principal_in_contador != contador_m_principal){
      anterior_principal_in_contador = contador_m_principal;
      Lcd_menu(0, contador_m_principal);
      if (index_alturas != -1){
        char *str_alturas = Converter(alturas[index_alturas]);
        if (str_alturas != NULL){
          char msg[15];
          strcpy(msg, "Altura:");
          strcat(msg, str_alturas);
          strcat(msg, "m");
          Imprime(0, 3, msg);
          free(str_alturas);
        }
      }
    }
  }
  if (dentro_m_dados){
    if (anterior_dados_in_contador != contador_m_dados){
      anterior_dados_in_contador = contador_m_dados;
      Lcd_menu(1, contador_m_dados);
    }
    if (mostrar_gravidade){
      if(aux_gravidade == 0){
        char *str_gravidade = Converter(ge);
        Serial.print("gravidade: ");
        Serial.println(str_gravidade);
        if (str_gravidade != NULL){
          Limpa();
          char str_g[20] = {0};
          strcat(str_g, str_gravidade);
          strcat(str_g, " m/s2");
          Imprime(0, 0, "Gravidade");
          Imprime(0, 1, str_g);
          free(str_gravidade);
        }
        aux_gravidade++;
      }
     
    }
    if (mostrar_velocidade){
      if(aux_velocidade == 0){
        char *str_velocidade = Converter(vf);
        if (str_velocidade != NULL){
          Limpa();
          char str_v[32] = {0};
          strcat(str_v, str_velocidade);
          strcat(str_v, " m/s");
          Imprime(0, 0, "Velocidade");
          Imprime(0, 1, str_v);
          free(str_velocidade);
        }
        aux_velocidade++;
      }
    }
    if (mostrar_erro){
      if(aux_erro == 0){
        char *str_erro = Converter(ep);
        if (str_erro != NULL)
        {
          Limpa();
          char str_e[32] = {0};
          strcat(str_e, str_erro);
          strcat(str_e, " %");
          Imprime(0, 0, "Erro");
          Imprime(0, 1, str_e);
          free(str_erro);
        }
        aux_erro++;
      }
    }
  }
  if (dentro_m_alturas){
    if (anterior_alturas_in_contador != contador_m_alturas){
      anterior_alturas_in_contador = contador_m_alturas;
      Lcd_menu(2, contador_m_alturas);
    }
  }

  if (dentro_iniciar) {
    if (aux_iniciar == 0) {
      if (index_alturas == -1) {
        dentro_iniciar = false;
        dentro_m_principal = false;
        dentro_m_dados = false;
        dentro_m_alturas = true;
      } else {
        aux_iniciar += 1;
        Limpa();
        Iniciar();
      }
    }
  }
}
void Devices::Imprime(const int x, const int y, const char *text){
  lcd.Imprimir(x,y,text);
}
void Devices::Limpa(){
  lcd.Limpar();
}
/*desenho do satanás de difícil*/
void Devices::Animar(){
  Limpa();
  /*
    ImprimirA tem utilidade apenas aqui, Imprimir Animação(imprimir bytes)
  */
  int limite_x = 20;  // Limite de colunas (0 a 19)
  int limite_y = 4; // Limite de linhas (0 a 3)

  int acima = 0, abaixo = limite_y - 1, lado_esquerdo = 0, lado_direito = limite_x - 1;
  

  while (acima <= abaixo && lado_esquerdo <= lado_direito){
    // Desenha a linha superior (da esquerda para a direita)
    for (int x = lado_esquerdo; x <= lado_direito; x++){
      lcd.ImprimirA(x, acima);
      delay(100);
    }
    acima++;

    // Desenha a coluna direita (de acima para baixo)
    for (int y = acima; y <= abaixo; y++){
      lcd.ImprimirA(lado_direito, y);
      delay(100);
    }
    lado_direito--;

    // Desenha a linha inferior (da direita para a esquerda)
    if (acima <= abaixo) {
      for (int x = lado_direito; x >= lado_esquerdo; x--) {
        lcd.ImprimirA(x, abaixo);
        delay(100);
      }
      abaixo--;
    }

    // Desenha a coluna esquerda (de baixo para acima)
    if (lado_esquerdo <= lado_direito){
      for (int y = abaixo; y >= acima; y--){
        lcd.ImprimirA(lado_esquerdo, y);
        delay(100);
      }
      lado_esquerdo++;
    }
  }
}

void Devices::ControleBotoes(){
  bool r_left = btns.eEsquerdo(btn_esquerdo);
  bool r_right = btns.eDireito(btn_direito);
  bool r_center = btns.eCentro(btn_centro);
  // Navegação decrescente
  if (r_left){ 
    if (dentro_m_principal) contador_m_principal = btns.DecreContador(contador_m_principal, 2);
    if (dentro_m_dados) contador_m_dados = btns.DecreContador(contador_m_dados, 3);
    if (dentro_m_alturas) contador_m_alturas = btns.DecreContador(contador_m_alturas, 3);
    if(mostrar_gravidade && aux_gravidade > 0){
      mostrar_gravidade = false;
      aux_gravidade = 0;
    }
    if(mostrar_velocidade && aux_velocidade > 0){
      mostrar_velocidade = false;
      aux_velocidade = 0;
    }
    if(mostrar_erro && aux_erro){
      mostrar_erro = false;
      aux_erro = 0;
    }
  }
  //Navegação crescente
  if (r_right){ 
    if (dentro_m_principal) contador_m_principal = btns.IncreContador(contador_m_principal, 2);
    if (dentro_m_dados) contador_m_dados = btns.IncreContador(contador_m_dados, 3);
    if (dentro_m_alturas) contador_m_alturas = btns.IncreContador(contador_m_alturas, 3);
    if(mostrar_gravidade && aux_gravidade > 0){
      mostrar_gravidade = false;
      aux_gravidade = 0;
    }
    if(mostrar_velocidade && aux_velocidade > 0){
      mostrar_velocidade = false;
      aux_velocidade = 0;
    }
    if(mostrar_erro && aux_erro){
      mostrar_erro = false;
      aux_erro = 0;
    }
  }

   // Enter pressionado
  if (r_center){
    if (dentro_m_principal){
      switch (contador_m_principal) {
        case 0:
          dentro_iniciar = true;
          dentro_m_dados = false;
          dentro_m_principal = false;
          dentro_m_alturas = false;
        break;
        case 1:
          dentro_m_dados = true;
          dentro_m_principal = false;
          dentro_m_alturas = false;
          dentro_iniciar = false;
        break;
        case 2:
          dentro_m_alturas = true;
          dentro_m_principal = false;
          dentro_m_dados = false;
          dentro_iniciar = false;
        break;
        default:
        break;
      }
    }

    if (dentro_m_dados){
      switch (contador_m_dados){
        case 0:
          mostrar_gravidade = true;
          mostrar_velocidade = false;
          mostrar_erro = false;
        break;
        case 1:
          mostrar_gravidade = false;
          mostrar_velocidade = true;
          mostrar_erro = false;
        break;
        case 2:
          mostrar_gravidade = false;
          mostrar_velocidade = false;
          mostrar_erro = true;
        break;
        case 3:
          mostrar_gravidade = false;
          mostrar_velocidade = false;
          mostrar_erro = false;
          aux_gravidade = 0;
          aux_velocidade = 0;
          aux_erro = 0;
          dentro_m_principal = true;
          dentro_m_dados = false;
          dentro_m_alturas = false;
          dentro_iniciar = false;
          anterior_principal_in_contador = 1;
          contador_m_principal = 0;
          contador_m_dados = 0;
        break;
        default:
        break;
      }
    }

    if (dentro_m_alturas){
      switch (contador_m_alturas){
        case 0:
        case 1:
        case 2:
          if(aux_alturas_in > 0){
          index_alturas = contador_m_alturas;
          selectAltura(contador_m_alturas);
          aux_alturas_in = 0;
          }else{
          aux_alturas_in++;
          }

        break;
        case 3:
          dentro_m_principal = true;
          dentro_m_dados = false;
          dentro_m_alturas = false;
          anterior_principal_in_contador = 1;
          contador_m_principal = 0;
          contador_m_alturas = 0;
        break;
        default:
        break;
      }
    }
  }
}
void Devices::Lcd_menu(const int menu_index, const int mm_index) {
  int t = 4; 
  String *tmp = conteiner[menu_index];

  if (menu_index == 0) t = 3;
 
  Limpa(); 

  for (int i = 0; i < t; i++) {
    String linha = tmp[i]; 
    if (menu_index == 2 && index_alturas > -1 && i == index_alturas){
      linha = "[x] " + linha; 
    }

    if (i == mm_index){
      linha = "> " + linha;
    }

    Imprime(0, i, linha.c_str());
  }
}
void Devices::selectAltura(const int item)/*somente menu alturas usa esse método*/
{
  String *tmpAltura = conteiner[2];
  for(int i = 0; i < 4; i++){
    if(i == item){
      Imprime(0,i, (tmpAltura[i]+" -> [x]").c_str());
    }else{
      Imprime(0,i, tmpAltura[i].c_str());
    }
  }
}
void Devices::Iniciar(){
  if(!aberto_garra) OpenAnt();

  Imprime(0,0, "Iniciando...");
  Imprime(0, 1,"Em 10 segundos");
  delay(3000);
  Timer(5);
  
  
  aux_iniciar = 0;
  dentro_iniciar = false;
  dentro_m_principal = true;
  anterior_principal_in_contador = 1;
  Limpa();
  Imprime(0,0,"Aguardando queda");
  Capturar();
}
void Devices::Capturar() {
  unsigned long t1 = 0, t2 = 0;
  bool checkpoint_1 = false;
  bool final_point = false;
 unsigned long startTime = millis(); // Tempo inicial para o timeout

  while (!final_point) {
    //if((milis() - startTime) >= t_limite) break;

    if (digitalRead(IR[0]) == LOW && !checkpoint_1) {
      t1 = micros();
      checkpoint_1 = true;
      Limpa();
      Imprime(0, 0, "T1 capturado");
      
    }
    if (digitalRead(IR[index_alturas+1]) == LOW && checkpoint_1) {
      t2 = micros();
      Imprime(0,1, "T2 capturado");
      final_point = true;

    }
  }

  Calcular(t1, t2); // Calcula a gravidade, velocidade e erro
}
void Devices::Calcular(const unsigned long t1, const unsigned long t2)
{
  if(t1 != 0 && t2 != 0)
  {
    dt = (t2 - t1);// micros para segundos
    dt=dt/1000000.0;
    ge = (2*alturas[index_alturas])/(dt*dt);
    vf = ge * dt;
    ep = abs((ge-Gt)/Gt)*100;
    //------------------------------------------
    //--para debug---
    Serial.print("t1: ");
    Serial.println(t1/1000000.0, 6);
    Serial.print("t2: ");
    Serial.println(t2/1000000.0, 6);
    Serial.print("dt: ");
    Serial.println(dt, 6);//com 6 casas decimais
    Serial.print("ge: ");
    Serial.println(ge, 6);
    Serial.print("Vf: ");
    Serial.println(vf, 6);
    Serial.print("ep: ");
    Serial.println(ep, 6);
    
    delay(2000);
    Limpa();
    Imprime(0,0, "Concluido");
    delay(2000);
  }else{
    Limpa();
    Imprime(0,0,"Erro no experimento");
    Imprime(0,1, "Verifique os sensores");
    delay(2000);
  }
}
char* Devices::Converter(const float valor){
  char* buffer = (char*)malloc(100 * sizeof(char));
  if (buffer == NULL) {
    return NULL;
  }
  dtostrf(valor, 6, 2, buffer);
  return buffer;
}

void Devices::Timer(const int t){
  char str_time[10];
  int tt=t;
  while(tt > 0){
    snprintf(str_time, sizeof(str_time), "%d", tt);
    Limpa();
    Imprime(2,0,str_time);
    delay(1000);
    tt--;
  }
}

/*funções do servo*/
void Devices::OpenAnt(){
  ant.write(2);
  aberto_garra = true;
}
void Devices::CloseAnt(){
  for(int i = 0; i < 45; i++){
  ant.write(i);
  delay(50);
  }
  aberto_garra = false;
}
