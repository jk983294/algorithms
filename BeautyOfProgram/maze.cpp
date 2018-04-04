#include "MyUtility.h"

struct coordinate {
    int x;
    int y;
};

bool operator==(const coordinate& lhs, const coordinate& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }

bool operator!=(const coordinate& lhs, const coordinate& rhs) { return !(operator==(lhs, rhs)); }

ostream& operator<<(ostream& os, const coordinate& c) {
    os << c.x << "," << c.y;
    return os;
}

int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void path_dfs(const vector<vector<int>>& maze, const coordinate& start, const coordinate& end);
void path_bfs(const vector<vector<int>>& maze, const coordinate& start, const coordinate& end);

int main() {
    vector<vector<int>> maze{{1, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 1}, {1, 0, 1, 0, 0, 1},
                             {1, 0, 0, 1, 0, 1}, {1, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1}};

    coordinate start{1, 1}, end{1, 4};

    path_dfs(maze, start, end);
    path_bfs(maze, start, end);
    return 0;
}

void path_bfs(const vector<vector<int>>& maze, const coordinate& start, const coordinate& end) {
    int n = maze.size(), m = maze[0].size();
    vector<vector<int>> visited;
    make_two_dimension_vector(n, m, 0, visited);
    queue<coordinate> q;
    q.push(start);
    visited[start.x][start.y] = 1;

    while (!q.empty()) {
        coordinate current = q.front();
        q.pop();
        int depth = visited[current.x][current.y];

        for (int i = 0; i < 4; ++i) {
            int nextX = current.x + directions[i][0];
            int nextY = current.y + directions[i][1];
            if (maze[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
                q.push({nextX, nextY});
                visited[nextX][nextY] = depth + 1;
            }
        }
    }

    if (visited[end.x][end.y] > 0) {
        vector<coordinate> result;
        coordinate current = end;
        result.push_back(current);
        while (current != start) {
            int depth = visited[current.x][current.y];

            for (int i = 0; i < 4; ++i) {
                int nextX = current.x + directions[i][0];
                int nextY = current.y + directions[i][1];
                if (visited[nextX][nextY] == depth - 1) {
                    current = {nextX, nextY};
                    result.push_back(current);
                    break;
                }
            }
        }

        reverse(result.begin(), result.end());

        cout << "path:\n";
        cout << result << endl;
    } else {
        cout << "path not found\n";
    }
}

void path_dfs(const vector<vector<int>>& maze, const coordinate& start, const coordinate& end) {
    int n = maze.size(), m = maze[0].size();
    vector<vector<int>> visited;
    make_two_dimension_vector(n, m, 0, visited);
    stack<coordinate> s;
    s.push(start);
    visited[start.x][start.y] = 1;

    while (!s.empty()) {
        coordinate current = s.top();
        if (current == end) break;

        bool found = false;
        for (int i = 0; i < 4; ++i) {
            int nextX = current.x + directions[i][0];
            int nextY = current.y + directions[i][1];
            if (maze[nextX][nextY] == 0 && visited[nextX][nextY] == 0) {
                s.push({nextX, nextY});
                visited[nextX][nextY] = 1;
                found = true;
                break;
            }
        }

        if (!found) {
            s.pop();
        }
    }

    if (!s.empty()) {
        vector<coordinate> result;
        while (!s.empty()) {
            result.push_back(s.top());
            s.pop();
        }
        reverse(result.begin(), result.end());

        cout << "path:\n";
        cout << result << endl;
    } else {
        cout << "path not found\n";
    }
}
