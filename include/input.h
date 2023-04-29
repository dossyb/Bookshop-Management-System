#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

using std::string;

void write(string input);
void write_line(string input);
void write_double(double input);
string read_line();
string read_string(string prompt);
int convert_to_integer(const string &text);
double convert_to_double(const string &text);
int read_integer(string prompt);
double read_double(string prompt);