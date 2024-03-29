//
// Created by ArcziPT on 29.07.2019.
//

#include "CalcFunction.h"

std::unique_ptr<RPN> CalcFunction::operator()(const std::vector<double> &args) {
    auto rpnc = std::make_unique<RPN>(*rpn);

    for(auto& token : rpnc->stack){
        if(token.type != Token_type::func)
            continue;

        if(token.val.size() < 2)
            continue;

        if(token.val[0] != 'x')
            continue;

        auto num = stoi(std::string(token.val.begin() + 1, token.val.end()));

        if(num > arg_num)
            continue;

        Token t;
        t.val = std::to_string(args[args.size() - num - 1]);
        t.type = Token_type::number;

        token = t;
    }

    return rpnc;
}

CalcFunction::CalcFunction(const CalcFunction &calcFunction) {
    this->arg_num = calcFunction.arg_num;
    this->rpn = std::make_unique<RPN>(*(calcFunction.rpn.get()));
}

std::string CalcFunction::get_info() {
    std::string info = "";

    info += "Args number: " + std::to_string(arg_num) + "\nFunction: ";

    for(auto& token : rpn->stack){
        info += token.val + " ";
    }

    info += "\n";

    return info;
}
