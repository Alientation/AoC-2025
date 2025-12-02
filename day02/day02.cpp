#include <iostream>

#include <cstring>
#include <cassert>

using namespace std;

void p1 ()
{
    string line;
    getline (cin, line);
    line += ",";
    long long tot = 0;
    while (true)
    {
        size_t pos = line.find(',');
        if (pos == string::npos)
        {
            break;
        }
        string range = line.substr(0, pos);
        line = line.substr(pos + 1);

        string begin = range.substr(0, range.find('-'));
        string end = range.substr(range.find('-') + 1);

        unsigned long long b = stoull(begin);
        unsigned long long e = stoull(end);


        for (unsigned long long i = b; i <= e; i++)
        {
            string s = to_string (i);
            if (s.length () % 2 == 0 && s.substr(0, s.length () / 2) == s.substr(s.length() / 2))
            {
                tot += i;
            }
        }
    }

    cout << tot;
}


void p2 ()
{
    string line;
    getline (cin, line);
    line += ",";
    long long tot = 0;
    while (true)
    {
        size_t pos = line.find(',');
        if (pos == string::npos)
        {
            break;
        }
        string range = line.substr(0, pos);
        line = line.substr(pos + 1);

        string begin = range.substr(0, range.find('-'));
        string end = range.substr(range.find('-') + 1);

        unsigned long long b = stoull(begin);
        unsigned long long e = stoull(end);

        for (unsigned long long i = b; i <= e; i++)
        {
            string s = to_string (i);
            for (size_t len = 1; len <= s.length () / 2; len++)
            {
                if (s.length () % len != 0)
                {
                    continue;
                }
                string rep = s.substr(0, len);
                bool possible = true;
                for (size_t times = 0; possible && times < s.length() / len; times++)
                {
                    if (s.substr (times * rep.length (), rep.length ()) != rep)
                    {
                        possible = false;
                    }
                }

                if (possible)
                {
                    tot += i;
                    break;
                }
            }
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