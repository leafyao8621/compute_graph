#include "../core.h"

ComputeGraph::ComputeGraph::NodeConstant::NodeConstant(double value) {
    this->value = value;
}

void ComputeGraph::ComputeGraph::NodeConstant::push_input(
    ComputeGraph::ComputeGraph::NodeBase *item) {
    if (!item) {
        throw Err::NULL_PTR;
    }
    throw Err::CONSTANT_INPUT;
}

void ComputeGraph::ComputeGraph::NodeConstant::push_output(
    ComputeGraph::ComputeGraph::NodeBase *item) {
    if (!item) {
        throw Err::NULL_PTR;
    }
    this->output.push_back(item);
}

bool ComputeGraph::ComputeGraph::NodeConstant::operator()() {
    this->locked = true;
    return true;
}

void ComputeGraph::ComputeGraph::NodeConstant::log(std::ostream &os) {
    os << "idx: " << this->idx << "\n" << "constant: " << this->value << '\n';
}
