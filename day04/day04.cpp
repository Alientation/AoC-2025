#include "../aoc.hpp"

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void p1 ()
{
    vector<vector<char>> map;

    string line;
    while (getline(cin, line))
    {
        map.push_back(vector<char>());
        for (char c : line)
        {
            map.back ().push_back (c);
        }
    }

    const int directions[8][2] = {
        {1, 0},
        {1, -1},
        {1, 1},
        {0, 1},
        {0, -1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
    };

    int tot = 0;
    for (size_t i = 0; i < map.size (); i++)
    {
        for (size_t j = 0; j < map[i].size (); j++)
        {
            int count = 0;
            for (int d = 0; d < 8; d++)
            {
                int ii = i + directions[d][0];
                int jj = j + directions[d][1];
                if (ii >= 0 && ii < map.size () && jj >= 0 && jj < map[ii].size ())
                {
                    count += map[ii][jj] == '@';
                }
            }
            if (count < 4 && map[i][j] == '@')
            {
                tot++;
            }
        }
    }
    cout << tot;
}


void p2 ()
{
    vector<vector<char>> map;

    string line;
    while (getline(cin, line))
    {
        map.push_back(vector<char>());
        for (char c : line)
        {
            map.back ().push_back (c);
        }
    }

    const int directions[8][2] = {
        {1, 0},
        {1, -1},
        {1, 1},
        {0, 1},
        {0, -1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
    };

    int tot = 0;
    while (true)
    {
        int rem = 0;
        for (size_t i = 0; i < map.size (); i++)
        {
            for (size_t j = 0; j < map[i].size (); j++)
            {
                int count = 0;
                for (int d = 0; d < 8; d++)
                {
                    int ii = i + directions[d][0];
                    int jj = j + directions[d][1];
                    if (ii >= 0 && ii < map.size () && jj >= 0 && jj < map[ii].size ())
                    {
                        count += map[ii][jj] == '@';
                    }
                }
                if (count < 4 && map[i][j] == '@')
                {
                    rem++;
                    tot++;
                    map[i][j] = '.';
                }
            }
        }

        if (rem == 0)
        {
            break;
        }
    }
    cout << tot;
}

int main (int argc, char *argv[])
{
    if (argc <= 0)
    {
        cerr << "Invalid argc (<= 0): " << argc << "\n";
        exit (EXIT_FAILURE);
    }

    // Inputs are passed via stdin.
    if (strcmp (argv[1], "1") == 0)
    {
        p1 ();
    }
    else if (strcmp (argv[1], "2") == 0)
    {
        p2 ();
    }
    else
    {
        cerr << "Invalid argument: " << argv[1];
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}