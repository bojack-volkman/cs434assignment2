#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<vector>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<algorithm>


struct values{
  std::vector<float> qualifiers;
  bool weight;
};


void get_points(std::vector<values>&, std::string);
void normalize(std::vector<values>&);
void neighborize(std::vector<values>&, std::vector<values>&, int);
float distance(std::vector<float>, std::vector<float>);

