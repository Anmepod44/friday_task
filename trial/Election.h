#ifndef ELECTION_H
#define ELECTION_H

#include <vector>
#include "Party.h"
#include "ElectoralDivision.h"

class Election {
public:
    std::vector<Party> parties;
    std::vector<ElectoralDivision> divisions;
    int m;

    Election(int n, int days);
    void displayPartyInfo() const;
    void displayNationInfo() const;
    void simulateEventDays();
    void electionDay();
};

#endif
