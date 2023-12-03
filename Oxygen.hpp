#pragma once
#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <vector>

class OxygenProducer{
private:
    bool oxygen;
public:
    OxygenProducer();
    ~OxygenProducer();
    bool hasOxygen();
    void resetOxygen();
    void produceOxygen(int *n, std::vector<OxygenProducer*>& queue);
};