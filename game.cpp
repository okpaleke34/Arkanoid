#include <iostream>
#include<list>
#include<map>
#include<thread>
#include<chrono>
#include<mutex>
#include<string>
#include<vector>
#include <sstream>
#include <windows.h>
#include<time.h>

#pragma comment(lib, "winmm.lib")

using namespace std;
static int g_width;
static int g_height;
static int g_curlevel;
static float g_ball_speed;
static int g_hearts;
static int g_total_blocks;


#define g_platform_increase 0.01
#define g_platform_decrease 0.01
#define g_ability_speed 0.4
#define g_total_level 4
#define gs_hit "assets\\effects\\hit.wav"
#define gs_bonus "assets\\effects\\bonus.wav"
#define gs_level_completed "assets\\effects\\level_completed.wav"
#define gs_lost "assets\\effects\\lost.wav"
#define gs_burst "assets\\effects\\burst.wav"
#define g_dir "assets\\sprites\\"


#include "./includes/Framework.h"
#include "./includes/Utils.h"
#include "./includes/Printer.h"


#include"./includes/Point.h"

#include "./includes/Background.h"
#include "./includes/Pointer.h"
#include "./includes/Platform.h"
#include "./includes/Ball.h"
#include "./includes/Ability.h"
#include "./includes/Block.h"



