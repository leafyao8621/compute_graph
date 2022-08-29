#include <sstream>
#include "core.h"

ComputeGraph::ComputeGraph::NodeFactory::NodeFactory() {
    this->handlers["constant"] =
        new HandlerConstant();
    this->handlers["variable"] =
        new HandlerVariable();
    this->handlers["add"] =
        new HandlerAdd();
    this->handlers["subtract"] =
        new HandlerSubtract();
    this->handlers["multiply"] =
        new HandlerMultiply();
    this->handlers["divide"] =
        new HandlerDivide();
}

ComputeGraph::ComputeGraph::NodeFactory::~NodeFactory() {
    for (const auto &i : this->handlers) {
        delete i.second;
    }
}

ComputeGraph::ComputeGraph::NodeBase
    *ComputeGraph::ComputeGraph::NodeFactory::operator()(std::string line) {
    std::istringstream iss(line);
    std::string buf;
    iss >> buf;
    if (this->handlers.find(buf) == this->handlers.end()) {
        throw Err::INVALID_NODE;
    }
    return (*this->handlers[buf])(line);
}
