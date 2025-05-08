// Grade Book.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Constants
const int MAX_STUDENTS = 100;
const int MAX_SCORES = 10; // max test scores per student
const int NUM_SCORES = 5;  // this should match actual number of scores per line in your file

// Function prototypes
int readData(ifstream&, string[], int[][MAX_SCORES]);
void calculateAverages(const int[][MAX_SCORES], double[], int);
char getLetterGrade(double);
void printReport(const string[], const double[], int);

// Main function
int main() {
    string names[MAX_STUDENTS];
    int scores[MAX_STUDENTS][MAX_SCORES];
    double averages[MAX_STUDENTS];
    int studentCount;

    ifstream inFile("grades.txt");
    if (!inFile) {
        cout << "Error: Could not open file.\n";
        return 1;
    }

    studentCount = readData(inFile, names, scores);
    calculateAverages(scores, averages, studentCount);
    printReport(names, averages, studentCount);

    inFile.close();
    return 0;
}

// Reads student names and scores into arrays
int readData(ifstream& file, string names[], int scores[][MAX_SCORES]) {
    int count = 0;
    while (count < MAX_STUDENTS && file >> names[count]) {
        for (int i = 0; i < NUM_SCORES; i++) {
            file >> scores[count][i];
        }
        count++;
    }
    return count;
}

// Calculates average for each student
void calculateAverages(const int scores[][MAX_SCORES], double averages[], int studentCount) {
    for (int i = 0; i < studentCount; i++) {
        int sum = 0;
        for (int j = 0; j < NUM_SCORES; j++) {
            sum += scores[i][j];
        }
        averages[i] = static_cast<double>(sum) / NUM_SCORES;
    }
}

// Returns letter grade based on average score
char getLetterGrade(double avg) {
    if (avg >= 90) return 'A';
    else if (avg >= 80) return 'B';
    else if (avg >= 70) return 'C';
    else if (avg >= 60) return 'D';
    else return 'F';
}

// Prints formatted student report
void printReport(const string names[], const double averages[], int studentCount) {
    cout << left << setw(15) << "Student"
        << setw(10) << "Average"
        << setw(10) << "Grade" << endl;

    cout << string(35, '-') << endl;

    for (int i = 0; i < studentCount; i++) {
        cout << left << setw(15) << names[i]
            << fixed << setprecision(1) << setw(10) << averages[i]
                << setw(10) << getLetterGrade(averages[i]) << endl;
    }
}
