#include "../inc/pinWatcher.h"
#include "../inc/client.h"


void p1_handler(void){
    printf("Borda detectada\n");
    int state = digitalRead(P1_pin);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
    watcher();
}
void p2_handler(void){
    printf("Borda detectada\n");
    int state = digitalRead(P2_pin);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
    watcher();
}
void s1_handler(void){
    printf("Borda detectada\n");
    int state = digitalRead(S1_pin);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
    watcher();
}
void s2_handler(void){
    printf("Borda detectada\n");
    int state = digitalRead(S2_pin);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
    watcher();
}
void s3_handler(void){
    printf("Borda detectada\n");
    int state = digitalRead(S3_pin);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
    watcher();
}
void s4_handler(void){
    printf("Borda detectada\n");
    int state = digitalRead(S4_pin);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
    watcher();
}
void s5_handler(void){
    printf("Borda detectada\n");
    int state = digitalRead(S5_pin);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
    watcher();
}
void s6_handler(void){
    printf("Borda detectada\n");
    int state = digitalRead(S6_pin);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
    watcher();
}
void watcher(){
  wiringPiISR(P1_pin,INT_EDGE_BOTH,&p1_handler);
  wiringPiISR(P2_pin,INT_EDGE_BOTH,&p2_handler);
  wiringPiISR(S1_pin,INT_EDGE_BOTH,&s1_handler);
  wiringPiISR(S2_pin,INT_EDGE_BOTH,&s2_handler);
  wiringPiISR(S3_pin,INT_EDGE_BOTH,&s3_handler);
  wiringPiISR(S4_pin,INT_EDGE_BOTH,&s4_handler);
  wiringPiISR(S5_pin,INT_EDGE_BOTH,&s5_handler);
  wiringPiISR(S6_pin,INT_EDGE_BOTH,&s6_handler);
}