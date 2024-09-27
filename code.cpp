#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

class Issue {
public:
    std::string name;
    std::string description;
    float significance;
    float strength;

    Issue(const std::string& n, const std::string& desc, float sig, float str)
        : name(n), description(desc), significance(sig), strength(str) {}
};

class Candidate {
private:
    std::string name;
    float popularity;
    std::vector<std::pair<float, float>> stances;

public:
    Candidate(const std::string& n, float pop, const std::vector<std::pair<float, float>>& s)
        : name(n), popularity(pop), stances(s) {}

    float getPopularity() const { return popularity; }
    const std::string& getName() const { return name; }
    const std::vector<std::pair<float, float>>& getStances() const { return stances; }

    void adjustPopularity(float delta) {
        popularity += delta;
    }
};

class Leader {
private:
    std::string name;
    float popularity;

public:
    Leader(const std::string& n, float pop) : name(n), popularity(pop) {}

    float getPopularity() const { return popularity; }
    const std::string& getName() const { return name; }

    void adjustPopularity(float delta) {
        popularity += delta;
    }
};

class Party {
private:
    std::string name;
    Leader leader;
    std::vector<Candidate> candidates;

public:
    Party(const std::string& n, const Leader& l) : name(n), leader(l) {}

    const std::string& getName() const { return name; }
    Leader& getLeader() { return leader; }
    std::vector<Candidate>& getCandidates() { return candidates; }

    void addCandidate(const Candidate& candidate) {
        candidates.push_back(candidate);
    }
};

class Division {
private:
    std::string name;
    float population;
    std::vector<std::pair<float, float>> stances;

public:
    Division(const std::string& n, float pop, const std::vector<std::pair<float, float>>& s)
        : name(n), population(pop), stances(s) {}

    const std::string& getName() const { return name; }
    const std::vector<std::pair<float, float>>& getStances() const { return stances; }

    void adjustStance(int issueIndex, float deltaX, float deltaY) {
        stances[issueIndex].first += deltaX;
        stances[issueIndex].second += deltaY;
    }
};

// Function to calculate cosine similarity between two stances
float cosineSimilarity(std::pair<float, float> stance1, std::pair<float, float> stance2) {
    float dotProduct = stance1.first * stance2.first + stance1.second * stance2.second;
    float magnitude1 = sqrt(stance1.first * stance1.first + stance1.second * stance1.second);
    float magnitude2 = sqrt(stance2.first * stance2.first + stance2.second * stance2.second);
    return dotProduct / (magnitude1 * magnitude2);
}

class ElectionSimulation {
private:
    std::vector<Party> parties;
    std::vector<Division> divisions;

public:
    ElectionSimulation(int numDivisions) {
        // Initialize parties
        parties.push_back(Party("Party A", Leader("Leader A", 0.7)));
        parties.back().addCandidate(Candidate("Candidate A1", 0.6, generateRandomStances()));
        parties.back().addCandidate(Candidate("Candidate A2", 0.5, generateRandomStances()));

        parties.push_back(Party("Party B", Leader("Leader B", 0.65)));
        parties.back().addCandidate(Candidate("Candidate B1", 0.55, generateRandomStances()));
        parties.back().addCandidate(Candidate("Candidate B2", 0.45, generateRandomStances()));

        // Initialize divisions
        for (int i = 1; i <= numDivisions; ++i) {
            float population = 0.5 + (rand() % 1000) / 1000.0f;
            divisions.push_back(Division("Division " + std::to_string(i), population, generateRandomStances()));
        }
    }

    // Utility function to generate random stances
    std::vector<std::pair<float, float>> generateRandomStances() {
        std::vector<std::pair<float, float>> stances;
        for (int i = 0; i < 5; ++i) {
            stances.push_back({ (rand() % 1000) / 1000.0f, (rand() % 1000) / 1000.0f });
        }
        return stances;
    }

    // Simulating the event days
    void simulateEventDay() {
        for (auto& party : parties) {
            for (auto& candidate : party.getCandidates()) {
                if (rand() % 10 < 8) {  // 80% chance of event affecting popularity
                    candidate.adjustPopularity((rand() % 200 - 100) / 1000.0);  // Small adjustments
                }
            }
            if (rand() % 10 < 8) {  // Leader events
                party.getLeader().adjustPopularity((rand() % 200 - 100) / 1000.0);
            }
        }

        for (auto& division : divisions) {
            if (rand() % 10 < 8) {  // 80% chance of events affecting division stance
                for (size_t i = 0; i < division.getStances().size(); ++i) {
                    division.adjustStance(i, (rand() % 200 - 100) / 1000.0, (rand() % 200 - 100) / 1000.0);
                }
            }
        }
    }

    // Function to compute the election results
    void computeElectionResults() {
        for (auto& division : divisions) {
            float maxScore = -1.0;
            std::string winningParty;

            for (auto& party : parties) {
                for (auto& candidate : party.getCandidates()) {
                    float totalScore = 0.0;

                    for (size_t i = 0; i < division.getStances().size(); ++i) {
                        totalScore += 0.6 * cosineSimilarity(candidate.getStances()[i], division.getStances()[i]);
                        totalScore += 0.3 * candidate.getPopularity();
                        totalScore += 0.1 * party.getLeader().getPopularity();
                    }

                    if (totalScore > maxScore) {
                        maxScore = totalScore;
                        winningParty = party.getName();
                    }
                }
            }

            std::cout << "Division " << division.getName() << " was won by " << winningParty << std::endl;
        }
    }

    // Simulate the entire election process
    void runSimulation(int numEventDays) {
        for (int i = 0; i < numEventDays; ++i) {
            simulateEventDay();
        }
        computeElectionResults();
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./APE n m\n";
        return 1;
    }

    int numDivisions = std::stoi(argv[1]);
    int numEventDays = std::stoi(argv[2]);

    srand(static_cast<unsigned int>(time(0)));

    ElectionSimulation simulation(numDivisions);
    simulation.runSimulation(numEventDays);

    return 0;
}
