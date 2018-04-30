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
  std::vector<double> qualifiers;
  bool weight;     //1 for positive, 0 for negative
};



void get_points(std::vector<values>&, std::string);
void normalize(std::vector<values>&);
int neighborize(std::vector<values>&, std::vector<values>&, int);
double mydistance(std::vector<double>, std::vector<double>);
void write_file(std::vector< std::vector<int> >, int);

