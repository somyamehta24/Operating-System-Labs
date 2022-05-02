
// Somya Mehta
// 190001058

#include <bits/stdc++.h>
using namespace std;
typedef std::vector<int> vi;
typedef std::vector<vector<int>> vvi;
#define F first
#define S second
#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
#define mod 1000000007
#define PB push_back
#define MP make_pair
#define PI 3.14159265358979323846
#define all(a) a.begin(), a.end()
#define mx(a) *max_element(all(a))
#define mn(a) *min_element(all(a))

// Declaring Variables and Functions
void displayArray(vvi matrix);
void displayArray(vi matrix);
vvi allocationMatrix;
vi safeSequ;

int unsafeState;
int numOfProcesses, numOfResources;
pair<int, vi> BankersAlgo();
pair<int, vi> result;
vvi maxNumOfResourcesReq;
vi numOfavailableResources;

// To check safety
bool safetyCheck(vi &processNeed, vi &currently_available) {
    int flag = 1, numOfResources = processNeed.size();
    for (int i = 0; i < numOfResources; i++) {
        // Unsafe condition
        if (processNeed[i] > currently_available[i]) {
            flag = 0;
            break;
        }
    }
    return flag;
}
// To check availability for resources
vi CheckAvailability() {
    vi currentlyAllocatedResources(numOfResources, 0);
    for (int i = 0; i < numOfProcesses; i++) {
        for (int j = 0; j < numOfResources; j++) {
            currentlyAllocatedResources[j] += allocationMatrix[i][j];
        }
    }
    vi res(numOfResources);
    for (int i = 0; i < numOfResources; i++) {
        res[i] = numOfavailableResources[i] - currentlyAllocatedResources[i];
    }
    return res;
}
// Bankers Algorithm
pair<int, vi> BankersAlgo() {
    vi isCompleted(numOfProcesses, 0);
    vvi currReq(numOfProcesses, vi(numOfResources, 0));
    int i = 0;
    int counti = 0;
    int unsafeState = 0;
    vi safeSequ;
    for (int i = 0; i < numOfProcesses; i++) {
        for (int j = 0; j < numOfResources; j++) {
            currReq[i][j] = maxNumOfResourcesReq[i][j] - allocationMatrix[i][j];
        }
    }
    cout << "Currently Available:";
    displayArray(numOfavailableResources);
    while (counti < numOfProcesses) {
        vi currently_available = CheckAvailability();
        cout << "Curr Available:";
        displayArray(currently_available);
        bool flag = 0;
        for (int i = 0; i < numOfProcesses; i++) {
            if (!isCompleted[i] && safetyCheck(currReq[i], currently_available)) {
                flag = 1;
                counti++;
                safeSequ.push_back(i + 1);
                isCompleted[i] = 1;
                for (int j = 0; j < numOfResources; j++) {
                    allocationMatrix[i][j] = 0;
                }
                break;
            }
        }
        if (flag == 0) {
            unsafeState = 1;
            break;
        }
        cout << "Allocation Matrix:\n";
        displayArray(allocationMatrix);
    }
    vi currently_available = CheckAvailability();
    cout << "Curr Available:";
    displayArray(currently_available);
    return {unsafeState, safeSequ};
}
void takeInput() {
    cout << "\n Enter Number of Processes: ";
    cin >> numOfProcesses;
    cout << "\n Enter Number of Resources: ";
    cin >> numOfResources;
    // Creating Allocation Matrix
    allocationMatrix = vvi(numOfProcesses, vi(numOfResources, 0));

    // Creating array for number of available resources
    numOfavailableResources = vi(numOfResources, 0);

    // Creating matrix for max number of required resources by the process
    maxNumOfResourcesReq = vvi(numOfProcesses, vi(numOfResources, 0));
    // Taking input for Allocation Matrix
    cout << "\n Enter Allocation matrix:\n";
    for (int i = 0; i < numOfProcesses; i++) {
        for (int j = 0; j < numOfResources; j++) {
            cin >> allocationMatrix[i][j];
        }
    }
    cout << "\n Enter number of resources Available matrix:\n";
    for (int i = 0; i < numOfResources; i++) {
        cin >> numOfavailableResources[i];
    }
    // Max Need Matrix
    cout << "\nEnter Max number of resources required matrix:\n";
    for (int i = 0; i < numOfProcesses; i++) {
        for (int j = 0; j < numOfResources; j++) {
            cin >> maxNumOfResourcesReq[i][j];
        }
    }
}
int main() {
    takeInput();
    // result from Bankers Algo function
    result = BankersAlgo();
    unsafeState = result.first;
    // If Unsafe state
    if (unsafeState) {
        cout << "\n ********Deadlock********\n\nInadequate number of resources, Deadlock unavoidable\n\n";
        cout << "Allocation Matrix:\n";
        displayArray(allocationMatrix);
        cout << "Available Matrix:\n";
        displayArray(numOfavailableResources);
        cout << "maxNumOfResourcesReq Matrix:\n";
        displayArray(maxNumOfResourcesReq);
        cout << "\n";
    }
    // Safe state
    else {
        cout << "\nSystem is in Safe State";
        // Displaying Safe sequence,Allocation Matrix,maxNumOfResourcesReq matrix and Available Matrix
        cout << "\n Safe sequence : ";
        safeSequ = result.second;
        displayArray(safeSequ);
        cout << "Allocation Matrix:\n";
        displayArray(allocationMatrix);
        cout << "Available Matrix:\n";
        displayArray(numOfavailableResources);
        cout << "maxNumOfResourcesReq Matrix:\n";
        displayArray(maxNumOfResourcesReq);
        cout << "\n";
    }
    return 0;
}
// Display Array
void displayArray(vi matrix) {
    for (auto i : matrix) {
        cout << i << " ";
    }
    cout << endl;
}

// Display 2D Array
void displayArray(vvi matrix) {
    for (auto i : matrix) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}