#include "Oxygen.hpp"

OxygenProducer::OxygenProducer(){
    oxygen = false;
}

OxygenProducer::~OxygenProducer(){}

void OxygenProducer::produceOxygen(int *n, std::vector<OxygenProducer*>& queue){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g(seed);
    std::uniform_int_distribution<int> rng(0, 10000);
    while (true) {
        if (!oxygen){
        std::this_thread::sleep_for(std::chrono::milliseconds(rng(g)));
        oxygen = true;
        (*n)++;
        std::cout << "O produced" << std::endl;
        queue.push_back(this);
        }   
    }
}

void OxygenProducer::resetOxygen(){
    oxygen = false;
}

bool OxygenProducer::hasOxygen(){
    return oxygen;
}