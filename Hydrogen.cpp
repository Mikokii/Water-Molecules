#include "Hydrogen.hpp"

HydrogenProducer::HydrogenProducer(){
    hydrogen = false;
}

HydrogenProducer::~HydrogenProducer(){}

void HydrogenProducer::produceHydrogen(std::atomic<int> *n, std::vector<HydrogenProducer*>& queue){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g(seed);
    std::uniform_int_distribution<int> rng(0, 10000);
    while (true){
        if (!hydrogen){
            std::this_thread::sleep_for(std::chrono::milliseconds(rng(g)));
            hydrogen = true;
            (*n)+=1;
            std::cout << "H produced " << std::endl;
            queue.push_back(this);
        }
    }
}

void HydrogenProducer::resetHydrogen(){
    hydrogen = false;
}

bool HydrogenProducer::hasHydrogen(){
    return hydrogen;
}