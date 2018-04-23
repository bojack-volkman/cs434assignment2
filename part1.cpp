/*********************************************************************
 ** Program Filename:  part1.cpp
 ** Author: Justin Sherburne
 ** Date: 4/22/18
 ** Description: 
 ** Input: 
 ** Output:
 *********************************************************************/
#include "part1.hpp"

using namespace std;

int main(){
	
	string trainfile = "knn_train.csv";
	string testfile = "knn_test.csv";
	
	vector<values> train_values; //creates a vector that holds all the points for training
	get_points(train_values, trainfile);	
	normalize(train_values);
	
/*	for(int i =0; i < all_values.size(); i++){
		cout << all_values.at(i).weight << ", ";
		cout << all_values.at(i).qualifiers.at(0) << ", ";
		cout << all_values.at(i).qualifiers.at(1) << ", ";
		cout << all_values.at(i).qualifiers.at(2) << ", ";
		cout << all_values.at(i).qualifiers.at(3) << endl;
	}*/
	//cout << all_values.size() << endl;
	
	vector<values> test_values; //creates a vector that holds all the points for testing
	get_points(test_values, testfile);	
	normalize(test_values);	
	
  return 0;
}


void get_points(vector<values>& all_values, string filename){
  int flip = 0; //The deliminator between x & y
  int i = 0;
  int pos = 0; // vector position variable 
  char c;
  char stringx[250];
  memset (stringx, '\0', 250);
  values current_value;

    ifstream input_file(filename.c_str()); //opens the file example.input

    if(input_file.is_open()){
      while(input_file.get(c)){
		if( flip == 1){
			pos++;
			flip = 0;
		}
		else if( c == '\n' ){					//If it's a newline
			current_value.qualifiers.push_back(atof(stringx));
			all_values.push_back(current_value); //adds it to the vector
			memset (stringx, '\0', 250);			//Clear string
			current_value.qualifiers.clear();
			i = 0;									//Reset the string counter
			pos = 0;					//starting a new line
		}
		else if(pos == 0){
			if(c == '-'){
				current_value.weight = 0;
				flip = 1;					//We need to skip 1.
			} else{
				current_value.weight = 1;
			}
			pos++;
	
		}
        else if( c != ',' ){
			stringx[i] = c;				//If there is not a comma. Add it to the X string
			i++;
			pos++;
        }
		else if( c == ','){
			if(i > 0){
				current_value.qualifiers.push_back(atof(stringx));	
			}
			memset (stringx, '\0', 250);		//Clear the string.
			i = 0;				//Reset the sting counter
			pos++;
		}
      }
      input_file.close();					 //closes the input file
    }else{
      cout << "Unable to open file";
    }
}



void normalize(vector<values>& all_values){
	vector<float> maximums, minimums;		//Store the maximum value in an expanding vector
	float norm = 0;
	
	//First loop to find the max of each column.
	for(int i = 0; i < all_values.at(0).qualifiers.size(); i++){
		float max =0, min =0;
		for(int j = 0; j < all_values.size(); j++){
			if(all_values.at(j).qualifiers.at(i) > max){	//if x > y, store x
				max = all_values.at(j).qualifiers.at(i);
			}
			if(all_values.at(j).qualifiers.at(i) < min){	//if x > y, store x
				min = all_values.at(j).qualifiers.at(i);
			}
		}
		maximums.push_back(max);
		minimums.push_back(min);
	}
	
/*	for(int i =0; i < maximums.size(); i++){
		cout << maximums.at(i) << endl;
	}*/
	
	
	//Second loop to normalize
	for(int i = 0; i < all_values.at(0).qualifiers.size(); i++){
		for(int j = 0; j < all_values.size(); j++){
			norm = ((all_values.at(j).qualifiers.at(i) - minimums.at(i))/(maximums.at(i) - minimums.at(i)));
			all_values.at(j).qualifiers.at(i) = norm;
		}
	}	
}




