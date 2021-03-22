#ifndef _PID_
#define _PID_

extern float ki;
extern float kp;
extern float kd;

extern float reference;
extern float erro_total;
extern float erro_anterior;
extern float T;
extern float max_control;
extern float min_control;

void setReference(float r);

int pidControl(float temp);

#endif