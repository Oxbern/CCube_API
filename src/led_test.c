#include "../../CCube_Firmware/usb/user/usbd_cdc_if.h"


int main(int argc, char* argv[])
{
    if (argc != 9){
	printf("Usage : ./main --dev /dev/ttyACM0 -x x -y y -z z");
	exit(0);
    }
    char * cubeToUse = argv[2];
  
    if (strcmp(argv[1], "--dev")){
	printf("Precise which cube you want to use with --dev CubeToUse ");
	exit(0);
    }
    int x = 0, y = 0, z = 0;
    if (strcmp(argv[3], "-x")){
	printf("Precise coords with -x x -y y -z z ");
	exit(0);
    }
    x = atoi(argv[4]);
    if (strcmp(argv[5], "-y")){
	printf("Precise coords with -x x -y y -z z ");
	exit(0);
    }
    y = atoi(argv[6]);
    if (strcmp(argv[7], "-z")){
	printf("Precise coords with -x x -y y -z z ");
	exit(0);
    }
    z = atoi(argv[8]);
    connect(cubeToUse); 
    display(x,y,z);
    disconnect(cubeToUse); 
  
}

    
