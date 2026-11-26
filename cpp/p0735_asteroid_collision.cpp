#include <vector>

class Solution {
public:
    std::vector<int> asteroidCollision(std::vector<int>& asteroids) {
        std::vector<int> survivors;
        survivors.reserve(asteroids.size());
        for (int value : asteroids) {
            bool alive = true;
            while (alive && value < 0 && !survivors.empty() && survivors.back() > 0) {
                if (survivors.back() < -value) {
                    survivors.pop_back();
                } else {
                    if (survivors.back() == -value) survivors.pop_back();
                    alive = false;
                }
            }
            if (alive) survivors.push_back(value);
        }
        return survivors;
    }
};
