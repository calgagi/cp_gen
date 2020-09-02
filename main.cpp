/*
 * CP Template Generator
 *
 * author: calgagi
 *         Calvin Gagliano 
 */

#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
#define ld long double
#define ll long long

fstream new_file;
vector<string> CLI_args;
string cwd, filename;
const string USACO_USERNAME = "calgagi1";
bool CASE_NUMBERS = 0, USACO_PRESENT = 0;

void error(string msg) {
    cout << "cp_gen: " << msg << endl;
    exit(1);
}

void parse_args() {
    int num_args = CLI_args.size();

    for (int i = 0; i < num_args; i++) {
        if (CLI_args[i] == "-c") {
            // CASE_NUMBER
            CASE_NUMBERS = 1; 
        }
        else if (CLI_args[i] == "-u") {
            USACO_PRESENT = 1; 
        }
        else {
            filename = CLI_args[i];
            string path = cwd + "/" + CLI_args[i];
            new_file.open(path, ios_base::out);
            if (!new_file.is_open()) {
                error("Could not open file for output");
            }
        }
    }

    return;
}

string get_task() {
    int where = filename.find(".");
    if (where == string::npos) {
        error("Could not find task in filename");
    } 
    return filename.substr(0, where);
}

void output_file() {
    // USACO header
    if (USACO_PRESENT) {
        new_file << "/*\nID: " << USACO_USERNAME << "\nLANG: C++\nTASK: ";
        new_file << get_task() << "\n*/\n";
    }

    // Header
    time_t now = time(0);
    new_file << "/*\n * author: calgagi\n * file: " << filename << "\n * time: " << ctime(&now) << " */\n\n";

    new_file << "#include<bits/stdc++.h>\n\n"
                "using namespace std;\n"
                "#define ld long double\n"
                "#define ll long long\n\n";
    
    // solve() function
    new_file << "void solve() {\n"
                "    \n"
                "    \n"
                "    return;\n"
                "}\n\n";

    // main() function
    new_file << "int main() {\n"
                "    ios_base::sync_with_stdio(false);\n"
                "    cin.tie(NULL);\n"
                "    srand(chrono::steady_clock::now().time_since_epoch().count());\n\n";

    // USACO files
    if (USACO_PRESENT) {
        new_file << "    FILE *IN = freopen(\"" << get_task() << ".in\", \"r\", stdin);\n"
                    "    FILE *OUT = freopen(\"" << get_task() << ".out\", \"w\", stdout);\n\n";
    }

    new_file << "    int num_tests = 1;\n"
                "    /* cin >> num_tests; */\n"
                "    for (int i = 0; i < num_tests; i++) {\n";

    if (CASE_NUMBERS) {
        new_file << "        cout << \"Case #\" << i+1 << \": \";\n";
    }

    new_file << "        solve();\n"
                "    }\n\n"
                "    return 0;\n"
                "}\n";
             
    return;
 
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);  
    cin.tie(NULL);
    srand(chrono::steady_clock::now().time_since_epoch().count()); 

    for (int i = 1; i < argc; i++) {
        CLI_args.push_back(argv[i]);
    }

    char cwd_buf[10000];
    if (getcwd(cwd_buf, sizeof(cwd_buf)) == NULL) {
        error("Could not get current working directory");
    } else {
        cwd = cwd_buf;
    }

    // Parse args
    parse_args();

    if (filename == "") {
        error("No filename found");
    }

    // Output file
    output_file();

    return 0;
}
