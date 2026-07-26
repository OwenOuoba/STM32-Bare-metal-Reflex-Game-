#ifndef BUZZER_H
#define BUZZER_H

#include "main.h"

extern TIM_HandleTypeDef htim2;

// Notes (Period = 1MHz / fréquence)
#define NOTE_C4  3822   // Do  262Hz
#define NOTE_D4  3405   // Ré  294Hz
#define NOTE_E4  3030   // Mi  330Hz
#define NOTE_F4  2865   // Fa  349Hz
#define NOTE_G4  2551   // Sol 392Hz
#define NOTE_A4  2272   // La  440Hz
#define NOTE_B4  2024   // Si  494Hz
#define NOTE_C5  1912   // Do  523Hz

void Buzzer_Play(uint32_t note, uint32_t duration_ms);
void Buzzer_Stop(void);

#endif
