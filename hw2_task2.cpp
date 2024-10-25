#include <iostream>
#include <cmath>

using namespace std;

//Defines Pi for use in the calculation of the distance
const float Pi = 3.14;
const float left_boundary = -5.0;
const float right_boundary = 5.0;
const float top_boundary = 2.0;
const float bottom_boundary = -2.0;
float eps = 1e-3;


void UserInput(float& first_Coordinate_X, float& second_Coordinate_Y);
bool IsInsideRectangle(float first_Coordinate_X, float second_Coordinate_Y);
float Inclination(float& previous_Coordinate_Y, float& previous_Coordinate_X, float& first_Coordinate_X, float& second_Coordinate_Y, float& inclination, float eps);
float Calculating_B(float& first_Coordinate_X, float& second_Coordinate_Y, float& inclination, float& b);
void Crossing_Point(float& right_CP, float& left_CP, float& top_CP, float& bottom_CP, float inclination, float b);
void RayMovementAndCoodinatesAdjustment(float previous_Coordinate_X, float previous_Coordinate_Y, float& first_Coordinate_X, float& second_Coordinate_Y, float right_CP,
	float left_CP, float top_CP, float bottom_CP, float& temp_C_X, float& temp_C_Y);
float Calculating_X(float& first_Coordinate_X, float& second_Coordinate_Y, float& previous_Coordinate_X, float& previous_Coordinate_Y, float& X, float temp_C_X, float temp_C_Y);
float Distance(float& distance, float X);

