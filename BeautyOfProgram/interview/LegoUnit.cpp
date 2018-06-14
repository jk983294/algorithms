#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace std::placeholders;

string testFile{"/home/kun/github/algorithms/BeautyOfProgram/interview/LegoUnit.test.txt"};

/// Parser for the Akuna Lego Unit input file
//
// When the process() method is called, this class read from stdin and call callbacks for each unit, input,
// connection, and value.
class input_parser {
public:
    input_parser() { ifs = new ifstream(testFile, ifstream::in); }
    ~input_parser() { delete ifs; }

    /// Register the callback for each UNIT in the input file.
    /// The first parameter is the "unit-name", the second parameter is the "unit-type".
    /// E.g:
    ///    a := sum
    /// We would call unit_callback_("a", "sum")
    ///
    void register_unit_callback(std::function<void(std::string, std::string)> cb) { unit_callback_ = cb; }

    /// Register the callback for the INPUTS line in the input file
    ///
    /// The parameter tells how many input ports there are.
    /// E.g:
    ///    INPUTS: 2
    /// We would call input_callback_(2)
    void register_input_callback(std::function<void(int)> cb) { input_callback_ = cb; }

    /// Register the callback for each CONNECTION in the input file
    ///
    /// The first 3 parameters tell you the "from" side,
    /// the last 3 parameters tell you the "to" side.
    ///
    /// For each three parameter group:
    ///  - The first is the unit name, "input" or "result"
    ///  - The second is "in", "out" or "" (empty)
    ///  - The third is port number (could be empty string), e.g. "0", "1", or "".
    /// Example 1:
    ///   input/0 -- a/in/0
    ///   =>   connection_callback_("input", "", "0", "a", "in", "0")
    /// Example 2:
    ///   a/out/0 -- result
    ///   =>   connection_callback_("a", "out", 0, "result", "", "")
    /// Example 3:
    ///   a/out/3 -- b/in/1
    ///   =>   connection_callback_("a", "out", "3", "b", "in", "1")
    ///
    void register_connection_callback(
        std::function<void(std::string, std::string, std::string, std::string, std::string, std::string)> cb) {
        connection_callback_ = cb;
    }

    /// Register the callback for each VALUE in the input file
    ///
    /// The first parameter is always "input" :)
    /// The second parameter is the input port number in string. e.g. "0", "1"
    /// The third parameter is the value number in string. e.g. "999"
    /// E.g:
    ///    input/0 := 3
    /// We would call value_callback_("input", "0", "3")
    void register_value_callback(std::function<void(std::string, std::string, std::string)> cb) {
        value_callback_ = cb;
    }

    /// Process lines from stdin and call the appropriate callbacks.  Note that
    /// this is very intolerant of syntax errors, and will assert in any unexpected
    /// input
    void process() {
        // process the UNITS line
        int units_num = get_section_title_line();  // UNITS: 1

        // handle the expected number of units
        for (int i = 0; i < units_num; i++) {
            std::string name, type;
            get_section_internal_line(name, type);  // a := sum
            if (unit_callback_) unit_callback_(name, type);
        }

        // process the INPUTS line
        int inputs_num = get_section_title_line();  // INPUTS: 2
        if (input_callback_) input_callback_(inputs_num);

        // process the CONNECTIONS line
        int connections_num = get_section_title_line();  // CONNECTIONS: 3

        // handle the expected number of connections
        for (int i = 0; i < connections_num; i++) {
            std::string from, to;
            get_section_internal_line(from, to);  // input/0 -- a/in/0
            assert(from != "result");
            std::vector<std::string> from_strs = split(from, '/');
            assert(from_strs.size() >= 2);
            std::vector<std::string> to_strs = split(to, '/');
            assert(from_strs.size() >= 1);

            // the first parameter is from_strs[0]
            std::string second = from_strs[0] == "input" ? "" : from_strs[1];
            std::string third = from_strs[0] == "input" ? from_strs[1] : from_strs[2];

            std::string fifth = "";
            std::string sixth = "";
            if (to_strs[0] == "input") {
                sixth = to_strs[1];
            } else if (to_strs[0] != "result") {
                fifth = to_strs[1];
                sixth = to_strs[2];
            }

            if (connection_callback_) connection_callback_(from_strs[0], second, third, to_strs[0], fifth, sixth);
        }

        // process the VALUES line
        int values_num = get_section_title_line();  // VALUES: 3

        // handle the expected number of values
        for (int i = 0; i < values_num; i++) {
            std::string input, value;
            get_section_internal_line(input, value);
            std::vector<std::string> strs = split(input, '/');
            assert(strs.size() == 2);
            if (value_callback_) value_callback_(strs[0], strs[1], value);  // input/0 := 3
        }
    }

private:
    // hackerrank doesn't support boost files, so use our own utilities...

