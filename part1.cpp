/*********************************************************************
 ** Program Filename:  part1.cpp
 ** Author: Justin Sherburne, Scott Russell, Jacob Volkman
 ** Date: 4/22/18
 ** Description: Take's two CSV files and run's K-nearest neighbor calculations
 ** Input: knn_train.csv knn_test.csv
 ** Output: output.csv
 *********************************************************************/
#include "part1.hpp"

using namespace std;

int main(){
	string trainfile = "knn_train.csv";
	string testfile = "knn_test.csv";
	vector<int> errors;
	int k = 0;
	vector<values> train_values; //creates a vector that holds all the points for training
	get_points(train_values, trainfile);	
	normalize(train_values);
	
	vector<values> test_values; //creates a vector that holds all the points for testing
	get_points(test_values, testfile);	
	normalize(test_values);	
	
/*	for(int i =0; i < train_values.size(); i++){
		cout << train_values.at(i).weight << ", ";
		cout << train_values.at(i).qualifiers.at(0) << ", ";
		cout << train_values.at(i).qualifiers.at(1) << ", ";
		cout << train_values.at(i).qualifiers.at(2) << ", ";
		cout << train_values.at(i).qualifiers.at(3) << endl;
	}*/
	//cout << train_values.size() << endl;
	//cout << test_values.size() << endl;
	
	//errors = neighborize(train_values, test_values, k);
	//cout << "For K = " << k << " Total Errors = " << errors << endl;
	
	
	for(k = 0; k < 250; k++){
		errors.push_back(neighborize(train_values, train_values, k));
		cout << "running K = " << k << endl;
	}
	write_file(errors, 250);
	
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
	vector<double> maximums, minimums;		//Store the maximum value in an expanding vector
	double norm = 0;
	
	//First loop to find the max of each column.
	for(int i = 0; i < all_values.at(0).qualifiers.size(); i++){
		double max =0, min =0;
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

int neighborize(vector<values>& train_values, vector<values>& test_values, int k){
	std::vector<double> shortdist;
	std::vector<int> position;
	std::vector<double> distances;		// This will contain the distances from one point to all other points. 
	distances.clear();				//Clear for safe measure.
	shortdist.clear();
	position.clear();
	int errors = 0;
	int positives = 0;
	bool neighbors = 0;
	double dist =0;
	
	for(int i = 0; i < test_values.size(); i++){   //for each teest value
		for(int j = 0; j < train_values.size(); j++){  //go through all train values
			dist = mydistance(test_values.at(i).qualifiers, train_values.at(j).qualifiers);
			distances.push_back(dist);
		}
		
		for(int h = 0; h < k; h++){    //find the k smallest distances.
			shortdist.push_back(10000);  //push some placeholders. shortdist needs to be large for later...
			position.push_back(1);    //size doesnt matter here...
			for(int l = 0; l < distances.size(); l++){
				if(distances.at(l) < shortdist.at(h)){	//if it's smaller than shortdist
						shortdist.at(h) = distances.at(l);
						position.at(h) = l;
				}		
			}
			//cleanup distances to avoid duplicates
			distances.at(position.at(h)) = 1000;
		}
		
		/*you now have a list of k smallest distances in shortdist<>, and the positions in the test data stored in position<>.
		for(int h = 0; h <= k; h++){
		cout << distances.at(position.at(h)) << "== 1000" << endl;	
		cout << "Shortest: " << shortdist.at(h) << endl;
		cout << "Location: " << position.at(h) << endl;
		}*/
		
		//Now we find if it is a positive or negative point
		for(int h = 0; h < k; h++){
			if(train_values.at(position.at(h)).weight == 1){
				positives++;				//count the neighbors
			}
		}
		if(positives >= (k/2)){  	//classify the point
			neighbors = 1;
		}else{
			neighbors = 0;
		}
		if(k == 1){
			neighbors = positives;
		}
		//cout << positives << " : " << (k/2) << endl;
		if(test_values.at(i).weight != neighbors){ 	//check if KNN worked
			errors++;
		}
		
		distances.clear();				//Clear for next point.
		shortdist.clear();
		position.clear();
		neighbors = 0;
		positives = 0;
	}
	
	return errors;
		//cout << distances.size() << endl;
		//distances.clear();
}

double mydistance(std::vector<double> point1, std::vector<double> point2){
	double x = 0;	//distance accumulator
	double y = 0;	//temp var
	for(int i = 0; i < point1.size(); i++){
		y = (point1.at(i) - point2.at(i));      // x1+y1 , x2+y2,....
		y = y*y;								// y^2, squared distance
		x = x+y;								//Accumulate distances into x
		y = 0;
	}
	//x = sqrt(x);								//sqrt(everything)
	return x;									//distance
}


void write_file(vector<int> errors, int kmax){
ofstream output_file;
output_file.open("output.csv");
	for(unsigned i = 0; i < errors.size(); i++){
		output_file << i;
		output_file << ",";
		output_file << errors[i];
		output_file << endl;
		i++;
    }
}



