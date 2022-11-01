#pragma once
/*
* This class stores the cordinate of any point around the background of the game window
*/
class Point
{
private:
	float x;
	float y;
public:
	Point() { x = 0; y = 0; }
	Point(float x, float y) :x(x), y(y) {}

	/*
	* Get the value of the X cordinate
	* @returns the X cordinate
	*/
	float& GetX()
	{
		return this->x;
	}
	/*
	* Get the value of the Y cordinate
	* @returns the Y cordinate
	*/
	float& GetY()
	{
		return this->y;
	}

	/*
	* Operator that checks for the equality between two points
	* @param other a reference to a point that you want to compare the equality 
	* @returns true if the both X and Y cordinates are equal else false 
	*/
	bool operator==(const Point& other)
	{
		return this->x == other.x && this->y == other.y;
	}

	/*
	* Operator that checks for the inequality between two points
	* @param other a reference to a point that you want to compare the equality
	* @returns not if the both X and Y cordinates are not equal else false
	*/
	bool operator != (const Point& other)
	{
		return !(*this == other);
	}


	friend std::ostream& operator << (std::ostream& out, const Point& other)
	{
		out << " X " << other.x << " y " << other.y << std::endl;
		return out;
	}


	/*
	* Add Operator that adds two points
	* @param other a reference to a point that you want to add to the current point
	* @returns point value of the addition of the two points
	*/
	Point operator+(Point other) const
	{
		return Point(this->x + other.x, this->y + other.y);
	}

	virtual ~Point() {}
};
