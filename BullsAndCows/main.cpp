// ------------------------------------------------------------
// main.cpp - Local runner for Questions 1-2 (demo only).
// This file is for your local verification; the checker uses its own main.
// ------------------------------------------------------------

#include <iostream>
#include "question_1.h"
#include "question_2.h"

static void runQuestion1ProvidedTests() {
    std::cout << "=== Question 1: Provided test cases ===\n\n";

    auto runCase = [](int caseId,
        int newGuess,
        Feedback* feedbacks,
        int* guesses,
        int n,
        bool expectedOutput) {
            const bool actual = question_1(newGuess, feedbacks, guesses, n);

            std::cout << "case " << caseId << "\n"
                << "------\n"
                << "output = " << (actual ? "true" : "false")
                << " (expected " << (expectedOutput ? "true" : "false") << ")\n\n";
        };

    // case 0
    {
        int newGuess = 1234;
        Feedback feedbacks[2] = { {2,0}, {1,1} };
        int guesses[2] = { 1736, 1546 };
        runCase(0, newGuess, feedbacks, guesses, 2, true);
    }

    // case 1
    {
        int newGuess = 1234;
        Feedback feedbacks[2] = { {2,0}, {1,1} };
        int guesses[2] = { 1376, 1546 };
        runCase(1, newGuess, feedbacks, guesses, 2, false);
    }

    // case 2
    {
        int newGuess = 9741;
        Feedback feedbacks[3] = { {0,3}, {2,1}, {2,2} };
        int guesses[3] = { 4196, 7341, 9714 };
        runCase(2, newGuess, feedbacks, guesses, 3, true);
    }

    // case 3
    {
        int newGuess = 9741;
        Feedback feedbacks[3] = { {0,3}, {2,1}, {1,3} };
        int guesses[3] = { 4196, 7341, 9714 };
        runCase(3, newGuess, feedbacks, guesses, 3, false);
    }
}

static void printMenu() {
    std::cout << "\n=== Local Runner Menu ===\n";
    std::cout << "1) Run Question 1 (provided tests)\n";
    std::cout << "2) Run Question 2 (DFS experiment)\n";
    std::cout << "9) Run All\n";
    std::cout << "0) Exit\n";
    std::cout << "Choose: ";
}

int main() {
    while (true) {
        printMenu();

        int choice = -1;
        std::cin >> choice;

        if (!std::cin) {
            std::cout << "Invalid input. Exiting.\n";
            return 0;
        }

        std::cout << "\n";

        switch (choice) {
        case 1:
            runQuestion1ProvidedTests();
            break;

        case 2:
            std::cout << "=== Question 2: DFS Strategy ===\n";
            question_2();   // if your function name differs, change it here
            std::cout << "\n";
            break;

        case 9:
            runQuestion1ProvidedTests();
            std::cout << "=== Question 2: DFS Strategy ===\n";
            question_2();
            std::cout << "\n";
            break;

        case 0:
            std::cout << "Bye!\n";
            return 0;

        default:
            std::cout << "Unknown choice.\n\n";
            break;
        }
    }
}