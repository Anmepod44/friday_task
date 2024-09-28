#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Election.h"

int main(int argc, char* argv[]) {
    // Check for correct number of command line arguments
    if (argc != 3) {
        std::cerr << "Usage: ./APE n m (where n: electoral divisions, m: campaign days)" << std::endl;
        return 1;
    }

    // Parse command line arguments
    int n = std::stoi(argv[1]);
    int m = std::stoi(argv[2]);

    // Validate input values for n and m
    if (n < 1 || n > 10 || m < 1 || m > 30) {
        std::cerr << "n must be between 1 and 10, m must be between 1 and 30." << std::endl;
        return 1;
    }

    // Seed for randomness
    srand(static_cast<unsigned>(time(0))); 

    // Initialize the Election with user-defined parameters
    Election election(n, m);

    // Display initial information about parties and the nation
    std::cout << "Initial Party Information: " << std::endl;
    election.displayPartyInfo();
    std::cout << "Initial Nation Information: " << std::endl;
    election.displayNationInfo();
    std::cout << std::endl;

    // Simulate event days and conduct the election
    election.simulateEventDays();
    election.electionDay();

    return 0;
}
