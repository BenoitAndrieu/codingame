#include <iostream>
#include <array>
#include <numeric>
#include <unordered_set>
#include <algorithm>
#include <numeric>

using namespace std;

struct xy
{
	int x{ -1 };
	int y{ -1 };
};

struct square
{
	char value{};
	array<bool, 9> remaining_values;

	square()
	{
		remaining_values.fill(true);
	}

	square(char c)
	{
		value = c;
		remaining_values.fill(false);
	}
};

using row_t = std::array<square, 9>;
using grid_t = std::array<row_t, 9>;

void output(grid_t const& grid)
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			cerr << grid[row][col].value;
		}
		cerr << endl;
	}
	cerr << "-------" << endl;
}

class solver
{
	void remove_value_in_block_and_line(grid_t& grid, int row, int col)
	{
		const char value = grid[row][col].value;
		if (value == 0)
			return;

		//cerr << "clean " << col << ' ' << row << endl;

		int block[2] = { col / 3, row / 3 };
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				const int it_col = block[0] * 3 + j;
				const int it_row = block[1] * 3 + i;
				//cerr << ", " <<  it_col << ' ' << it_row << " removes ";

				if (it_col == col && it_row == row)
					continue;

				if (grid[it_row][it_col].value != 0)
					continue;

				//cerr << " ." << value;
				grid[it_row][it_col].remaining_values[value - 1] = false;
			}
		}

		//cerr << endl;

		for (int it_col = 0; it_col < 9; it_col++)
		{
			//cerr << ", " <<  it_col << ' ' << row << " removes ";
			if (it_col == col)
				continue;

			if (grid[row][it_col].value != 0)
				continue;

			//cerr << " -" << value;

			grid[row][it_col].remaining_values[value - 1] = false;
		}

		//cerr << endl;

		for (int it_row = 0; it_row < 9; it_row++)
		{
			//cerr << ", " <<  col << ' ' << it_row << " removes ";
			if (it_row == row)
				continue;

			if (grid[it_row][col].value != 0)
				continue;

			//cerr << " -" << value;

			grid[it_row][col].remaining_values[value - 1] = false;
		}

		//cerr << endl;
	}

	void simplify(grid_t& grid)
	{
		for (bool again = true; again == true; again = false)
		{
			for (int row = 0; row < 9; row++)
			{
				for (int col = 0; col < 9; col++)
				{
					remove_value_in_block_and_line(grid, row, col);
				}
			}

			for (int row = 0; row < 9; row++)
			{
				for (int col = 0; col < 9; col++)
				{
					char sum{};
					char value{};
					for (char i = 0; i < 9; ++i)
					{
						if (grid[row][col].remaining_values[i] == 0)
							continue;

						sum++;

						if (sum > 1)
							break;

						value = i + 1;
					}

					if (sum == 1)
					{
						grid[row][col].value = value;
						grid[row][col].remaining_values.fill(false);
						again = true;
					}
				}
			}
		}
	}

	bool check(grid_t const& grid)
	{
		int sum{};
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (grid[row][col].value == 0)
					return false; // square not filled
				sum += grid[row][col].value;
			}
		}

		if (sum != 45 * 9)
			return false; // wrong sum

		for (int it_col = 0; it_col < 9; it_col++)
		{
			int col_sum{};
			for (int it_row = 0; it_row < 9; it_row++)
			{
				col_sum += grid[it_row][it_col].value;
			}

			if (col_sum != 45)
				return false; // wrong sum
		}

		for (int it_row = 0; it_row < 9; it_row++)
		{
			int row_sum{};
			for (int it_col = 0; it_col < 9; it_col++)
			{
				row_sum += grid[it_row][it_col].value;
			}

			if (row_sum != 45)
				return false; // wrong sum
		}

		return true; // solution found !
	}

	bool find_easy_square(grid_t const& grid, xy& easy)
	{
		char max = 100;
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (grid[row][col].value != 0)
					continue;

				const char sum = std::accumulate(
					grid[row][col].remaining_values.cbegin(),
					grid[row][col].remaining_values.cend(),
					0,
					[](char acc, char more) {return acc + more; });

				if (sum >= max)
					continue;

				max = sum;
				easy = { col, row };
			}
		}

		return max < 100;
	}

public:
	bool traverse(grid_t& grid)
	{
		simplify(grid);
		if (check(grid) == true)
			return true;

		xy easy;
		if (find_easy_square(grid, easy) == false)
		{
			return false;
		}

		//cerr << easy.x << ' ' << easy.y << endl;
		auto values = grid[easy.y][easy.x].remaining_values;
		grid[easy.y][easy.x].remaining_values.fill(false);
		for (char i = 0; i < size(values); ++i)
		{
			if (values[i] == false)
				continue;

			const char value = i + 1;
			grid_t mutation = grid;
			mutation[easy.y][easy.x].value = value;
			if (traverse(mutation) == true)
			{
				//cerr << easy.x << ' ' << easy.y << ' ' << value << endl;
				grid = mutation;
				return true;
			}
		}
		grid[easy.y][easy.x].value = 0;
		grid[easy.y][easy.x].remaining_values = values;

		return false;
	}
};

#ifndef WITHIN_VS
int main()
{
	grid_t grid;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			char c;
			cin >> c;
			if (c != '0')
				grid[row][col] = square(c - '0');
		}
		cin.ignore();
	}

	output(grid);

	solver().traverse(grid);

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			cout << char(grid[row][col].value + '0');
		}
		cout << endl;
	}
			}
#endif