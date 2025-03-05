#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <ctime>
#include <unistd.h>
#include <chrono>

using namespace std;
long long gridSize = 576;

double getAngle(int x1, int y1, int x2, int y2)
{
    return atan2(y2 - y1, x2 - x1); // Returns the angle between the line (x1, y1) -> (x2, y2)
}

double normalizeAngleDifference(double angle1, double angle2)
{
    double diff = fmod((angle2 - angle1 + M_PI), 2 * M_PI) - M_PI;
    return diff;
}

struct CompareVectors
{
    bool operator()(const vector<double> &a, const vector<double> &b)
    {
        // Min-heap behavior: prioritize lower f-costs
        return a[0] > b[0];
    }
};

double heuristic(int x, int y)
{
    return sqrt(pow(gridSize - 1 - x, 2) + pow(gridSize - 1 - y, 2)); // Euclidean distance to goal (9, 9)
}

int main()
{
    time_t timestamp = time(NULL);
    // Get the current time from the system clock
    auto now = chrono::system_clock::now();

    // Convert the current time to time since epoch
    auto duration = now.time_since_epoch();

    // Convert duration to milliseconds
    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(duration).count();
    cout << milliseconds << endl;

    double i = 5, j = 3, k = 4; // Adjust penalty factors and heuristic scaling
    // i = stepCost, j = momentumPenalty, k = heuristicWeight
    priority_queue<vector<double>, vector<vector<double>>, CompareVectors> minHeap;
    vector<vector<int>> visited(gridSize, vector<int>(gridSize, 0));           // 0 means not visited, 1 means visited
    vector<vector<double>> momentumMap(gridSize, vector<double>(gridSize, 0)); // Store angle (momentum) at each cell
    vector<vector<int>> map(gridSize, vector<int>(gridSize, 0));               // 0 means open, 1 means blocked
    vector<vector<pair<int, int>>> parent(gridSize, vector<pair<int, int>>(gridSize, {-1, -1}));
    vector<vector<double>> seen(gridSize, vector<double>(gridSize, gridSize - 1));
    minHeap.push({0, 0, 0}); // {f-cost, x, y}

    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    while (!minHeap.empty())
    {
        vector<double> cur = minHeap.top();
        minHeap.pop();
        double f = cur[0];
        int x = static_cast<int>(cur[1]), y = static_cast<int>(cur[2]);

        if (x == gridSize - 1 && y == gridSize - 1)
        {
            cout << "Goal reached with cost: " << f << endl;
            break;
        }
        visited[x][y] = 1;

        for (auto &dir : directions)
        {
            int nx = x + dir.first, ny = y + dir.second;

            if (nx >= 0 && nx < gridSize && ny >= 0 && ny < gridSize && map[nx][ny] == 0 && visited[nx][ny] == 0)
            {
                double newAngle = getAngle(x, y, nx, ny);

                // Calculate momentum penalty but scale it down
                double momentumPenalty = abs(normalizeAngleDifference(momentumMap[x][y], newAngle));

                // Use a smaller momentum penalty
                momentumPenalty = momentumPenalty * j;

                double newCost = cur[0] + i + momentumPenalty + heuristic(nx, ny) * k - heuristic(x, y) * k;

                if (newCost < seen[nx][ny])
                {
                    momentumMap[nx][ny] = newAngle;
                    minHeap.push({newCost, static_cast<double>(nx), static_cast<double>(ny)});
                    parent[nx][ny] = {x, y};
                    seen[nx][ny] = newCost; // Update the cost in 'seen' map
                }
            }
        }
    }

    vector<pair<int, int>> path;
    pair<int, int> current = {gridSize - 1, gridSize - 1};
    while (current != make_pair(-1, -1))
    {
        path.push_back(current);
        current = parent[current.first][current.second];
    }

    if (path.empty())
    {
        cout << "No path found!" << endl;
    }
    else
    {
        reverse(path.begin(), path.end());

        cout << "Path: ";
        for (const auto &p : path)
        {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }

    // Get the current time from the system clock

    // Convert duration to milliseconds
    cout << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count() - milliseconds << endl;

    return 0;
}
