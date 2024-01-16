#ifndef ANALYZER_HPP
#define ANALYZER_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include "regex"
#include "operators/BaseOperator.hpp"
#include "operators/InputOperator.hpp"
#include "operators/OutputOperator.hpp"
#include "operators/LoopOperator.hpp"
#include "operators/ForOperator.hpp"
#include "operators/WhileOperator.hpp"
#include "operators/IfOperator.hpp"
#include "operators/SwitchOperator.hpp"
#include "operators/TryCatchOperator.hpp"

class FileAnalyzer{
private:
protected:
    std::string code;
    std::vector<BaseOperator*> blocks;
public:
    FileAnalyzer();
    FileAnalyzer(std::string, std::string = "");

    std::string getcode();
    std::vector<BaseOperator*> getBlocks();
    std::string getSubProg();
    std::string findStart(std::string, std::string="");
    std::vector<std::string> splitCode();
    void findOps();
    void genBlocks(std::vector<std::string>, std::vector<BaseOperator*>&);

    void trim(std::string &);
};

#endif
