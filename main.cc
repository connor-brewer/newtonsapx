
#include "calculator.hpp"
#include <string>











int main() {
    Calculator melvin;
    std::string dialouge = "";
    std::cout << "" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Evaluate a Square Root (1)" << std::endl;
    std::cout << "Evaluate a Polynomial Function at a Value (2)" << std::endl;
    std::cout << "Rewrite an Polynomial Expression to Solve for Zeros (3)" << std::endl;
    std::cout << "Solve for the Value of X in a Polynomial Expression (4)" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Enter your choice here: ";

    std::getline(std::cin, dialouge);
    if (dialouge == "2") {
        std::cout << "" << std::endl;
        std::string meb = "";
        std::string strpower = "";
        std::cout << "ex.)   5x^2 + 3x - 2x^3 + 1" << std::endl;
        std::cout << "What positive-powered polynomial function would you like to evaluate? Enter Here: ";
        std::getline(std::cin, meb);
        std::cout << "" << std::endl;
        std::cout << "At what value of x would you like to evaluate the function? Enter Here: ";
        std::getline(std::cin, strpower);
        std::cout << "" << std::endl;
        std::cout << "The input was: \"" << meb << "\" and the input value for x was " << strpower << std::endl;
        std::cout << "" << std::endl;
        std::cout << "The evaluation is " << std::to_string(melvin.EvaluateFunction(meb, strpower)) << std::endl;
    } else if (dialouge == "1") {
        double result = 0.0;
        bool isValid = false;
        std::string meb = "";
        while (!isValid) {
            std::cout << "" << std::endl;
            std::cout << "What non-negative integer would you like to square root? Enter Here: ";
            std::cin >> meb;
            try {
                melvin.SquareRoot(meb);
                isValid = true;
            } catch (const std::invalid_argument& e) {
                std::cout << "" << std::endl;
                std::cout << "That was not a valid non-negative integer, try again..." << std::endl;
            }
        }
        std::cout << "" << std::endl;
        std::cout << "The square root of " + meb + " is " + std::to_string(melvin.SquareRoot(meb)) << std::endl;
    } else if (dialouge == "3") {
        std::string connor = "";
        std::cout << "" << std::endl;
        std::cout << "ex.)   2 + x + 4x^2 = -3x^2 + 5x^6" << std::endl;
        std::cout << "What positive-powered polynomial expression would you like to rearrange? Enter Here: ";
        std::getline(std::cin, connor);
        std::cout << "" << std::endl;
        std::cout << "The rearrangement of \"" + connor + "\" is \"" + melvin.BasicExpressionRearranger(connor) << " = 0\"" << std::endl;
    } else if (dialouge == "4") {
        std::string mumbo = "";
        std::cout << "" << std::endl;
        std::cout << "ex.)   2 + x + 4x^2 = -3x^2 + 5x^6" << std::endl;
        std::cout << "What positive-powered polynomial expression would you like to find a solution for? Enter Here: ";
        std::getline(std::cin, mumbo);
        std::cout << "" << std::endl;
        try {
            melvin.SolveBasicExpressionForX(mumbo);
            std::cout << "A solution to the expression \"" << mumbo << "\" is x = " << std::to_string(melvin.SolveBasicExpressionForX(mumbo)) << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "A real solution to the expression \"" << mumbo << "\" does not exist." << std::endl;
        }
    } else {
        std::cout << "" << std::endl;
        std::cout << "Invalid dialouge option." << std::endl;
    }
    std::cout << "" << std::endl;
    return 0;
}





















