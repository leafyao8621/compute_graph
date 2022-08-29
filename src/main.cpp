#include "core/core.h"

int main() {
    try {
        ComputeGraph::ComputeGraph cg("data/test.graph");
        std::vector<double> inp = {
            1, 2
        };
        cg.calculate(inp);
        cg.log(std::cout);
    } catch (ComputeGraph::ComputeGraph::Err err) {
        std::cout << "Errcode: " << err << '\n';
    }
    return 0;
}
