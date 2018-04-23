#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <fstream>
using namespace std;

double entropy(int x);
int import_data(char* filename);
struct entropy_values{
	double rootPositive;
	double rootNegative;
	double LeftPositive;
	double LeftNegative;
	double rightPositive;
	double rightNegative;
	
	
};entropy_values tree[100];





int main (int argc, char* argv[]){

import_data (argv[1]);



// testing entropy
tree[0].rootPositive = 26;
tree[0].rootNegative = 7;
tree[0].LeftPositive = 21;
tree[0].LeftNegative = 3;
tree[0].rightPositive = 5;
tree[0].rightNegative = 4;
	double gain;
	gain = entropy(0);	
	cout<<gain<<endl;
// end of testing entropy	
	
	return 0;
}




int import_data(char *filename){
	
// to be added				
			
}

double entropy (int x){
double root_total = tree[x].rootPositive + tree[x].rootNegative;
double left_total = tree[x].LeftPositive + tree[x].LeftNegative;
double right_total = tree[x].rightPositive + tree[x].rightNegative;

double Htree = (-1*tree[x].rootPositive / root_total)*(log2(tree[x].rootPositive / root_total)) - (tree[x].rootNegative / root_total) * log2(tree[x].rootNegative/ root_total);

double HLeft = (-1*tree[x].LeftPositive / left_total)* (log2(tree[x].LeftPositive / left_total)) - (tree[x].LeftNegative / left_total) * log2(tree[x].LeftNegative / left_total);

double HRight = (-1*tree[x].rightPositive / right_total)* (log2(tree[x].rightPositive / right_total)) - (tree[x].rightNegative / right_total) * log2(tree[x].rightNegative / right_total);

double Left_Count = (tree[x].LeftPositive+tree[x].LeftNegative) / root_total;

double Right_Count = (tree[x].rightNegative+tree[x].rightPositive) / root_total;

double gain = Htree - Left_Count * HLeft - Right_Count * HRight;

	
return gain;	
}
