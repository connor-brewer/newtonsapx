#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <iostream>
#include <string>
#include <map>

class Calculator {
    public:
        double SquareRoot(std::string input_string);
        std::string BasicExpressionRearranger(std::string expression);
        double EvaluateFunction(std::string expression, std::string n);
        double SolveBasicExpressionForX(std::string expression);
    private:
        double BasicSolveForX(std::string expression);
        double SquareRootHelper(double guess, int input_integer);
        bool IsValidToSqrt(std::string meb);
        bool IsNumber(const std::string& s);
        int CountSpaces(std::string s);
        std::map<int, std::string> BasicExpressionRearrangerHelper(std::string right_side_of_expression);
        inline std::string& RightTrim(std::string& s, const char* t);
        std::string ConvertXtoN(std::string function, std::string n);
        double RaisePower(double value, int power);
        int CountXs(std::string s);
        std::string Derivativizer(std::string function);
        double SolveBasicExpressionForXHelper(double guess, std::string function, std::string der_function, int safety);
        bool CanFactorX(std::string expression);
};

#endif