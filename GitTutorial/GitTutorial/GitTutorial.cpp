#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

bool Guess(int number) {
	static int target = -1;

	srand(time(NULL));
	if (target == -1) {
		target = rand() % 100 + 1;
	}
	if (number == target)
		if (number == target) {
			std::cout << "Correct !!";
			target = -1;
			return true;
		}
		else std::cout << "Wrong" << std::endl;
	return false;
}
int main() 
{
	int guess;
	do {
		std::cin >> guess;
	} while (!Guess(guess));
	return 0;
	
}