#include "../aoc.hpp"

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void p1 ()
{
    int count = 0;
    vector<pair<U64, U64>> ranges;

    string line;
    while (getline (cin, line) && line != "")
    {
        string p1 = line.substr(0, line.find('-'));
        string p2 = line.substr(line.find('-') + 1);


        U64 i1 = stoull(p1);
        U64 i2 = stoull(p2);
        ranges.push_back(pair<U64,U64>(i1, i2));
    }

    while (getline(cin, line))
    {
        U64 p = stoull(line);
        for (auto &r : ranges)
        {
            if (p >= r.first && p <= r.second)
            {
                count++;
                break;
            }
        }
    }


    cout << count;
}


void p2 ()
{
    U64 count = 0;
    vector<pair<U64, U64>> ranges;

    string line;
    vector<bool> alive;
    while (getline (cin, line) && line != "")
    {
        string p1 = line.substr(0, line.find('-'));
        string p2 = line.substr(line.find('-') + 1);


        U64 i1 = stoull(p1);
        U64 i2 = stoull(p2);

        count += i2 - i1 + 1;
        for (size_t i = 0; i < ranges.size (); i++)
        {
            if (!alive[i]) continue;

            auto &p = ranges[i];
            if (i1 <= p.second && i2 >= p.first)
            {
                if (i1 <= p.first && i2 <= p.second)
                {
                    count -= i2 - p.first + 1;
                }
                else if (i1 <= p.first && i2 > p.second)
                {
                    count -= p.second - p.first + 1;
                }
                else if (i1 > p.first && i2 <= p.second)
                {
                    count -= i2 - i1 + 1;
                }
                else if (i1 > p.first && i2 > p.second)
                {
                    count -= p.second - i1 + 1;
                }
                else
                {
                    assert (false);
                }

                i1 = min(i1, p.first);
                i2 = max(i2, p.second);
                alive[i] = false;
            }
        }

        alive.push_back (true);
        ranges.push_back(pair<U64,U64>(i1, i2));
    }

    while (getline(cin, line))
    {
        // do nothing
    }

    cout << count;
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