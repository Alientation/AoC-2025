#include "../aoc.hpp"

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void p1 ()
{
    string line;
    std::vector<std::vector<U64>> values;

    while (getline(cin, line))
    {
        if (line.find('*') != string::npos || line.find('+') != string::npos)
        {
            cout << "breaking\n";
            break;
        }

        size_t pos = line.find_first_not_of(' ');
        std::vector<U64> t;
        while (line.find(' ', pos) != string::npos)
        {
            U64 v = stoull(line.substr(pos, line.find(' ', pos) - pos));
            t.push_back(v);
            pos = line.find_first_not_of(' ', pos + line.find(' ', pos) - pos + 1);
        }
        t.push_back(stoull(line.substr(pos)));
        values.push_back(t);
    }

    size_t pos = 0;
    U64 tot = 0;
    int i = 0;
    while(pos < line.length() && line.find_first_not_of(' ', pos) != string::npos)
    {
        size_t p1 = line.find_first_not_of(' ', pos);
        pos = p1 + 1;
        U64 s = 0;
        if (line[p1] == '+')
        {
            for (int j = 0; j < values.size (); j++)
            {
                s += values[j][i];
            }
        }
        else if (line[p1] == '*')
        {
            s = 1;
            for (int j = 0; j < values.size (); j++)
            {
                s *= values[j][i];
            }
        }

        i++;
        tot += s;
    }
    cout << tot;
}


void p2 ()
{
    string line;
    vector<string> nums;
    while (getline(cin, line))
    {
        if (line.find('+') != string::npos || line.find('*') != string::npos)
        {
            break;
        }

        nums.push_back(line);
    }

    size_t pos = 0;
    U64 tot = 0;
    int i = 0;
    while(pos < line.length() && line.find_first_not_of(' ', pos) != string::npos)
    {
        size_t p1 = line.find_first_not_of(' ', pos);
        pos = p1 + 1;
        U64 s = (line[p1] == '+') ? 0 : 1;

        size_t p2 = line.find_first_not_of(' ', pos);
        if (p2 == string::npos) p2 = line.length () + 1;

        for (int j = p1; j < p2 - 1; j++)
        {
            U64 n = 0;
            for (int r = 0; r < nums.size (); r++)
            {
                if (nums[r][j] == ' ') continue;
                n *= 10;
                n += nums[r][j] - '0';
            }

            if (line[p1] == '+')
            {
                s += n;
            }
            else
            {
                s *= n;
            }
        }

        i++;
        tot += s;
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