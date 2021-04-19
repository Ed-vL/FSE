#include "../inc/pinWatcher.h"
#include "../inc/client.h"


void p1_handler(void){
    int state = digitalRead(6);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
    
}
void p2_handler(void){
    int state = digitalRead(25);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
}
void s1_handler(void){
    int state = digitalRead(21);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
}
void s2_handler(void){
    int state = digitalRead(22);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
}
void s3_handler(void){
    int state = digitalRead(26);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
}
void s4_handler(void){
    int state = digitalRead(27);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
}
void s5_handler(void){
    int state = digitalRead(28);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
}
void s6_handler(void){
    int state = digitalRead(29);
    if(state){
        sendMessage("1");
    } else {
        sendMessage("0");
    }
}
int watcher(){
  wiringPiISR(6,INT_EDGE_BOTH,&p1_handler);
  wiringPiISR(25,INT_EDGE_BOTH,&p2_handler);
  wiringPiISR(21,INT_EDGE_BOTH,&s1_handler);
  wiringPiISR(22,INT_EDGE_BOTH,&s2_handler);
  wiringPiISR(26,INT_EDGE_BOTH,&s3_handler);
  wiringPiISR(27,INT_EDGE_BOTH,&s4_handler);
  wiringPiISR(28,INT_EDGE_BOTH,&s5_handler);
  wiringPiISR(29,INT_EDGE_BOTH,&s6_handler);
}