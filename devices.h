//Copyright (c) 2025 Bruno da Silva Santos

#pragma once

#include <ESP32Servo.h>
#include <vector>
#include "buttons.h"
#include "lcd.h"

class Devices{
public:

  Devices();

  void SetServoPin(const int servoPin);
  void SetBtnPin(const int left, const int center, const int right);
  void SetIrPin(const int ir1, const int ir2, const int ir3, const int ir4);
  void SetGteorico(const float gt);
  void SetTlimite(const int time);
  void Setup();
  void Run();
  void Imprime(const int x, const int y, const char * text);
  void Limpa();
  void Animar();

private:
  void ControleBotoes();
  void Lcd_menu(const int menu_index, const int mm_index);
  void selectAltura(const int item);
  void Iniciar();
  void Capturar();
  void Calcular(const unsigned long t1, const unsigned long t2);
  char * Converter (const float valor);

  void Timer(const int t);
  void OpenAnt();
  void CloseAnt();
  BUTTONS btns;
  LCD lcd;
  Servo ant;

  int IR[4];
  int servo_pin;
  int btn_esquerdo;
  int btn_centro;
  int btn_direito;
  int ir_1;
  int ir_2;
  int ir_3;
  int ir_4;

  String menu_principal [3] ={"INICIAR","DADOS","ALTURAS"};
  String menu_dados [5] = {"GRAVIDADE","VELOCIDADE","ERRO","VOLTAR"};
  String menu_alturas [4] ={"0.3m","0.6m","0.9m","VOLTAR"};

  int anterior_alturas_in_contador = 1;
  int anterior_principal_in_contador = 1;
  int anterior_dados_in_contador = 1;
  int aux_dados_in = 0;
  int aux_alturas_in = 0;
  int aux_iniciar = 0;
  int contador_m_principal, contador_m_dados, contador_m_alturas = 0;
  bool dentro_m_principal = true;
  bool dentro_m_dados = false;
  bool dentro_m_alturas = false;
  bool dentro_iniciar = false;
  bool mostrar_gravidade = false;
  bool mostrar_velocidade = false;
  bool mostrar_erro = false;

  const float alturas[3] = {0.30, 0.60, 0.90};
  float Gt;
  float ge;
  float dt;
  float ep;
  float vf;
  int aux_gravidade = 0;
  int aux_velocidade = 0;
  int aux_erro = 0;
  int index_alturas = -1;
  volatile bool cancelar_captura = false;
  bool aberto_garra = false;

  unsigned long t_limite;
  String *conteiner[3] = {menu_principal, menu_dados, menu_alturas};

};
