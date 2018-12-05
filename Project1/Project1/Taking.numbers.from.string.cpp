#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct not_digit {
	bool operator()(const char c)
	{
		return c != ' ' && !isdigit(c);
	}
};

//
//int main()
//{
//	//bool redWin = true;
//	not_digit notADigit;
//
//	int x = 80;
//	int y = 90;
//
//	string message = string("X: " + to_string(x) + ", Y: "+to_string(y));
//
//	std::cout << message << std::endl;
//	std::cout << "Here is another line" << std::endl;
//
//	string::iterator end = std::remove_if(message.begin(), message.end(), notADigit);
//
//	string all_numbers(message.begin(), end);
//	std::cout << all_numbers;
//
//	stringstream ss(all_numbers);
//	vector<int> vec;
//    std::cout<< std::endl; 
//    std::cout << "Let's start next line" << std::endl;
//    int i;
//	for (; ss >> i;)
//	{
//		vec.push_back(i);
//		cout << i << endl;
//	}
//
//	system("PAUSE");
//
//}
//
