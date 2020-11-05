#include <iostream>			//std::cout
#include <bits/stdc++.h>	//std::bitset

int main() { 
	long long number_A = 634;
	long long number_B = 301;	
	int factor_A = 16807;
	int factor_B = 48271;
	int multiplier_A = 4;
	int multiplier_B = 8;
	long int divide_factor = 2147483647;
	int result = 0; 

  	for(int i = 0; i < 5000000; i++) {
      	do {
			number_A *= factor_A;
			number_A %= divide_factor;
      	} while(number_A % multiplier_A != 0);
      	do {
			number_B *= factor_B;
			number_B %= divide_factor;
      	} while(number_B % multiplier_B != 0);

      	std::bitset<16> bit_A(number_A), bit_B(number_B);
      	if(bit_A == bit_B) 
		  	result++;
  	}

  	std::cout << result; 

  	return 0;
}