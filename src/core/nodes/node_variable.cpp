#include "../core.h"

ComputeGraph::ComputeGraph::NodeVariable::NodeVariable(std::string name) {
    this->name = name;
}

void ComputeGraph::ComputeGraph::NodeVariable::set_value(double value) {
    this->value = value;
}

void ComputeGraph::ComputeGraph::NodeVariable::push_input(
    ComputeGraph::ComputeGraph::NodeBase *item) {
    if (!item) {
        throw Err::NULL_PTR;
    }
    throw Err::VARIABLE_INPUT;
}

void ComputeGraph::ComputeGraph::NodeVariable::push_output(
    ComputeGraph::ComputeGraph::NodeBase *item) {
    if (!item) {
        throw Err::NULL_PTR;
    }
    this->output.push_back(item);
}

bool ComputeGraph::ComputeGraph::NodeVariable::operator()() {
    this->locked = true;
    return true;
}

void ComputeGraph::ComputeGraph::NodeVariable::log(std::ostream &os) {
    os << "idx: " << this->idx << "\n" << "variable " << this->name << ": " <<
        this->value << '\n';
}
