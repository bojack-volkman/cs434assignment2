/*********************************************************************
 ** Program Filename:  Enhanced_Divide_And_Concoqer.cpp
 ** Author: Austin Hodgin, Justin Sherburne
 ** Date: 1/28/17
 ** Description: Finds the two closest points using Navive_Divide_And_Concoqer (O(nlogn))
 ** Input: example.input (points.txt)
 ** Output: output_enhanceddnc.txt
 *********************************************************************/
#include "Enhanced_Divide_And_Conquer.hpp"

using namespace std;

int main(int argc, char* argv[]){
	if(argv[1] == NULL){
		cout << "I NEED AN INPUT" << endl;
		return 0;
	}
	
	clock_t t;
	t = clock();
	vector<points> all_points; //creates a vector that holds all the points
	vector<points> short_dis_points; //holds the points that have the shortest distance

	float min_distance = 1000;														//store the current minimum distance between two points
	unsigned position = 0;


	get_points(all_points, argv[1]);												//gets all the points form example.input
	closest_points(all_points, short_dis_points, min_distance);
	t = clock() - t;
	write_file(short_dis_points, min_distance,(float) t);										//the two points (or all points of that value)

   //prints the full vector for testing
   for(unsigned i = 0; i < short_dis_points.size() - 1 ; i++){
       cout << "X: " << short_dis_points[i].x << " ";
       cout << "Y: " << short_dis_points[i].y << " ";
       cout << "X: " << short_dis_points[i+1].x << " ";
       cout << "Y: " << short_dis_points[i+1].y << endl;
       i++;
   }
     cout << "The min distance is: " << min_distance << endl;

  return 0;
}

/*********************************************************************
 ** Function: Min
 ** Description: returns the minimum number between x and y
 ** Parameters: float x, float y
 *********************************************************************/
float min(float x, float y){
  if(x < y){			 //if x is less than y then return x
    return x;
  }
  else if(y <= x){ 		//if x is less than or equal to y then return y
    return y;
  }
}

/*********************************************************************
 ** Function: compareX
 ** Description: utility functions for the sort function to sort based on X
 ** Parameters:  const points p1,  const points p2
 *********************************************************************/
bool compareX(const points x1, const points x2){
    return x1.x < x2.x;
}

/*********************************************************************
 ** Function: compareY
 ** Description: utility function for the sort function to sort based on Y
 ** Parameters: points p1, points p2
 *********************************************************************/
bool compareY(const points x1, const points x2){
    return x1.y < x2.y;
}

/*********************************************************************
 ** Function: min_dist
 ** Description: returns the distance between to given points
 ** Parameters: points p1, points p2
 *********************************************************************/
