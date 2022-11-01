#pragma once
/*
* This class creates and manage block sprite
*/
class Block {
private:
	Point current;
	Point center;
public:
	Sprite* sprite;
	int width = 99;
	int height = 25;
	int hit = 0;
	int index = 0;
	string color;
	string type;
	bool transparent = false;
	bool move = false;
	bool goRight = true;

	/*
	* get the sprite object of the platform
	* @returns the sprite
	*/
	Sprite* GetSprite()
	{
		return sprite;
	}

	Sprite* CreateBlock(Point point,string filename = "block_")
	{
		filename += this->color + "_" + this->type + ".png";
		this->sprite = createSprite((g_dir + filename).c_str());

		setSpriteSize(this->sprite, this->width, this->height);
		int perRow = g_width / this->width;
		int row = 1 + int(index / perRow);
		if (index % perRow == 0) {
			row = index / perRow;
		}		
		current = point;
		return this->sprite;
	}
	/*
	* This method automatically moves a block with move = true from left to right edge until burtsted
	* This feature is currently only in level 4
	*/
	void AutoMoveBlock()
	{
		if (this->move) {
			Point step;
			if ((current.GetX() > (g_width - this->width))) {
				//cout << "Go left";
				goRight = false;
			}
			if ((current.GetX() < 0)) {
				goRight = true;
				//cout << "Go right";
			}

			if (goRight) {
				step = Point(0.2, 0);
			}
			else {
				step = Point(-0.2, 0);
			}
			current = current + step;
		}
		
	}
	/*
	* get the current point of the block
	* @returns the current cordinate points of the block
	*/
	Point& GetCurrent()
	{
		return current;
	}

	/*
	* get the current center of the block
	* @returns the current center cordinate points of the block
	*/
	Point& GetCurrentCenter()
	{
		Point addPoint = Point(this->width / 2, 0);
		center = current + addPoint;
		return center;
	}
	
	/*
	* this method draws the block sprite at a point in the screen
	*/
	void DrawBlock()
	{
		//this checks if it is a blue block and transparency is true to change the block color
		if (this->color == "blue" && transparent == true) {
			this->color = "skyblue";
			this->CreateBlock(this->GetCurrent());
		}
		//this change back the color 
		if (this->color == "skyblue" && transparent == false) {
			this->color = "blue";
			this->CreateBlock(this->GetCurrent());
		}
		drawSprite(sprite, current.GetX(), current.GetY());
	}

	/*
	* destroy a bursted block sprite
	*/
	void killed() {
		destroySprite(sprite);
	}

	virtual ~Block() {
		destroySprite(sprite);
	}
};






/*
* This class manages the group or array of blocks sprite
*/
class Blocks {
private:
public:
	Utils util;
	int timer = 10 * 500;//10 seconds
	int timer3s = 3 * 500;//3 seconds
	bool transparent = false;

	/*
	* countdown timer that counts down and reset the time stored in timer
	*/
	void countDown() {
		if (timer == 0) {
			this->timer = 10 * 500;//10 seconds
			this->transparent = !this->transparent;
		}
		this->timer -= 1;
	}

	/*
	* Three seconds countdown for transparent block
	*/
	void countDown3s() {
		if (timer3s == 0) {
			this->timer3s = 3 * 500;//3 seconds
			this->timer = 10 * 500;//10 seconds
			this->transparent = !this->transparent;
		}
		this->timer3s -= 1;
	}

	/*
	* Re-organizing the blocks to suit level 1.
	* Level 1 should have atleast 2  and at most 3 red blocks to produce hearts
	*/
	void organizeLv1(vector<Block*>& blocks) {
		int redBlocks = 0;
		vector<int> redPos;
		while (redBlocks < 2) {
			for (auto block : blocks) {
				if (block->color == "red") {
					redBlocks += 1;
					redPos.push_back(block->index - 1);
				}
			}
			//if there is less than two red blocks repale a random 0-11 block to red
			if (redBlocks < 2) {
				int rand = util.randomNum(0, 11);
				blocks[rand]->color = "red";
				blocks[rand]->CreateBlock(blocks[rand]->GetCurrent());
			}
			//if there is more than three red blocks change the last one to orange
			if (redPos.size() > 3) {
				int index = redPos[redPos.size() - 1];
				blocks[index]->color = "orange";
				blocks[index]->CreateBlock(blocks[index]->GetCurrent());
				redPos.pop_back();
			}
		}
		
	}

	/*
	* Re organize the blocks to make sure it suits the level two standard
	* Level 2 should have atleast 2  and at most 3 red blocks to produce hearts
	*/
	void organizeLv2(vector<Block*>& blocks) {
		int redBlocks = 0;
		vector<int> redPos;
		while (redBlocks < 2) {
			for (auto block : blocks) {
				if (block->color == "red") {
					redBlocks += 1;
					redPos.push_back(block->index - 1);
				}
			}
			//if there is less than two red blocks repale a random 0-11 block to red
			if (redBlocks < 2) {
				int rand = util.randomNum(0, g_total_blocks);
				blocks[rand]->color = "red";
				blocks[rand]->CreateBlock(blocks[rand]->GetCurrent());
			}
			//if there is more than three red blocks change the last one to orange
			if (redPos.size() > 3) {
				int index = redPos[redPos.size() - 1];
				blocks[index]->color = "orange";
				blocks[index]->CreateBlock(blocks[index]->GetCurrent());
				redPos.pop_back();
			}
		}
	}

