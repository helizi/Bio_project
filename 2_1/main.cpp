#include<iostream>
#include<fstream>

using namespace std;

int dp[9000][19000];

pair <int,int> aligner(string ref, string read){
    int n = ref.size();
    int m = read.size();
    int match = 1;
    int mismatch = -2;
    int gap_open = -3;;
    for (int i = 0; i < n+1; i++) {
        dp[0][i] = 0;
    }
    for (int i = 1; i < m+1; i++) {
        dp[i][0] = dp[i - 1][0] + gap_open;
    }
    for (int i = 1; i < n+1; i++){
        for (int j = 1; j < m+1; j++){
            if (ref[i-1] == read[j-1]){
                dp[j][i] = max(dp[j-1][i-1] + match, max(dp[j-1][i] + gap_open, dp[j][i-1] + gap_open));
            }
            if (ref[i-1] != read[j-1]){
                dp[j][i] = max(dp[j-1][i-1] + mismatch, max(dp[j-1][i] + gap_open, dp[j][i-1] + gap_open));
            }
        }
    }
    int maximum = -1e9;
    int endIndexi = 0;
    for (int i = 0; i < n +1; i++){
        if (dp[m][i] > maximum) {
            maximum = dp[m][i];
            endIndexi = i;
        }
    }
    int indexi = endIndexi;
    int indexj = m;
    while (indexj > 0) {
		if (dp[indexj][indexi] == dp[indexj - 1][indexi] + gap_open){indexj -= 1;}
        else if(dp[indexj][indexi] == dp[indexj][indexi - 1] + gap_open){indexi -= 1;}
        else if(dp[indexj][indexi] == dp[indexj - 1][indexi - 1] + mismatch && ref[indexi - 1] != read[indexj - 1]){
            indexi -= 1;
            indexj -= 1;
        }
        else if(dp[indexj][indexi] == dp[indexj - 1][indexi - 1] + match && ref[indexi - 1] == read[indexj - 1]){
            indexi -= 1;
            indexj -= 1;
        }

    }
    int startIndexi = indexi;
    return make_pair(startIndexi, endIndexi - 1);
}
int main() {
    string genome[5];
    string dict[] = {"Reston_genome", "Sudan_genome", "TaiForest_genome", "Zaire_genome", "Bundibugyo_genome"};
    string dict2[] = {"NP", "VP35", "VP40", "GP", "VP30", "VP24", "L"};
    for (int i = 0; i < 5; i++) {
        ifstream cin("BioProjectFiles/" + dict[i] + ".fasta");
        string s;
        cin >> s;
        cin >> s;
        while (cin >> s) {
            genome[i] += s;
        }
    }
    ifstream cin("BioProjectFiles/Marburg_Genes.fasta");
    string genes[7];
    string s;
    cin >> s;
    for (int i = 0; i < 7; i++) {
        string gene = "";
        while (cin >> s) {
            if (s[0] == '>') {
                break;
            }
            gene += s;
        }
        genes[i] = gene;
    }
    ofstream cout("a.txt");
    pair <int,int> alignes[5][7];
    for (int i= 0; i < 7; i++){
        for(int j = 0; j < 5; j++){
            alignes[j][i] = aligner(genome[j], genes[i]);
            cout << dict[j] << " " << dict2[i] << " " << alignes[j][i].first << " " << alignes[j][i].second <<endl;
        }
    }

}
