string get_until(const string& in, int& start, char delim = '\0') {
    string ans = "";
    while (start < (int) in.length() && in[start] != delim) {
        ans += in[start];
        start++;
    }
    return ans;
}


