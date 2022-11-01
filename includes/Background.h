#pragma once
/*
* This creates and manage the background of the game window
*/
class BackGround
{
private:
	Sprite* sprite;
	int width;
	int height;
public:

	/*
	* Create a background sprite
	* @returns the created background sprite
	*/
	Sprite* CreateBackGround(std::string filename)
	{
		if (sprite == nullptr)
		{
			sprite = createSprite((g_dir + filename).c_str());
			getSpriteSize(sprite, width, height);
		}
		return sprite;
	}

	/*
	* get the sprite object of the Background
	* @returns the sprite
	*/
	Sprite* GetSprite()
	{
		return sprite;
	}

	/*
	* Draw the sprite a to fullscreen
	*/
	void DrawBackground()
	{
		for (int i = 0; i < g_width; i += this->width)
		{
			for (int j = 0; j < g_height; j += height)
				drawSprite(sprite, i, j);
		}
	}

	virtual ~BackGround() {
		destroySprite(sprite); 
	}
};