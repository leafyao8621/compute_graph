#include <fstream>
#include "core.h"

ComputeGraph::ComputeGraph::ComputeGraph(std::string ifn) {
    std::ifstream ifs(ifn);
    if (ifs.fail()) {
        throw Err::FILE_IO;
    }
    size_t n;
    ifs >> n;
    std::string buf;
    std::getline(ifs, buf);
    this->nodes.reserve(n);
    NodeBase *temp = nullptr;
    NodeVariable *temp_var = nullptr;
    for (size_t i = 0; i < n; ++i) {
        std::getline(ifs, buf);
        temp = this->factory(buf);
        temp->idx = i;
        temp_var = dynamic_cast<NodeVariable*>(temp);
        if (temp_var) {
            this->input.push_back(temp_var);
        }
        this->nodes.push_back(temp);
    }
    ifs >> n;
    size_t from, to;
    for (size_t i = 0; i < n; ++i) {
        ifs >> from >> to;
        this->nodes[from]->push_output(this->nodes[to]);
        this->nodes[to]->push_input(this->nodes[from]);
    }
}

ComputeGraph::ComputeGraph::~ComputeGraph() {
    for (const auto &i : this->nodes) {
        delete i;
    }
}

void ComputeGraph::ComputeGraph::calculate(std::vector<double> val) {
    if (val.size() != this->input.size()) {
        throw Err::INVALID_NUMBER_OF_INPUT;
    }
    size_t idx = 0;
    for (const auto &i : this->input) {
        i->set_value(val[idx++]);
    }
    for (const auto &i : this->nodes) {
        i->level = 0;
        i->locked = false;
    }
    for (const auto &i : this->nodes) {
        if (i->input.size()) {
            continue;
        }
        std::list<NodeBase*> stack;
        stack.push_back(i);
        for (; stack.size();) {
            NodeBase *item = stack.back();
            stack.pop_back();
            if ((*item)()) {
                if (item->level >= this->output.size()) {
                    this->output.push_back(std::list<NodeBase*>());
                }
                this->output[item->level].push_back(item);
                for (const auto &j : item->output) {
                    stack.push_back(j);
                }
            }
        }
    }

}

void ComputeGraph::ComputeGraph::log(std::ostream &os) {
    for (size_t i = 0; i < this->output.size(); ++i) {
        os << "Level " << i << '\n';
        for (const auto &j : this->output[i]) {
            j->log(os);
        }
    }
}
