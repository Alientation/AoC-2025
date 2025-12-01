#include <iostream>

#include <cstring>
#include <cassert>

using namespace std;

void p1 ()
{
    int p = 50;
    int count = 0;

    string line;
    while (getline (cin, line))
    {
        char dir = line[0];
        int amt = stoi (line.substr (1));

        if (dir == 'L')
        {
            p -= amt;
            p += 100 * ((amt + 99) / 100);
            p %= 100;
            assert (p >= 0);
        }
        else if (dir == 'R')
        {
            p += amt;
            p %= 100;
        }
        if (p == 0)
        {
            count++;
        }
    }

    cout << count;
}


void p2 ()
{
    int p = 50;
    int count = 0;

    string line;
    while (getline (cin, line))
    {
        char dir = line[0];
        int amt = stoi (line.substr (1));

        if (dir == 'L')
        {
            while (amt > 0)
            {
                p--;
                amt--;
                if (p == 0)
                {
                    count++;
                }
                else if (p < 0)
                {
                    p = 99;
                }
            }
        }
        else if (dir == 'R')
        {
            while (amt > 0)
            {
                p++;
                amt--;
                if (p == 100)
                {
                    count++;
                    p = 0;
                }
            }
        }

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