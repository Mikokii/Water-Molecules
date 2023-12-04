#pragma once
#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <vector>
#include <atomic>

class OxygenProducer{
private:
    bool oxygen;
public:
    OxygenProducer();
    ~OxygenProducer();
    bool hasOxygen();
    void resetOxygen();
    void produceOxygen(std::atomic<int> *n, std::vector<OxygenProducer*>& queue);
};