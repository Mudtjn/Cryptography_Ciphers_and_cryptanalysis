#include <bits/stdc++.h>
using namespace std;

time_t current_time = time(NULL);

float freq[26] = {0.082, 0.015, 0.028, 0.043,
                  0.127, 0.022, 0.020, 0.061,
                  0.070, 0.002, 0.008, 0.04,
                  0.024, 0.067, 0.075, 0.019,
                  0.001, 0.06, 0.063, 0.091,
                  0.028, 0.01, 0.023, 0.001,
                  0.020, 0.001};

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

void removeCapsAndCapitals(string &s)
{
    string ans = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            ans += char(s[i] + 32);
        }
        else if (s[i] >= 'a' && s[i] <= 'z')
            ans += s[i];
    }
    s = ans;
}

string encrypt(string s, int r, vector<int> &keys)
{
    string ans = "";
    for (int i = 0; i < s.size(); i++)
    {
        ans += char(((s[i] - 'a' + keys[i % r]) % 26) + 'a');
    }
    return ans;
}

string decrypt(string s, int r, vector<int> &keys)
{
    string ans = "";
    for (int i = 0; i < s.size(); i++)
    {
        int x = (s[i] - 'a' - keys[i % r]);
        while (x <= 0)
            x += 26;
        ans += char((x % 26) + 'a');
    }
    return ans;
}

int getBestShift(string &s)
{
    int len = s.length();
    vector<int> freq1(26, 0);
    for (int i = 0; i < s.length(); i++)
        freq1[s[i] - 'a']++;

    int bestShiftAmount = 0;
    float minShiftCost = 1000.000;
    for (int i = 0; i < 26; i++)
    {
        vector<int> arr(26, 0);

        // shift the array
        for (int j = 0; j < 26; j++)
        {
            int newIndex = (j + i) % 26;
            arr[newIndex] = freq1[j];
        }
        // calculate diff
        float shiftCost = 0.000;
        for (int j = 0; j < 26; j++)
        {
            float x = (arr[j] * 1.0) / (len * 1.0);
            shiftCost += abs(freq[j] - x);
            // cout<<"SHIFT COST IS = " << shiftCost << endl;
        }
        if (shiftCost <= minShiftCost)
        {
            bestShiftAmount = i;
            minShiftCost = shiftCost;
        }
        // bestShiftAmount = rand() % 26;
    }
    return bestShiftAmount;
}

string possibleDecryption(string &s, int key)
{
    // dividing the key into strings
    vector<string> v(key);
    for (int i = 0; i < s.length(); i++)
    {
        v[i % key] += s[i];
    }

    // getting best shift for each string
    for (int i = 0; i < key; i++)
    {
        int shiftAmount = getBestShift(v[i]);
        cout << shiftAmount << endl;
        string ans = "";
        for (int j = 0; j < v[i].length(); j++)
        {
            int newChar = ((v[i][j] - 'a') + shiftAmount);
            while (newChar < 0)
                newChar += 26;
            newChar %= 26;
            ans += char('a' + newChar);
        }
        v[i] = ans;
    }

    int totalLength = 0, maxLength = 0;
    for (int i = 0; i < v.size(); i++)
    {
        int x = v[i].length();
        maxLength = max(maxLength, x);
        totalLength += v[i].length();
    }

    string final_ans = "";
    int it = 0;
    for (int j = 0; j < maxLength; j++)
    {
        for (int i = 0; i < v.size(); i++)
        {
            if (it < v[i].length())
                final_ans += v[i][it];
        }
        it++;
    }
    return final_ans;
}

// CRYPTANALYSIS

float getProb(string &en, int r)
{
    // cout<<"Calculting for r = "<<r<<endl;
    int len = en.length();
    float netSum = 0.0;
    for (int st = 0; st < min(r, len); st++)
    {
        vector<int> freq(26);
        int totalLen = 0;
        for (int i = st; i < len; i += r)
        {
            freq[en[i] - 'a']++;
            totalLen++;
        }
        float subSum = 0.0;
        for (int i = 0; i < 26; i++)
        {
            float x = freq[i] / (totalLen * 1.0);
            x *= x; 
            subSum += x;
            // cout << freq[i] << ' ';
        }
        float z = subSum - 0.065 ;  
        if(z<0)
            z *= -1; 
        netSum += z;

        // cout<<"= "<<abs(subSum-0.065);
        // cout << endl;
    }
    return netSum/r ;
}

int getLengthOfKey(string &en)
{
    int len = en.size();
    int s = 3, e = min(26, len);
    float minProb = INT_MAX;
    int bestShift = INT_MAX;
    for (int i = s; i <= e; i++)
    {
        float x = getProb(en, i);
        // cout << x << endl;
        if (x < minProb)
        {
            minProb = x;
            bestShift = i;
        }
    }
    return bestShift;
}

int main()
{
    srand((unsigned)time(NULL));
    freopen("msg_processed.txt", "r", stdin);
    string s;
    cin >> s;
    int r = rand();
    r %= 26;
    r++;
    cout << "R IS : " << r << endl;
    vector<int> keys(r);
    for (int i = 0; i < r; i++)
    {
        keys[i] = rand();
        keys[i] %= 26;
        cout << keys[i] << ' ';
    }
    cout << endl;

    string en = encrypt(s, r, keys);
    // cout << en << endl;
    string dec = decrypt(en, r, keys);
    // cout << dec << endl;
    // cout << "-------------------------------------------------" << endl;
    int aptLength = getLengthOfKey(en);
    cout << aptLength << endl;
    // cout << possibleDecryption(en, aptLength) << endl;

    if(dec == s){
        cout<<"STRING DECRYPTED CORRECTLY"<<endl; 
    }

    return 0;
}

/**
 * @brief cryptanalysis
 * get the apt length of the r
 * -> text after r characters should appear shifted and follow same distribution
 * --> this means this distribution should be as close to 0.065 as possible
 *
 */
