//Copyright (c) 2025 Bruno da Silva Santos

#pragma once
#include <Arduino.h>

class BUTTONS{
public:
  bool eEsquerdo(const int btn_esquerdo);
  bool eDireito(const int btn_direito);
  bool eCentro(const int btn_centro);
  int IncreContador(int contador, int max);
  int DecreContador(int contador, int max);
private:
  int estado_btn_esquerdo = HIGH;
  int estado_btn_centro = HIGH;
  int estado_btn_direito = HIGH;

  int ultimoEstadoEsquerdo = HIGH;
  int ultimoEstadoCentro = HIGH;
  int ultimoEstadoDireito = HIGH;
  
  unsigned long ultimoDebounceTime_esquerdo = 0;
  unsigned long ultimoDebounceTime_centro = 0;
  unsigned long ultimoDebounceTime_direito = 0;
  unsigned long debounceDelay = 50;
};
