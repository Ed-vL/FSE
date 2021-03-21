float ki = 1.0;
float kp = 5.0;
float kd = 5.0;

float reference;
float erro_total = 0;
float erro_anterior = 0;
float T = 1;
float max_control = 100;
float min_control = -100;

void setReference(float r){
    reference = r;
}

int pidControl(float temp){
    float erro = reference - temp;

    erro_total += erro;
    if(erro_total >= max_control){
        erro_total = max_control;
    } else if(erro_total <= min_control) {
        erro_total = min_control;
    }
    float delta_error = erro - erro_anterior;

    float pid = kp*erro + (ki*T)*erro_total + (kd/T)*delta_error;

    if(pid >= max_control){
        pid = max_control;
    } else if(pid <= min_control){
        pid = min_control;
    }
    erro_anterior = erro;
    return (int)pid;
}

