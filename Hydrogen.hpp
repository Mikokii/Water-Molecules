#pragma once
#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <vector>
#include <atomic>

class HydrogenProducer{
private:
    bool hydrogen;
public:
    HydrogenProducer();
    ~HydrogenProducer();
    bool hasHydrogen();
    void resetHydrogen();
    void produceHydrogen(std::atomic<int> *n, std::vector<HydrogenProducer*>& queue);
};