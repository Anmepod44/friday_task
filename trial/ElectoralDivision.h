#ifndef ELECTORALDIVISION_H
#define ELECTORALDIVISION_H

#include <string>
#include <vector>
#include "Stance.h"

class ElectoralDivision {
public:
    std::string name;
    std::vector<Stance> stances;
    double population;

    ElectoralDivision(std::string n);
    void display() const;
};

#endif
