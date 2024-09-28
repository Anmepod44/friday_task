#include "Party.h"
#include <iostream>

Party::Party(std::string n, Leader l, Candidate c) : name(n), leader(l), candidate(c) {}

void Party::display() const {
    std::cout << "Party: " << name << ", Leader: " << leader.name << ", Leader Popularity: "
              << leader.popularity << std::endl;
    candidate.display();
}
