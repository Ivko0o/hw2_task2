#include <iostream>
#include <cmath>

using namespace std;

//Defines Pi for use in the calculation of the distance
const float Pi = 3.14;
const float left_boundary = -5.0;
const float right_boundary = 5.0;
const float top_boundary = 2.0;
const float bottom_boundary = -2.0;


void UserInput(float& first_Coordinate_X, float& second_Coordinate_Y);
bool IsInsideRectangle(float first_Coordinate_X, float second_Coordinate_Y);
float Inclination(float& temporary_Coordinate_Y, float& temporary_Coordinate_X, float& first_Coordinate_X, float& second_Coordinate_Y, float& inclination, float eps);
float Calculating_B(float& first_Coordinate_X, float& second_Coordinate_Y, float& inclination, float& b);
void Calculating_CrossingPoints(float& top_Crossing_Point, float& bottom_Crossing_Point, float& left_Crossing_Point, float& right_Crossing_Point, float inclination, float b);
void Checking_CrossingPoints(float& first_Coordinate_X, float& second_Coordinate_Y, float top_Crossing_Point, float bottom_Crossing_Point, float left_Crossing_Point, float right_Crossing_Point);
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
	float top_Crossing_Point = 0.0;
	float bottom_Crossing_Point = 0.0;
	float left_Crossing_Point = 0.0;
	float right_Crossing_Point = 0.0;
	float eps = 1e-3;


	//Validates if the user has entered a correct number
	while (true) {
		cout << "Enter a positive whole number between 1 and 2,000,000,000: ";
		cin >> input_Number;
		if (input_Number >= 1 && input_Number <= 2000000000) {
			break;
		}
	}

	int a = 0;
	while (a < input_Number) {
		UserInput(first_Coordinate_X, second_Coordinate_Y);

		//This covers if both of the dots are outside of the rectangle(field)
		if (!IsInsideRectangle(first_Coordinate_X, second_Coordinate_Y) && !IsInsideRectangle(temporary_Coordinate_X, temporary_Coordinate_Y)) {
			temporary_Coordinate_X = first_Coordinate_X;
			temporary_Coordinate_Y = second_Coordinate_Y;
			a++;
			continue;
		}
		//This covers if the previous dot is inside of the rectangle and the current dot is outside
		if (IsInsideRectangle(temporary_Coordinate_X, temporary_Coordinate_Y) && !IsInsideRectangle(first_Coordinate_X, second_Coordinate_Y)) {
			Inclination(temporary_Coordinate_Y, temporary_Coordinate_X, first_Coordinate_X, second_Coordinate_Y, inclination, eps);
			Calculating_B(first_Coordinate_X, second_Coordinate_Y, inclination, b);
			Calculating_CrossingPoints(top_Crossing_Point, bottom_Crossing_Point, left_Crossing_Point, right_Crossing_Point, inclination, b);
			Checking_CrossingPoints(first_Coordinate_X, second_Coordinate_Y, top_Crossing_Point, bottom_Crossing_Point, left_Crossing_Point, right_Crossing_Point);
			X = Calculating_X(first_Coordinate_X, second_Coordinate_Y, temporary_Coordinate_X, temporary_Coordinate_Y, X);
			total_Distance += Distance(distance, X);
			a++;
			continue;
		}

		temporary_Coordinate_X = first_Coordinate_X;
		temporary_Coordinate_Y = second_Coordinate_Y;
		a++;
	}

	cout << "\n" << total_Distance;

}

//Takes the coordinates from the user (chip)
void UserInput(float& first_Coordinate_X, float& second_Coordinate_Y) {
	cin >> first_Coordinate_X;
	cin >> second_Coordinate_Y;
}

//Checks if the dot is inside or outside of the rectangle
bool IsInsideRectangle(float first_Coordinate_X, float second_Coordinate_Y) {
	return (first_Coordinate_X >= left_boundary && first_Coordinate_X <= right_boundary && second_Coordinate_Y >= bottom_boundary && second_Coordinate_Y <= top_boundary);
}

//Calculates the inclination of the line if the dot is outside of the rectangle(field)

float Inclination(float& temporary_Coordinate_Y, float& temporary_Coordinate_X, float& first_Coordinate_X, float& second_Coordinate_Y, float& inclination, float eps) {

	if ((first_Coordinate_X - temporary_Coordinate_X) < eps) {
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

void Calculating_CrossingPoints(float& top_Crossing_Point, float& bottom_Crossing_Point, float& left_Crossing_Point, float& right_Crossing_Point, float inclination, float b) {
	//This calculates the crossing points if the inclination is 0
	if (inclination == 0) {
		if (b >= -2 && b <= 2) {
			top_Crossing_Point = 2;
			bottom_Crossing_Point = -2;
			left_Crossing_Point = -5;
			right_Crossing_Point = 5;
		}
	}
	else {
			//Checks the top boundary of the rectangle where y = 2
		top_Crossing_Point = (top_boundary - b) / inclination;

			//Checks the bottom boundary of the rectangle where y = -2
		bottom_Crossing_Point = (bottom_boundary - b) / inclination;

			//Checks the right boundary of the rectangle where x = 5
		right_Crossing_Point = (inclination * right_boundary) + b;

			//Checks the left boundary of the rectangle where x = -5
			left_Crossing_Point = (inclination * (left_boundary)) + b;
		}
	
}

void Checking_CrossingPoints(float& first_Coordinate_X, float& second_Coordinate_Y, float top_Crossing_Point, float bottom_Crossing_Point, float left_Crossing_Point, float right_Crossing_Point) {
	//Gets the the right crossing point for the calculation of the distance
	if (first_Coordinate_X > right_boundary && second_Coordinate_Y <= top_boundary && second_Coordinate_Y >= bottom_boundary) {
		second_Coordinate_Y = right_Crossing_Point;
	}
	//Gets the the left crossing point for the calculation of the distance
	if (first_Coordinate_X < left_boundary && second_Coordinate_Y <= top_boundary && second_Coordinate_Y >= bottom_boundary){
		second_Coordinate_Y = left_Crossing_Point;
	}
	//Gets the the top crossing point for the calculation of the distance
	if (second_Coordinate_Y > top_boundary && first_Coordinate_X <= right_boundary && first_Coordinate_X >= left_boundary) {
		first_Coordinate_X = top_Crossing_Point;
	}
	//Gets the the bottom crossing point for the calculation of the distance
	if (second_Coordinate_Y < bottom_boundary && first_Coordinate_X <= right_boundary && first_Coordinate_X >= left_boundary) {
		first_Coordinate_X = bottom_Crossing_Point;
	}
}


//Calculates X and stores the coordinates in temporary values so they can be used in the next cycle
float Calculating_X(float& first_Coordinate_X, float& second_Coordinate_Y, float& temporary_Coordinate_X, float& temporary_Coordinate_Y, float& X) {
	X = pow((temporary_Coordinate_X - first_Coordinate_X),2) + pow((temporary_Coordinate_Y - second_Coordinate_Y), 2);
	temporary_Coordinate_X = first_Coordinate_X;		//Stores the first coordinates so they can be used again in the next calculation
	temporary_Coordinate_Y = second_Coordinate_Y;		//Stores the first coordinates so they can be used again in the next calculation
	return sqrt(X);
}

//Calculates the distance from one point to another point
float Distance(float& distance, float X) {
	distance = (((Pi * X) / 2) + X) / 2;
	return distance;
}