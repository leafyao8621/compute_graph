#include "../core.h"

void ComputeGraph::ComputeGraph::NodeMultiply::push_input(
    ComputeGraph::ComputeGraph::NodeBase *item) {
    if (!item) {
        throw Err::NULL_PTR;
    }
    if (this->input.size() == 2) {
        throw Err::MULTIPLY_INPUT;
    }
    this->input.push_back(item);
}

void ComputeGraph::ComputeGraph::NodeMultiply::push_output(
    ComputeGraph::ComputeGraph::NodeBase *item) {
    if (!item) {
        throw Err::NULL_PTR;
    }
    this->output.push_back(item);
}

bool ComputeGraph::ComputeGraph::NodeMultiply::operator()() {
    if (this->input.size() != 2) {
        throw Err::ADD_INPUT;
    }
    if (this->locked) {
        return false;
    }
    this->value = 0;
    size_t max_level = 0;
    bool init = true;
    for (const auto &i : this->input) {
        if (!i->locked) {
            return false;
        }
        if (init) {
            this->value += i->value;
            init = false;
        } else {
            this->value *= i->value;
        }
        if (i->level > max_level) {
            max_level = i->level;
        }
    }
    this->level = max_level + 1;
    this->locked = true;
    return true;
}

void ComputeGraph::ComputeGraph::NodeMultiply::log(std::ostream &os) {
    os << "idx: " << this->idx << "\n" << "multiply: " << this->value << '\n';
}
