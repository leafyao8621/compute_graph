#ifndef CORE_H_
#define CORE_H_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <unordered_map>

namespace ComputeGraph {
    class ComputeGraph {
    public:
        enum Err {
            FILE_IO,
            INVALID_NODE,
            NULL_PTR,
            CONSTANT_INPUT,
            VARIABLE_INPUT,
            ADD_INPUT,
            SUBTRACT_INPUT,
            MULTIPLY_INPUT,
            DIVIDE_INPUT,
            INVALID_NUMBER_OF_INPUT
        };
    protected:
        class NodeBase {
        public:
            bool locked;
            size_t idx;
            size_t level;
            std::list<NodeBase*> input;
            std::list<NodeBase*> output;
            double value;
            virtual ~NodeBase() {}
            virtual void push_input(NodeBase* item) = 0;
            virtual void push_output(NodeBase* item) = 0;
            virtual bool operator()() = 0;
            virtual void log(std::ostream &os) = 0;
        };
        class NodeConstant : public NodeBase {
        public:
            NodeConstant(double value);
            void push_input(NodeBase* item);
            void push_output(NodeBase* item);
            bool operator()();
            void log(std::ostream &os);
        };
        class NodeVariable : public NodeBase {
        public:
            std::string name;
            NodeVariable(std::string name);
            void set_value(double value);
            void push_input(NodeBase* item);
            void push_output(NodeBase* item);
            bool operator()();
            void log(std::ostream &os);
        };
        class NodeAdd : public NodeBase {
        public:
            void push_input(NodeBase* item);
            void push_output(NodeBase* item);
            bool operator()();
            void log(std::ostream &os);
        };
        class NodeSubtract : public NodeBase {
        public:
            void push_input(NodeBase* item);
            void push_output(NodeBase* item);
            bool operator()();
            void log(std::ostream &os);
        };
        class NodeMultiply : public NodeBase {
        public:
            void push_input(NodeBase* item);
            void push_output(NodeBase* item);
            bool operator()();
            void log(std::ostream &os);
        };
        class NodeDivide : public NodeBase {
        public:
            void push_input(NodeBase* item);
            void push_output(NodeBase* item);
            bool operator()();
            void log(std::ostream &os);
        };
        class NodeSum : public NodeBase {
        public:
            void push_input(NodeBase* item);
            void push_output(NodeBase* item);
            bool operator()();
            void log(std::ostream &os);
        };
        class NodeProduct : public NodeBase {
        public:
            void push_input(NodeBase* item);
            void push_output(NodeBase* item);
            bool operator()();
            void log(std::ostream &os);
        };
        class NodeMin : public NodeBase {
        public:
            void push_input(NodeBase* item);
            void push_output(NodeBase* item);
            bool operator()();
            void log(std::ostream &os);
        };
        class NodeMax : public NodeBase {
        public:
            void push_input(NodeBase* item);
            void push_output(NodeBase* item);
            bool operator()();
            void log(std::ostream &os);
        };
        class NodeFactory {
        protected:
            class HandlerBase {
            public:
                virtual ~HandlerBase() {};
                virtual NodeBase *operator()(std::string line) = 0;
            };
            class HandlerConstant : public HandlerBase {
            public:
                NodeBase *operator()(std::string line);
            };
            class HandlerVariable : public HandlerBase {
            public:
                NodeBase *operator()(std::string line);
            };
            class HandlerAdd : public HandlerBase {
            public:
                NodeBase *operator()(std::string line);
            };
            class HandlerSubtract : public HandlerBase {
            public:
                NodeBase *operator()(std::string line);
            };
            class HandlerMultiply : public HandlerBase {
            public:
                NodeBase *operator()(std::string line);
            };
            class HandlerDivide : public HandlerBase {
            public:
                NodeBase *operator()(std::string line);
            };
            class HandlerSum : public HandlerBase {
            public:
                NodeBase *operator()(std::string line);
            };
            class HandlerProduct : public HandlerBase {
            public:
                NodeBase *operator()(std::string line);
            };
            class HandlerAverage : public HandlerBase {
            public:
                NodeBase *operator()(std::string line);
            };
            class HandlerMin : public HandlerBase {
            public:
                NodeBase *operator()(std::string line);
            };
            class HandlerMax : public HandlerBase {
            public:
                NodeBase *operator()(std::string line);
            };
        private:
            std::unordered_map<std::string, HandlerBase*> handlers;
        public:
            NodeFactory();
            ~NodeFactory();
            NodeBase *operator()(std::string line);
        };
    private:
        NodeFactory factory;
        std::vector<NodeBase*> nodes;
        std::list<NodeVariable*> input;
        std::vector<std::list<NodeBase*> > output;
    public:
        ComputeGraph(std::string ifn);
        ~ComputeGraph();
        void calculate(std::vector<double> val);
        void log(std::ostream &os);
    };
}

#endif
