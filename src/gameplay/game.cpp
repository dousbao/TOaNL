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
	Cell()
	{
		m_is_leaf = false;
		m_is_flipped = false;
		m_value = -1;
	}

	Cell(int v)
	{
		m_is_leaf = true;
		m_is_flipped = false;
		m_value = v;
	}

	bool is_leaf()
	{
		return m_is_leaf;
	}

	int value()
	{
		return m_value;
	}

	void flip()
	{
		m_is_flipped = true;
	}

	int is_flipped()
	{
		return m_is_flipped;
	}
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
	Game(int h, int w)
	{	
		m_width = w;
		m_height = h;
		m_is_game_over = false;
		m_last_leaf_val = -1;
		m_number_of_guess = 0;
		
		time_t currentTime = time(nullptr);
	    unsigned int s = static_cast<unsigned int>(currentTime);
		m_seed = s;

		srand(s);
		for (int i = 0; i < m_height; i++)
		{	
			vector<Cell> row;
			for (int j = 0; j < m_width; j++)
			{	
				row.push_back(Cell());
			}
			m_grid.push_back(row);
		}
	}

	Game(int h, int w, unsigned int s)
	{	
		m_width = w;
		m_height = h;
		m_is_game_over = false;
		m_last_leaf_val = -1;
		m_number_of_guess = 0;
		m_seed = s;
		srand(s);
		for (int i = 0; i < m_height; i++)
		{	
			vector<Cell> row;
			for (int j = 0; j < m_width; j++)
			{	
				row.push_back(Cell());
			}
			m_grid.push_back(row);
		}
	}

	void initialize(int number_of_leaves)
	{
		// m_number_of_leaves = number_of_leaves;
		// vector<int> shuffled_vector;
		// for (int i = 0; i < number_of_leaves; i++) {
		// 	shuffled_vector.push_back(i);
		// }
		// random_shuffle(shuffled_vector.begin(), shuffled_vector.end());
		

		for (int i = 0; i < number_of_leaves; i++)
		{
			int rand_r = rand() % m_height;
			int rand_c = rand() % m_width;

			while (m_grid[rand_r][rand_c].is_leaf())
			{
				rand_r = rand() % m_height;
				rand_c = rand() % m_width;
			}
			
			m_grid[rand_r][rand_c] = i;
			pair<int, int> coord;
			coord.first = rand_c;
			coord.second = rand_r;
			m_answer.push_back(coord);
		}
	}

	void display()
	{
		for (int i = 0; i < m_height; i++)
		{
			for (int j = 0; j < m_width; j++)
			{
				if (m_grid[i][j].is_leaf())
				{	
					if (m_grid[i][j].is_flipped())
					{
						cout << m_grid[i][j].value();

					}
					else
					{
						cout << '#';
					}
				}
				else
				{
					cout << '_';
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	void show_all()
	{
		for (int i = 0; i < m_height; i++)
		{
			for (int j = 0; j < m_width; j++)
			{
				if (m_grid[i][j].is_leaf())
				{	
					cout << m_grid[i][j].value();
				}
				else
				{
					cout << '_';
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	void flip(int row, int col)
	{
		if (m_grid[row][col].is_flipped())
		{
			cout << "This cell is flipped" << endl;
			return;
		}
		if (m_is_game_over)
		{
			cout << "Game is already over" << endl;
			return;
		}

		// cout << "last leaf val " << m_last_leaf_val << endl;
		// cout << "flipping row " << row << " col " << col << endl;
		// cout << "cell value: " << m_grid[row][col].value() << endl;

		if (m_last_leaf_val + 1 != m_number_of_guess)
		{	
			cout << "wrong guess gg" << endl;
			m_is_game_over = true;
			return;
		}
		m_grid[row][col].flip();
		m_last_leaf_val = m_grid[row][col].value();
		m_number_of_guess++;
		if (m_number_of_guess == m_number_of_leaves)
		{
			m_is_game_over = true;
		}
	}

	bool is_game_over()
	{
		return m_is_game_over;
	}

	vector<pair<int, int>> answer()
	{
		return m_answer;
	}
};
