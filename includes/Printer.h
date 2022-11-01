#pragma once
/*
* A class that stores all the beautidul printing information
*/
class Printer {

public:
	/*
	* This prints a heart and a text inside it
	* @params message the message to print in the middle of the heart
	*/
	void heart(string message) {
		cout << "\n\n";
		int size = 4;
		int n = message.length();

		int print_line = 1;

		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y <= 4 * size; y++)
			{
				double dist1 = sqrt(pow(x - size, 2) + pow(y - size, 2));
				double dist2 = sqrt(pow(x - size, 2) + pow(y - 3 * size, 2));

				if (dist1 < size + 0.5 || dist2 < size + 0.5) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
			printf("\n");
		}

		for (int x = 1; x < 2 * size; x++)
		{
			for (int y = 0; y < x; y++) {
				printf(" ");
			}

			for (int y = 0; y < 4 * size + 1 - 2 * x; y++)
			{
				if (x >= print_line - 1 && x <= print_line + 1)
				{
					int idx = y - (4 * size - 2 * x - n) / 2;
					if (idx < n && idx >= 0)
					{
						if (x == print_line) {
							printf("%c", message[idx]);
						}
						else {
							printf(" ");
						}
					}
					else {
						printf("*");
					}
				}
				else {
					printf("*");
				}
			}
			printf("\n");
		}
		cout << "\n\n";
	}

	void arcanoidMaster() {
		cout << "\n\n";
		cout << "**** **** **** **** **** **** **** **** **** *****\n"
				"***** **** **** **** **** **** **** **** **** ****\n"
				"**** **** **** **** **** **** **** **** **** *****\n"
				"***** **** **** **** **** **** **** **** **** ****\n"
				"*                                                *\n"
				"*                                                *\n"
				"*                                                *\n"
				"*      **                                        *\n"
				"*                                                *\n"
				"*        *****                                   *\n"
				"**************************************************\n"
				"  *    **     **    *   **   *   **  *  ***  \n"
				" ***   ***  *      ***  *  * *  *  * *  *  * \n"
				"*   *  *  *   **  *   * *   **   **  *  ***  \n"
				"                                             \n"
				"  *  *      *       *** ***  ****   **      \n"
				" * *  *    ***     *     *   ***    ***     \n"
				"*  *   *  *   *  ***     *   ****   *  *     \n";
		cout << "\n\n\n\n";
		cout << "===================================================\n";
		cout << "#                ARCANOID MASTER!!!!!             #\n";
		cout << "#        YOU FINISHED ALL THE LEVELS!!!!!         #\n";
		cout << "#  Thanks for playing my game to the en           #\n";
		cout << "#  Game developed by: Chukwudi Okpaleke           #\n";
		cout << "#  Github: github.com/okapleke34                  #\n";
		cout << "#  Instagram: @okapleke34                         #\n";
		cout << "#  Restarting to Level 1 in 10 seconds            #\n";
		cout << "===================================================\n\n\n\n";
	}
	
	void victory(int hearts) {
		cout << "\n\n";
		cout << " **         **  **    ****  ******    ****       *****    **    ** \n"
				"  **       **   **   **       **    **    **    **   **    **  **  \n"
				"   **     **    **  **        **   **      **   ******       **    \n"
				"    **   **     **   **       **    **    **    **   **     **     \n"
				"      ***       **    ****    **      ****      **    **   **   \n"
				"\n";
		cout << "\n\n\n";
		cout << "=============================================\n";
		cout << "#                                           #\n";
		cout << "#      CONGRATULATIONS YOU WON!!!!!         #\n";
		cout << "#        You have " << hearts << " heart(s) left           #\n";
		cout << "#     Next level loading in 5 seconds       #\n";
		cout << "#                                           #\n";
		cout << "=============================================\n\n\n\n";
	}

	void ballOut(int hearts) {
		cout << "\n\n\n===================================================\n";
		cout << "#                                                 #\n";
		cout << "#             OPPSSS BALL OUT :(                  #\n";
		cout << "# You Failed to Catch The Ball With The Platform  #\n";
		cout << "#            You have " << hearts << " heart(s) left             #\n";
		cout << "#                                                 #\n";
		cout << "===================================================\n\n\n\n";
	}
	
	void done() {

		cout << "\n\n";
		cout << "******         ****     **     **  ******   ** ** ** \n"
				"**    **     **    **   ** *   **  **       ** ** **\n"
				"**      **  **      **  **  *  **  ******   ** ** **\n"
				"**    **     **    **   **   * **  **               \n"
				"******         ****     **    ***  ******   ** ** **\n"
				"\n";
		cout << "\n\n";
	}


	void level1() {
		cout << "\n\n";
		cout << "**     ******  **       ** ******  **       **** \n"
				"**     **       **     **  **      **         **  \n"
				"**     ******    **   **   ******  **         **  \n"
				"**     **         ** **    **      **         **  \n"
				"*****  ******      ***     ******  ******    **** \n"
				"\n";
		cout << "\n\n";
	}

	void level2() {
		cout << "\n\n";		
		cout << "**     ******  **       ** ******  **       ******  \n"
				"**     **       **     **  **      **       **   **  \n"
				"**     ******    **   **   ******  **           **   \n"
				"**     **         ** **    **      **         ***  \n"
				"*****  ******      ***     ******  ******    ****** \n"
				"\n";
		cout << "\n\n";
	}
	

	
	void level3() {
		cout << "\n\n";		
		cout << "**     ******  **       ** ******  **       *****  \n"
				"**     **       **     **  **      **           **  \n"
				"**     ******    **   **   ******  **       ******   \n"
				"**     **         ** **    **      **           **  \n"
				"*****  ******      ***     ******  ******   *****  \n"
			
			"\n";
		cout << "\n\n";
	}
	void level4() {
		cout << "\n\n";		
		cout << "**     ******  **       ** ******  **          **   \n"
				"**     **       **     **  **      **         **     \n"
				"**     ******    **   **   ******  **        **  **   \n"
				"**     **         ** **    **      **       ********  \n"
				"*****  ******      ***     ******  ******       **   \n"
				"\n";
		cout << "\n\n";
	}
		
	void lost() {
		cout << "\n\n";
		cout << "**        ****       ****  ******         **      **  \n"
				"**      **    **    **       **           **   **    \n"
				"**     **      **    **      **               **     \n"
				"**      **    **     **      **           **   **    \n"
				"*****     ****    ****       **           **      **  \n"
				"\n";
		cout << "\n\n";
		cout << "===================================================\n";
		cout << "#                                                 #\n";
		cout << "#             OPPSSS YOU LOST :(                  #\n";
		cout << "# You Failed to Catch The Ball With The Platform  #\n";
		cout << "#            THE GAME IS OVER :(                  #\n";
		cout << "#      Restarting Level in 5 Seconds              #\n";
		cout << "#                                                 #\n";
		cout << "===================================================\n\n\n\n";
	}
		
	
};