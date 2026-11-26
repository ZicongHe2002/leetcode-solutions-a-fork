#include <stack>

class MyQueue {
    std::stack<int> incoming;
    std::stack<int> outgoing;

    void prepareFront() {
        if (!outgoing.empty()) return;
        while (!incoming.empty()) {
            outgoing.push(incoming.top());
            incoming.pop();
        }
    }

public:
    MyQueue() = default;
    void push(int value) { incoming.push(value); }
    int pop() {
        prepareFront();
        const int value = outgoing.top();
        outgoing.pop();
        return value;
    }
    int peek() {
        prepareFront();
        return outgoing.top();
    }
    bool empty() const { return incoming.empty() && outgoing.empty(); }
};
