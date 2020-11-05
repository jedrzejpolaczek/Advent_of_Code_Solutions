#include <FTensor.hpp>

#include <fstream>
#include <vector>
#include <set>
#include <iostream>

struct Point
{
  FTensor::Tensor1<int64_t,3> x, v, a;
};

int main(int argc, char *argv[])
{
  std::ifstream infile(argv[1]);
  int source;
  std::vector<Point> points, new_points;
  Point p;
  FTensor::Index<'i',3> i;
  infile >> p.x;
  while(infile)
    {
      infile >> p.v >> p.a;
      points.push_back(p);
      infile >> p.x;
    }
  for(size_t step=0; step<100; ++step)
    {
      std::cout << points.size() << "\n";
      for(auto &p: points)
        {
          p.v(i)=p.v(i)+p.a(i);
          p.x(i)=p.x(i)+p.v(i);
        }
      std::set<size_t> to_be_removed;
      for(size_t p=0; p!=points.size(); ++p)
        {
          auto q=p;
          ++q;
          for(; q!=points.size(); ++q)
            {
              FTensor::Tensor1<int64_t,3> diff;
              diff(i)=points[p].x(i)-points[q].x(i);
              if(diff.l2_squared(FTensor::Number<3>())==0)
                {
                  to_be_removed.insert(p);
                  to_be_removed.insert(q);
                }
            }
        }
      new_points.clear();
      for(size_t p=0; p!=points.size(); ++p)
        {
          if(to_be_removed.find(p)==to_be_removed.end())
            { new_points.push_back(points[p]); }
        }
      std::swap(points,new_points);
    }
}