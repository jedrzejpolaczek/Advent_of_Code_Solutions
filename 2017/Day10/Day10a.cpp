#include <vector>	//std::vector
#include <numeric>	//std::iota
#include <iostream>	//std::cout
#include <iomanip>	//std::setfill

std::vector<size_t> run_rounds(const std::vector<uint8_t> inputs, const size_t &hash_length, const size_t &num_rounds) {
  std::vector<size_t> ring(hash_length), new_ring(hash_length);
  std::iota(ring.begin(), ring.end(), 0);

  size_t skip(0), current(0);
  for (size_t round=0; round<num_rounds; ++round)
      for (auto &input: inputs)
          for (size_t ix=0; ix != input; ++ix)
            {
              new_ring[(current + (input-1-ix))%hash_length]=
                ring[(current + ix)%hash_length];
            }
          for (size_t ix=input; ix != hash_length; ++ix)
            {
              new_ring[(current + ix)%hash_length]=
                ring[(current + ix)%hash_length];
            }
          std::swap(ring,new_ring);
          current += input + skip;
          ++skip;
  return ring;
}

int main() {
  	const size_t hash_length(256);

    std::vector<uint8_t> inputs{46,41,212,83,1,255,157,65,139,52,39,254,2,86,0,204};
    auto ring(run_rounds(inputs,hash_length,1));
    std::cout << "Round 1: " << ring[0]*ring[1] << "\n";

    std::string input_string("46,41,212,83,1,255,157,65,139,52,39,254,2,86,0,204");
    std::vector<uint8_t> inputs;
    for (size_t ix=0; ix<input_string.size(); ++ix)
    	inputs.push_back(input_string[ix]); 

    for (auto &c: {17, 31, 73, 47, 23})
    	inputs.push_back(c); 
    auto ring(run_rounds(inputs,hash_length,64));

    std::vector<uint8_t> dense_hash(hash_length/16);
    for (size_t ix=0; ix<hash_length; ix+=16)
		for(size_t jx=0; jx<16; ++jx)
        	dense_hash[ix/16]^=ring[ix+jx];
    std::cout << "Round 2: ";
    for (auto &h: dense_hash)
    	std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)h;
    std::cout << "\n";
}