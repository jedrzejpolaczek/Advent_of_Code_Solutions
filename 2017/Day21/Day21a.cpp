#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

std::vector<std::vector<std::string>>
split(const size_t &step, const std::vector<std::string> &current)
{
  std::vector<std::vector<std::string>> result;
  for(size_t x=0; x<current.size(); x+=step)
    {
      std::vector<std::string> row;
      for(size_t y=0; y<current.size(); y+=step)
        {
          std::string temp;
          for(size_t dy=0; dy<step; ++dy)
            {
              if(dy!=0)
                { temp+='/'; }
              temp+=current.at(y+dy).substr(x,step);
            }
          row.push_back(temp);
        }
      result.push_back(row);
    }
  return result;
}

std::string mirror(const std::string &s)
{
  std::string result(s);
  if(s.size()==5)
    {
      std::swap(result[0],result[1]);
      std::swap(result[3],result[4]);
    }
  else
    {
      std::swap(result[0],result[2]);
      std::swap(result[4],result[6]);
      std::swap(result[8],result[10]);
    }
  return result;
}

std::string flip(const std::string &s)
{
  std::string result(s);
  if(s.size()==5)
    {
      std::swap(result[0],result[3]);
      std::swap(result[1],result[4]);
    }
  else
    {
      std::swap(result[0],result[8]);
      std::swap(result[1],result[9]);
      std::swap(result[2],result[10]);
    }
  return result;
}

std::string rotate(const std::string &s)
{
  std::string result(s);
  if(s.size()==5)
    {
      result[0]=s[1];
      result[1]=s[4];
      result[4]=s[3];
      result[3]=s[0];
    }
  else
    {
      result[0]=s[2];
      result[2]=s[10];
      result[10]=s[8];
      result[8]=s[0];

      result[1]=s[6];
      result[6]=s[9];
      result[9]=s[4];
      result[4]=s[1];
    }
  return result;
}


std::string rotate(const std::string &s, const size_t &rotation)
{
  std::string result(s);
  for(size_t s=0; s<rotation; ++s)
    { result=rotate(result); }
  return result;
}

int main(int argc, char *argv[])
{
  std::ifstream infile(argv[1]);
  std::map<std::string,std::string> rules;

  std::string input, output, temp;
  infile >> input;
  while(infile)
    {
      infile >> temp >> output;

      std::string flipped_input(flip(input)), mirrored_input(mirror(input));
      for(size_t rotation=0; rotation<4; ++rotation)
        {
          if(rules.find(rotate(input,rotation))==rules.end())
            { rules.insert(std::make_pair(rotate(input,rotation), output)); }
          if(rules.find(rotate(flipped_input,rotation))==rules.end())
            { rules.insert(std::make_pair(rotate(flipped_input,rotation),
                                          output)); }
          if(rules.find(rotate(mirrored_input,rotation))==rules.end())
            { rules.insert(std::make_pair(rotate(mirrored_input,rotation),
                                          output)); }
        }

      infile >> input;
    }

  std::vector<std::string> current ({".#.","..#","###"});

  for(size_t count=0; count<18; ++count)
    {
      std::cout << "step: " << count << " " << current.size() << "\n";
      size_t step = (current.size()%2==0) ? 2 : 3;
      auto blocks=split(step,current);
      current.clear();
      for(auto &row: blocks)
        for(auto &block: row)
          {
            if(rules.find(block)==rules.end())
              std::cerr << "Not found: " << block << "\n";
            block=rules[block];
          }

      current.resize(blocks.size()*(step+1));
      for(auto &c:current)
        { c.resize(blocks.size()*(step+1)); }

      for(size_t x=0; x<blocks.size(); ++x)
        for(size_t y=0; y<blocks[x].size(); ++y)
          for(size_t dx=0; dx<(step+1); ++dx)
            for(size_t dy=0; dy<(step+1); ++dy)
              { current.at((step+1)*y+dy).at((step+1)*x+dx)=
                  blocks.at(x).at(y).at(dx+(step+2)*dy); }
      size_t on=0;
      for(auto &c: current)
        { on+=std::count(c.begin(),c.end(),'#'); }
      std::cout << "on: " << on << "\n";
    }
}