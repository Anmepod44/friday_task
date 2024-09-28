#include "ElectoralDivision.h"
#include <iostream>
#include <cstdlib>

ElectoralDivision::ElectoralDivision(std::string n) : name(n), population(0.5 + static_cast<double>(rand()) / RAND_MAX) {
    // Hardcoding the significance and strength for each national issue
    stances.emplace_back(0.9, 0.8); // Issue 1: Healthcare
    stances.emplace_back(0.8, 0.6); // Issue 2: Education
    stances.emplace_back(0.7, 0.9); // Issue 3: Climate Change
    stances.emplace_back(0.6, 0.5); // Issue 4: Economy
    stances.emplace_back(0.5, 0.7); // Issue 5: Immigration
}

void ElectoralDivision::display() const {
    std::cout << "Division: " << name << ", Population: " << population << " million" << std::endl;
    std::cout << "National Issues:" << std::endl;
    std::cout << "  1. Healthcare" << std::endl;
    std::cout << "  2. Education" << std::endl;
    std::cout << "  3. Climate Change" << std::endl;
    std::cout << "  4. Economy" << std::endl;
    std::cout << "  5. Immigration" << std::endl;

    for (size_t i = 0; i < stances.size(); ++i) {
        std::cout << "  Issue " << i + 1 << " - Significance: " << stances[i].significance
                  << ", Strength: " << stances[i].strength << std::endl;
    }
}