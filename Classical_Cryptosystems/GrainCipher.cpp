#include <bits/stdc++.h>
using namespace std;
#define N 80
#define M 64

time_t current_time = time(NULL);
// n => 80
// LFSR => n bit
// NFSR -> n bit
// h(xt, yt)
vector<int> lfsr_arr(N, 0);
vector<int> nfsr_arr(N, 0);
int A[] = {1, 2, 4, 10, 31, 43, 56}; 


int lfsr(int in = 0 )
{
    int ans = lfsr_arr[62] ^ lfsr_arr[51] ^ lfsr_arr[38] ^ lfsr_arr[23] ^ lfsr_arr[13] ^ in ;
    for (int i = N - 1; i >= 0; i--)
    {
        int x = lfsr_arr[i];
        lfsr_arr[i] = ans;
        ans = x;
    }
    return ans;
}

int nonLinearFunc()
{
    return nfsr_arr[62] ^
           nfsr_arr[60] ^
           nfsr_arr[52] ^
           nfsr_arr[45] ^
           nfsr_arr[37] ^
           nfsr_arr[33] ^
           nfsr_arr[28] ^
           nfsr_arr[21] ^
           nfsr_arr[14] ^
           nfsr_arr[9] ^
           nfsr_arr[0] ^
           (nfsr_arr[63] & nfsr_arr[60]) ^
           (nfsr_arr[37] & nfsr_arr[33]) ^
           (nfsr_arr[15] & nfsr_arr[9]) ^
           (nfsr_arr[60] & nfsr_arr[52] & nfsr_arr[45]) ^
           (nfsr_arr[33] & nfsr_arr[28] & nfsr_arr[21]) ^
           (nfsr_arr[63] & nfsr_arr[45] & nfsr_arr[28] & nfsr_arr[9]) ^
           (nfsr_arr[60] & nfsr_arr[52] & nfsr_arr[37] & nfsr_arr[33]) ^
           (nfsr_arr[63] & nfsr_arr[60] & nfsr_arr[21] & nfsr_arr[15]) ^
           (nfsr_arr[63] & nfsr_arr[60] & nfsr_arr[52] & nfsr_arr[45] & nfsr_arr[37]) ^
           (nfsr_arr[33] & nfsr_arr[28] & nfsr_arr[21] & nfsr_arr[15] & nfsr_arr[9]) ^
           (nfsr_arr[52] & nfsr_arr[45] & nfsr_arr[37] & nfsr_arr[33] & nfsr_arr[28] & nfsr_arr[21]) ;
}

int h_func(int s0, int s1, int s2, int s3, int s4){
    return s1 ^ s4 ^ (s0 & s3) ^ (s2 & s3) ^ (s3 & s4) ^ (s0 & s1 & s2) ^ (s0 & s2 & s3) ^ (s0 & s2 & s4) ^ (s1 & s2 & s4) ^ (s2 & s3 & s4); 
}

int nfsr(int yt, int ip2 = 0 )
{
    int ans = yt ^ (nonLinearFunc())^ip2;
    for (int i = N - 1; i >= 0; i--)
    {
        int x = nfsr_arr[i];
        nfsr_arr[i] = ans;
        ans = x;
    }
    return ans;
}

int zt(){
    int ans1 = h_func(lfsr_arr[3], lfsr_arr[25], lfsr_arr[46], lfsr_arr[64], nfsr_arr[63]);
    int ans = 0;
    for (int i = 0; i < sizeof(A) / sizeof(int); i++){
        ans = ans ^ (nfsr_arr[A[i]] ^ ans1); 
    }
    return ans; 
}

void printVec(vector<int> v){
    for (int i = 0; i < v.size(); i++){
        cout << v[i]; 
    }
    cout << endl;
}

int main()
{
    srand((unsigned)time(NULL));
    freopen("msg_processed.txt", "r", stdin);
    string s;
    cin >> s; 

    for (int i = 0; i < N; i++)
    {
        nfsr_arr[i] = rand() % 2;
        }

    for (int i = 0; i < M; i++){
        lfsr_arr[i] = rand() % 2; 
    }
    for (int i = M; i < N; i++){
        lfsr_arr[i] = 1; 
    }

    cout<<"NFSR IS : " ;
    for (int i = 0; i < N; i++){
        cout << nfsr_arr[i]; 
    }
    cout << endl;

    cout << "LFSR IS : ";
    for (int i = 0; i < N; i++)
    {
        cout << lfsr_arr[i];
    }
    cout << endl;

    int zt_ = 0; 
    for (int i = 0; i < 2 * N; i++){
        int b1 = lfsr(zt_) ;
        // cout << b1 << endl;
        int b2 = nfsr(b1, zt_) ;
        // cout << b2 << endl; 
        zt_ = zt(); 
        
    }

    cout << "NFSR IS : ";
    for (int i = 0; i < N; i++)
    {
        cout << nfsr_arr[i];
    }
    cout << endl;

    cout << "LFSR IS : ";
    for (int i = 0; i < N; i++)
    {
        cout << lfsr_arr[i];
    }
    cout << endl;

    vector<int> key;
    vector<int> binInput;
    vector<int> binOutput; 

    for (int i = 0; i < s.length(); i++){
        int x = int(s[i]);
        for (int j = 7; j >= 0; j--){
            binInput.push_back((x & (1 << j)) >> j); 
        }
    }

    for (int i = 0; i < binInput.size(); i++){
        int b1 = lfsr();
        int b2 = nfsr(b1);
        int zt_ = zt();
        binOutput.push_back(zt_ ^ binInput[i]);
        key.push_back(zt_);
    }

    printVec(key);
    printVec(binInput);
    printVec(binOutput); 



    return 0;
}
