#include "analyzer.hpp"

FileAnalyzer::FileAnalyzer(){};

FileAnalyzer::FileAnalyzer(std::string text, std::string func){
    if (func == "") {
        code = text;
        findOps();
    } else {
        code = findStart(text, func);
        if (code.length()){
            blocks.push_back(new BaseOperator(start));
            findOps();
            blocks.push_back(new BaseOperator(end));
        }
    }
}

std::string FileAnalyzer::getcode(){
    return code;
}

std::vector<BaseOperator*> FileAnalyzer::getBlocks(){
    return blocks;
}

std::string FileAnalyzer::getSubProg(){
    std::string res = "";
    std::istringstream istrm;
    istrm.str(code);
    std::regex rgx("^\\s*(\\w+)\\s*\\((.*)\\);$");

    for (std::string s; std::getline(istrm, s);){
        if (std::regex_search(s, rgx)){
            res += s.substr(0, s.find('(')) + '\n';
        }
    }
    return res;
}

std::string FileAnalyzer::findStart(std::string text, std::string func){
    size_t idx_start = text.find(func);
    if (idx_start == std::string::npos){
        return "";
    }
    while (text[idx_start] != '{'){
        idx_start++;
        if (idx_start >= text.length())
            return "";
    }

    size_t idx_end = idx_start + 1;
    int bracket_k = 1;
    while (idx_end < text.length() && bracket_k != 0){
        if (text[idx_end] == '{')
            bracket_k++;
        else if (text[idx_end] == '}')
            bracket_k--;
        ++idx_end;
    }

    std::string func_code = text.substr(idx_start, idx_end - idx_start);

    return func_code;
}

void FileAnalyzer::findOps(){
    std::vector<std::string> ops = splitCode();

    genBlocks(ops, blocks);
}

std::vector<std::string> FileAnalyzer::splitCode(){
    std::vector<std::string> res;

    int idx_start = 1;
    while (!isalpha(code[idx_start])){
        idx_start++;
    }
    size_t bracket_k = 0, cbracket_k = 0;
    for (size_t i = idx_start; i < code.length() - 1; ++i){
        if (code[i] == '{'){
            bracket_k++;
        }
        if (code[i] == '}'){
            bracket_k--;
            if (bracket_k == 0){
                if (i - idx_start + 1 > 1)
                    res.push_back(code.substr(idx_start, i - idx_start + 1));
                idx_start = i + 1;
            }
        }
        if (code[i] == '(' && code[i - 1] != '\'' && code[i - 1] != '\"'){
            cbracket_k++;
        }
        if (code[i] == ')' && code[i + 1] != '\'' && code[i + 1] != '\"'){
            cbracket_k--;
        }
        if (bracket_k == 0 && code[i] == ';' && cbracket_k == 0){
            if (i - idx_start > 0){
                std::string s = code.substr(idx_start, i - idx_start);
                if (s.length() > 0){
                    res.push_back(s);
                }
                idx_start = i + 1;
            }
        }
    }

    return res;
}

void FileAnalyzer::genBlocks(std::vector<std::string> ops, std::vector<BaseOperator*> &arr){
    IfOperator *lastIf = nullptr;
    for (auto op : ops){
        trim(op);
        if (op.find("cin") == 0 || op.find("std::cin") == 0){
            arr.push_back(new InputOperator(op));
        } else if (op.find("cout") == 0 || op.find("std::cout") == 0) {
            arr.push_back(new OutputOperator(op));
        } else if (op.find("if") == 0) {
            lastIf = new IfOperator(op);
            arr.push_back(lastIf);
        } else if (op.find("else") == 0) {
            FileAnalyzer* a = new FileAnalyzer(op.substr(op.find('{')));
            if (lastIf){
                lastIf->setElseBranch(a->getBlocks());
            }
            delete a;
        } else if (op.find("for") == 0 || op.find("while") == 0) {
            arr.push_back(new LoopOperator(op));
        } else {
            arr.push_back(new BaseOperator(op));
        }
    }
}

void FileAnalyzer::trim(std::string &op){
    size_t start = 0;
    while (isspace(op[start])) {
        start++;
    }

    size_t end = op.length() - 1;
    while (isspace(op[end])) {
        end--;
    }

    op = op.substr(start, end - start + 1);
}


















