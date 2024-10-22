#include <iostream>
#include <cmath>

using namespace std;

//Defines Pi for use in the calculation of the distance
const float Pi = 3.14;


void UserInput(float& first_Coordinate_X, float& second_Coordinate_Y);
float Inclination(float& temporary_Coordinate_Y, float& temporary_Coordinate_X, float& first_Coordinate_X, float& second_Coordinate_Y, float& inclination);
float Calculating_B(float& first_Coordinate_X, float& second_Coordinate_Y, float& inclination, float& b);
void Calculating_CrossingPoints(float& topCrossingPoint, float& bottomCrossingPoint, float& leftCrossingPoint, float& rightCrossingPoint, float inclination, float b);
void Checking_CrossingPoints(float& first_Coordinate_X, float& second_Coordinate_Y, float topCrossingPoint, float bottomCrossingPoint, float leftCrossingPoint, float rightCrossingPoint);
float Calculating_X(float& first_Coordinate_X, float& second_Coordinate_Y, float& temporary_Coordinate_X, float& temporary_Coordinate_Y, float& X);
float Distance(float& distance, float X);

int main()
{
	unsigned int input_Number = 0;
	float first_Coordinate_X = 0.0;
	float second_Coordinate_Y = 0.0;
	float temporary_Coordinate_X = 0.0;		// This will store the value of coordinate X for the next cycle
	float temporary_Coordinate_Y = 0.0;		// This will store the value of coordinate Y for the next cycle
	float X = 0.0;							// THis will store the value of X that is needed to calculate the distance from A to B
	float distance = 0.0;					// Stores the distance made by the player
	float total_Distance = 0.0;
	float inclination = 0.0;
	float b = 0.0;					//This is needed for calculating where the line crosses the rectangle and its from the formula y=(m*x)+b
	float topCrossingPoint = 0.0;
	float bottomCrossingPoint = 0.0;
	float leftCrossingPoint = 0.0;
	float rightCrossingPoint = 0.0;

	cout << "Enter a positive number for number of iterations: ";
	cin >> input_Number;

	int a = 0;
	while (a < input_Number) {
		UserInput(first_Coordinate_X, second_Coordinate_Y);
		Inclination(temporary_Coordinate_Y, temporary_Coordinate_X, first_Coordinate_X, second_Coordinate_Y, inclination);
		Calculating_B(first_Coordinate_X, second_Coordinate_Y, inclination, b);
		Calculating_CrossingPoints(topCrossingPoint, bottomCrossingPoint, leftCrossingPoint, rightCrossingPoint, inclination, b);
		Checking_CrossingPoints(first_Coordinate_X, second_Coordinate_Y, topCrossingPoint, bottomCrossingPoint, leftCrossingPoint, rightCrossingPoint);
		X = Calculating_X(first_Coordinate_X, second_Coordinate_Y, temporary_Coordinate_X, temporary_Coordinate_Y, X);
		total_Distance += Distance(distance, X);
		a++;
	}

	cout << "\n" << total_Distance;

}

//Takes the coordinates from the user (chip)
void UserInput(float& first_Coordinate_X, float& second_Coordinate_Y) {
	cin >> first_Coordinate_X;
	cin >> second_Coordinate_Y;
}

//Calculates the inclination of the line if the dot is outside of the rectangle(field)
float Inclination(float& temporary_Coordinate_Y, float& temporary_Coordinate_X, float& first_Coordinate_X, float& second_Coordinate_Y, float& inclination) {

	if (first_Coordinate_X == temporary_Coordinate_X) {
		inclination = 0;
	}
	else {
		inclination = (second_Coordinate_Y - temporary_Coordinate_Y) / (first_Coordinate_X - temporary_Coordinate_X);
	}
	return inclination;
}

//This formula is needed if the line crosses the rectangle (field)
float Calculating_B(float& first_Coordinate_X, float& second_Coordinate_Y, float& inclination, float& b) {
	b = second_Coordinate_Y - (inclination * first_Coordinate_X);
	return b;
}

void Calculating_CrossingPoints(float& topCrossingPoint, float& bottomCrossingPoint, float& leftCrossingPoint, float& rightCrossingPoint, float inclination, float b) {
	//This calculates the crossing points if the inclination is 0
	if (inclination == 0) {
		if (b >= -2 && b <= 2) {
			topCrossingPoint = 2;
			bottomCrossingPoint = -2;
			leftCrossingPoint = -5;
			rightCrossingPoint = 5;
		}
	}
	else {
			//Checks the top boundary of the rectangle where y = 2
			topCrossingPoint = (2 - b) / inclination;

			//Checks the bottom boundary of the rectangle where y = -2
			bottomCrossingPoint = (-2 - b) / inclination;

			//Checks the right boundary of the rectangle where x = 5
			rightCrossingPoint = (inclination * 5) + b;

			//Checks the left boundary of the rectangle where x = -5
			leftCrossingPoint = (inclination * (-5)) + b;
		}
	
}

void Checking_CrossingPoints(float& first_Coordinate_X, float& second_Coordinate_Y, float topCrossingPoint, float bottomCrossingPoint, float leftCrossingPoint, float rightCrossingPoint) {
	//Gets the the right crossing point for the calculation of the distance
	if (first_Coordinate_X > 5 && second_Coordinate_Y <= 2 && second_Coordinate_Y >= -2) {
		second_Coordinate_Y = rightCrossingPoint;
	}
	//Gets the the left crossing point for the calculation of the distance
	if (first_Coordinate_X < -5 && second_Coordinate_Y <= 2 && second_Coordinate_Y >= -2){
		second_Coordinate_Y = leftCrossingPoint;
	}
	//Gets the the top crossing point for the calculation of the distance
	if (second_Coordinate_Y > 2 && first_Coordinate_X <= 5 && first_Coordinate_X >= -5) {
		first_Coordinate_X = topCrossingPoint;
	}
	//Gets the the bottom crossing point for the calculation of the distance
	if (second_Coordinate_Y < -2 && first_Coordinate_X <= 5 && first_Coordinate_X >= -5) {
		first_Coordinate_X = bottomCrossingPoint;
	}
	
}


//Calculates X and stores the coordinates in temporary values so they can be used in the next cycle
float Calculating_X(float& first_Coordinate_X, float& second_Coordinate_Y, float& temporary_Coordinate_X, float& temporary_Coordinate_Y, float& X) {
	X = pow((temporary_Coordinate_X - temporary_Coordinate_Y),2) + pow((first_Coordinate_X - second_Coordinate_Y), 2);
	temporary_Coordinate_X = first_Coordinate_X;		//Stores the first coordinates so they can be used again in the next calculation
	temporary_Coordinate_Y = second_Coordinate_Y;		//Stores the first coordinates so they can be used again in the next calculation
	return sqrt(X);
}

//Calculates the distance from one point to another point
float Distance(float& distance, float X) {
	distance = (((Pi * X) / 2) + X) / 2;
	return distance;
}