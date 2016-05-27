#include <unistd.h>

#include "Cube.h"

int main () {

	Cube cube;

	for (int z = 0; z < 9; ++z) {
		cube.on(0, 0, z);
		cube.display((const char*)("/dev/ttyACM0"));
		sleep(1);
	}

	return 0;
}
