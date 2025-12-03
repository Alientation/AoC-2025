#include <iostream>

#include <cstring>
#include <cassert>

using namespace std;

void p1 ()
{
    string line;

    long long tot = 0;
    while (getline(cin, line))
    {
        int largest_val = 0;
        int largest_before = 0;
        for (char c : line)
        {
            int val = largest_before * 10 + (c - '0');
            if (val > largest_val)
            {
                largest_val = val;
            }
            if ((c - '0') > largest_before)
            {
                largest_before = (c - '0');
            }
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


        for (int i = 0; i < line.length (); i++)
        {
            for (int j = 0; j < 12; j++)
            {
                if (dp[i + 1][j + 1] < dp[i][j] * 10 + line[i] - '0')
                {
                    dp[i + 1][j + 1] = dp[i][j] * 10 + line[i] - '0';
                }

                if (dp[i + 1][j] < dp[i][j])
                {
                    dp[i + 1][j] = dp[i][j];
                }
            }
        }
        unsigned long long max = 0;
        for (int i = 0; i <= line.length (); i++)
        {
            if (max < dp[i][12])
            {
                max = dp[i][12];
            }
        }
        tot += max;
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