#include <iostream>
#include <cmath>

using namespace std;

//Defines Pi for use in the calculation of the distance
const float Pi = 3.14;


void UserInput(float& first_Coordinate_X, float& second_Coordinate_Y);
float Inclination(float& temporary_Coordinate_Y, float& temporary_Coordinate_X, float& first_Coordinate_X, float& second_Coordinate_Y, float& inclination);
float Calculating_X(float& first_Coordinate_X, float& second_Coordinate_Y, float& temporary_Coordinate_X, float& temporary_Coordinate_Y, float& X);
float Distance(float& distance, float X);

int main()
{
	unsigned int input_Number = 0;
	float first_Coordinate_X = 0.0;
	float second_Coordinate_Y = 0.0;
	float temporary_Coordinate_X = 0.0;		// This will store the value of coordinate X for the next cycle
	float temporary_Coordinate_Y = 0.0;		// This will store the value of coordinate Y for the next cycle
	float prim_X = 0.0;						// This will be used when the dot is outside of the boundary
	float prim_Y = 0.0;						// This will be used when the dot is outside of the boundary
	float X = 0.0;							// THis will store the value of X that is needed to calculate the distance from A to B
	float distance= 0.0;					// Stores the distance made by the player
	float total_Distance = 0.0;
	float inclination = 0.0;

	cout << "Enter a positive number for number of iterations: ";
	cin >> input_Number;

	int a = 0;
	while (a < input_Number) {
		UserInput(first_Coordinate_X, second_Coordinate_Y);
		Inclination(temporary_Coordinate_Y, temporary_Coordinate_X, first_Coordinate_X, second_Coordinate_Y, inclination);
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
	inclination = (second_Coordinate_Y - temporary_Coordinate_Y) / (first_Coordinate_X - temporary_Coordinate_X);
	return inclination;
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