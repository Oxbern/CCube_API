#include <cstdint>
#include <stdio.h>
#include <cstdlib>

#include "Cube.h"

int main() {
    Cube cube;

    cube.on(0, 0, 0);
    cube.display("local");

    return 0;
}
