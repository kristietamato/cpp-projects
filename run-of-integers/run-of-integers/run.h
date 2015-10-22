//  run.h

#include <vector>
using namespace std;

#ifndef RUN
#define RUN

class Run // Produce a Run object with a data vector
{
public:
    Run(void) {}; // Empty constructor
    Run(int data) {nList.push_back(data);} // Constructor to initialize nList vector
    Run(vector<int> &data) {nList = data;} // Copy constructor
    
    ~Run() {}; // Destructor
    
    Run mergedRun(Run run); // Merges runs and returns a merged run
    friend Run operator+(const Run &run1, const Run &run2);
    vector<int> getList();
    
private:
    vector<int> nList;
};

#endif
