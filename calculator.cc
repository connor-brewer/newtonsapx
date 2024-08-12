#include "calculator.hpp"
#include <string>
#include <map>






double Calculator::SquareRoot(std::string input_string) {
    bool meangus = Calculator::IsValidToSqrt(input_string);
    int input_integer = 0;
    if (meangus) {
        input_integer = std::stoi(input_string);
    } else {
        throw std::invalid_argument("NO!");
    }
    if (input_integer == 1 || input_integer == 0) {
        return input_integer;
    }
    double starting_guess = (input_integer) / 2;
    double appx_result = Calculator::SquareRootHelper(starting_guess, input_integer);
    return appx_result;
}

double Calculator::SquareRootHelper(double guess, int input_integer) {
    // xn+1 = xn - f(xn) / f'(xn)
    double guess_function_result = std::stod(std::to_string((guess * guess) - input_integer));
    double guess_der_function_result = std::stod(std::to_string((2 * guess)));
    double appx = std::stod(std::to_string((guess - ((guess_function_result) / (guess_der_function_result)))));
    if (appx == guess) {
        return appx;
    }
    return Calculator::SquareRootHelper(appx, input_integer);
}

bool Calculator::IsNumber(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool Calculator::IsValidToSqrt(std::string meb) {
    bool is_valid_number = Calculator::IsNumber(meb);
    bool is_short_enough = (meb.length() <= 10);
    if (is_short_enough && std::stol(meb) > 2147483647) {
        is_short_enough = false;
    }
    if (!is_valid_number || !is_short_enough) {
        return false;
    }
    return true;
}




//    ---------------------------------------------------------------




double Calculator::BasicSolveForX(std::string expression) {
    // this is any basic algebra that is the format for individual power rule
    // i.e.         14x^3 12x^2 = 13x - 3
    std::string rearranged_expression = expression;
    if (expression.substr((expression.length() - 3), 3) != "= 0") {
        rearranged_expression = Calculator::BasicExpressionRearranger(expression);
    }
    double result = 0.0;
    return result;
}

std::string Calculator::BasicExpressionRearranger(std::string expression) {
    // rearranges expressions to equal 0
    // i.e.         14x^3 12x^2 = 13x - 3    -->     14x^3 12x^2 -13x + 3 = 0
    // 2x = 3 - 4x^2     -->     = 2x - 3 + 4x^2 = 0
    std::string result = "";
    int location_of_equal = expression.find("=");
    std::string right_side_of_expression = expression.substr(location_of_equal + 2, expression.length() - (location_of_equal + 2));
    std::string left_side_of_expression = expression.substr(0, location_of_equal - 1);
    //std::cout << "The left side of the expression is: \"" << left_side_of_expression << "\"" << std::endl;
    //std::cout << "The right side of the expression is: \"" << right_side_of_expression << "\"" << std::endl;
    int amt_of_spaces = Calculator::CountSpaces(right_side_of_expression);
    int amt_of_terms = ((amt_of_spaces + 2) / 2);
    std::map<int, std::string> da_map = Calculator::BasicExpressionRearrangerHelper(right_side_of_expression);
    //std::cout << "First Term: " << da_map.at(1) << std::endl;
    result += left_side_of_expression + " ";
    for (int i = 1; i <= amt_of_terms; i++) {
        if (da_map.at(i).at(0) == '+') {
            result += "- " + da_map.at(i).substr(1, da_map.at(i).length() - 1) + " ";
        } else {
            result += "+ " + da_map.at(i).substr(1, da_map.at(i).length() - 1) + " ";
        }
    }
    const char* ws = " \t\n\r\f\v";
    std::string final_result = Calculator::RightTrim(result, ws);
    return final_result;
}


std::map<int, std::string> Calculator::BasicExpressionRearrangerHelper(std::string right_side_of_expression) {
    // this converts the string into a map of each term in order
    // i.e.   14x^3 12x^2 = 13x - 3    -->     14x^3 12x^2 -13x + 3 = 0    -->    my_map.at(1) == 14x^3
    //
    // 16
    std::string indiv_term;
    std::map<int, std::string> da_map;
    int da_count = 1;
    std::string trailing_char = "";
    bool is_second_space = false;
    bool got_here = false;
    for (int i = 0; i < right_side_of_expression.length(); i++) {
        if (i != 0) {
            trailing_char = right_side_of_expression.substr(i - 1, 1);
        } else {
            if (right_side_of_expression.substr(i, 1) != "-") {
                indiv_term += "+";
                if (Calculator::CountXs(right_side_of_expression) == 0) {
                    got_here = true;
                }
            }
        }
        if ((trailing_char == "+" || trailing_char == "-") && Calculator::CountSpaces(right_side_of_expression) > 0) {
            is_second_space = true;
        } else {
            is_second_space = false;
        }
        if (right_side_of_expression.at(i) == ' ' || i == right_side_of_expression.length() - 1) {
            if (is_second_space) {
                // do nothing
            } else {    
                if (i == right_side_of_expression.length() - 1) {
                    indiv_term += right_side_of_expression.at(i);
                }
                da_map[da_count] = indiv_term;
                indiv_term = "";
                da_count++;
            }
        } else {
            //checks if it is a digit
            if (!got_here || (right_side_of_expression.at(i) >= '0' && right_side_of_expression.at(i) <= '9')) {
                indiv_term += right_side_of_expression.at(i);
            }
            got_here = false;
        }
    }
    return da_map;
}




int Calculator::CountSpaces(std::string s) {
  int count = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == ' ') {
        count++;
    }
  }
  return count;
}



