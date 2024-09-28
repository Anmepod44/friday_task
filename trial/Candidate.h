#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>
#include <vector>
#include "Stance.h"

class Candidate {
public:
    std::string name;
    double popularity;
    std::vector<Stance> stances;

    Candidate(std::string n, double pop);
    void display() const;
};

#endif