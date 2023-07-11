#include <bits/stdc++.h>
using namespace std;

time_t current_time = time(NULL);

void removeSpaces(string &s1)
{
    string ans = "";
    for (int i = 0; i < s1.length(); i++)
    {
        int j = 0;
        for (; j < s1.length() && s1[j] != ' '; j++)
        {
            ans += s1[j];
        }
        i = j;
    }
    s1 = ans;
}

int gcd(int a, int b){
    if(a==0)
        return b;
    if(a<b){
        return gcd(b, a); 
    }
    return gcd(a % b, b);
}

int gcdExtended(int a)
{
    for (int i = 0; i < 26; i++){
        if((i*a)%26 == 1){
            return i; 
        }
    }
    return -1; 
}

string encryptAffine(string &s1, int a, int b){
    string ans = "";
    for (int i = 0; i < s1.length(); i++){
        ans += char('a' + ( a*int(s1[i]-'a') + b )%26 ); 
    }
    return ans; 
}

string decryptAffine(string &s1, int a, int b){
    int x = gcdExtended(a);
    string ans = "" ; 
    for (int i = 0; i < s1.length(); i++){
        int p1 = (s1[i] - 'a') - b + 26 ;
        p1 %= 26 ; 
        int ans1 = (x * (p1)) ;
        ans1 %= 26;  
        ans += char('a' + (ans1)); 
    }
    return ans;
}

void cryptoAnalysis(vector<int> &a, string &s1, string &check){
    cout << "Possible Decryption are: " << endl;
    int indx = -1; 
    for (int i = 0; i < a.size(); i++){
        for(int j =0 ;  j<26 ; j++){
            string a1 = decryptAffine(s1, a[i], j); 
            cout<< (26 * i + j) << ' ' << a1 << endl;
            if( a1 == check){
                indx = 26*i + j ; 
            }
        }
    }
    cout << indx << endl; 
}


int main()
{

    string s = "helloeveryonemynameismuditjainiamtwentyyearsoldistudyiniitjammu"; 

    srand((unsigned)time(NULL));
    vector<int> pos_a;
    for (int i = 1; i < 26; i++){
        if(gcd(i, 26) == 1){
            pos_a.push_back(i); 
        }
    }
    removeSpaces(s);

    int a = rand()%(pos_a.size()) ;
    int b = rand() % 26;

    string encryptedStr = encryptAffine(s, pos_a[a], b);
    string decryptedStr = decryptAffine(encryptedStr, pos_a[a], b);

    cout << encryptedStr << endl
         << decryptedStr << endl;

    cout << endl;
    cryptoAnalysis(pos_a, encryptedStr, decryptedStr);

    return 0;
}
