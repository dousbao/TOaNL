#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <random>

using namespace std;

class Cell
{
private:
	bool m_is_leaf;
	bool m_is_flipped;
  int m_value;
    
public:
	Cell();
	Cell(int v);
	bool is_leaf();
	int value();
	void flip();
	int is_flipped();
};

class Game
{
private:
	int m_width;
	int m_height;
	int m_number_of_leaves;
	int m_number_of_guess;
	int m_last_leaf_val;
	bool m_is_game_over;
	unsigned int m_seed;
	vector<vector<Cell>> m_grid;
	vector<pair<int, int>> m_answer;

public:
	Game(int h, int w);
	Game(int h, int w, unsigned int s);

	void initialize(int number_of_leaves);
	void display();
	void show_all();
	void flip(int row, int col);
	bool is_game_over();
	vector<pair<int, int>> answer();
};