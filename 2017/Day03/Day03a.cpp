#include <iostream>		//std::cout
#include <array>		//std::array

int solve_wk(int num) {
    std::array<int,8> slice{{1, 1, 1, 1, 1, 1, 1, 1}};
    std::array<int,8> offsets{{1, 2, 3, 4, 5, 6, 7, 8}};
	
    for (int disp = 1; true; ++disp) {
        for (int i = 0; i < 8; ++i) {
            slice[i] += offsets[i];
            if (slice[i] >= num) 
                return (disp + (num - slice[(i + 7) & 0x7]));
            offsets[i] += 8;
        }
    }
}

int main(int argc, char ** argv) {
	
	int num = 361527;
	std::cout<<solve_wk(num)<<std::endl;

	return 0;
}