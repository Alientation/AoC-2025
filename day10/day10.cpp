#include "../aoc.hpp"

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void p1 ()
{
    U64 tot = 0;
    string line;
    while (getline (cin, line))
    {
        // cout << line << endl;

        const string part1 = line.substr(1, line.find(']') - 1);
        U32 desired_state = 0;
        const int nlights = part1.size ();
        for (int i = 0; i < nlights; i++)
        {
            if (part1[i] == '#') desired_state |= (1 << i);
        }
        // cout << "TARGET STATE: " << bitset<32>(desired_state) << endl;

        const string part3 = line.substr(line.find ('{') + 1, line.length () - line.find ('{') - 2);

        vector<vector<U16>> buttons;
        size_t pos = 0 ;
        while (line.find_first_of ('(', pos) != string::npos)
        {
            pos = line.find_first_of ('(', pos) + 1;
            string p = line.substr(pos, line.find_first_of (')', pos) - pos);
            vector<U16> b;

            size_t loc = 0;
            while (p.find_first_not_of (',', loc) != string::npos)
            {
                loc = p.find_first_not_of (',', loc);
                b.push_back (stoul (p.substr(loc)));
                loc = p.find_first_of (',', loc);

                // cout << b.back () << ", ";
            }
            // cout << "\n";
            buttons.push_back (b);
        }

        unordered_set<U32> visited;
        queue<pair<U32, U32>> q;
        q.push (pair<U32,U32>(0, 0));
        while (!q.empty ())
        {
            auto p = q.front ();
            q.pop ();

            if (p.first == desired_state)
            {
                tot += p.second;
                // cout << ">> " << p.second << endl;
                break;
            }

            if (visited.find (p.first) != visited.end ())
            {
                continue;
            }

            // cout << ">> " << bitset<32>(p.first) << endl;
            visited.emplace(p.first);

            for (auto &b : buttons)
            {
                U32 s = p.first;
                for (U16 l : b)
                {
                    s ^= (1 << l);
                }
                q.push (pair<U32, U32>(s, p.second + 1));
            }
        }
    }
    cout << tot;
}


void p2 ()
{
    U64 tot = 0;
    string line;

    vector<vector<vector<U16>>> all_buttons;
    vector<vector<U16>> all_volts;
    while (getline (cin, line))
    {
        const string part1 = line.substr(1, line.find(']') - 1);
        const int nlights = part1.size ();

        const string part3 = line.substr(line.find ('{') + 1, line.length () - line.find ('{') - 2);
        size_t ploc = 0;
        vector <U16> volts;
        while (part3.find_first_not_of (',', ploc) != string::npos)
        {
            ploc = part3.find_first_not_of (',', ploc);
            volts.push_back (stoul (part3.substr(ploc)));
            ploc = part3.find_first_of (',', ploc);
        }
        all_volts.push_back (volts);

        vector<vector<U16>> buttons;
        size_t pos = 0 ;
        while (line.find_first_of ('(', pos) != string::npos)
        {
            pos = line.find_first_of ('(', pos) + 1;
            string p = line.substr(pos, line.find_first_of (')', pos) - pos);
            vector<U16> b;

            size_t loc = 0;
            while (p.find_first_not_of (',', loc) != string::npos)
            {
                loc = p.find_first_not_of (',', loc);
                b.push_back (stoul (p.substr(loc)));
                loc = p.find_first_of (',', loc);
            }
            buttons.push_back (b);
        }
        all_buttons.push_back(buttons);

/*
Minimize[{-(3x + 2y),
  2x + y <= 8 &&
  x + 2y <= 7 &&
  x >= 0 && y >= 0},
 {x, y} \[Element] Integers]
*/
    }

    cout << "Minimize[{";
    size_t variable_i = 0;
    bool first = true;
    for (auto &buttons : all_buttons)
    {
        for (auto &b : buttons)
        {
            if (!first) cout << " + ";
            cout << "x" << variable_i;
            first = false;
            variable_i++;
        }
    }
    cout << ",\n";

    variable_i = 0;
    for (size_t vi = 0; vi < all_volts.size (); vi++)
    {
        auto &volts = all_volts[vi];
        auto &buttons = all_buttons[vi];
        for (int i = 0; i < volts.size (); i++)
        {
            size_t variable_i_temp = variable_i;
            bool plusfirst = true;
            for (size_t bi = 0; bi < buttons.size (); bi++)
            {
                bool found = false;
                for (auto l : buttons[bi])
                {
                    if (l == i)
                    {
                        found = true;
                        break;
                    }
                }

                if (found)
                {
                    if (!plusfirst) cout << " + ";
                    cout << "x" << variable_i_temp;
                    plusfirst = false;
                }
                variable_i_temp++;
            }

            cout << " == " << volts[i] << " &&\n";
        }

        for (size_t i = 0; i < buttons.size (); i++)
        {
            cout << "x" << (variable_i + i) << " >= 0";
            if (i + 1 != buttons.size ()) cout << " && ";
        }

        if (vi + 1 != all_volts.size ()) cout << " &&\n";

        variable_i += buttons.size ();
    }

    cout << "},\n{";

    variable_i = 0;
    first = true;
    for (auto &buttons : all_buttons)
    {
        for (auto &b : buttons)
        {
            if (!first) cout << ", ";
            cout << "x" << variable_i;
            first = false;
            variable_i++;
        }
    }
    cout << "} \\[Element] Integers]\n";
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