#pragma once
/*
* This are game bonus that falls at a random time from top of the screen
* The red heart ability increments the life of the player to respawn after death
*/
class Ability
{
private:
	Sprite* sprite;
	Point start;
	Point center;
	Point finish;
public:
	Point current;
	Utils util;
	int width = 100, height = 25;
	string type = "positive";
	bool move = false;
	bool isNegative = false;
	bool collected = false;


	/*
	* get the sprite object of the Ability
	* @returns the sprite
	*/
	Sprite* GetSprite()
	{
		return sprite;
	}
	/*
	* Create a ability sprite
	* @param myType the type of the ability to create
	* @returns the created ability sprite
	*/
	Sprite* CreateAbility(string myType)
	{
		this->type = myType;
		//if it is a positive ability set the isNegative attribute to false
		if (myType == "positive") {
			this->isNegative = false;
		}
		else {
			this->isNegative = true;
		}
		int pos_x = util.randomNum(1, (g_width - this->width));
		string filename = "ability_" + this->type + ".png";
		this->sprite = createSprite((g_dir + filename).c_str());
		setSpriteSize(this->sprite, this->width, this->height);
		Point point = Point(pos_x, -this->width);
		current =  point;
		return this->sprite;
	}

	/*
	* get the current point of the Ability
	* @returns the current cordinate points of the Ability
	*/
	Point& GetCurrent()
	{
		return current;
	}

	/*
	* get the current center of the Ability
	* @returns the current center cordinate points of the Ability
	*/
	Point& GetCurrentCenter()
	{
		Point addPoint = Point(this->width / 2, 0);
		center = current + addPoint;
		return center;
	}

	/*
	* This manage the movement of an ability
	* @param platform to know when the ability hits the platform
	* @param hearts the reference to the total avaialble hearts for increment incase the red ability hits the platform
	*/
	void MoveAbility(Platform& platform, int& hearts)
	{
		Printer p;
		if (this->move) {
			Point step = Point(0, g_ability_speed);
			current = current + step;
		}
		float cur_x_pos = current.GetX();
		float cur_y_pos = current.GetY();
		Point platformPoint;
		platformPoint = platform.GetCurrent();
		//Check for collision with platform or out of the box
		if ( ((platformPoint.GetX() < cur_x_pos && (platformPoint.GetX() + platform.width) > cur_x_pos) && (cur_y_pos <= platformPoint.GetY() && (cur_y_pos + this->height) >= platformPoint.GetY()) ) || (cur_y_pos > g_height)) {
			
			if (cur_y_pos > g_height) {
				//Ability escaped the platform

			}
			else {
				//collected ability with the platform
				PlaySound(TEXT(gs_bonus), NULL, SND_FILENAME | SND_ASYNC);
				this->collected = true;
				if (this->type == "heart") {
					hearts += 1;
					p.heart("Total: " + to_string(hearts));
					cout << "\nCOLLECTED A HEART!!"<<endl;
				}
			}

			int pos_x = util.randomNum(1, (g_width - this->width));
			this->move = false;
			current = Point(pos_x, -this->width);
		}
	}


	/*
	* Draw the sprite at a Point on the screen
	*/
	void DrawAbility()
	{
		drawSprite(sprite, current.GetX(), current.GetY());
	}

	virtual ~Ability() {
		destroySprite(sprite);
	}

};


/*
* This class manages the vector of abilities
*/
class AbilityManager {
private:
public:
	Utils util;
	int percent = 0;
	int collections = 0;
	int timer = 20 * 500;//20 seconds