    // split a string on a delimiter and append each item to result.
    template <typename Out>
    void split(const std::string& s, char delim, Out result) {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    // split a string an a delimiter and return a vector of the results
    std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }

    // read a line from stdin and return the number in the second token UNITS: 1
    int get_section_title_line() {
        std::string line;
        //        std::getline(std::cin, line);
        std::getline(*ifs, line);
        std::vector<std::string> words = split(line, ' ');
        assert(words.size() == 2);
        return atoi(words[1].c_str());
    }

    // read a line from stdin and return the first and third token
    void get_section_internal_line(std::string& a, std::string& b) {
        std::string line;
        //        std::getline(std::cin, line);
        std::getline(*ifs, line);
        std::vector<std::string> words = split(line, ' ');
        assert(words.size() == 3);
        a = words[0];
        b = words[2];
    }

private:
    std::function<void(std::string, std::string)> unit_callback_;

    std::function<void(int n)> input_callback_;

    std::function<void(std::string, std::string, std::string, std::string, std::string, std::string)>
        connection_callback_;

    std::function<void(std::string, std::string, std::string)> value_callback_;

    ifstream* ifs;
};

struct Data {
    int data{0};
    bool valid{false};

    Data() {}
    Data(int d, bool v) : data(d), valid(v) {}

    void set(int v) {
        data = v;
        valid = true;
    }
};

enum NodeType { sum, max, min, mul, negate, input, result };

NodeType string2nodeType(string str) {
    if (str == "sum")
        return NodeType::sum;
    else if (str == "max")
        return NodeType::max;
    else if (str == "min")
        return NodeType::min;
    else if (str == "mul")
        return NodeType::mul;
    else if (str == "negate")
        return NodeType::negate;
    else if (str == "input")
        return NodeType::input;
    else if (str == "result")
        return NodeType::result;
    else
        throw invalid_argument("unsupported type");
}

struct Node {
    NodeType type;
    string name;
    Data input1;
    Data input2;
    vector<std::pair<shared_ptr<Node>, int>> connections;

    int topologicalOrder{0};

    Node(string name_, string typeStr) : type(string2nodeType(typeStr)), name(name_) {}

    Data calculate() {
        bool firstValid = input1.valid;
        bool bothValid = input1.valid & input2.valid;
        if (type <= NodeType::mul && bothValid) {
            int result = 0;
            if (type == NodeType::sum) {
                result = input1.data + input2.data;
            } else if (type == NodeType::max) {
                result = std::max(input1.data, input2.data);
            } else if (type == NodeType::min) {
                result = std::min(input1.data, input2.data);
            } else if (type == NodeType::mul) {
                result = input1.data * input2.data;
            }
            return Data(result, true);
        } else if (type >= NodeType::negate && firstValid) {
            int result = input1.data;
            if (type == NodeType::negate) {
                result = -input1.data;
            }
            return Data(result, true);
        } else {
            return Data(0, false);
        }
    }
};

ostream& operator<<(ostream& os, const Data& data) {
    os << "[" << data.data << ", " << data.valid << "]";
    return os;
}

