#include<iostream>
#include<fstream>

using namespace std;

int dp[20000][20000];

int aligner(string ref, string read){
    int n = ref.size();
    int m = read.size();
    int match = 0;
    int mismatch = 1;
    int gap_open = 1;
    for (int i = 0; i < n+1; i++) {
        dp[0][i] = i;
    }
    for (int i = 1; i < m+1; i++) {
        dp[i][0] = i;
    }
    for (int i = 1; i < n+1; i++){
        for (int j = 1; j < m+1; j++){
            if (ref[i-1] == read[j-1]){
                dp[j][i] = min(dp[j-1][i-1] + match, min(dp[j-1][i] + gap_open, dp[j][i-1] + gap_open));
            }
            if (ref[i-1] != read[j-1]){
                dp[j][i] = min(dp[j-1][i-1] + mismatch, min(dp[j-1][i] + gap_open, dp[j][i-1] + gap_open));
            }
        }
    }

    return dp[m][n];
}

int main() {
    string genome[6];
    string dict[] = {"Reston_genome", "Sudan_genome", "TaiForest_genome", "Zaire_genome", "Bundibugyo_genome","Marburg_genome"};
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

    ifstream cin("BioProjectFiles/Marburg_genome.fasta");
    string s;
    cin >> s;
    cin >> s;
    while (cin >> s) {
        genome[5] += s;
    }
    cout<<genome[5].size()<<endl;
    int alignes[6][6];
    ofstream fout("3-4.csv");
    for (int j = 0; j < 6; j++){
        fout<< dict[j];
        if(j != 5){
            fout<<",";
        }
    }
    fout<<endl;
    for (int i = 0; i < 6; i++){
        for (int j = i+1; j < 6; j++){
            alignes[i][j] = aligner(genome[i], genome[j]);
            alignes[j][i] = alignes[i][j];
        }
    }
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++){
            if(i == j){
                fout<<0;
            }
            else{
                fout<<alignes[i][j];
            }
            if (j!=5){
                fout<<",";
            }
        }
        fout<<endl;
    }
}




