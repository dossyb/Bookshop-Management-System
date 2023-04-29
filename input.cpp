#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

using std::string;

void write(string input)
{
    std::cout << input;
}

void write_line(string input)
{
    std::cout << input << std::endl;
}

void write_double(double input)
{
    std::cout << std::fixed << std::setprecision(2) << input;
}

string read_line()
{
    string input;
    getline(std::cin, input);
    return input;
}

string read_string(string prompt)
{
    string result;
    write(prompt);
    result = read_line();
    return result;
}

int convert_to_integer(const string &text)
{
    return std::stoi(text);
}

double convert_to_double(const string &text)
{
    return std::stod(text);
}

int read_integer(string prompt)
{
    string line;
    int result;

    line = read_string(prompt);

    result = convert_to_integer(line);
    return result;
}

double read_double(string prompt)
{
    string line;
    double result;

    line = read_string(prompt);

    result = convert_to_double(line);
    return result;
}