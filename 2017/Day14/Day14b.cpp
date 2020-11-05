#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

#include <bitset>
#include <vector>
#include <array>
#include <numeric>
#include <iostream>
#include <fstream>
#include <iomanip>

std::array<uint8_t,256> run_rounds(const std::vector<uint8_t> inputs,
                                   const size_t &hash_length,
                                   const size_t &num_rounds)
{
  std::array<uint8_t,256> ring;
  std::iota(ring.begin(), ring.end(), 0);

  size_t skip(0), current(0);
  for (size_t round=0; round<num_rounds; ++round)
    {
      for (auto &input: inputs)
        {
          uint8_t start (current + (input-1));
          uint8_t finish(current);

          const uint8_t stop (input/2);
          for (uint8_t ix=0; ix != stop; ++ix)
            {
              std::swap(ring[start], ring[finish]);
              --start;
              ++finish;
            }
          current += input + skip;
          ++skip;
        }
    }
  return ring;
}
std::vector<uint8_t> compute_dense_hash(const size_t &hash_length,
                                        const std::vector<uint8_t> &inputs)
{
  auto inputs_copy(inputs);
  for (auto &c: {17, 31, 73, 47, 23})
    { inputs_copy.push_back(c); }
  auto ring(run_rounds(inputs_copy,hash_length,64));

  std::vector<uint8_t> dense_hash(hash_length/16);
  for (size_t ix=0; ix<hash_length; ix+=16)
    { for(size_t jx=0; jx<16; ++jx)
        { dense_hash[ix/16]^=ring[ix+jx]; } }

  return dense_hash;
}

int main(int, char *argv[])
{
  const size_t hash_length(256);

  size_t total_memory(0);
  std::vector<std::vector<size_t>> bit_array(128);
  for(auto &b: bit_array)
    { b.resize(128,-1); }

  boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS> graph;
  size_t memory_id(0);
  for (size_t row=0; row<128; ++row)
    {
      std::vector<uint8_t> inputs;
      for (auto &c: argv[1] + ("-" + std::to_string(row)))
        { inputs.push_back(c); }

      auto dense_hash(compute_dense_hash(hash_length,inputs));
      for (auto &h: dense_hash)
        { total_memory+=std::bitset<8>(h).count(); }

      for(size_t b=0; b<128/8; ++b)
        {
          std::bitset<8> b8(dense_hash[b]);
          for(size_t c=0; c<8; ++c)
            {
              auto is_on (b8[7-c]);
              if(is_on)
                {
                  bit_array[row][b*8 + c]=memory_id;
                  if(row!=0 && bit_array[row-1][b*8 + c]!=-1)
                    { add_edge(memory_id, bit_array[row-1][b*8 + c], graph); }

                  if((b!=0 || c!=0) && bit_array[row][b*8 + c-1]!=-1)
                    { add_edge(memory_id, bit_array[row][b*8 + c-1], graph); }
                  ++memory_id;
                }
            }
        }
    }
  std::cout << "Part 1: " << total_memory << "\n";

  std::vector<int> component(boost::num_vertices(graph));
  std::cout << "Part 2: "
            << connected_components(graph, &component[0])
            << "\n";


}