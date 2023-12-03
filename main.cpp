#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "Oxygen.hpp"
#include "Hydrogen.hpp"

void printInfo(int &numberWater, int inputOxygenProducers, int inputHydrogenProducers, std::vector<OxygenProducer> &oxygenProducersVector, std::vector<HydrogenProducer> &hydrogenProducersVector);

int main(){
    int inputOxygenProducers, inputHydrogenProducers;
    int numberOxygen = 0, numberHydrogen = 0, numberWater = 0;
    std::vector<OxygenProducer> oxygenProducersVector;
    std::vector<HydrogenProducer> hydrogenProducersVector;
    std::vector<OxygenProducer*> oxygenQueue;
    std::vector<HydrogenProducer*> hydrogenQueue;
    std::vector<std::thread> oxygenThreads, hydrogenThreads;
    while (true){
        std::cout << "Number of Oxygen Producers: ";
        std::cin >> inputOxygenProducers;
        std::cout << "Number of Hydrogen Producers: ";
        std::cin >> inputHydrogenProducers;
        if (inputOxygenProducers >= 1 && inputHydrogenProducers >= 2){
            break;
        }
        std::cout << "Wrong input. Try again." << std::endl;
    }

    for (int i = 0; i < inputOxygenProducers; i++){
        oxygenProducersVector.push_back(OxygenProducer());
    }
    for (int i = 0; i < inputHydrogenProducers; i++){
        hydrogenProducersVector.push_back(HydrogenProducer());
    }

    for (int i = 0; i < inputOxygenProducers; i++){
        std::thread th([i, &oxygenProducersVector, &numberOxygen, &oxygenQueue]() {
            oxygenProducersVector[i].produceOxygen(&numberOxygen, oxygenQueue);
        });
        oxygenThreads.push_back(std::move(th));
    }
    for (int i = 0; i < inputHydrogenProducers; i++){
        std::thread th([i, &hydrogenProducersVector, &numberHydrogen, &hydrogenQueue]() {
            hydrogenProducersVector[i].produceHydrogen(&numberHydrogen, hydrogenQueue);
        });
        hydrogenThreads.push_back(std::move(th));
    }

    std::thread printThread(printInfo, std::ref(numberWater), inputOxygenProducers, inputHydrogenProducers, std::ref(oxygenProducersVector), std::ref(hydrogenProducersVector));

    while (true){
        if (numberHydrogen >= 2 && numberOxygen >= 1){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            numberWater++;
            numberHydrogen -= 2;
            numberOxygen -= 1;
            for (int i = 0; i < 2; i++){
                hydrogenQueue[0]->resetHydrogen();
                hydrogenQueue.erase(hydrogenQueue.begin());
            }
            oxygenQueue[0]->resetOxygen();
            oxygenQueue.erase(oxygenQueue.begin());
            std::cout << "Number of water molecules: " << numberWater << std::endl;
        }
    }

    for (int i = 0; i < inputOxygenProducers; i++){
        oxygenThreads[i].join();
    }
    for (int i = 0; i < inputHydrogenProducers; i++){
        hydrogenThreads[i].join();
    }
    printThread.join();

    std::cout << "Hydrogen: " << numberHydrogen << " Oxygen: " << numberOxygen << std::endl;

    return 0;
}

void printInfo(int &numberWater, int inputOxygenProducers, int inputHydrogenProducers, std::vector<OxygenProducer> &oxygenProducersVector, std::vector<HydrogenProducer> &hydrogenProducersVector){
    while (true){
        std::cout << "------------------------------------------------------------------------------------" << std::endl;
        std::cout << "Number of water molecules: " << numberWater << std::endl;
        std::cout << "O: ";
        for (int i = 0; i < inputOxygenProducers; i++){
            if (oxygenProducersVector[i].hasOxygen()){
                std::cout << "O ";
            }
            else{
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
        std::cout << "H: ";
        for (int i = 0; i < inputHydrogenProducers; i++){
            if (hydrogenProducersVector[i].hasHydrogen()){
                std::cout << "H ";
            }
            else{
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}