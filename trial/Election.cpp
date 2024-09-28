#include "Election.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

Election::Election(int n, int days) : m(days) {
    // Initializing parties
    for (int i = 0; i < 3; ++i) {
        Leader leader("Leader " + std::to_string(i + 1), static_cast<double>(rand()) / RAND_MAX);
        Candidate candidate("Candidate " + std::to_string(i + 1), static_cast<double>(rand()) / RAND_MAX);
        parties.emplace_back("Party " + std::to_string(i + 1), leader, candidate);
    }

    // Initializing electoral divisions
    for (int i = 0; i < n; ++i) {
        divisions.emplace_back("Division " + std::to_string(i + 1));
    }
}

void Election::displayPartyInfo() const {
    for (const auto& party : parties) {
        party.display();
    }
}

void Election::displayNationInfo() const {
    for (const auto& division : divisions) {
        division.display();
    }
}

void Election::simulateEventDays() {
    for (int day = 1; day <= m; ++day) {
        std::cout << "Event Day: " << day << std::endl;
        for (auto& division : divisions) {
            // Simulating events with probabilities
            double event = static_cast<double>(rand()) / RAND_MAX;
            if (event < 0.2) continue; // No event

            // Random events impact popularity and stances
            if (event < 0.4) {
                parties[0].candidate.popularity += static_cast<double>(rand()) / (RAND_MAX / 0.1);
            } else if (event < 0.6) {
                parties[1].candidate.popularity += static_cast<double>(rand()) / (RAND_MAX / 0.1);
            } else if (event < 0.8) {
                // Leader popularity impact
                parties[0].leader.popularity += static_cast<double>(rand()) / (RAND_MAX / 0.1);
            } else {
                // Issues-related event
                for (auto& stance : division.stances) {
                    stance.significance += static_cast<double>(rand()) / (RAND_MAX / 0.1);
                }
            }

            std::cout << "  In " << division.name << " - Events Occurred" << std::endl;
        }

        displayPartyInfo();
        displayNationInfo();
        std::cout << std::endl;
    }
}

void Election::electionDay() {
    std::vector<int> wins(3, 0);
    for (const auto& division : divisions) {
        double maxScore = -1;
        int winnerIndex = -1;

        for (size_t i = 0; i < parties.size(); ++i) {
            double stanceFactor = 0;
            for (size_t j = 0; j < 5; ++j) {
                double cosSim = (parties[i].candidate.stances[j].significance * division.stances[j].significance +
                                 parties[i].candidate.stances[j].strength * division.stances[j].strength) /
                                (sqrt(pow(parties[i].candidate.stances[j].significance, 2) + 
                                      pow(parties[i].candidate.stances[j].strength, 2)) *
                                 sqrt(pow(division.stances[j].significance, 2) + 
                                      pow(division.stances[j].strength, 2)));
                stanceFactor += cosSim;
            }
            stanceFactor /= 5;

            double populationFactor = stanceFactor * division.population;
            double candidatePopularity = parties[i].candidate.popularity;
            double leaderPopularity = parties[i].leader.popularity;

            double score = 0.5 * populationFactor + 0.3 * candidatePopularity + 0.2 * leaderPopularity;

            if (score > maxScore) {
                maxScore = score;
                winnerIndex = i;
            }
        }

        if (winnerIndex != -1) {
            wins[winnerIndex]++;
            std::cout << "Winner of " << division.name << ": " << parties[winnerIndex].name << std::endl;
        }
    }

    // Display election results
    std::cout << "Election Results:" << std::endl;
    for (size_t i = 0; i < parties.size(); ++i) {
        std::cout << parties[i].name << ": " << wins[i] << " divisions won" << std::endl;
    }
}
