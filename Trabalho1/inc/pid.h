int getPid(float systemTemp, float entryTemp){
    float error = entryTemp - systemTemp;
    int pid = ((2*(error*5)) + error);
    return pid;
}