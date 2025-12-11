#include "../aoc.hpp"

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void p1 ()
{
    string line;
    unordered_map<string, vector<string>> map;
    while (getline (cin, line))
    {
        string p = line.substr(0, line.find (':'));
        line = line.substr(line.find (':') + 2);
        vector<string> outs;
        for (size_t pos = 0; pos < line.length (); pos += 4)
        {
            outs.push_back (line.substr(pos, 3));
        }

        map[p] = outs;
    }


    const string begin = "you";
    const string end = "out";
    queue<pair<string, U16>> q;
    q.push (pair<string, U16> (begin, 0));
    U64 count = 0;
    while (!q.empty ())
    {
        auto p = q.front ();
        q.pop ();

        if (p.first == end)
        {
            count += 1;
            continue;
        }

        for (string n : map[p.first])
        {
            q.push (pair<string, U64> (n, p.second));
        }
    }

    cout << count;
}


U64 func (string begin, string end, unordered_map <string, vector<string>> &map)
{
    queue<string> q;
    q.push (begin);
    unordered_map <string, U64> visited;
    visited[begin] = 1;
    U64 count = 0;
    while (!q.empty ())
    {
        string p = q.front ();
        q.pop ();

        if (p == end)
        {
            count += visited[p];
            visited.erase (p);
            continue;
        }

        for (string n : map[p])
        {
            if (visited.find (n) != visited.end ())
            {
                visited[n] += visited[p];
            }
            else
            {
                q.push (n);
                visited[n] = visited[p];
            }
        }

        visited.erase (p);
    }
    cout << ">> " << count << endl;
    return count;
}

void p2 ()
{
    string line;
    unordered_map<string, vector<string>> map;
    while (getline (cin, line))
    {
        string p = line.substr(0, line.find (':'));
        line = line.substr(line.find (':') + 2);
        vector<string> outs;
        for (size_t pos = 0; pos < line.length (); pos += 4)
        {
            outs.push_back (line.substr(pos, 3));
        }

        map[p] = outs;
    }


    const string begin = "svr";
    const string end = "out";
    const string t1 = "dac";
    const string t2 = "fft";

    cout << (func (begin, t1, map) * func(t1, t2, map) * func(t2, end, map)) +
            (func (begin, t2, map) * func (t2, t1, map) * func (t1, end, map));
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