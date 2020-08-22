#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Reader {
    string path;
    char delimiter;
    vector<vector<string> > data;
    static unordered_map<string, int> rows, columns;

public:
    explicit Reader(string name, char dl = ',') :
            path(move(name)), delimiter(dl) {}

    vector<vector<string> > read();

    static vector<string> split(string, char);

    static bool is_digits(const string &s);

    static int compute(int arg1, int arg2, char op);

    int get_val(const string &arg);

    void parse();

    void print();
};

// Maps for indexing rows and columns
unordered_map<string, int> Reader::rows = {};
unordered_map<string, int> Reader::columns = {};

// Reading from file
vector<vector<string> > Reader::read() {
    ifstream file(path);
    string line;

    if (file.good()) {
        int count = 0;
        while (getline(file, line)) {
            // Deleting spaces if there some
            line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

            // String -> tokens array
            vector<string> vec = split(line, delimiter);

            // Filling columns indexes
            if (!count) {
                for (int i = 0; i < vec.size(); ++i) {
                    if (vec[i].length()) columns.insert(make_pair(vec[i], i - 1));
                }
            }
            // Filling row indexes
            if (vec[0].length()) rows.insert(make_pair(vec[0], count - 1));

            // Push data
            data.push_back(vec);
            ++count;
        }
        file.close();
    } else throw runtime_error("The file does not exist");

    return data;
}

// Splits string into tokens vector<string> by delimeter
vector<string> Reader::split(string s, char dl) {
    int it;
    string token;
    vector<string> tokens;

    while ((it = s.find(dl)) != std::string::npos) {
        token = s.substr(0, it);
        tokens.push_back(token);
        s.erase(0, it + 1);
    }

    tokens.push_back(s);
    return tokens;
}

//
void Reader::parse() {
    for (int q = 1; q < data.size(); ++q) {
        auto vec = data[q]; // row
        for (int k = 1; k < vec.size(); ++k) {
            auto token = vec[k];

            // Solving formulas
            if (token[0] == '=') {
                token.erase(token.begin(), token.begin() + 1);

                // Getting operator
                char op = *find_if(token.begin(), token.end(), [](char c) {
                    string ops = "+-*/";
                    if (ops.find(c) != string::npos) return 1;
                    return 0;
                });

                // Getting args
                auto args = split(token, op);

                int arg1, arg2;
                arg1 = get_val(args[0]);
                arg2 = get_val(args[1]);

                data[q][k] = to_string(compute(arg1, arg2, op));
            }
        }
    }
}

// Retrieves a value from the table by accessing map
int Reader::get_val(const string &arg) {
    string col, row;

    if (!is_digits(arg)) {
        for (char it : arg) {
            if (!isdigit(it)) {
                col += it;
            } else {
                row += it;
            }
        }

        for (auto i: data) {
            // Checking array bounds
            if (data.size() >= rows[row] + 1 && data[0].size() >= columns[col] + 1) {
                // Making sure that the cell contains a number
                if (is_digits(data[rows[row] + 1][columns[col] + 1])) {
                    return stoi(data[rows[row] + 1][columns[col] + 1]);
                } else {
                    throw runtime_error("Nested cell contain symbols");
                }
            } else {
                throw runtime_error("Array bounds exceeded");
            }
        }
    } else {
        return stoi(arg);
    }
    return 0;
}

// Checking whether the string is a number
bool Reader::is_digits(const string &s) {
    return all_of(s.begin(), s.end(), ::isdigit);
}

// Implementing operations
int Reader::compute(int arg1, int arg2, char op) {
    switch (op) {
        case '+':
            return arg1 + arg2;
        case '-':
            return arg1 - arg2;
        case '*':
            return arg1 * arg2;
        case '/':
            if (arg2)
                return arg1 / arg2;
            else throw runtime_error("Dividing by zero");
        default:
            return 0;
    }
}

// Printing the result
void Reader::print() {
    for (const vector<string> &vec : data) {
        for (const string &value : vec) {
            cout << value;
            if (&value != &vec.back()) cout << ",";
        }
        cout << endl;
    }
}

int main(int argc, char **argv) {
    try {
        if (argc != 2) {
            throw invalid_argument("No file specified");
        } else {
            Reader csvfile(argv[1]);
            csvfile.read();
            csvfile.parse();
            csvfile.print();
        }
    }
    catch (exception &e) {
        cerr << e.what();
        return 1;
    }
    return 0;
}