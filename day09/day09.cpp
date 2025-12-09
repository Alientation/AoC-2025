#include "../aoc.hpp"

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void p1 ()
{
    string line;
    vector<pair<U64,U64>> rects;
    while (getline(cin, line))
    {
        size_t pos = line.find(',');
        rects.push_back(pair<U64,U64>(stoull(line.substr(0, pos)), stoull(line.substr(pos + 1))));
    }

    U64 area = 0;
    for (size_t i = 0; i < rects.size (); i++)
    {
        for (size_t j = i + 1; j < rects.size (); j++)
        {
            U64 top_y = max(rects[i].first, rects[j].first);
            U64 bottom_y = min(rects[i].first, rects[j].first);
            U64 left_x = min(rects[i].second, rects[j].second);
            U64 right_x = max(rects[i].second, rects[j].second);

            bool valid = true;

            if (valid)
            {
                area = max(area, (right_x - left_x + 1) * (top_y - bottom_y + 1));
            }
        }
    }
    cout << area;
}

#include <set>
void p2 ()
{
    string line;
    vector<pair<U64,U64>> rects;
    while (getline(cin, line))
    {
        size_t pos = line.find(',');
        rects.push_back(pair<U64,U64>(stoull(line.substr(0, pos)), stoull(line.substr(pos + 1))));
    }

    set<U64> distinct_i;
    set<U64> distinct_j;
    for (auto &r : rects)
    {
        distinct_i.insert(r.first);
        distinct_j.insert(r.second);
    }

    unordered_map<U64,U64> map_i;
    unordered_map<U64,U64> map_j;
    vector<U64> map_inv_i;
    vector<U64> map_inv_j;
    U64 cnt = 0;
    for (U64 i : distinct_i)
    {
        map_i[i] = cnt++;
        map_inv_i.push_back(i);
    }
    cnt = 0;
    for (U64 j : distinct_j)
    {
        map_j[j] = cnt++;
        map_inv_j.push_back(j);
    }

    for (auto &r : rects)
    {
        r.first = map_i[r.first];
        r.second = map_j[r.second];
    }

    char map[map_i.size ()][map_j.size ()];
    for (size_t i = 0; i < map_i.size (); i++)
    {
        for (size_t j = 0; j < map_j.size (); j++)
        {
            map[i][j] = '.';
        }
    }

    auto prev = rects.back ();
    for (auto r : rects)
    {
        int di = (prev.first == r.first) ? 0 : ((prev.first < r.first) ? 1 : -1);
        int dj = (prev.second == r.second) ? 0 : ((prev.second < r.second) ? 1 : -1);

        assert(abs(di) + abs(dj) == 1);

        int i = prev.first;
        int j = prev.second;

        while (i != r.first || j != r.second)
        {
            map[i][j] = '#';
            i += di;
            j += dj;
        }
        prev = r;
    }

    queue <pair<int,int>> q;
    if (rects.size () == 8)
    {
        q.push(pair<int,int>(2, 1));
    }
    else
    {
        q.push(pair<int,int>(1, 128));
    }
    int dirs[4][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    while (!q.empty())
    {
        auto p = q.front ();
        q.pop();
        if (p.first < 0 || p.second < 0 || p.first >= map_i.size () || p.second >= map_j.size () || map[p.first][p.second] == '#') continue;

        map[p.first][p.second] = '#';
        for (int d = 0; d < 4; d++)
        {
            q.push(pair<int,int>(p.first + dirs[d][0], p.second + dirs[d][1]));
        }
    }

    // for (int i = 0; i < map_i.size (); i++)
    // {
    //     for (int j = 0; j < map_j.size (); j++)
    //     {
    //         cout << map[i][j];
    //     }
    //     cout << "\n";
    // }

    U64 counts[map_i.size () + 1][map_j.size () + 1];
    for (int i = 0; i <= map_i.size (); i++)
    {
        for (int j = 0; j <= map_j.size(); j++)
        {
            counts[i][j] = 0;
        }
    }

    counts[1][1] = map[0][0] == '#' ? 1 : 0;
    for (int i = 1; i < map_i.size (); i++)
    {
        counts[i + 1][1] = counts[i][1] + (map[i][0] == '#' ? 1 : 0);
    }

    for (int j = 1; j < map_j.size (); j++)
    {
        counts[1][j + 1] = counts[1][j] + (map[0][j] == '#' ? 1 : 0);
    }

    for (int i = 1; i < map_i.size (); i++)
    {
        for (int j = 1; j < map_j.size (); j++)
        {
            counts[i + 1][j + 1] = counts[i + 1][j] + counts[i][j + 1] - counts[i][j] + (map[i][j] == '#' ? 1 : 0);
        }
    }

    // for (int i = 0; i <= map_i.size (); i++)
    // {
    //     for (int j = 0; j <= map_j.size (); j++)
    //     {
    //         cout << counts[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    U64 area = 0;
    for (size_t i = 0; i < rects.size (); i++)
    {
        for (size_t j = i + 1; j < rects.size (); j++)
        {
            U64 bottom_y = max(rects[i].first, rects[j].first);
            U64 top_y = min(rects[i].first, rects[j].first);
            U64 left_x = min(rects[i].second, rects[j].second);
            U64 right_x = max(rects[i].second, rects[j].second);

            U64 a = (right_x - left_x + 1) * (bottom_y - top_y + 1);
            U64 c = counts[bottom_y + 1][right_x + 1] - counts[bottom_y + 1][left_x] - counts[top_y][right_x + 1] + counts[top_y][left_x];
            U64 actual_area = (map_inv_i[bottom_y] - map_inv_i[top_y] + 1) * (map_inv_j[right_x] - map_inv_j[left_x] + 1);

            // cout << top_y << ", " << left_x << ", " << bottom_y << ", " << right_x << ": " << c << " vs " << a << endl;
            // cout << map_inv_i[top_y] << ", " << map_inv_j[left_x] << ", " << map_inv_i[bottom_y] << ", " << map_inv_j[right_x] << ": " << actual_area << endl;
            if (a == c)
            {
                area = max(area, actual_area);
            }
        }
    }
    cout << area;
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