//Copyright (c) 2025 Bruno Santos

#pragma once
#include "lcd.h"


LCD::LCD ():  lcd(0x27, 20, 4) {}

void LCD::Setup(){
  Wire.begin();
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.clear();
  lcd.createChar(0, blocoCheio);
}
void LCD::Imprimir(const int x, const int y, const char * text){
  lcd.setCursor(x, y);
  lcd.print(text);
}
void LCD::ImprimirA(const int x, const int y){
  lcd.setCursor(x,y);
  lcd.write((uint8_t)0);
}
void LCD::Limpar(){
  lcd.clear();
}
