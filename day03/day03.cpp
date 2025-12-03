#include "../aoc.hpp"

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void p1 ()
{
    string line;

    unsigned long long tot = 0;
    while (getline(cin, line))
    {
        int largest_val = 0;
        int largest_digit = 0;
        for (char c : line)
        {
            const int d = c - '0';
            const int val = largest_digit * 10 + d;
            largest_val = max(largest_val, val);
            largest_digit = max(largest_digit, d);
        }
        tot += largest_val;
    }
    cout << tot;
}


void p2 ()
{
    string line;

    unsigned long long tot = 0;
    while (getline(cin, line))
    {
        unsigned long long dp[line.size () + 1][13] = {0};

        for (size_t i = 0; i < line.length (); i++)
        {
            for (int j = 0; j < 12; j++)
            {
                dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] * 10 + line[i] - '0');
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            }
        }
        unsigned long long largest = 0;
        for (size_t i = 0; i <= line.length (); i++)
        {
            largest = max(largest, dp[i][12]);
        }
        tot += largest;
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