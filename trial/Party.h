#ifndef PARTY_H
#define PARTY_H

#include <string>
#include "Leader.h"
#include "Candidate.h"

class Party {
public:
    std::string name;
    Leader leader;
    Candidate candidate;

    Party(std::string n, Leader l, Candidate c);
    void display() const;
};

#endif
