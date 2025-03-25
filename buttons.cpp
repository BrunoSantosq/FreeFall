// Copyright (c) 2025 Bruno da Silva Santos

#pragma once
#include "buttons.h"

/*método modelo*/
bool BUTTONS::eEsquerdo(const int btn_esquerdo)
{
  int leitura = digitalRead(btn_esquerdo);
  bool r = false;
  
  if (leitura != ultimoEstadoEsquerdo) {
    ultimoDebounceTime_esquerdo = millis();
  }
  if ((millis() - ultimoDebounceTime_esquerdo) > debounceDelay && leitura != estado_btn_esquerdo) {
   /* if (leitura != estado_btn_esquerdo) {
      estado_btn_esquerdo = leitura;
      if (leitura == LOW) r = true; 
    }*/
    estado_btn_esquerdo = leitura;
    if(leitura == LOW) r = true;
  }
  ultimoEstadoEsquerdo = leitura;
  
  return r;
}

bool BUTTONS::eDireito(const int btn_direito)
{
  int leitura = digitalRead(btn_direito);
  bool r = false;
  
  if(leitura != ultimoEstadoDireito)
  {
    ultimoDebounceTime_direito = millis();
  }
  if((millis() - ultimoDebounceTime_direito) > debounceDelay && leitura != estado_btn_direito)
  {
    estado_btn_direito = leitura;
    if(leitura == LOW) r = true;
  }
  ultimoEstadoDireito = leitura;
  return r;
}

bool BUTTONS::eCentro(const int btn_centro)
{
  int leitura = digitalRead(btn_centro);
  bool r = false;
  if (leitura != ultimoEstadoCentro)
  {
    ultimoDebounceTime_centro = millis();
  }
  if ((millis() - ultimoDebounceTime_centro) > debounceDelay && leitura != estado_btn_centro)
  {
    estado_btn_centro = leitura;
    if (leitura == LOW) r = true;
  }
  ultimoEstadoCentro = leitura;
  return r;
}

int BUTTONS::IncreContador(int contador, int max)/*Incrementa*/
{
  return (contador < max) ? contador + 1 : 0;
}
int BUTTONS::DecreContador(int contador, int max)/*Decrementa*/
{
  return (contador > 0) ? contador - 1 : max;
}
