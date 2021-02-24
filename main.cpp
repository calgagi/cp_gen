/*
 * CP Template Generator
 *
 * author: calgagi
 *         Calvin Gagliano 
 */

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>

using namespace std;

const string CP_GEN_AFTER = "./user.cpp";

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

string pathToGen() {
    char buff[512];

    // Linux syscall that gets the linked path to the current executable, "gen"
    ssize_t r = ::readlink("/proc/self/exe", buff, 511);
    if (r == -1) {
        error("Could not find path to current executable."); 
    }
    else {
        buff[r] = '\0';
    }

    // this assumes that gen is in the root directory of cp_gen (where lib is)
    string gen_path = buff;
    shavePath(gen_path);
    return gen_path;
}

// Output functions
void output_file(fstream& new_file, const string& file_path) {
    fstream to_output;
    to_output.open(file_path);
    if (!to_output.is_open()) {
        error("Could not find " + file_path + " file");
    }
    string line;
    while (getline(to_output, line)) {
        new_file << line << endl;
    }
    return;
}

void output_templates(fstream& new_file, const vector<string>& templates) {
    // this assumes that gen is in the root directory of cp_gen (where lib is)
    string gen_path = pathToGen();
    gen_path += "lib/";

    for (const string& ds : templates) {
        output_file(new_file, gen_path + ds + ".hpp");
        new_file << endl;
    }

    return;
}

void output(fstream& new_file, const string& filename, const vector<string>& templates) {
    // Static Header
    time_t now = time(0);
    new_file << "/*\n"
                "ID: calgagi\n"
                "LANG: C++\n"
                "TASK: " << noAfterDot(filename) << "\n"
                "*/\n"
                "\n"
                "#include <bits/stdc++.h>\n"
                "using namespace std;\n"
                "#define FILENAME_IN \"" << noAfterDot(filename) << ".in\"\n"
                "#define FILENAME_OUT \"" << noAfterDot(filename) << ".out\"\n"
                "#define ll long long\n"
                "#define ld long double\n\n";
    
    string gen_path = pathToGen();

    // Output templates
    output_templates(new_file, templates);
    new_file << "\n";

    new_file << "/* ===== BEGIN USER CODE ===== */\n\n";
    // User-defined after cp namespace file
    output_file(new_file, gen_path + CP_GEN_AFTER);

    return;
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);  
    cin.tie(NULL);

    char cwdBuf[10000];
    string cwd = "";
    if (getcwd(cwdBuf, sizeof(cwdBuf)) == NULL) {
        error("Could not get current working directory");
    } 
    else {
        cwd = cwdBuf;
    }

    // Parse CLI arguments
    vector<string> cliArgs;
    string filename = "";
    for (int i = 1; i < argc; i++) {
        cliArgs.push_back(argv[i]);
        if (cliArgs.back()[0] != '-') {
            // we've found our filename
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
    fstream new_file;
    new_file.open(path, ios_base::out);
    if (!new_file.is_open()) {
        error("Could not open file for output");
    }

    output(new_file, filename, cliArgs);

    return 0;
}
