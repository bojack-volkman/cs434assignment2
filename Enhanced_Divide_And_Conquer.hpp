#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<vector>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<algorithm>


struct points{
  float x;
  float y;
};


float min(float, float);
float find_distance(points, points);
float strip_closest(std::vector<points>&, unsigned, float&);
float closest_points(std::vector<points>&, std::vector<points>&, float& );
float closest_points_recursive(std::vector<points>&, std::vector<points>&, std::vector<points>&, unsigned, float& );
float brute_force(std::vector<points>&, std::vector<points>&, float&);
void get_points(std::vector<points>&, char*);
void write_file(std::vector<points>&, float&, float);
void write_time(std::vector<points>&, float);
bool compareX(const points, const points);
bool compareY(const points, const points);
