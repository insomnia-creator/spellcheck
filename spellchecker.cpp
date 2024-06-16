#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#define vi vector<int>
#define vs vector<string>

using namespace std;
vs wordlist;

void readFileSync() {
  ifstream file;
  file.open("words.txt");
  if (file.fail()) {
    cout << "Failed at opening file";
    exit(-1);
  }

  string line;
  while (getline(file, line)) {
    line.pop_back();
    wordlist.push_back(line);
  }

  file.close();
}

int bestDistance(string s1, string s2) {

  vector<vi> matrix(s1.size() + 1, vector<int>(s2.size() + 1));

  for (int i = 0; i <= s1.size(); i++) {
    matrix[i][0] = i;
  }

  for (int i = 0; i <= s2.size(); i++) {
    matrix[0][i] = i;
  }

  for (int i = 1; i <= s1.size(); i++) {
    for (int j = 1; j <= s2.size(); j++) {
      int add = (s1[i - 1] != s2[j - 1]) * 1;
      matrix[i][j] = min(min(matrix[i][j - 1] + 1, matrix[i - 1][j] + 1),
                         matrix[i - 1][j - 1] + add);
    }
  }

  return matrix[s1.size()][s2.size()];
}

vector<string> check(string s) {

  map<int, vs> ind;
  int mn = INT_MAX;
  for (int i = 0; i < wordlist.size(); i++) {
    if (s == wordlist[i]) {
      vs q;
      q.push_back(s);
      return q;
    }

    int distance = bestDistance(s, wordlist[i]);
    ind[distance].push_back(wordlist[i]);
    mn = min(distance, mn);
  }

  vs r;

  for (int i = 0; i < min(5, (int)ind[mn].size()); i++) {
    r.push_back(ind[mn][i]);
  }
  return r;
}

int main() {
  // fastio
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  readFileSync();

  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    vector<string> res = check(s);

    for (int i = 0; i < res.size(); i++) {
      cout << res[i] << ", ";
    }
    cout << endl;
  }

  return 0;
}
