#pragma once

#include <random>

namespace random {

    inline std::mt19937& getRNG() {
        static std::mt19937 rng(std::random_device{}());
        return rng;
    }

    float getRandomFloat(float min, float max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(getRNG());
    }

    int getRandomInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(getRNG());
    }
}
