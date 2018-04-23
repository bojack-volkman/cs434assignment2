/*********************************************************************
 ** Program Filename:  Enhanced_Divide_And_Concoqer.cpp
 ** Author: Austin Hodgin, Justin Sherburne
 ** Date: 1/28/17
 ** Description: Finds the two closest points using Navive_Divide_And_Concoqer (O(nlogn))
 ** Input: example.input (points.txt)
 ** Output: output_enhanceddnc.txt
 *********************************************************************/
#include "part1.hpp"

using namespace std;

int main(int argc, char* argv[]){
	if(argv[1] == NULL){
		cout << "I NEED AN INPUT" << endl;
		return 0;
	}
	
	vector<values> all_values; //creates a vector that holds all the points
	get_points(all_values, argv[1]);	
	
	for(int i =0; i < all_values.size(); i++){
		cout << all_values.at(i).weight << ", ";
		cout << all_values.at(i).qualifiers.at(0) << ", ";
		cout << all_values.at(i).qualifiers.at(1) << ", ";
		cout << all_values.at(i).qualifiers.at(2) << ", ";
		cout << all_values.at(i).qualifiers.at(3) << endl;
	}
	//cout << all_values.size() << endl;
	
  return 0;
}





void get_points(vector<values>& all_values, char* filename){
  int flip = 0; //The deliminator between x & y
  int i = 0;
  int pos = 0; // vector position variable 
  char c;
  char stringx[250];
  memset (stringx, '\0', 250);
  values current_value;

    ifstream input_file (filename); //opens the file example.input

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




