#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib> // for abs()

using namespace std;

double getAngle(int x1, int y1, int x2, int y2) {
    return atan2(y2 - y1, x2 - x1);  // Returns the angle between the line (x1, y1) -> (x2, y2)
}

double normalizeAngleDifference(double angle1, double angle2) {
    double diff = fmod((angle2 - angle1 + M_PI), 2 * M_PI) - M_PI;
    return diff;
}

struct CompareVectors {
    bool operator()(const vector<double>& a, const vector<double>& b) {
        // Min-heap behavior: prioritize lower f-costs
        return a[0] > b[0];
    }
};

double heuristic(int x, int y) {
    return sqrt(pow(9 - x, 2) + pow(9 - y, 2));  // Euclidean distance to goal (9, 9)
}

int main() {
    double i = 5, j = 3, k = 4;  // Adjust penalty factors and heuristic scaling
    // i = stepCost, j = momentumPenalty, k = heuristicWeight
    priority_queue<vector<double>, vector<vector<double>>, CompareVectors> minHeap;
    vector<vector<int>> visited(10, vector<int>(10, 0));  // 0 means not visited, 1 means visited
    vector<vector<double>> momentumMap(10, vector<double>(10, 0));  // Store angle (momentum) at each cell
    vector<vector<int>> map;  // 0 means open, 1 means blocked
    map = { 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    vector<vector<pair<int, int>>> parent(10, vector<pair<int, int>>(10, {-1, -1}));
    vector<vector<double>> seen(10, vector<double>(10, 99));
    minHeap.push({0, 0, 0});  // {f-cost, x, y}

    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}, 
                                          {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    
    while (!minHeap.empty()) {
        vector<double> cur = minHeap.top();
        minHeap.pop();
        double f = cur[0];
        int x = static_cast<int>(cur[1]), y = static_cast<int>(cur[2]);

        if (x == 9 && y == 9) {
            cout << "Goal reached with cost: " << f << endl;
            break;
        }
        visited[x][y] = 1;

        for (auto& dir : directions) {
            int nx = x + dir.first, ny = y + dir.second;

            if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && map[nx][ny] == 0 && visited[nx][ny] == 0) {
                double newAngle = getAngle(x, y, nx, ny);

                // Calculate momentum penalty but scale it down
                double momentumPenalty = abs(normalizeAngleDifference(momentumMap[x][y], newAngle));

                // Use a smaller momentum penalty
                momentumPenalty = momentumPenalty * j;

                double newCost = cur[0] + i + momentumPenalty + heuristic(nx, ny) * k - heuristic(x, y) * k;

                if (newCost < seen[nx][ny]) {
                    momentumMap[nx][ny] = newAngle;
                    minHeap.push({newCost, static_cast<double>(nx), static_cast<double>(ny)});
                    parent[nx][ny] = {x, y};
                    seen[nx][ny] = newCost;  // Update the cost in 'seen' map
                }
            }
        }
    }

    vector<pair<int, int>> path;
    pair<int, int> current = {9, 9};
    while (current != make_pair(-1, -1)) {
        path.push_back(current);
        current = parent[current.first][current.second];
    }

    if (path.empty()) {
        cout << "No path found!" << endl;
    } else {
        reverse(path.begin(), path.end());

        cout << "Path: ";
        for (const auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }

    return 0;
}
