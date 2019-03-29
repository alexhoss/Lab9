#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <set>
/**
 * I also thought about doing this with a multi map, but I think this is cleaner
 */

using namespace std;

void printMap(map<string, set<string>> &locHistory);

void printPeopleVisited(map<string, set<string>> &locHistory, const string &a, const string &b);

void printPeopleNotVisited(map<string, set<string>> &locHistory, const string &a, const string &b);

void
printPeopleVisitedNotVisited(map<string, set<string>> &locHistory, const string &a, const string &b, const string &c,
                             const string &d);

bool visited(set<string> &locHistory, const string &a);

void removeSuspiciousPeople(map<string, set<string>> &locHistory, set<string> &locations);

int main() {

    ifstream file;
    file.open("../peoplePlaces.txt");
    string line;

    map<string, set<string>> locHistory;
    set<string> locations;


    while (getline(file, line)) {
        istringstream iss(line);
        string personTemp;
        iss >> personTemp;
        string locTemp;

        set<string> locationsVisited;

        while (iss >> locTemp) {
            locationsVisited.insert(locTemp);
            locations.insert(locTemp);

        }
        locHistory.insert(make_pair(personTemp, locationsVisited));

    }

    printMap(locHistory);
    printPeopleVisited(locHistory, "Krusty-Burger", "Tavern");
    printPeopleNotVisited(locHistory, "Krusty-Burger", "Home");
    printPeopleVisitedNotVisited(locHistory, "Krusty-Burger", "School", "Tavern", "Home");
    removeSuspiciousPeople(locHistory, locations);
    printMap(locHistory);

    return 0;
}

// print the people that have visited a and b
void printPeopleVisited(map<string, set<string>> &locHistory, const string &a, const string &b) {
    cout << "\nThose who did visit " << a << " and " << b << endl;
    for (auto it = locHistory.begin(); it != locHistory.end(); ++it) {
        if ((visited(it->second, a)) && visited(it->second, b)) cout << it->first << endl;
    }
}
//print people that have not visited a and b
void printPeopleNotVisited(map<string, set<string>> &locHistory, const string &a, const string &b) {
    cout << "Those who did not visit " << a << " and not " << b << endl;
    for (auto it = locHistory.begin(); it != locHistory.end(); ++it) {
        if (!(visited(it->second, a)) && !(visited(it->second, b))) cout << it->first << endl;
    }
}

//print people that have visited a and b but not c and d
void
printPeopleVisitedNotVisited(map<string, set<string>> &locHistory, const string &a, const string &b, const string &c,
                             const string &d) {
    cout << "\nThose who visited " << a << " and " << b << " and NOT " << c << " or " << d << endl;
    for (auto it = locHistory.begin(); it != locHistory.end(); ++it) {
        if (((visited(it->second, a)) && (visited(it->second, b))) &&
            (!(visited(it->second, c)) && !(visited(it->second, d))))
            cout << it->first << endl;
    }
}


//return true if a is found in set
bool visited(set<string> &locHistory, const string &a) {
    auto it = find(locHistory.begin(), locHistory.end(), a);
    return (it != locHistory.end());
}

// print the whole map
void printMap(map<string, set<string>> &locHistory) {
    cout << "\nEverybody in the city\n------------------" << endl;
    for (auto it = locHistory.begin(); it != locHistory.end(); ++it) {
        cout << it->first << endl;
    }
}
// erases people from the map that have the same location history as the master location set
void removeSuspiciousPeople(map<string, set<string>> &locHistory, set<string> &locations) {

    cout << "\nRemoving people that are too active" << endl;

    for (auto it = locHistory.begin(); it != locHistory.end(); ++it) {

        if (it->second == locations) {
            cout << "erasing: " << it->first << endl;
            locHistory.erase(it);
        }

    }
}