	/*
	* Re organize the blocks to make sure it suits the level three standard
	* Level 3 should have atleast 2  and at most 3 red blocks to produce hearts
	* The hearts should not be placed in specific locations where the black unbreakable blocks will
	*/
	void organizeLv3(vector<Block*>& blocks) {
		int redBlocks = 0;
		vector<int> redPos;
		while (redBlocks < 2) {
			for (auto block : blocks) {
				if (block->color == "red") {
					redBlocks += 1;
					redPos.push_back(block->index - 1);
				}
			}
			//if there is less than two red blocks replace a random 0-11 block to red
			if (redBlocks < 2) {
				int rand = util.randomNum(0, 30);
				if (rand != 12 || rand != 13 || rand != 16 || rand != 17) {
					blocks[rand]->color = "red";
					blocks[rand]->CreateBlock(blocks[rand]->GetCurrent());
				}
			}
			//if there is more than three red blocks change the last one to orange
			if (redPos.size() > 3) {
				int index = redPos[redPos.size() - 1];
				blocks[index]->color = "orange";
				blocks[index]->CreateBlock(blocks[index]->GetCurrent());
				redPos.pop_back();
			}
		}

	}

	/*
	* Re organize the blocks to make sure it suits the level four standard
	* Level 4 should have atleast 2  and at most 3 red blocks to produce hearts
	* The hearts should not be placed in specific locations where the black unbreakable blocks will
	*/
	void organizeLv4(vector<Block*>& blocks) {
		int redBlocks = 0;
		vector<int> redPos;
		while (redBlocks < 2) {
			for (auto block : blocks) {
				if (block->color == "red") {
					redBlocks += 1;
					redPos.push_back(block->index - 1);
				}
			}
			//if there is less than two red blocks repale a random 0-11 block to red
			if (redBlocks < 2) {
				int rand = util.randomNum(0, 30);
				if (rand != 19 || rand != 14 || rand != 15 || rand != 22) {
					blocks[rand]->color = "red";
					blocks[rand]->CreateBlock(blocks[rand]->GetCurrent());
				}
			}
			//if there is more than three red blocks change the last one to orange
			if (redPos.size() > 3) {
				int index = redPos[redPos.size() - 1];
				blocks[index]->color = "orange";
				blocks[index]->CreateBlock(blocks[index]->GetCurrent());
				redPos.pop_back();
			}
		}

	}
	
	/*
	* This checks when a block is hitted with the balls and calls functions that will happen when it is hit
	* @param blocks the reference of vector of the blocks that are in the screen to be managed
	* @param ball the reference of the ball object 
	* @param total_blocks the reference of total number blocks in the screen, use to be reduced when bursted
	* @param h_ability the reference to the heart ability object to be moved if red block is bursted
	* @param platform the reference to the platform object to be passed through the h_ability moveAbility function
	* @param hearts the reference to the total number of hearts available
	*/
	void HitBlock(vector<Block*>& blocks,Ball& ball, int &total_blocks, Ability& h_ability, Platform& platform,int& hearts) {
		int newIndex = 1;
		Point b_point;
		b_point = ball.GetCurrent();
		for (auto block : blocks) {
			//If the 20 secs transparent countdown has elasped and block is blue set the block transparent property to true 
			if (this->transparent && block->color == "blue") {
				block->transparent = true;
			}
			//If the 20 secs transparent countdown is elasoed and block is blue set the block transparent property to true 
			if (!this->transparent && block->color == "skyblue") {
				block->transparent = false;
			}
			//if only one block remains, let the block start moving && g_curlevel == 4
			if (total_blocks == 1 ) {
				if (block->color != "gray") {
					block->move = true;
				}

			}


			//check for hitting of the block in x axis
			if (block->GetCurrent().GetX() <= b_point.GetX() && (block->GetCurrent().GetX() + block->width) >= b_point.GetX()) {
				//check for hitting of the blocks in y axis
				if (block->GetCurrent().GetY() <= b_point.GetY() && (block->GetCurrent().GetY() + block->height) >= b_point.GetY()) {
					//allow the passage of the ball if it is skyblue block if not run this block
					if (block->color != "skyblue") {
						//Control ball movement when it hit the block
						Point next; //next movement of the ball
						//if it is coming from the right side and hit the ball, it should go to the bottom left
						if (ball.start.GetX() < ball.GetCurrent().GetX()) {
							next = Point(g_width, ball.start.GetY());
						}
						//if it is coming from the left side and hit the ball, it should go to the bottom right
						else {
							next = Point(0, ball.start.GetY());
						}
						ball.HitBall(next);
						
						//if the ball is gray make sound and do not count as hit
						if (block->color != "gray") {
							if (block->hit == 0) {
								PlaySound(TEXT(gs_hit), NULL, SND_FILENAME | SND_ASYNC);
								//On first hit, change the sprite to cracked image and increment the hit on the particular block
								block->type = "half";
								block->CreateBlock(block->GetCurrent());
								block->hit += 1;
							}
							else {
								//On the second hit remove the block from the array and destroy the sprite then reduce the number of available blocks
								PlaySound(TEXT(gs_burst), NULL, SND_FILENAME | SND_ASYNC);
								blocks.erase(blocks.begin() + block->index - 1);
								block->killed();
								int i = (block->index - 1);
								total_blocks -= 1;
								//if the bursting hit is the red block set the heart abilit to start moving from the center of the red block location
								if (block->color == "red") {
									h_ability.current = block->GetCurrentCenter();
									h_ability.move = true;
								}
							}
						}
						else {
							PlaySound(TEXT(gs_hit), NULL, SND_FILENAME | SND_ASYNC);
						}					

					}
					else {
						//set a new 3 seconds timer with a countdown function.
						//when the timer is zero, reset the original timer to 20 seconds and change the transparent 
						this->countDown3s();
					}
				}
			}
			block->index = newIndex;
			newIndex += 1;

		}

		if (h_ability.move) {
			h_ability.MoveAbility(platform,hearts);
		}
	}

};