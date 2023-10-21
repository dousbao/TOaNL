#include <ncurses.h>
#include <string>
#include <vector>
struct leaf{//SUPER TEMPORARY
	int x;
	int y;
	int width;
	std::string text;
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
void const display_leaf(int x, int y, int width, std::string &leaf_array){
	for (int h = 0; h < leaf_array.size()/width; h++){
		move(y+h, x);
		for (int w = 0; w < width; w++){
			addch(leaf_array[h*width + w]);
		}
	}

}
void display_menu(){
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
	std::string s = "Try to turn the leaves in    the correct order! Turn the  leaves by clicking!";
	for (int i = 0; i <= s.size()/(menu_width-1); i++){
		move(lineCount++, COLS-menu_width+1);
		for (int h = 0; h < menu_width-1 && i*(menu_width-1)+h < s.size(); h++){
			addch(s[i*(menu_width-1)+h]);
		}
	}

	lineCount++;
	move(lineCount++, COLS-menu_width+1);
	printw("Remember these!");

	//list leave info

	

	//add a [PAUSED] to the center of the gameplay section
	move((int) LINES/2, (int) ((COLS-menu_width)/2)-4);;// -4 to center pause
	printw("[PAUSED]");
	attroff(A_BOLD);


}
std::vector<leaf> get_leaves(){
	//temptemptemp
	std::vector<leaf> s;
	s.push_back({1, 1, 5, "qwertasdfgzxcvb"});
	s.push_back({10, 17, 5, "qwertasdfgzxcvb"});
	s.push_back({40, 3, 7, "qwertyuasdfghjzxcvbnm1234567!@#$%^&"});
	return s;
}
void display_gameplay(){
	//display leaves
	std::vector<leaf> leaves = get_leaves();
	for (int i = 0; i < leaves.size(); i++){
		display_leaf(leaves[i].x, leaves[i].y, leaves[i].width, leaves[i].text);	
	}
}
void display_state(int paused){
	//clear any old info
	clear();
	if (paused == 1){
		//display game as backdrop behind the [paused] section
		display_gameplay();

		display_menu();
	}
	else {
		display_gameplay();
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

	display_state(1);

	

	return 0;
}
