#pragma once
/*
* The platform object controlled by the player to hit the ball to avoid it from falling down
* It can only be moved left and right of the screen with the arrow keyboard
* This class stores it data and manages it 
*/
class Platform
{
private:
	Sprite* sprite;
	Point start;
	Point current;
	Point center;
	Point finish;
public:
	int width = 100, height = 25;

	/*
	* get the sprite object of the platform
	* @returns the sprite
	*/
	Sprite* GetSprite()
	{
		return sprite;
	}

	/*
	* get the current point of the platform
	* @returns the current cordinate points of the platform
	*/
	Point& GetCurrent()
	{
		return current;
	}
	/*
	* get the current center of the platform
	* @returns the current center cordinate points of the platform
	*/
	Point& GetCurrentCenter()
	{
		Point addPoint = Point(this->width / 2, 0);
		center = current + addPoint;
		return center;
	}

	/*
	* Create a platform sprite
	* @param filename the name of the png file
	* @returns the created platform sprite
	*/
	Sprite* CreatePlatform(string filename)
	{
		sprite = createSprite((g_dir + filename).c_str());
		setSpriteSize(this->sprite, this->width, this->height);
		start = current = Point( (g_width + this->width)  / 2, (g_height - this->height) );
		
		return sprite;
	}
	
	/*
	* Move the platform to and fro the screen width
	* @param the point in the screen to move the platform to
	*/
	void MovePlatform(Point step)
	{ 
		/*
		* Making sure the platform does not go out of bound
		* If the platform is not at the end or 0 position, move to any direction
		*/
		if ( (current.GetX() < (g_width - this->width))  && (current.GetX() > 0) ) {
			current = current + step;
		}
		//If the platform is at the right most side, it can only go left and not right
		else if ((current.GetX() > (g_width - this->width)) && step.GetX() < 0) {
			current = current + step;
		}
		//If the platform is at the left most side, it can only go right and not left
		else if ((current.GetX() < 0) && step.GetX() > 0) {
			current = current + step;
		}
	}

	/*
	* Draw the sprite at a Point on the screen
	*/
	void DrawPlatform()
	{
		//drawSprite(sprite, current.GetX(), (g_height - this->height));
		drawSprite(sprite, current.GetX(), current.GetY() );
	}

	virtual ~Platform() { 
		destroySprite(sprite); 
	}

};