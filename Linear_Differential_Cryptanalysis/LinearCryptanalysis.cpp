#include<bits/stdc++.h>
using namespace std ;
#define vi vector<int>
#define vvi vector<vector<int>>
#define N 16
// #define ITER 1<<16

time_t current_time = time(NULL);

vi SBox = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 };
vi PermLayer = { 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15 };
vi revSBox(16), revPermLayer(16) ; 

void sBoxFunc(vi &ans){
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


vector<int> fullForwardSPN(vvi &keys, vi &input){
	vector<int> ans = input; 
	for(int i = 0;  i<3;  i++){
		// key xor layer
		for(int j = 0; j<16; j++){
			ans[j] = keys[i][j]^ans[j] ; 
		}
		// sbox 
		sBoxFunc(ans); 
		// permutation
		vector<int> cp(16) ;
		for(int j = 0 ; j<16 ; j++){
			cp[j] = ans[j] ; 
		} 
		for(int j = 0 ; j<16 ; j++){
			ans[PermLayer[j]] = cp[j]; 
		}
	}

	// final layer 

	// key
	for(int i = 0;  i<16 ; i++){
		ans[i] = keys[3][i]^ans[i] ; 
	}
	//SPN
	sBoxFunc(ans); 
	// np permutation
	// final xor
	for(int i =0 ; i<16 ;i++){
		ans[i] = keys[4][i]^ans[i] ;
	}

	return ans; 
}

int main(){

	// #ifndef ONLINE_JUDGE
	// freopen("input.txt","r",stdin); //file input.txt is opened in reading mode i.e "r"
	// freopen("output.txt","w",stdout);  //file output.txt is opened in writing mode i.e "w"
	// #endif

	srand((unsigned)time(NULL));
	// master key
	vi masterKey(48); 
	for(int i = 0 ; i<48 ; i++) masterKey[i] = rand()%2 ;
	// cout << "hello1" << endl;
	// making keys
	vvi keys(5,vi(16)); 
	for(int i = 0 ; i<5 ; i++){
		for(int it = 0 ; it<16 ; it++){
			keys[i][it] = masterKey[(i+it)%16] ; 
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

	// for getting u values go backwards using keys
	int ans1 = INT_MAX ;
	vi validKey ;  
	for(int i = 0 ; i<(1<<8) ; i++){
		vi testKey(16,0) ;
		// fill values in key 4-7 and 11-15
		// cout << "hello " << (i + 2) << endl; 
		cout<<"---------------------------------------"<<endl ; 
		testKey[4] = (i&(1<<7))>>7 ;
		testKey[5] = (i&(1<<6))>>6 ;
		testKey[6] = (i&(1<<5))>>5 ;
		testKey[7] = (i&(1<<4))>>4 ;
		testKey[12] = (i&(1<<3))>>3 ;
		testKey[13] = (i&(1<<2))>>2 ;
		testKey[14] = (i&(1<<1))>>1 ;
		testKey[15] = (i&(1<<0))>>0 ;
		int cnt = 0 ;
		// for (int i = 0; i < 16; i++)
		// 	cout << testKey[i] << ' ';
		// cout << endl; 
		set<int> s;
		for (int it = 0; s.size()<8000; it++)
		{
			// taking 8000 random nums
			int num = rand() % (1 << 16); 
			if(s.find(num)!=s.end()) continue ;
			s.insert(num) ;
			vi ip(16);

			for (int j = 0; j < 16; j++)
			{
				ip[j] = (num & (1 << j)) >> j;
			}
			vi ans = fullForwardSPN(keys, ip);

			// xor with last layer keys
			for (int j = 0; j < 16; j++)
			{
				ans[j] = ans[j] ^ testKey[j];
			}
			// cout<<cnt<<endl ;
			// rev S BOX
			revSBoxFunc(ans);
			// for (int j = 0; j < 16; j++)
			// 	cout << ans[j] << ' ';
			// cout << endl; 

			if ((ip[4] ^ ip[6] ^ ip[7] ^ ans[5] ^ ans[7] ^ ans[13] ^ ans[15]) == 0)
				cnt++;
			}
		// 4250  3750
			int val = min(abs(4250 - cnt), abs(3750 - cnt));
			cout << i << ' ' << val << endl;
			if (ans1 > val)
			{
			validKey = testKey ; 
			ans1 = val ; 
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
		cout << validKey[i] << ' ';
		if (i % 4 == 3)
			cout << ' ';
	}
	return 0 ; 
}
