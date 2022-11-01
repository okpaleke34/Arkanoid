#pragma once

struct Switches
{
	int screen_width = 600;
	int screen_height = 600;
	int level = 1;
	int heart = 5;
	bool help = false;
};


class Utils {
private:
public:

	/*
	* Generate a random number from minimum passed in the parameters to the maximum
	* @param min the min number in the range
	* @param max the maximum number in the range
	* @returns integer within the range passed in the parameter
	*/
	int randomNum(int min, int max) {
		return (min + (std::rand() % (max - min + 1)));
	}
	/*
	* Calculate the percentage of a number
	* @param total the number to find the percentage
	* @param percentage the percent of the number to get
	* @returns a float of the sum of the total and calculated percentage
	*/
	float percentageCal(float total, float percent) {
		return total + ((percent / 100) * total);
	}

	/*
	* converts a string of separated char to a vector
	* @param str the string to convert to vector
	* @param delimeter the delimeter to explode
	* @returns a vector separated by the delimeter of the str
	*/
	vector<string> str2vec(string str, char delimeter) {
		vector<string> vect;
		stringstream ss(str);

		while (ss.good()) {
			string substr;
			getline(ss, substr, delimeter);
			vect.push_back(substr);
		}
		return vect;
	}
	/*
	* This handles the permutation of the command line switches since there is no getopt for c++ windows as in linux
	* @param argc is the number of switches passed through the command line
	* @param argv is an array of char passed through the command line
	* @returns it return a Switches struct containing the different values passed through the command line for easy reading
	*/
	struct Switches permuation(int argc, char** argv)
	{
		Switches mySwitch;
		if (argc == 1)
		{
			mySwitch.help = true;
		}
		for (int i = 0; i < argc; i++)
		{

			if (i != 0)
			{
				string prevSwitch = argv[i - 1];
				string currSwitch = argv[i];
				if (currSwitch == "-h")
				{
					mySwitch.help = true;
				}
				else if (prevSwitch == "-window")
				{
					vector<string> window = str2vec(argv[i], 'x');
					mySwitch.screen_width = stoi(window[0]);
					mySwitch.screen_height = stoi(window[1]);
				}
				else if (prevSwitch == "-level")
				{
					mySwitch.level = stoi(argv[i]);
				}
				else if (prevSwitch == "-heart")
				{
					mySwitch.heart = stoi(argv[i]);
				}
			}
		}
		if (mySwitch.help) {
			cout << "   \n\nARKANOID GAME HELP\n\n\
		\n *Use the command line switch eg '-window 600x650 -level 1 -heart 10 -h' \
		\n*-Where 600 is the width and 650 is the height of the display screen \
		\n*-Where 1 is the current game level(we have total number of 1-4 levels) \
		\n*-Where 10 is the number of hearts/respawn at start. \
		\n*-If you have -h it will print the help. It will also print it if there is no arguments passed in the commandline. \
		\n*\
		\n* Black blocks are edges it does not break but bounce back. It cannot be in the first two rows given that the game is in 600x(any height) display \
		\n* When you break a red block extra heart comes down it must be atleast 2 in each game level\
		\n* Blue balls changes from blue to skyblue every 10 seconds and skyblue are transparent to the ball for 3 seconds\
		\n* If you die(exhuated your hearts) in any level you will start the level afresh\
		\n* The last block in every game will start moving from left to right\
		\n*\
		\n*Sounds\
		\n*-There is sound when the ball hit the platform,block and edges\
		\n*-There is sound when you finally break the block.\
		\n*-There is sound when you in collect ability with the platform\
		\n*-There is sound when you you lost all hearts(game over) when you break all blocks and collect the ball with the platform(victory)\n\n\
		";
		}
		return mySwitch;
	}
};