int Calculator::CountXs(std::string s) {
  int count = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == 'x') {
        count++;
    }
  }
  return count;
}





inline std::string& Calculator::RightTrim(std::string& s, const char* t) {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}






std::string Calculator::ConvertXtoN(std::string function, std::string n) {    
    for (int i = 0; i < function.length(); i++) {
        if (function.at(i) == 'x') {
            function.replace(i, 1, ("(" + n + ")") );
        }
    }
    return function;
}





double Calculator::EvaluateFunction(std::string expression, std::string n) {
    std::string indiv_term;
    std::map<int, std::string> da_map;
    int da_count = 1;
    std::string trailing_char = "";
    bool is_second_space = false;
    for (int i = 0; i < expression.length(); i++) {
        if (i != 0) {
            trailing_char = expression.substr(i - 1, 1);
        } else {
            if (expression.substr(i, 1) != "-") {
                indiv_term += "+";
            }
        }
        if (trailing_char == "+" || trailing_char == "-") {
            is_second_space = true;
        } else {
            is_second_space = false;
        }
        if (expression.at(i) == ' ' || i == expression.length() - 1) {
            if (is_second_space) {
                // do nothing
            } else {    
                if (i == expression.length() - 1) {
                    indiv_term += expression.at(i);
                }
                da_map[da_count] = indiv_term;
                indiv_term = "";
                da_count++;
            }
        } else {
            indiv_term += expression.at(i);
        }
    }
    double final_value = 0.0;
    for (int i = 1; i < da_count; i++) {
        bool we_add_it = false;
        if (da_map.at(i).at(0) == '+') {
            we_add_it = true;
        }    
        if (Calculator::CountXs(da_map.at(i)) != 0) {
            std::string coefficient = "";
            std::string power = "";
            bool left_bracket_passed = false;
            we_add_it = false;
            std::string filled_in_expression = Calculator::ConvertXtoN(da_map.at(i), n);
            size_t loc_of_right_bracket = filled_in_expression.find(')');
            if (filled_in_expression.at(0) == '+') {
                we_add_it = true;
            }
        
            for (int j = 1; j < filled_in_expression.length(); j++) {
                if (!left_bracket_passed) {
                    if (filled_in_expression.at(j) != '(') {
                        coefficient += filled_in_expression.at(j);
                    } else {
                        left_bracket_passed = true;
                        j += 1 + n.length();
                    }
                } else {
                    if (filled_in_expression.at(j) != '^') {
                        power += filled_in_expression.at(j);
                    }
                }
            }
            if (coefficient == "") {
                coefficient += "1";
            }
            if (power == "") {
                power += "1";
            }
            if (we_add_it) {
                final_value += std::stod(coefficient) * (Calculator::RaisePower(std::stod(n), std::stoi(power)));
            } else {
                final_value -= std::stod(coefficient) * (Calculator::RaisePower(std::stod(n), std::stoi(power)));
            }
        } else {
            if (we_add_it) {
                final_value += std::stod(da_map.at(i).substr(1, da_map.at(i).length() - 1));
            } else {
                final_value -= std::stod(da_map.at(i).substr(1, da_map.at(i).length() - 1));
            }
        }
    }
    return final_value;
}