class MyFramework : public Framework {

public:
	BackGround background;
	Platform platform;
	Utils util;
	std::vector<Block*> blocks;
	std::vector<Ability*> abilities;
	int total_blocks = g_total_blocks;
	int hearts = g_hearts;
	Pointer pointer;
	Ball ball;
	Blocks blockPack;
	AbilityManager abilityPack;
	Ability h_ability;
	Printer p;

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = g_width;
		height = g_height;
		fullscreen = false;
	}
	

	virtual bool Init() {
		ball.CreateBall("ball.png");
		platform.CreatePlatform("platform.png");
		background.CreateBackGround("background.png");

		int totalAbility = util.randomNum(1, 4);
		string abilityTypes[2] = { "positive", "negative" };
		for (int i = 0; i < totalAbility; i++)
		{
			int rand = util.randomNum(0, 1);
			Ability* ability = new Ability;
			/*
			* if rand is negative(increasing of speed) make a random that will choose from 50
			*/
			ability->CreateAbility(abilityTypes[rand]);
			abilities.push_back(ability);
		}
		h_ability.height = 25;
		h_ability.width = 25;
		h_ability.CreateAbility("heart");


		//Make sure there are both positive and negative abilities
		AbilityManager AbManger;
		AbManger.balanceAbility(abilities);

		/*
		* Load levels differences
		*/
		if (g_curlevel == 1) {
			p.level1();
			string colors[7] = { "green", "darkgreen", "red", "orange", "yellow","brown","purple" };
			int k = 0;
			for (int i = 0; i < total_blocks; i++)
			{
				int j = i + 1;
				k += 1;
				Block* block = new Block;
				int perRow = g_width / block->width;
				int row = 1 + int(j / perRow);
				if (j % perRow == 0) {
					row = j / perRow;
				}

				Point point;
				point = Point((((k - 1) * block->width) + k), (((row - 1) * block->height) + row));
				block->index = 1 + i;
				block->hit = 1;
				block->type = "half";
				int rand = util.randomNum(1, 7);
				rand -= 1;
				block->color = colors[rand];
				if (i > 11) {
					block->color = "blue";
				}
				block->CreateBlock(point);
				blocks.push_back(block);

				if (j % perRow == 0) {
					k = 0;
				}
			}
			blockPack.organizeLv1(blocks);
		}
		else if (g_curlevel == 2) {
			p.level2();
			string colors[8] = { "green", "darkgreen", "red", "orange", "yellow","blue","brown","purple" };
			string blockTypes[2] = { "half", "full" };
			int k = 0;
			for (int i = 0; i < total_blocks; i++)
			{
				int chooseType = util.randomNum(0, 1);
				int j = i + 1;
				k += 1;
				Block* block = new Block;
				int perRow = g_width / block->width;
				int row = 1 + int(j / perRow);
				if (j % perRow == 0) {
					row = j / perRow;
				}

				Point point;
				point = Point((((k - 1) * block->width) + k), (((row - 1) * block->height) + row));
				block->index = 1 + i;
				if (chooseType == 0) {
					block->hit = 1;
				}
				block->type = blockTypes[chooseType];//"full";
				int rand = util.randomNum(1, 8);
				rand -= 1;
				block->color = colors[rand];
				block->CreateBlock(point);
				blocks.push_back(block);

				if (j % perRow == 0) {
					k = 0;
				}
			}
			blockPack.organizeLv2(blocks);
		}
		else if(g_curlevel == 3) {
			p.level3();
			string colors[8] = { "green", "darkgreen", "red", "orange", "yellow","brown","blue","purple" };
			string blockTypes[2] = { "half", "full" };
			int k = 0;
			for (int i = 0; i < total_blocks; i++)
			{
				int chooseType = util.randomNum(0, 1);
				int j = i + 1;
				k += 1;
				Block* block = new Block;
				int perRow = g_width / block->width;
				int row = 1 + int(j / perRow);
				if (j % perRow == 0) {
					row = j / perRow;
				}

				Point point;
				point = Point((((k - 1) * block->width) + k), (((row - 1) * block->height) + row));
				block->index = 1 + i;
				if (chooseType == 0) {
					block->hit = 1;
				}
				block->type = blockTypes[chooseType];//"full";
				int rand = util.randomNum(1, 8);
				rand -= 1;
				block->color = colors[rand];
				if (i == 12 || i == 13 || i == 16 || i == 17) {
					block->type = "full";
					block->color = "gray"; 
				}
				block->CreateBlock(point);
				blocks.push_back(block);

				if (j % perRow == 0) {
					k = 0;
				}
			}
			blockPack.organizeLv3(blocks);
			total_blocks -= 4;
		}
		else {
			p.level4();
			string colors[8] = { "green", "darkgreen", "red", "orange", "yellow","brown","blue","purple" };
			int k = 0;
			for (int i = 0; i < total_blocks; i++)
			{
				int j = i + 1;
				k += 1;
				Block* block = new Block;
				int perRow = g_width / block->width;
				int row = 1 + int(j / perRow);
				if (j % perRow == 0) {
					row = j / perRow;
				}

				Point point;
				point = Point((((k - 1) * block->width) + k), (((row - 1) * block->height) + row));
				block->index = 1 + i;
				block->type = "full";
				int rand = util.randomNum(1, 8);
				rand -= 1;
				block->color = colors[rand];
				if (i == 19 || i == 14 || i == 15 || i == 22) {
					block->type = "full";
					block->color = "gray"; 
				}
				block->CreateBlock(point);
				blocks.push_back(block);

				if (j % perRow == 0) {
					k = 0;
				}
			}
			blockPack.organizeLv4(blocks);
			total_blocks -= 4;
		}
		

		
		Point point;
		return true;
	}

	virtual void Close() {

	}
	/*
	* This method restart the game by resetting all the needed features wait for 5 seconds then call the Init() function
	*/
	void Restart() {
		std::this_thread::sleep_for(chrono::seconds(5));
		ball.gameOver = false;
		ball.firstMoved = 0;
		blocks.clear();
		abilities.clear();
		//total_blocks = g_total_blocks;
		total_blocks = (g_curlevel  == 1)?24:30;
		//hearts = g_hearts;
		Init();
	}
	/*
	* This implements what will happen on game over
	*/
	void GameOver() {

		if (total_blocks == 0 && ball.onPlatform) {			
			PlaySound(TEXT(gs_level_completed), NULL, SND_FILENAME | SND_ASYNC);
			if (g_curlevel == 4) {				
				p.arcanoidMaster();
				std::this_thread::sleep_for(chrono::seconds(5));
				g_curlevel = 1;
			}
			else {
				g_curlevel += 1;
				p.victory(hearts);
			}
			Restart();
		}
		if (ball.gameOver) {
			if (hearts != 0) {
				hearts -= 1;
				p.ballOut(hearts);
				ball.gameOver = false;
				ball.DrawBall(platform.GetCurrentCenter());
				ball.firstMoved = 0;
			}
			else {
				PlaySound(TEXT(gs_lost), NULL, SND_FILENAME | SND_ASYNC);
				p.lost();
				Restart();
			}
		}
	}

	virtual bool Tick() {
		//draw backgroud at first
		background.DrawBackground();

		//Platform
		platform.DrawPlatform();
		//Draw all blocks
		for (auto block : blocks) {
			block->DrawBlock();
			block->AutoMoveBlock();
		}
		h_ability.DrawAbility();
		/*
		* Draw ball below the declaration of blocks draw
		* This will make is that ball will appear when passing through blocks
		*/
		ball.DrawBall(platform.GetCurrentCenter());
		ball.MoveBall(platform);

		
		
		//Only create ability when the ball has been shoot out
		if (ball.firstMoved != 0) {
			//Pack all the blocks in one Block park so that it can easily be managed
			blockPack.HitBlock(blocks, ball, total_blocks, h_ability, platform, hearts);
			blockPack.countDown();

			for (auto ability : abilities) {
				ability->DrawAbility();
			}
			abilityPack.manage(abilities,platform, ball);
			

			//Checking for game over
			GameOver();
		}

		if (inertia_l)
		{
			onKeyPressed(key_l);
		}
		else
		{
			onKeyReleased(key_l);
		}

		if (inertia_r)
		{
			onKeyPressed(key_r);
		}
		else
		{
			onKeyReleased(key_r);
		}
		return false;

		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		//pointer tracks and saves the mouse movement
		pointer.MovePointer(Point(x, y));
	}



	static float power_l;
	static float power_r;

	static bool inertia_l;
	static bool inertia_r;

	static FRKey key_l;
	static FRKey key_r;
	static FRKey* key;

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

		if (button == FRMouseButton::LEFT && isReleased)
		{
			//if there have not been a movement in the ball, clicking on the left key of the mouse moves it to the point of the mouse cursor
			if (ball.firstMoved == 0) {
				ball.HitBall(pointer.GetCurrent());
			}
		}

	}

	virtual void onKeyPressed(FRKey k) {
		//moving the platform on keyboard press and release

		switch (k)
		{
			case FRKey::LEFT:
			{
				key_l = k;
				inertia_l = true;
				platform.MovePlatform(Point(-power_l, 0));
				power_l += g_platform_increase;

			}
			break;
			case FRKey::RIGHT:
			{
				key_r = k;
				inertia_r = true;
				platform.MovePlatform(Point(power_r, 0));
				power_r += g_platform_increase;
			}
			break;
		}

		
	}

	virtual void onKeyReleased(FRKey k) {
		//moving the platform on keyboard press and release
		switch (k)
		{
			case FRKey::LEFT:
			{
				inertia_l = false;
				if (power_l > 0)
				{
					platform.MovePlatform(Point(-power_l, 0));
					power_l -= g_platform_decrease;
				}

			}
			break;

			case FRKey::RIGHT:
			{
				inertia_r = false;
				if (power_r > 0)
				{
					platform.MovePlatform(Point(power_r, 0));
					power_r -= g_platform_decrease;
				}
			}
			break;
		}
	}

	virtual const char* GetTitle() override
	{
		return "Arcanoid";
	}
};



float MyFramework::power_l = 0;
float MyFramework::power_r = 0;

bool MyFramework::inertia_l = false;
bool MyFramework::inertia_r = false;

FRKey MyFramework::key_l = FRKey::COUNT;
FRKey MyFramework::key_r = FRKey::COUNT;
FRKey* MyFramework::key = nullptr;




//-window 800x600 -level 2
int main(int argc, char* argv[])
{
	
	Utils util;

	struct Switches mySwitch;
	mySwitch = util.permuation(argc, argv); 

	srand(time(NULL));

	g_curlevel = mySwitch.level;
	g_hearts = mySwitch.heart;
	g_width = mySwitch.screen_width;
	g_height = mySwitch.screen_height;

	switch (g_curlevel)
	{
	case 1:
		g_ball_speed = 0.35;
		g_total_blocks = 24;
		break;
	case 2:
		g_ball_speed = 0.40;
		g_total_blocks = 30;
		break;
	default:
		g_ball_speed = 0.45;
		g_total_blocks = 30;
		break;
	}
	run(new MyFramework); 


	
	return EXIT_SUCCESS;
}
