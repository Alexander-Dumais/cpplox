#pragma once

void report(int line, std::string where, std::string message);
void error(int line, std::string message);
void runFile(char *filename);
void runPrompt();