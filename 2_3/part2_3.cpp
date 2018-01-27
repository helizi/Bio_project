#include<iostream>
#include<fstream>

using namespace std;

int dp[19000][19000];

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
    ifstream cin("a.txt");
    string ref, read;
    int start, finish;
    pair <int,int> indexes[5][7];
    for (int i = 0; i < 7; i++){
        for(int j = 0; j < 5; j++){
        	cin>>ref>>read>>start>>finish;
			indexes[j][i] = make_pair(start, finish);
        }
    }
    int edit_distance[7][5][5];
    for (int i = 0; i < 7; i++){
        ofstream cout(dict2[i] +".csv");
        for (int j = 0; j < 5; j++){
            cout<< dict[j];
            if(j != 4){
                cout<<",";
            }
        }
        cout<<endl;
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
				string ref1 = genome[j].substr(indexes[j][i].first,indexes[j][i].second - indexes[j][i].first + 1);
                string ref2 = genome[k].substr(indexes[k][i].first,indexes[k][i].second - indexes[k][i].first + 1);
                edit_distance[i][j][k] = aligner(ref1,ref2);
           		cout<<edit_distance[i][j][k];
                if(k!=4){
                    cout<<",";
                }
			}
			cout<<endl;
        }
    }
}
