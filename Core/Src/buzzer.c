#include "buzzer.h"


void Buzzer_Play(uint32_t note, uint32_t duration_ms)
{
    // 1. Set frequency and 50% duty cycle
    __HAL_TIM_SET_AUTORELOAD(&htim2, note);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, note / 2);

    // 2. Force the timer to update its registers immediately
    HAL_TIM_GenerateEvent(&htim2, TIM_EVENTSOURCE_UPDATE);

    // 3. Make sure it's actually started
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

    HAL_Delay(duration_ms);
}

void Buzzer_Stop(void)
{
    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
}
