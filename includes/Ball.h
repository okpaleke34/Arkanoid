#pragma once
/*
* This class holds the ball object and manages it
* The ball object goes around the screen and hit on edges and burst the blocks.
*  On escape from the bottom of the screen without been caught with the platform willl be counted as lost
*/
class Ball
{
private:
	Sprite* sprite;
	Point current;
	Point finish;
	Point step;
public:
	float speed = g_ball_speed;
	Point start;
	bool gameOver = false;
	bool onPlatform = false;
	int firstMoved = 0;
	/*
	* get the sprite object of the Ball
	* @returns the sprite
	*/
	Sprite* GetSprite()
	{
		return sprite;
	}

	/*
	* Create a ball sprite
	* @returns the created ball sprite
	*/
	Sprite* CreateBall(string filename)
	{
		this->sprite = createSprite((g_dir + filename).c_str());
		return this->sprite;
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
	* Draw the sprite at a Point on the screen
	*/
	void DrawBall(Point& playerPos)
	{
		//if the ball have not moved before place it on the center of the platform
		if (firstMoved == 0) {
			Point addPoint = Point(0, -15);
			Point initPos = playerPos + addPoint;
			this->current = initPos;
		}
		
		drawSprite(sprite, current.GetX(), current.GetY());
	}

	/*
	* This implements what happens when the ball hits a surface
	* @param next it accepts next position of the ball and it will move towards it 
	*/
	void HitBall(Point& next)
	{
		if (firstMoved == 0) {
			firstMoved = 1;
		}
		this->start = this->current;
		this->finish = next;

		float finish_x = finish.GetX() - 10;
		float finish_y = finish.GetY() - 10;

		float start_x = start.GetX();
		float start_y = start.GetY();
		float mx = speed;
		float my = speed;
		//it turns the speed of the ball to point and move at such point every tick ro reach to the next position
		if ((finish.GetX() - start.GetX()) < 0) {
			mx *= -1;
		}
		if ((finish.GetY() - start.GetY()) < 0) {
			my *= -1;
		}
		step = Point(mx,my);
		this->current = current + step;	
	}

	/*
	* This changes the spead of the ball on a fly by changing the stepss point it will take to the next point
	* @param speed of the ball to change it to
	*/
	void SetSpeed(float speed) {
		float mx = speed;
		float my = speed;

		if ((finish.GetX() - start.GetX()) < 0) {
			mx *= -1;
		}
		if ((finish.GetY() - start.GetY()) < 0) {
			my *= -1;
		}
		step = Point(mx, my);
		this->speed = speed;
		this->step = step;
	}

	/*
	* Calls and implements functions that happens when a ball is on a motion
	* @param platform accepts platform object to knwo when it hits the platform with the cordinate 
	*/
	void MoveBall(Platform& platform)
	{
		current = current + step;
	
		float cur_x_pos = current.GetX();
		float cur_y_pos = current.GetY();
		float start_x = start.GetX();
		float start_y = start.GetY();
		float finish_x = finish.GetX();
		float finish_y = finish.GetY();
		Point next;

		this->onPlatform = false;
		if (cur_x_pos < 0 || cur_y_pos < 0 || cur_x_pos > g_width || (cur_y_pos + 25) > g_height ) {
			if ((cur_y_pos + 25) > g_height) {
				Point platformPoint;
				platformPoint = platform.GetCurrent();
				//check if the ball hits the platform
				if (platformPoint.GetX() < cur_x_pos && (platformPoint.GetX() + platform.width) > cur_x_pos && platformPoint.GetY() <= cur_y_pos && (platformPoint.GetY() + platform.height) >= cur_y_pos) {
					PlaySound(TEXT(gs_hit), NULL, SND_FILENAME | SND_ASYNC);
					//if it is coming from the right side and hit the top, it should go to the bottom left
					if (start_x > cur_x_pos) {
						next = Point(0, start_y/2);
					}
					//if it is coming from the left side and hit the top, it should go to the bottom right
					else {
						next = Point(g_width, start_y / 2);
					}
					start = current;
					this->HitBall(next);
					this->onPlatform = true;
				}
				//if the ball is out of the game background let there be gameover
				if (cur_y_pos > g_height) {
					this->gameOver = true;
				}
				
			}
			else{
				//when the ball hits the edges 
				PlaySound(TEXT(gs_hit), NULL, SND_FILENAME | SND_ASYNC);
				if (cur_x_pos < 0) {
					//if it is coming from bottom and hit the left side, it should go to the top
					if (start_y > cur_y_pos) {
						next = Point(start_x, 0);
					}
					//if it is coming from the top and hit the bottom it should go to the down
					else {
						next = Point(g_width / 2, cur_y_pos * 2);
					}
					start = current;
				}
				else if (cur_y_pos < 0) {
					//if it is coming from the right side and hit the top, it should go to the bottom left
					if (start_x < cur_x_pos) {
						next = Point(g_width, start_y);
					}
					//if it is coming from the left side and hit the top, it should go to the bottom right
					else {
						next = Point(0, start_y);
					}

					start = current;

				}
				else if (cur_x_pos > g_width) {
					//if it is coming from the bottom and hit the right it should go to top
					if (start_y < cur_y_pos) {
						next = Point(g_width / 2, cur_y_pos * 2);
					}
					//if it is coming from the top and hit the right it should go to bottom
					else {
						next = Point(start_x, 0);
					}
					start = current;
				}

				this->HitBall(next);

			}

		}
		
	}


	virtual ~Ball() { 
		destroySprite(sprite);
	}


};