ostream& operator<<(ostream& os, const Node& node) {
    os << "type: " << node.type << " name: " << node.name << " input1: " << node.input1 << " input2: " << node.input2
       << " order: " << node.topologicalOrder << " ";
    for (const auto& connection : node.connections) {
        os << "conn: [" << connection.first->name << ", " << connection.second << "] ";
    }
    return os;
}

class Engine {
public:
    Engine() {
        parser.register_unit_callback(bind(&Engine::unitCallback, this, _1, _2));
        parser.register_input_callback(bind(&Engine::inputCallback, this, _1));
        parser.register_connection_callback(bind(&Engine::connectionCallback, this, _1, _2, _3, _4, _5, _6));
        parser.register_value_callback(bind(&Engine::valueCallback, this, _1, _2, _3));
    }

    void process() {
        nodes.insert(make_pair("result", make_shared<Node>("result", "result")));
        parser.process();
    }

    void unitCallback(std::string unitName, std::string unitType) {
        nodes.insert(make_pair(unitName, make_shared<Node>(unitName, unitType)));
    }

    void inputCallback(int n) {
        for (int i = 0; i < n; ++i) {
            ostringstream oss;
            oss << "input" << i;
            string name = oss.str();
            nodes.insert(make_pair(name, make_shared<Node>(name, "input")));
        }
    }
    void connectionCallback(std::string fromName, std::string fromDir, std::string fromPort, std::string toName,
                            std::string toDir, std::string toPort) {
        shared_ptr<Node> fromNode;
        if (!fromDir.empty()) {
            fromNode = nodes.at(fromName);
        } else {
            fromNode = nodes.at(fromName + fromPort);
        }
        shared_ptr<Node> toNode = nodes.at(toName);
        if (!toPort.empty()) {
            int port = atoi(toPort.c_str());
            fromNode->connections.push_back({toNode, port});
        } else {
            fromNode->connections.push_back({toNode, 0});
        }
    }

    void valueCallback(std::string input, std::string port, std::string value) {
        if (!topologicalSorted) {
            topologicalSort();
            topologicalSorted = true;
        }

        unordered_map<shared_ptr<Node>, bool> visited;
        string name = input + port;
        shared_ptr<Node> inputNode = nodes.at(name);
        inputNode->input1.set(atoi(value.c_str()));
        queue<shared_ptr<Node>> q;
        q.push(inputNode);
        visited[inputNode] = true;
        while (!q.empty()) {
            shared_ptr<Node> node = q.front();
            q.pop();

            if (node->type == NodeType::result) {
                if (node->input1.valid) {
                    cout << node->input1.data << endl;
                }
            } else {
                Data result = node->calculate();
                if (result.valid) {
                    for (const auto& connection : node->connections) {
                        if (connection.second == 0) {
                            connection.first->input1.set(result.data);
                        } else {
                            connection.first->input2.set(result.data);
                        }
                        if (visited.find(connection.first) == visited.end()) {
                            q.push(connection.first);
                            visited[connection.first] = true;
                        }
                    }
                }
            }
        }
    }

private:
    input_parser parser;
    unordered_map<string, shared_ptr<Node>> nodes;
    int time{1};
    bool topologicalSorted{false};

    void topologicalSort() {
        for (auto& item : nodes) {
            if (item.second->topologicalOrder == 0) dfs(item.second);
        }

        for (auto& item : nodes) {
            sort(item.second->connections.begin(), item.second->connections.end(),
                 [](const std::pair<shared_ptr<Node>, int>& n1, const std::pair<shared_ptr<Node>, int>& n2) {
                     return n1.first->topologicalOrder > n2.first->topologicalOrder;
                 });
        }
    }

    void dfs(shared_ptr<Node> node) {
        node->topologicalOrder = 1;
        for (auto& connection : node->connections) {
            if (connection.first->topologicalOrder == 0) {
                dfs(connection.first);
            }
        }
        node->topologicalOrder = time++;
    }
};

int main() {
    Engine engine;
    engine.process();
    return 0;
}
