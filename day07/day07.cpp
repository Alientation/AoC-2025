#include "../aoc.hpp"

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void p1 ()
{
    string line;
    vector<string> map;
    while (getline(cin, line))
    {
        map.push_back(line);
    }

    vector<U64> prev_counts;
    vector<U64> counts;
    counts.reserve(map[0].size ());
    prev_counts.reserve(map[0].size ());

    for (int c = 0; c < map[0].size (); c++)
    {
        counts[c] = 0;
        prev_counts[c] = 0;
    }

    U64 tot = 0;
    prev_counts[map[0].find('S')] = 1;
    for (int r = 0; r < map.size (); r++)
    {
        for (int c = 0; c < map[r].size (); c++)
        {
            if (prev_counts[c] == 0) continue;

            if (map[r][c] == '.')
            {
                counts[c] += prev_counts[c];
            }
            else
            {
                tot += 1;
                counts[c - 1] += prev_counts[c];
                counts[c + 1] += prev_counts[c];
            }
        }

        for (int c = 0; c < map[r].size (); c++)
        {
            prev_counts[c] = counts[c];
            counts[c] = 0;
        }
    }
    cout << tot;
}


void p2 ()
{
    string line;
    vector<string> map;
    while (getline(cin, line))
    {
        map.push_back(line);
    }

    vector<U64> prev_counts;
    vector<U64> counts;
    counts.reserve(map[0].size ());
    prev_counts.reserve(map[0].size ());

    for (int c = 0; c < map[0].size (); c++)
    {
        counts[c] = 0;
        prev_counts[c] = 0;
    }

    prev_counts[map[0].find('S')] = 1;
    for (int r = 0; r < map.size (); r++)
    {
        for (int c = 0; c < map[r].size (); c++)
        {
            if (prev_counts[c] == 0) continue;

            if (map[r][c] == '.')
            {
                counts[c] += prev_counts[c];
            }
            else
            {
                counts[c - 1] += prev_counts[c];
                counts[c + 1] += prev_counts[c];
            }
        }

        for (int c = 0; c < map[r].size (); c++)
        {
            prev_counts[c] = counts[c];
            counts[c] = 0;
        }
    }

    U64 tot = 0;
    for (int c = 0; c < map[0].size (); c++)
    {
        tot += prev_counts[c];
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