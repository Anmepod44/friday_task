#ifndef ISSUE_H
#define ISSUE_H

#include <string>

class Issue {
public:
    std::string name;       // Name of the issue
    double significance;     // Significance of the issue (0.0 to 1.0)
    double strength;         // Strength of the stance on the issue (0.0 to 1.0)

    // Constructor
    Issue(std::string n, double sig, double str);
};

#endif // ISSUE_H
