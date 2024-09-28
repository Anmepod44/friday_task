#include "Candidate.h"
#include <iostream>
#include <cstdlib>

Candidate::Candidate(std::string n, double pop) : name(n), popularity(pop) {
    for (int i = 0; i < 5; ++i) {
        double sig = static_cast<double>(rand()) / RAND_MAX;
        double str = static_cast<double>(rand()) / RAND_MAX;
        stances.emplace_back(sig, str);
    }
}

void Candidate::display() const {
    std::cout << "Candidate: " << name << ", Popularity: " << popularity << std::endl;
    for (size_t i = 0; i < stances.size(); ++i) {
        std::cout << "  Issue " << i + 1 << " - Significance: " << stances[i].significance
                  << ", Strength: " << stances[i].strength << std::endl;
    }
}
