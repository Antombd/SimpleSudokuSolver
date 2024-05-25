#include <iostream>
#include <vector>
#include <utility>
#include <bitset>
using namespace std;

int rows[9], columns[9], squares[9];    // to keep track of numbers on each row, column and 3x3 square
int layout[9][9];

void Input(vector<pair<int, int>> &blanks)
{
    for (int row = 0; row < 9; row++)
    {
        for (int column = 0; column < 9; column++)
        {
            char temp;
            cin >> temp;
            
            // add the blank space position to an array
            if (temp < '1' || temp > '9')
            {
                blanks.push_back(pair<int, int> (row, column));
                continue;
            }
            
            // if it's a number
            layout[row][column] = temp - '0';
            int mark = 1 << (temp - '1');
            rows[row] |= mark;
            columns[column] |= mark;
            squares[column / 3 + (row / 3) * 3] |= mark;
        }
    }
}

void Solve(vector<pair<int, int>> &blanks, int i)
{
    for (int j = 0; j < 9; j++)
    {
        int mark = 1 << j;
        int blankRow = blanks[i].first, blankCol = blanks[i].second, blankSqu = blankCol / 3 + (blankRow / 3) * 3;
        int indicator = (rows[blankRow] | columns[blankCol]) | squares[blankSqu];
        if ((indicator & mark) != 0)
            continue;
        
        layout[blankRow][blankCol] = j + 1;
        rows[blankRow] |= mark;
        columns[blankCol] |= mark;
        squares[blankSqu] |= mark;
        if (i == blanks.size() - 1)
        {
            for (int row = 0; row < 9; row++)
            {
                for (int column = 0; column < 9; column++)
                    cout << layout[row][column] << ' ';
                cout << endl;
            }
            return ;
        }
        else
            Solve(blanks, i + 1);
        
        layout[blankRow][blankCol] = 0;
        rows[blankRow] ^= mark;
        columns[blankCol] ^= mark;
        squares[blankSqu] ^= mark;
    }
}

int main()
{
    vector<pair<int, int>> blanks; // pair <row, column>
    Input(blanks);
    if (!blanks.empty())
        Solve(blanks, 0);
    else
    {
        for (int i = 0; i < blanks.size(); i++)
            cout << blanks[i].first << ' ' << blanks[i].second << endl;
        for (int row = 0; row < 9; row++)
        {
            for (int column = 0; column < 9; column++)
                cout << layout[row][column] << ' ';
            cout << endl;
        }
    }
}
