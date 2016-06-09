#include "Controller.h"
#include <time.h>
#include <cstdlib>
// #include <iostream>

#define TIME ((const struct timespec[]){{0, 500000000L}})

Device * d = NULL;
Controller c;

struct args{
    int x;
    int y;
};

void *update(void * args) 
{
    struct args *g = (struct args*) args;
    int z = 8;
    while(1){
        if (!z)
            break;
        sleep(1);
        //nanosleep(TIME, NULL);
        c.off(g->x,g->y,z);
        c.on(g->x,g->y,--z);
        
    }
    return NULL;
}

void *displayT() 
{
    while(1){
        sleep(1);
        //nanosleep(TIME, NULL);
        c.display();
    }
    return NULL;
}
    
int main(int argc, char** argv) {
    
    c.connectDevice(1);
    d = c.getConnectedDevice();
    
    // srand(time(NULL));
    // int nb_alea = (rand() % 9);
    
    struct args *g1 = new struct args();
    g1->x = 2;
    g1->y = 4;
    struct args *g2 = new struct args();
    g2->x = 4;
    g2->y = 5;
    std::thread dis(displayT);

    std::thread goutte(update,g1);
    sleep(1);
    std::thread goutte2(update,g2);
    goutte2.join();
    goutte.join();
    
    
    //sleep(10);
    
    // goutte.detach();
    // goutte2.detach();
    dis.detach();
        
    c.disconnectDevice();
    return 0;
}



