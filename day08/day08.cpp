#include "../aoc.hpp"

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void p1 ()
{
    string line;
    vector<vector<U64>> positions;
    while (getline (cin, line))
    {
        vector<U64> xyz;
        size_t p = 0;
        while (line.find_first_not_of(',', p) != string::npos)
        {
            size_t next = line.find_first_of(',', p);
            if (next == string::npos) next = line.size ();
            xyz.push_back(stoull(line.substr(p, next - p)));
            p = next + 1;
        }

        positions.push_back(xyz);
    }

    vector<pair<U64, int>> distances;
    vector<pair<int,int>> ids;

    for (int i = 0; i < positions.size (); i++)
    {
        for (int j = i + 1; j < positions.size (); j++)
        {
            U64 dx = (positions[i][0] - positions[j][0]) * (positions[i][0] - positions[j][0]);
            U64 dy = (positions[i][1] - positions[j][1]) * (positions[i][1] - positions[j][1]);
            U64 dz = (positions[i][2] - positions[j][2]) * (positions[i][2] - positions[j][2]);
            U64 distsqr = dx + dy + dz;
            distances.push_back(pair<U64, int>(distsqr, ids.size ()));
            ids.push_back(pair<int,int>(i, j));
        }
    }

    U64 tot = 1;
    sort(distances.begin (), distances.end ());

    int parents[positions.size()];
    vector<U64> counts;
    for (int i = 0; i < positions.size (); i++)
    {
        parents[i] = i;
        counts.push_back(0);
    }

    int takecnt = (positions.size () == 20) ? 10 : 1000;
    for (int take = 0; take < takecnt; take++)
    {
        int id = distances[take].second;

        int parent_1 = ids[id].first;
        int parent_2 = ids[id].second;
        while (parent_1 != parents[parent_1])
        {
            parent_1 = parents[parent_1];
        }

        while (parent_2 != parents[parent_2])
        {
            parent_2 = parents[parent_2];
        }

        parents[parent_2] = parent_1;
    }

    for (int i = 0; i < positions.size (); i++)
    {
        int parent = i;
        while (parents[parent] != parent)
        {
            parent = parents[parent];
        }

        counts[parent]++;

    }

    sort(counts.begin(), counts.end());

    for (int i = counts.size () - 1; i >= counts.size () - 3; i--)
    {
        tot *= counts[i];
    }

    cout << tot;
}


void p2 ()
{
    string line;
    vector<vector<U64>> positions;
    while (getline (cin, line))
    {
        vector<U64> xyz;
        size_t p = 0;
        while (line.find_first_not_of(',', p) != string::npos)
        {
            size_t next = line.find_first_of(',', p);
            if (next == string::npos) next = line.size ();
            xyz.push_back(stoull(line.substr(p, next - p)));
            p = next + 1;
        }

        positions.push_back(xyz);
    }

    vector<pair<U64, int>> distances;
    vector<pair<int,int>> ids;

    for (int i = 0; i < positions.size (); i++)
    {
        for (int j = i + 1; j < positions.size (); j++)
        {
            U64 dx = (positions[i][0] - positions[j][0]) * (positions[i][0] - positions[j][0]);
            U64 dy = (positions[i][1] - positions[j][1]) * (positions[i][1] - positions[j][1]);
            U64 dz = (positions[i][2] - positions[j][2]) * (positions[i][2] - positions[j][2]);
            U64 distsqr = dx + dy + dz;
            distances.push_back(pair<U64, int>(distsqr, ids.size ()));
            ids.push_back(pair<int,int>(i, j));
        }
    }

    sort(distances.begin (), distances.end ());

    int parents[positions.size()];
    for (int i = 0; i < positions.size (); i++)
    {
        parents[i] = i;
    }

    int last1 = 0;
    int last2 = 0;
    for (int take = 0; take < distances.size (); take++)
    {
        int id = distances[take].second;

        int parent_1 = ids[id].first;
        int parent_2 = ids[id].second;
        while (parent_1 != parents[parent_1])
        {
            parent_1 = parents[parent_1];
        }

        while (parent_2 != parents[parent_2])
        {
            parent_2 = parents[parent_2];
        }

        if (parent_2 != parent_1)
        {
            parents[parent_2] = parent_1;
            last1 = ids[id].first;
            last2 = ids[id].second;
        }
    }

    cout << positions[last1][0] * positions[last2][0];
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