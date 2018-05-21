#include "MyUtility.h"

float ExpectedCrabWalk(int numSteps);  // optiver interview question 3
float ExpectedCrabWalk1(int numSteps);

int main() {
    cout << ExpectedCrabWalk(1) << " <--> " << ExpectedCrabWalk1(1) << endl;
    cout << ExpectedCrabWalk(5) << " <--> " << ExpectedCrabWalk1(5) << endl;
    return 0;
}

/**
 * one crab sitting at (0, 0), each step it can go north/south/east/west/sleep by same probability(1/5)
 * if sleep, it will not move any more
 * calculate expected walk distance
 * 5 branch tree, level order iterator
 */
constexpr float oneStepProb = 0.2;

struct point {
    float x;
    float y;
    int step;
    float probability;

    float distance() { return sqrt(x * x + y * y); }

    float expectedValue() { return distance() * probability; }
};

float ExpectedCrabWalk(int numSteps) {
    float expected = 0;
    queue<point> q;
    q.push({0, 0, 0, 1});
    while (!q.empty()) {
        point p = q.front();
        q.pop();
        if (p.step == numSteps) {
            expected += p.expectedValue();
        } else {
            float prob = p.probability * oneStepProb;
            int step = p.step + 1;
            q.push({p.x + 1, p.y, step, prob});
            q.push({p.x - 1, p.y, step, prob});
            q.push({p.x, p.y + 1, step, prob});
            q.push({p.x, p.y - 1, step, prob});
            expected += prob * p.distance();
        }
    }
    return expected;
}

int combination(int n, int m) {
    if (m == 0 || n == 0) return 1;
    int a = 1, b = 1;
    for (int i = 1; i <= n; ++i) {
        if (i > m) a *= i;
        if (i <= n - m) {
            b *= i;
        }
    }
    return a / b;
}

int possible_path_count(int steps, int x, int y) {
    x = abs(x);
    y = abs(y);
    int count = 0;
    // at least move (x + y), the rest can choose 2 * i go x direction, (steps - x - y - 2 * i) go y direction
    for (int i = 0; i <= (steps - x - y) / 2; ++i) {
        /**
         * total steps, must x left, y up
         * choose x + i left from steps
         * choose i right from steps - (x + i)
         * choose y + [(steps - x - y) / 2 - i] up from steps - (x + i) - i
         */
        count += combination(steps, x + i) * combination(steps - x - i, i) *
                 combination(steps - x - 2 * i, y + (steps - x - y - 2 * i) / 2);
    }
    return count;
}

float ExpectedCrabWalk1(int numSteps) {
    float expected = 0;
    for (int i = -numSteps; i <= numSteps; ++i) {
        int jMax = numSteps - abs(i);
        for (int j = -jMax; j <= jMax; ++j) {
            int minimumStep = abs(i) + abs(j);
            float distance = sqrt(static_cast<float>(i * i + j * j));
            do {
                if (minimumStep == numSteps) {
                    expected += distance * pow(oneStepProb, minimumStep) * possible_path_count(minimumStep, i, j);
                } else {
                    // minimumStep + 1 means move minimumStep plus sleep chance
                    expected += distance * pow(oneStepProb, minimumStep + 1) * possible_path_count(minimumStep, i, j);
                }

                minimumStep += 2;
            } while (minimumStep <= numSteps);
        }
    }
    return expected;
}