	/*
	* countdown timer that counts down and reset the time stored in timer
	* It use use to reset Ability expiration time
	*/
	void countDown() {
		if (timer == 0) {
			cout << "Available Ability Expired!! \n";
			collections = 0;
			percent = 0;
			timer = 20 * 500;
		}
		this->timer -= 1;

	}
	/*
	* This method makes sure that the generated abilities have both the negative and positive in the vector
	* @param abilities, this is the reference of the vector of abilities  
	*/
	void balanceAbility(vector<Ability*>& abilities) {
		int positive = 0;
		int negative = 0;
		for (auto ability : abilities) {
			if (ability->type == "positive") {
				positive += 1;
			}
			if (ability->type == "negative") {
				negative += 1;
			}
		}
		if (negative == 0) {
			//if all is positive and all is total number of posible abilities(4)
			if (positive == abilities.size() && abilities.size() == 4) {
				abilities[0]->type = "negative";
				abilities[2]->type = "negative";
			}
			else {
				Ability* ability = new Ability;
				ability->CreateAbility("negative");
				abilities.push_back(ability);
			}
		}
		if (positive == 0) {
			//if all is negative and all is total number of posible abilities(4)
			if (negative == abilities.size() && abilities.size() == 4) {
				abilities[0]->type = "positive";
				abilities[2]->type = "positive";
			}
			else {
				Ability* ability = new Ability;
				ability->CreateAbility("positive");
				abilities.push_back(ability);
			}
		}
	}
	/*
	* This method manages the vector of abilities
	* @param abilities the reference to vector of generated abilities to manage
	* @param platform the platform to know when the ability is collected with the platform
	* @param ball, the reference to ball object to set the ball speed when needed
	*/
	void manage(vector<Ability*>& abilities, Platform& platform, Ball& ball) {

		/*
		* If ability is active start the countdown for 20 seconds
		*/
		if (this->collections > 0) {
			this->countDown();
		}
		for (auto ability : abilities) {
			/*
			* This generates a 5000 random number every Tick/Miliseconds. 
			* If the random number is 34 then the slow ability will fall but if it is 10 the fast ability  will fall
			* it has 1/5000 probailty to work
			*/
			int rand = util.randomNum(1, 10000);
			if (rand == 34) {
				//Slow ability is coming
				if (!ability->isNegative) {
					ability->move = true;
				}				
			}
			if (rand == 10) {
				//Fast ability is coming
				if (ability->isNegative) {
					ability->move = true;
				}
			}
			//the second parameter hearts is not needed because the ability managed here are not heart ability 
			ability->MoveAbility(platform,g_hearts);

			if (ability->collected) {
				timer = 20 * 500;//refresh the timer to 20 seconds 
				this->collections += 1;
				//if the ability is a fast ability and the total number of accumulated abilities plus corrent ability is not up to 200 percent
				if (ability->isNegative)
					if ((percent + 40) < 200)
						percent += 40;
					else
						percent = 200;
				if (!ability->isNegative)
					if ((percent - 40) > -50)
						percent -= 40;
					else
						percent = -50;
				ability->collected = false;

				cout <<"Accumulated abilities: " << percent<< "%" << endl;
			}


			/*
			* Dividing the screen into four section like a 2x2 matrix, and making the ball go faster in the main daigonal
			* it increases at point range (<0-width/2>,<0,height/2>) and (<width/2,width>,<height/2,height>)
			*/		

			if (((ball.GetCurrent().GetX() >= 0 && ball.GetCurrent().GetX() <= (g_width / 2) ) && (ball.GetCurrent().GetY() >= 0 && ball.GetCurrent().GetY() <= (g_height/2) )) || ((ball.GetCurrent().GetX() >= g_width / 2 && ball.GetCurrent().GetX() <= g_width) && (ball.GetCurrent().GetY() >= g_height / 2 && ball.GetCurrent().GetY() <= g_height))) {
				

				if (this->collections > 0) {
					// if ability is active it will check if it is negative or positive and +-40% of the current speed for the diagonal 
					ball.SetSpeed(util.percentageCal(util.percentageCal(g_ball_speed, 50), percent));
				}
				else {
					ball.SetSpeed(util.percentageCal(g_ball_speed, 50));
				}

			}
			else {
				if (this->collections > 0) {
					// if ability is active it will check if it is negative or positive and +-40% of the current speed for the diagonal
					ball.SetSpeed(util.percentageCal(g_ball_speed, percent));
				}
				else {
					ball.SetSpeed(g_ball_speed);
				}
			}
		}
	}

};