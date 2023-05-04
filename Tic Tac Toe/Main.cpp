#include <iostream>

int main() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%i", 3 * (j + 1) - i);
			if (j < 2) printf("|");
		}
		
		printf("\n");
	}
}