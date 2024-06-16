#include "RandomUtil.h"

#include <chrono>

RandomUtil::RandomUtil(){
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator
}

float RandomUtil::randomFloat(float min, float max){
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX/(max-min));
}
