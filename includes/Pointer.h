#pragma once
/*
* This class just save the loaction of the mouse pointer. It is used in the begining of the game to know where to shoot the first ball
*/
class Pointer
{
private:
	Point current;
public:
	/*
	* get the current point cordinate of the pointer
	* @returns current Point cordinates at the moment of calling
	*/
	Point& GetCurrent()
	{
		return current;
	}
	/*
	* Move the pointer cordinate to a new one
	*/
	void MovePointer(Point current)
	{
		this->current = current;
	}

	virtual ~Pointer() { 
		//destroySprite(sprite); 
	}
};
