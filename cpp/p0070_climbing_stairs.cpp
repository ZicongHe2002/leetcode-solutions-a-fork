class Solution {
public:
    int climbStairs(int n) {
        int previous = 1; // Ways to reach step 0.
        int current = 1;  // Ways to reach step 1.
        for (int step = 2; step <= n; ++step) {
            const int next = previous + current;
            previous = current;
            current = next;
        }
        return current;
    }
};
