//Parker King-Fournier Assignment 4 - MUMT 306//

//COMPILE STATEMENT:
//g++ Randomlist.cpp; ./a.out

//include all of the libraries we need. 
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	//initialize the vector to contain numbers 1 to 10
	vector <int> numbers_to_ten(10, 0.0);

	//fill the vector with the numbers 1 to 10
	for(int i = 0; i < numbers_to_ten.size(); i++)
	{
		numbers_to_ten[i] = i+1;
	}

	//Generate a random position in the vector by seeding the rand() function with the time
	//print the number at that position, then remove it from the list
	//repeat this 10 times, since there are 10 items in the vector
	for(int i = 0; i < 10; i++)
	{
		srandomdev();
		//srand(time(0));
		int position = random() % numbers_to_ten.size();
		cout << " " << numbers_to_ten.at(position);
		numbers_to_ten.erase (numbers_to_ten.begin() + position);
	}

	//Formatting
	cout << "\n";
}