float find_distance(points p1, points p2 ){
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

/*********************************************************************
 ** Function: get_points
 ** Description: gets all the points from the input file example.input and puts
 ** in the vector all_points that is passed into the function
 ** Parameters: points p1, points p2
 *********************************************************************/

void get_points(vector<points>& all_points, char* filename){
  int count = 1; //This is the number of input values.
  int flip = 0; //The deliminator between x & y
  int i = 0;
  char c;
  char stringx[250], stringy[250];
  memset (stringx, '\0', 250);
  memset (stringy, '\0', 250);

    ifstream input_file (filename); //opens the file example.input

    if(input_file.is_open()){
      while(input_file.get(c)){
        points current_points;
        if( c != ' ' && flip == 0){
			stringx[i] = c;				//If there is not a space. Add it to the X string
			i++;
        }
        else if( c != '\n' && flip == 1){
			       stringy[i] = c;		//If there is not an /n. Add it to the Y string
			        i++;
		}
		else if( c == ' '){						//If it's a space:
			flip = 1 ;							//Switch to Y
			current_points.x = atof(stringx);	//convert the string to a float
			memset (stringx, '\0', 250);		//Clear the string.
			i = 0;								//Reset the sting counter
		}
		else if( c == '\n' ){					//If it's a newline
			flip = 0;							//Switch to X
			current_points.y = atof(stringy);	//convert the string to a float
			all_points.push_back(current_points); //adds it to the vector
			memset (stringy, '\0', 250);			//Clear string
			i = 0;									//Reset the string counter
		}
      }
      input_file.close();					 //closes the input file
    }else{
      cout << "Unable to open file";
    }
}

/*********************************************************************
 ** Function: brute_force
 ** Description:finds the shortacce distance betwen all the points returns that
 ** value and the points those values have
 ** Parameters: all_points, shortest_points, sample size, min_dist, position
 *********************************************************************/

float brute_force(vector<points>& all_points, vector<points>& short_dis_points, float& min_distance){
	float temp_min = 10000; //temp to hold the calulated min distance to be chcked against the current min distance
	for(unsigned i = 0; i < all_points.size()-1; i++){
		for(unsigned j = 1; j < all_points.size()-1; j++){			//Iterate through all combinations of points in the range
		if(i == j){
			break;
		}
		temp_min = find_distance(all_points[i], all_points[j]);
		if(min_distance == temp_min){								//If they match the minimum
			short_dis_points.push_back(all_points[i]);				//add them into the short vector
			short_dis_points.push_back(all_points[j]);
		}
		else if( min_distance > temp_min){						//If they are closer than the min
			short_dis_points.clear();								//clear the short vector for the new guys
			short_dis_points.push_back(all_points[i]);				//add them into the short vector
			short_dis_points.push_back(all_points[j]);
		}
		min_distance = min(min_distance, temp_min);
		}
	}
	return min_distance;
}



/*********************************************************************
 ** Function: strip_closest
 ** Description: Calulates the minimum distance in the middle strip. with O(N)
 ** Parameters: vector<points> strip, size, d (current min distance),
 *********************************************************************/

float strip_closest(vector<points>& strip, unsigned size, float& d){
	float min = d; //set the minimum distance as d
	for(int i = 0; i < size; i++ ){
		for(int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; j++){  //this loop will run at most 6 times making this O(n)
			if(find_distance(strip[i], strip[j] ) < min){
				min = find_distance(strip[i], strip[j]); //sets the new miniumum distance
			}
		}
	}
	return min;
}
/*********************************************************************
 ** Function: closest_points_recursive
 ** Description:
 ** Parameters:
 *********************************************************************/

 float closest_points_recursive(vector<points>& sorted_x, vector<points>& sorted_y, vector<points>& short_dist_points, unsigned size,  float& min_distance){
	if(size <= 3){
		return brute_force(sorted_x, short_dist_points, min_distance);
	}

	unsigned mid = size/2; //mid line for the start of the recurstion
	vector<points> Points_left; //vector to store the left half
	vector<points> Points_right; //vector to store the right half
	vector<points> sorted_x_right;
	vector<points> strip;
	float distance_left;
	float distance_right;
	points midPoint = sorted_x[mid]; //getting the middle point values
			//divied all points stored in the sorted(Y) around the vertical line (midpoint)
	for(unsigned i = 0; i < size; i++){
		if(sorted_y[i].x <= midPoint.x){
			Points_left.push_back(sorted_y[i]);
		}else{
			Points_right.push_back(sorted_y[i]);
		}
	}
	for(unsigned i = mid; i < size; i++){
			sorted_x_right.push_back(sorted_x[i]);
	}
	distance_left = closest_points_recursive(sorted_x, Points_left, short_dist_points, mid,  min_distance); //recurse on the left half
	distance_right = closest_points_recursive(sorted_x_right, Points_right, short_dist_points, (size - mid), min_distance); //recurse on the right half
	
	if(distance_left && distance_right != 0){
		min_distance = min(distance_left, distance_right); //find the smaller of the two points
	}
	for( unsigned i = 0; i < size; i++){
		if(fabs(sorted_y[i].x - midPoint.x) < min_distance){
				strip.push_back(sorted_y[i]);
		}
	}
	return min(min_distance, strip_closest(strip, strip.size(), min_distance));

}

/*********************************************************************
 ** Function:closest_points
 ** Description: sorts the vectors for both x and y and then starts the recursive function to find the
 ** closest points and returns those points as well as the vector lists that minimum distances
 ** Parameters: vector<points> all_points, int n (size of vector),
 *********************************************************************/

float closest_points(vector<points>& all_points, vector<points>& short_dis_points, float& min_distance){
	vector<points> sorted_y; //new vector to hold the vector that is sorted by y
	sort(all_points.begin(), all_points.end(), compareX ); //sorts the main vector by x
	for(unsigned i = 0; i < all_points.size(); i++ ){ //copy all points from main vector into new sorted_y vector to be sorted later
		sorted_y.push_back(all_points[i]);
	}
	sort(sorted_y.begin(), sorted_y.end(), compareY); //sorts the vector by the y componets.
	return closest_points_recursive(all_points, sorted_y, short_dis_points, all_points.size(), min_distance );
	
}


/*********************************************************************
 ** Function: Write_file
 ** Description: Writes our solution to the file.
 ** Parameters: The vector of shortest points and the min distance
*********************************************************************/
void write_file(vector<points>& short_dist, float& min_distance, float t){

  ofstream output_file;
  output_file.open("output_enhanceddnc.txt");
  output_file << min_distance << endl;
  //for(unsigned i = 0; i < short_dist.size(); i++){
	  int i=0;
    output_file << short_dist[i].x;
    output_file << " ";
    output_file << short_dist[i].y;
    output_file << "   ";
    output_file << short_dist[i+1].x;
    output_file << " ";
    output_file << short_dist[i+1].y;
    output_file << endl;
  //  i++;
  //  }
}

/*********************************************************************
 ** Function: Write_file
 ** Description: Writes the number of elements and how long it took for the
 **
 ** Parameters: Writes the times it took
 *********************************************************************/
void write_time(vector<points>& all_points, float t ){

  ofstream output_file;
  output_file.open("execution_time.txt",fstream::app);
	int num_input = all_points.size()+1;
	t = t / CLOCKS_PER_SEC;

	output_file << "execution_time_enhanced.txt:  " << num_input << " Elements" << endl;
	output_file << "It took: " << t << " seconds" << endl;
	output_file << endl;

}
