#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vvi vector<vector<int>>
#define N 16
// #define ITER 1<<16

time_t current_time = time(NULL);
const int checkVal = (27*20000)/(1024); 

vi SBox = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7};
vi PermLayer = {0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15};
vi revSBox(16), revPermLayer(16);

vector<int> XorVectors(vi &a1, vi &a2){
    vi ans(16) ; 
    for (int i = 0; i < 16; i++){
        ans[i] = a1[i] ^ a2[i]; 
    }
    return ans;
}

void sBoxFunc(vi &ans)
{
    for (int i = 0; i < N;)
    {
        int j = 0;
        int sum = 0;
        for (; j < 4; j++)
        {
            sum += ans[i + j] << (3 - j);
        }
        int val = SBox[sum];
        j = 0;
        for (; j < 4; j++)
        {
            ans[i + j] = (val & (1 << (3 - j))) >> (3 - j);
        }
        i += j;
    }
}

void revSBoxFunc(vi &arr)
{

    for (int i = 0; i < N;)
    {
        int j = 0;
        int sum = 0;
        for (; j < 4; j++)
        {
            sum += arr[i + j] << (3 - j);
        }
        // cout << sum << endl;
        int val = revSBox[sum];
        j = 0;
        for (; j < 4; j++)
        {
            arr[i + j] = (val & (1 << (3 - j))) >> (3 - j);
        }
        i += j;
    }
}

vector<int> fullForwardSPN(vvi &keys, vi &input)
{
    vector<int> ans = input;
    for (int i = 0; i < 3; i++)
    {
        // key xor layer
        for (int j = 0; j < 16; j++)
        {
            ans[j] = keys[i][j] ^ ans[j];
        }
        // sbox
        sBoxFunc(ans);
        // permutation
        vector<int> cp(16);
        for (int j = 0; j < 16; j++)
        {
            cp[j] = ans[j];
        }
        for (int j = 0; j < 16; j++)
        {
            ans[PermLayer[j]] = cp[j];
        }
    }

    // final layer

    // key
    for (int i = 0; i < 16; i++)
    {
        ans[i] = keys[3][i] ^ ans[i];
    }
    // SPN
    sBoxFunc(ans);
    // np permutation
    // final xor
    for (int i = 0; i < 16; i++)
    {
        ans[i] = keys[4][i] ^ ans[i];
    }

    return ans;
}

int main()
{

    // #ifndef ONLINE_JUDGE
    // freopen("input.txt","r",stdin); //file input.txt is opened in reading mode i.e "r"
    // freopen("output.txt","w",stdout);  //file output.txt is opened in writing mode i.e "w"
    // #endif

    srand((unsigned)time(NULL));
    // master key
    vi masterKey(48);
    for (int i = 0; i < 48; i++)
        masterKey[i] = rand() % 2;
    // cout << "hello1" << endl;
    // making keys
    vvi keys(5, vi(16));
    for (int i = 0; i < 5; i++)
    {
        for (int it = 0; it < 16; it++)
        {
            keys[i][it] = masterKey[(i + it) % 16];
        }
    }

    for (int i = 0; i < N; i++)
    {
        revPermLayer[PermLayer[i]] = i;
    }

    for (int i = 0; i < N; i++)
    {
        revSBox[SBox[i]] = i;
    }

    // m1 -> know what differential at input is needed to get desired difference
    // differential -> 0000 1111 0000 1111
    // ip differential -> 0000 1011 0000 1111
    vi op = {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0};
    vi differential = {0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    int maxVal = INT_MAX;
    vi ansKey; 
    for (int i = 0; i<(1<<8) ; i++){
        vi testKey(16, 0);
        testKey[4] = (i & (1 << 7)) >> 7;
        testKey[5] = (i & (1 << 6)) >> 6;
        testKey[6] = (i & (1 << 5)) >> 5;
        testKey[7] = (i & (1 << 4)) >> 4;
        testKey[12] = (i & (1 << 3)) >> 3;
        testKey[13] = (i & (1 << 2)) >> 2;
        testKey[14] = (i & (1 << 1)) >> 1;
        testKey[15] = (i & (1 << 0)) >> 0;
        
        set<vi> s;
        int cnt = 0; 
        // generate 16 bit random input 
        for(int i = 0 ;  i<20000 ; i++){
            vi ip1; 
            for (int j = 0; j<16 ; j++){
                ip1.push_back(rand() % 2); 
            }
            if(s.find(ip1)!=s.end()){
                i--;
                continue;  
            }
            vi ip2(16); 
            ip2 = XorVectors(ip1, differential); 
            vi ans1 = fullForwardSPN(keys, ip1);
            vi ans2 = fullForwardSPN(keys, ip2);

            // go one step back using test key 
            ans1 = XorVectors(ans1, keys[4]);
            ans2 = XorVectors(ans2, keys[4]); 
            
            // rev SBox
            revSBoxFunc(ans1);
            revSBoxFunc(ans2); 

            vi check = XorVectors(ans1, ans2); 

            // check if this is equal to cnt or not
            int it = 4;
            for (; it < 16; it++){
                if(it==8){
                    it = 12;
                }
                if(check[it]!=op[it])
                    break; 
            }
            if(it==16)
                cnt++;
        }
            cout << cnt << endl ; 
            for(int x: testKey) cout<<x<<' ' ;
            cout << endl;

        int diff = abs(cnt - checkVal); 
         
        if(diff < maxVal){
            maxVal = diff; 
            ansKey = testKey ; 
        }
    }
    cout << "ACTUAL: " << "  "; 
    for (int i = 0; i < 16; i++)
    {
        cout << keys[4][i] << ' ';
        if (i % 4 == 3)
            cout << ' ';
    }
    cout << endl;
    cout << "GUESSED: " << ' '; 
    for (int i = 0; i < 16; i++)
    {
        cout << ansKey[i] << ' ';
        if (i % 4 == 3)
            cout << ' ';
    }
    cout << endl; 
    cout<<checkVal<<endl; 
 
        return 0;
}
