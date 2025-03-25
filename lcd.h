//Copyright (c) 2025 Bruno da Silva Santos

#pragma once
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


class LCD{
public:
  LCD();
  void Setup();
  void Imprimir(const int x, const int y, const char * text);
  void ImprimirA(const int x, const int y);
  void Limpar();
private:
  LiquidCrystal_I2C lcd;
  uint8_t blocoCheio[8] = { 
    0b11111, 
    0b11111, 
    0b11111, 
    0b11111, 
    0b11111, 
    0b11111, 
    0b11111, 
    0b11111 
  };
};
