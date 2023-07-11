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

string shiftEncrypt(string &s1, int k)
{
    string ans = "";
    for (char letter : s1)
    {
        int m = (letter -'a') + k;
        m %= 26;
        ans += char(m + 'a');
    }
    return ans;
}

string shiftDecrypt(string &s1, int k)
{
    string m = "";
    for (int i = 0; i < s1.length(); i++)
    {
        int letterInt = (s1[i]-'a') - k;
        letterInt = (letterInt + 26 )%26;
        m += char('a' + letterInt);
    }

    return m;
}

vector<string> shiftCryptAnalysis(string &s1)
{
    vector<string> ans;
    for (int k = 0; k < 26; k++)
    {
        ans.push_back(shiftDecrypt(s1, k));
    }
    return ans;
}

int main()
{
    string s = "iitjammu";
    srand((unsigned)time(NULL));
    int key = rand();
    key %= 26; 
    cout << key << endl;
    removeSpaces(s);
    string shiftEncryption = shiftEncrypt(s, key);
    cout << "ENCRYPTED TEXT IS : " << shiftEncryption << endl;

    string DecryptShift = shiftDecrypt(shiftEncryption, key);
    cout << "DECRYPTED TEXT IS : " << DecryptShift << endl;

    vector<string> posDecryptShift = shiftCryptAnalysis(shiftEncryption);
    cout << "POSSIBLE DECRYPTIONS ARE:" << endl;
    for(auto x: posDecryptShift){
        cout << x << endl; 
    }

    

    return 0; 
}
