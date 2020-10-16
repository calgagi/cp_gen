/*
 * CP Template Generator
 *
 * author: calgagi
 *         Calvin Gagliano 
 */

#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

// Helper functions
void error(string msg) {
    cout << "cp_gen: " << msg << endl;
    exit(1);
}

string noAfterDot(const string& filename) {
    int where = filename.find(".");
    if (where == string::npos) {
        error("Could not find task in filename");
    } 
    return filename.substr(0, where);
}

void shavePath(string& path) {
    while (!path.empty() && path.back() != '/') {
        path.pop_back();
    }
    return;
}

// Output functions
void output_header(fstream& new_file, const bool& USACO, const string& usacoUsername, const string& filename) {
    // USACO header
    if (USACO) {
        new_file << "/*\nID: " << usacoUsername << "\nLANG: C++\nTASK: ";
        new_file << noAfterDot(filename) << "\n*/\n";
    }

    // Header
    time_t now = time(0);
    new_file << "/*\n * Generated by github.com/calgagi/cp_gen\n * file: " << filename << "\n * time: " << ctime(&now) << " */\n\n";

    new_file << "#include<bits/stdc++.h>\n\n"
                "using namespace std;\n\n";
    
    return;
}

void output_templates(fstream& new_file, const vector<string>& templates, const string& path) {
    char buff[512];
    // Linux syscall that gets the linked path to the current executable, "gen"
    ssize_t r = ::readlink("/proc/self/exe", buff, 511);
    if (r == -1) {
        error("Could not find path to current executable. If you are not on Linux, this is because the readlink syscall does not exist");
    }
    else {
        buff[r] = '\0';
    }

    // this assumes that gen is in the root directory of cp_gen (where lib is)
    string gen_path = buff;
    shavePath(gen_path); 
    gen_path += "lib/";

    for (const string& ds : templates) {
        fstream in_file;
        in_file.open(gen_path + ds + ".hpp");
        if (!in_file.is_open()) {
            error("Could not find file " + ds + ".hpp in " + gen_path);
        }
        string line;
        while (getline(in_file, line)) {
            new_file << line << endl;
        }
        new_file << endl;
    }

    return;
}

void output_main(fstream& new_file, const bool& USACO, const string& usacoUsername, const bool& PRINT_TC, const string& filename) {
    // solve() function
    new_file << "void solve() {\n"
                "    return;\n"
                "}\n\n";

    // main() function
    new_file << "int main() {\n"
                "    ios_base::sync_with_stdio(false);\n"
                "    cin.tie(NULL);\n"
                "    srand(chrono::steady_clock::now().time_since_epoch().count());\n\n";

    // USACO files
    if (USACO) {
        new_file << "    FILE *IN = freopen(\"" << noAfterDot(filename) << ".in\", \"r\", stdin);\n"
                    "    FILE *OUT = freopen(\"" << noAfterDot(filename) << ".out\", \"w\", stdout);\n\n";
    }

    new_file << "    int num_tests = 1;\n"
                "    // cin >> num_tests;\n"
                "    for (int i = 0; i < num_tests; i++) {\n";

    if (PRINT_TC) {
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

    char cwdBuf[10000];
    string cwd = "";
    if (getcwd(cwdBuf, sizeof(cwdBuf)) == NULL) {
        error("Could not get current working directory");
    } 
    else {
        cwd = cwdBuf;
    }

    vector<string> cliArgs;
    bool USACO = false, PRINT_TC = false;
    string filename = "", usacoUsername = "";
    fstream new_file;
    for (int i = 1; i < argc; i++) {
        cliArgs.push_back(argv[i]);
        if (cliArgs.back() == "-u") {
            USACO = true;
            cliArgs.pop_back();
            if (++i < argc) {
                usacoUsername = argv[i];
            }
            else {
                error("Expected USACO username after -u flag");
            }
        } 
        else if (cliArgs.back() == "-p") {
            PRINT_TC = true;
            cliArgs.pop_back();
        } 
        else if (cliArgs.back()[0] != '-') {
            filename = cliArgs.back();
            cliArgs.pop_back();
        }
        else {
            // remove leading '-'
            cliArgs.back().erase(cliArgs.back().begin());
        }
    }

    if (filename == "") {
        error("Could not find filename");
    }

    string path = cwd + "/" + filename;
    new_file.open(path, ios_base::out);
    if (!new_file.is_open()) {
        error("Could not open file for output");
    }

    output_header(new_file, USACO, usacoUsername, filename);

    output_templates(new_file, cliArgs, path);

    output_main(new_file, USACO, usacoUsername, PRINT_TC, filename);

    return 0;
}
