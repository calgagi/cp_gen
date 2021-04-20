mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
void preprocess();
void solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    preprocess();

    int tests = 1;
    cin >> tests;
    for (int tc = 1; tc <= tests; tc++) {
        cout << "Case #" << tc << ": ";
        solve();
    }

    return 0;
}

void preprocess() {

}

void solve() {

}
