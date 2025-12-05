#pragma once

enum
{
    TIMER_NUM = 6
};

typedef void (*pisr)(void);

void init_int(void);
void config_int(const pisr pisr, const char edg);

void init_timer(void);
void config_timer1(const pisr pisr, const long interval);
void config_timer3(const pisr pisr, const long interval);
void config_timer5(const pisr pisr, const long interval);