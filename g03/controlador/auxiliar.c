
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int res;
    srand (clock() * time(NULL));
    res = random () % 1000;
    return res;
}
