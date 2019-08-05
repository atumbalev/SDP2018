/*
Задача 3. Квадратна матрица е представена чрез свързан списък (с една връзка) от свързани списъци (с една връзка). Изтрийте елементите от главния и от вторичния главен диагонал на матрицата.
*/

#include <list>
#include <iostream>

void print(const std::list<std::list<int>>& matrix)
{
	for(const std::list<int>& row : matrix)
	{
		for(const int& el : row)
		{
			std::cout<<el<<" ";
		}
		std::cout<<std::endl;
	}
}

void removeDiagonals(std::list<std::list<int>>& matrix)
{
	size_t row = 0, column = 0, len = matrix.size();;

	for(auto itMatrix = matrix.begin(); itMatrix != matrix.end(); ++itMatrix)
	{
		column = 0;
		auto itRow = (*itMatrix).begin();
		while (itRow != (*itMatrix).end())
		{
			if (column == row || column + row == len - 1)
			{
				itRow = (*itMatrix).erase(itRow);
			}
			else
			{
				++itRow;
			}
			++column;
		}
		++row;
	}
}

int main(int argc, char const *argv[])
{
	std::list<std::list<int>> threeByThree = {{1,2,3,}, {4,5,6,}, {7,8,9,},};
	std::list<std::list<int>> fourByFour = {{1,2,3,4,}, {5,6,7,8,}, {9,10,11,12,}, {13,14,15,16},};

	print(threeByThree);
	std::cout<<std::endl;
	print(fourByFour);

	removeDiagonals(threeByThree);
	removeDiagonals(fourByFour);

	std::cout<<std::endl;
	print(threeByThree);
	std::cout<<std::endl;
	print(fourByFour);
	return 0;
}