int main()
{
	unsigned int input_Number = 0;
	float first_Coordinate_X = 0.0;
	float second_Coordinate_Y = 0.0;
	float previous_Coordinate_X = 0.0;		// This will store the value of coordinate X for the next cycle
	float previous_Coordinate_Y = 0.0;		// This will store the value of coordinate Y for the next cycle
	float X = 0.0;							// THis will store the value of X that is needed to calculate the distance from A to B
	float distance = 0.0;					// Stores the distance made by the player
	float total_Distance = 0.0;
	float inclination = 0.0;
	float b = 0.0;					//This is needed for calculating where the line crosses the rectangle and its from the formula y=(m*x)+b
	float right_CP = 0.0;					//CP stands for CrossingPoint
	float left_CP = 0.0;					//CP stands for CrossingPoint
	float top_CP = 0.0;						//CP stands for CrossingPoint
	float bottom_CP = 0.0;					//CP stands for CrossingPoint
	float temp_C_X = 0.0;
	float temp_C_Y = 0.0;						//Both of the temporary coordinates are needed to store the value of the original point so it can be used later

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
		if (!IsInsideRectangle(first_Coordinate_X, second_Coordinate_Y) && !IsInsideRectangle(previous_Coordinate_X, previous_Coordinate_Y)) {
			previous_Coordinate_X = first_Coordinate_X;
			previous_Coordinate_Y = second_Coordinate_Y;
			a++;
			continue;
		}
		//This covers if the previous dot is inside of the rectangle and the current dot is outside
		if (IsInsideRectangle(previous_Coordinate_X, previous_Coordinate_Y) && !IsInsideRectangle(first_Coordinate_X, second_Coordinate_Y)) {
			Inclination(previous_Coordinate_Y, previous_Coordinate_X, first_Coordinate_X, second_Coordinate_Y, inclination, eps);
			Calculating_B(first_Coordinate_X, second_Coordinate_Y, inclination, b);
			Crossing_Point(right_CP, left_CP, top_CP, bottom_CP, inclination, b);
			RayMovementAndCoodinatesAdjustment(previous_Coordinate_X, previous_Coordinate_Y, first_Coordinate_X, second_Coordinate_Y, right_CP, left_CP,  top_CP, bottom_CP, temp_C_X, temp_C_Y);
			X = Calculating_X(first_Coordinate_X, second_Coordinate_Y, previous_Coordinate_X, previous_Coordinate_Y, X, temp_C_X, temp_C_Y);
			total_Distance += Distance(distance, X);
			a++;
			continue;
		}
		//Òhis covers if the previous dot is outside of the rectangle and the current dot is inside
		if (!IsInsideRectangle(previous_Coordinate_X, previous_Coordinate_Y) && IsInsideRectangle(first_Coordinate_X, second_Coordinate_Y)) {
			Inclination(previous_Coordinate_Y, previous_Coordinate_X, first_Coordinate_X, second_Coordinate_Y, inclination, eps);
			Calculating_B(first_Coordinate_X, second_Coordinate_Y, inclination, b);
			Crossing_Point(right_CP, left_CP, top_CP, bottom_CP, inclination, b);
			RayMovementAndCoodinatesAdjustment(previous_Coordinate_X, previous_Coordinate_Y, first_Coordinate_X, second_Coordinate_Y, right_CP, left_CP, top_CP, bottom_CP, temp_C_X, temp_C_Y);
			X = Calculating_X(first_Coordinate_X, second_Coordinate_Y, previous_Coordinate_X, previous_Coordinate_Y, X, temp_C_X, temp_C_Y);
			total_Distance += Distance(distance, X);
			a++;
			continue;
		}
		//This covers if both dots are inside of the rectangle
		if (IsInsideRectangle(previous_Coordinate_X, previous_Coordinate_Y) && IsInsideRectangle(first_Coordinate_X, second_Coordinate_Y)) {
			Inclination(previous_Coordinate_Y, previous_Coordinate_X, first_Coordinate_X, second_Coordinate_Y, inclination, eps);
			Calculating_B(first_Coordinate_X, second_Coordinate_Y, inclination, b);
			X = Calculating_X(first_Coordinate_X, second_Coordinate_Y, previous_Coordinate_X, previous_Coordinate_Y, X, temp_C_X, temp_C_Y);
			total_Distance += Distance(distance, X);
			a++;
			continue;
		}

		previous_Coordinate_X = first_Coordinate_X;
		previous_Coordinate_Y = second_Coordinate_Y;
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

float Inclination(float& previous_Coordinate_Y, float& previous_Coordinate_X, float& first_Coordinate_X, float& second_Coordinate_Y, float& inclination, float eps) {
	if (abs(first_Coordinate_X - previous_Coordinate_X) < eps) {
		inclination = 0;
	}
	else {
		inclination = (second_Coordinate_Y - previous_Coordinate_Y) / (first_Coordinate_X - previous_Coordinate_X);
	}
	return inclination;
}

//This formula is needed if the line crosses the rectangle (field)
float Calculating_B(float& first_Coordinate_X, float& second_Coordinate_Y, float& inclination, float& b) {
	b = second_Coordinate_Y - (inclination * first_Coordinate_X);
	return b;
}

//Calculates the different crossing points with the sides of the rectangle
void Crossing_Point(float& right_CP, float& left_CP, float& top_CP, float& bottom_CP, float inclination, float b) {
	//This covers if the inclination is 0
	if (abs(inclination) < eps) {
		right_CP = right_boundary;
		left_CP = left_boundary;
		top_CP = top_boundary;
		bottom_CP = bottom_boundary;
	}
	else {
		//Calculates crossing point with right boundary when x = 5
		right_CP = (inclination * right_boundary) + b;

		//Calculates crossing point with left boundary  when x = -5
		left_CP = (inclination * left_boundary) + b;

		//Calculates crossing point with top boundary when y = 2
		top_CP = (top_boundary - b) / inclination;

		//Calculates crossing point with bottom boundary when y = -2
		bottom_CP = (bottom_boundary - b) / inclination;
	}
}

//This will calculate the direction of the ray and adjust the coodinates if needed
void RayMovementAndCoodinatesAdjustment(float previous_Coordinate_X, float previous_Coordinate_Y, float& first_Coordinate_X, float& second_Coordinate_Y, float right_CP,
 float left_CP, float top_CP, float bottom_CP, float& temp_C_X, float& temp_C_Y) {
	//This calculates the ray inclination
	float deltaX = first_Coordinate_X - previous_Coordinate_X;
	float deltaY = second_Coordinate_Y - previous_Coordinate_Y;

	temp_C_X = first_Coordinate_X;
	temp_C_Y = second_Coordinate_Y;

	//If the movement of the array is up or down
	if (deltaX == 0) {
		if (deltaY > 0) {  
			first_Coordinate_X = previous_Coordinate_X;
			second_Coordinate_Y = top_boundary;
		}
		else if (deltaY < 0) { 
			first_Coordinate_X = previous_Coordinate_X;
			second_Coordinate_Y = bottom_boundary;
		}
	}
	//If the movement of the array is left or right
	else if (deltaY == 0) {
		if (deltaX > 0) {  
			first_Coordinate_X = right_boundary;
			second_Coordinate_Y = previous_Coordinate_Y;
		}
		else if (deltaX < 0) { 
			first_Coordinate_X = left_boundary;
			second_Coordinate_Y = previous_Coordinate_Y;
		}
	}

	//If the movement of the ray is up and to the right
	if (deltaX > 0 && deltaY > 0) {
		if (right_CP <= top_boundary) {
			first_Coordinate_X = right_boundary;
			second_Coordinate_Y = right_CP;
		}
		else {
			first_Coordinate_X = top_CP;
			second_Coordinate_Y = top_boundary;
		}
	}
	//If the movement of the ray is up and to the left
	else if (deltaX < 0 && deltaY > 0) {
		if (left_CP <= top_boundary) {
			first_Coordinate_X = left_boundary;
			second_Coordinate_Y = left_CP;
		}
		else {
			first_Coordinate_X = top_CP;
			second_Coordinate_Y = top_boundary;
		}
	}
	//If the movement is down and to the right
	else if (deltaX > 0 && deltaY < 0) {
		if (right_CP >= bottom_boundary) {
			first_Coordinate_X = right_boundary;
			second_Coordinate_Y = right_CP;
		}
		else {
			first_Coordinate_X = bottom_CP;
			second_Coordinate_Y = bottom_boundary;
		}
	}
	//If the movement is down and to the left
	else if (deltaX < 0 && deltaY < 0) {
		if (left_CP >= bottom_boundary) {
			first_Coordinate_X = left_boundary;
			second_Coordinate_Y = left_CP;
		}
		else {
			first_Coordinate_X = bottom_CP;
			second_Coordinate_Y = bottom_boundary;
		}
	}


}



//Calculates X and stores the coordinates in another values so they can be used in the next cycle
float Calculating_X(float& first_Coordinate_X, float& second_Coordinate_Y, float& previous_Coordinate_X, float& previous_Coordinate_Y, float& X, float temp_C_X, float temp_C_Y) {
	X = pow((previous_Coordinate_X - first_Coordinate_X),2) + pow((previous_Coordinate_Y - second_Coordinate_Y), 2);
	previous_Coordinate_X = temp_C_X;		//Stores the first coordinates so they can be used again in the next calculation
	previous_Coordinate_Y =	temp_C_Y;		//Stores the first coordinates so they can be used again in the next calculation
	return sqrt(X);
}

//Calculates the distance from one point to another point
float Distance(float& distance, float X) {
	distance = (((Pi * X) / 2) + X) / 2;
	return distance;
}