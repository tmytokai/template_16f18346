#pragma once

enum
{
    TIMER_NUM = 6
};

typedef void (*pisr)(void);

void init_int(void);
void config_int(const pisr pisr, const char edg);

void init_timer(void);
void config_timer1(const pisr pisr);
void config_timer3(const pisr pisr);
void config_timer5(const pisr pisr);
void timer1(const long interval);
void timer3(const long interval);
void timer5(const long interval);