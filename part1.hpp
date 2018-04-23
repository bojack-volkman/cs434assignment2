#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<vector>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<algorithm>

//contains one data point, plus its weight
struct values{
  std::vector<float> qualifiers;
  bool weight;
};

void get_points(std::vector<values>&, char*);

