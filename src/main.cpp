#include <ncurses.h>
#include <string>
#include <vector>
#include "./gameplay/game.cpp"

using namespace std;
struct leaf{//SUPER TEMPORARY
	int x;
	int y;
	int width = 5;
	string text;
	bool flipped = false;
};

int initialize_terminal(){
	//initialize screen/colors, if the terminal doesnt support color return 1
	initscr();
	if(has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		return 1;
	}
	start_color();
	//set color to green
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	attron(COLOR_PAIR(1));

	//hide cursor
	curs_set(0);
	return 0;
}
vector<leaf> get_leaves(Game &cur_game){
	vector<pair<int, int>> positions = cur_game.answer();

	vector<leaf> s;
	for (int i = 0; i < positions.size(); i++){
		//pairs are of row, col, display is of x, y
		s.push_back({positions[i].first*5, positions[i].second*5, 5, "qwertasdfgzxcvb"});
	}
	//will generate the ascii art later

	// s.push_back({1, 1, 5, "qwertasdfgzxcvb"});
	// s.push_back({10, 17, 5, "qwertasdfgzxcvb"});
	// s.push_back({40, 3, 7, "qwertyuasdfghjzxcvbnm1234567!@#$%^&"});
	// s.push_back({100, 17, 5, "qwertasdfgzxcvb"});
	return s;
}
void const display_leaf(int x, int y, int width, string &leaf_array){
	for (int h = 0; h < leaf_array.size()/width; h++){
		move(y+h, x);
		if (y+h >= LINES){
			return;
		}
		for (int w = 0; w < width; w++){
			if (w >= COLS){
				return;
			}
			addch(leaf_array[h*width + w]);
		}
	}

}
void display_menu(Game &cur_game){
	//constants, can be fixed later
	int menu_width = 30;
	
	//display a bar seperating the menu and the game preview
	attron(A_BOLD);
	for (int i = 0; i < LINES; i++){
		mvaddch(i, (COLS - menu_width), '|');
	}

	//Add some text to the menu, top down
	int lineCount = 0;
	move(lineCount++, COLS-menu_width+1);
	printw(" ~~~~~~~~TOaNL~~~~~~~~");
	string s = "Try to turn the leaves in    the correct order! Turn the  leaves by clicking!";
	for (int i = 0; i <= s.size()/(menu_width-1); i++){
		move(lineCount++, COLS-menu_width+1);
		for (int h = 0; h < menu_width-1 && i*(menu_width-1)+h < s.size(); h++){
			addch(s[i*(menu_width-1)+h]);
		}
	}

	lineCount++;
	move(lineCount++, COLS-menu_width+1);
	printw("Remember the order!");
	lineCount++;
	//list leave info
	vector<leaf> leaves = get_leaves(cur_game);
	for (int i = 0; i < leaves.size(); i++){
		//write to middle of menu
		// left wall + half of the empty space
		display_leaf(COLS - menu_width + ((menu_width - leaves[i].width) / 2), lineCount, leaves[i].width, leaves[i].text);
		lineCount += leaves[i].text.length()/leaves[i].width+1;
	}
	

	//add a [PAUSED] to the center of the gameplay section
	move((int) LINES/2, (int) ((COLS-menu_width)/2)-4);;// -4 to center pause
	printw("[PAUSED]");
	attroff(A_BOLD);


}

void display_gameplay(Game &cur_game){
	//display leaves
	vector<leaf> leaves = get_leaves(cur_game);
	for (int i = 0; i < leaves.size(); i++){
		display_leaf(leaves[i].x, leaves[i].y, leaves[i].width, leaves[i].text);	
	}
}
void display_state(Game &cur_game, int paused){
	//clear any old info
	clear();
	if (paused == 1){
		//display game as backdrop behind the [paused] section
		display_gameplay(cur_game);

		display_menu(cur_game);
	}
	else {
		display_gameplay(cur_game);
	}

	refresh();

	//display screen until input stops it, placeholder
	getch();
	endwin();

}
int main(int argc, char **argv)
{
	if (initialize_terminal() == 1){
		return 1;
	}

	Game cur_game((int)LINES/5, (int)(COLS-30)/5);
	cur_game.initialize(5);
	display_state(cur_game, 1);



	return 0;
}
