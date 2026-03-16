#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cout << "========================================" << endl;
    cout << "   BANKER'S DEADLOCK AVOIDANCE SYSTEM   " << endl;
    cout << "========================================" << endl;
    
    cout << "Enter number of processes: "; cin >> n;
    cout << "Enter number of resource types: "; cin >> m;

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> avail(m);

    cout << "\nEnter Allocation Matrix:" << endl;
    for(int i = 0; i < n; i++) 
        for(int j = 0; j < m; j++) cin >> alloc[i][j];

    cout << "\nEnter Max Matrix:" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> max[i][j];
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    cout << "\nEnter Available Resources: ";
    for(int i = 0; i < m; i++) cin >> avail[i];

    // Safety Algorithm
    vector<int> safeSequence;
    vector<bool> finish(n, false);
    vector<int> work = avail;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool possible = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for (int j = 0; j < m; j++) work[j] += alloc[i][j];
                    safeSequence.push_back(i);
                    finish[i] = true;
                }
            }
        }
    }

    cout << "\n----------------------------------------";
    if (safeSequence.size() == (size_t)n) {
        cout << "\nRESULT: SYSTEM IS IN SAFE STATE.";
        cout << "\nSAFE SEQUENCE: ";
        for (int i = 0; i < n; i++) 
            cout << "P" << safeSequence[i] << (i == n - 1 ? "" : " -> ");
        cout << endl;
    } else {
        cout << "\nRESULT: SYSTEM IS IN UNSAFE STATE!";
        cout << "\nNo safe sequence exists. Potential Deadlock detected." << endl;
    }
    cout << "----------------------------------------" << endl;

    return 0;
}