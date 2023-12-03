#pragma once
#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <vector>

class HydrogenProducer{
private:
    bool hydrogen;
public:
    HydrogenProducer();
    ~HydrogenProducer();
    bool hasHydrogen();
    void resetHydrogen();
    void produceHydrogen(int *n, std::vector<HydrogenProducer*>& queue);
};