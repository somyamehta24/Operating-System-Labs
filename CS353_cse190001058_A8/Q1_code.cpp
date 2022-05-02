// 190001058
// Somya Mehta
#include <bits/stdc++.h>
using namespace std;

void FIFO(int noOfFrames, int n, vector<int> s) {
    vector<int> arr(noOfFrames);  // queue
    unordered_map<int, int> mp;
    int curr = 0, noOfPageFaults = 0, first = 0;  // curr is pointer of the queue
    for (int i = 0; i < n; i++) {
        // check if it's a page hit or not
        if (mp.find(s[i]) == mp.end()) {
            noOfPageFaults++;
            if (mp.size() == noOfFrames) {
                mp.erase(arr[first]);
                first = (first + 1) % noOfFrames;
            }
            arr[curr] = s[i];
            curr = (curr + 1) % noOfFrames;
            mp[s[i]]++;
        } else {
        }
    }
    cout << "No of Page faults in First in First Out Page Replacement Algorithm\n";
    cout << noOfPageFaults << "\n";
}
void LRU(int noOfFrames, int n, vector<int> s) {
    set<pair<int, int>> leastRecent;
    unordered_map<int, int> mp;
    int noOfPageFaults = 0;
    // cout << "1111\n\n";
    for (int i = 0; i < n; i++) {
        // check if it's a page hit or not
        // cout << i << "\n";
        if (mp.find(s[i]) == mp.end()) {
            noOfPageFaults++;
            if (leastRecent.size() == noOfFrames) {
                pair<int, int> p = *leastRecent.begin();
                mp.erase(p.second);
                leastRecent.erase(p);
            }
            mp[s[i]] = i;
            leastRecent.insert({i, s[i]});
        } else {
            leastRecent.erase(leastRecent.find({mp[s[i]], s[i]}));
            mp[s[i]] = i;
            leastRecent.insert({i, s[i]});
        }
    }
    cout << "No of Page faults in LRU Page Replacement Algorithm\n";
    cout << noOfPageFaults << "\n";
}
int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    cout << "Number of Frames\n";
    int n, noOfFrames;
    cin >> noOfFrames;
    cout << "Enter number of references\n";
    cin >> n;
    cout << "Enter the string\n";
    vector<int> s(n);
    for (int i = 0; i < n; i++)
        cin >> s[i];
    FIFO(noOfFrames, n, s);  // First In First Out
    LRU(noOfFrames, n, s);   // least recently used page replacement algo
}