double Calculator::RaisePower(double value, int power) {
    double mul = value;
    for (int i = 1; i < power; i++) {
        mul = mul * value;
    }
    return mul;
}






//   -----------------------------------------------




double Calculator::SolveBasicExpressionForX(std::string expression) {
    // xn+1 = xn - f(xn) / f'(xn)
    bool has_x_in_every_term = Calculator::CanFactorX(expression);
    std::string function = Calculator::BasicExpressionRearranger(expression);
    std::string der_function = Calculator::Derivativizer(function);
    double guess = 2;
    double appx_result = 0;
    try {
        appx_result = Calculator::SolveBasicExpressionForXHelper(guess, function, der_function, 0);
    } catch (const std::invalid_argument& e) {
        if (has_x_in_every_term) {
            return 0;
        } else {
            throw std::invalid_argument("A real solution does not exist for this expression");
        }
    }
    return appx_result; 
}


bool Calculator::CanFactorX(std::string expression) {
    bool has_x_in_every_term = true;
    bool has_x = false;
    bool term_started = false;
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == 'x') {
            has_x = true;
            term_started = true;
        }
        else if (term_started && (expression[i] == '+' || expression[i] == '-' || i == expression.length() - 1)) {
            if (!has_x) {
                has_x_in_every_term = false;
                break;
            }
            has_x = false;
            term_started = false;
        }
    }
    return has_x_in_every_term;
}


double Calculator::SolveBasicExpressionForXHelper(double guess, std::string function, std::string der_function, int safety) {
    if (safety == 500) {
        throw std::invalid_argument("sol dne");
    }
    double guess_function_result = Calculator::EvaluateFunction(function, std::to_string(guess));
    double guess_der_function_result = Calculator::EvaluateFunction(der_function, std::to_string(guess));
    double appx = std::stod(std::to_string((guess - ((guess_function_result) / (guess_der_function_result)))));
    if (appx == guess) {
        return appx;
    }
    return Calculator::SolveBasicExpressionForXHelper(appx, function, der_function, safety + 1);
}



std::string Calculator::Derivativizer(std::string function) {
    // use map from earlier, deal with each term individually, then plop em all together

    
    std::string derivative = "";
    std::map<int, std::string> da_map = Calculator::BasicExpressionRearrangerHelper(function);
    int amt_of_spaces = Calculator::CountSpaces(function);
    int amt_of_terms = ((amt_of_spaces + 2) / 2);
    for (int i = 1; i <= amt_of_terms; i++) {
        bool is_pos = false;
        if (da_map.at(i).at(0) == '+') {
            is_pos = true;
        }    
        if (Calculator::CountXs(da_map.at(i)) != 0) {
            std::string coefficient = "";
            std::string power = "";
            std::string new_coefficient = "";
            std::string new_power = "";
            bool we_passed_x = false;
            for (int j = 1; j < da_map.at(i).length(); j++) {
                if (da_map.at(i).at(j) != 'x' && !we_passed_x && da_map.at(i).at(j) != '^') {
                    coefficient += da_map.at(i).at(j);
                } else if (da_map.at(i).at(j) != 'x' && we_passed_x && da_map.at(i).at(j) != '^') {
                    power += da_map.at(i).at(j);
                } else {   
                    we_passed_x = true;
                }
            }
            if (coefficient == "") {
                coefficient += "1";
            }
            if (power == "") {
                power += "1";
            }
            new_power = std::to_string(std::stoi(power) - 1);
            new_coefficient = std::to_string(std::stoi(coefficient) * std::stoi(power));
            if (i == 1) {
                if (is_pos) {
                    derivative += new_coefficient + "x^" + new_power + " ";
                } else {
                    derivative += "-" + new_coefficient + "x^" + new_power + " ";
                }
            } else {
                if (is_pos) {
                    derivative += "+ " + new_coefficient + "x^" + new_power + " ";
                } else {
                    derivative += "- " + new_coefficient + "x^" + new_power + " ";
                }
            }
        } else {
            //do nothing, der of a constant is 0
        }
    }
    const char* ws = " \t\n\r\f\v";
    std::string final_result = Calculator::RightTrim(derivative, ws);
    return final_result;
}


