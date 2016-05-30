#include <iostream>
#include <time.h>

using namespace std;

void Run() {

	clock_t clocks_0 = 0;
	clock_t clocks_1;
	float delta_time = 200;
	float elapsed_ms;

	while(true) {

		clocks_1 = clock();
		elapsed_ms = float(clocks_1 - clocks_0) / (CLOCKS_PER_SEC/1000);

		if(elapsed_ms >= delta_time) {
			clocks_0 = clocks_1;
			
			// Do computations
		}
	}
}

int main(int argc, char** argv) {

	Run();

	return 0;
}