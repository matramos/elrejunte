//Booth's algorithm
//Find lexicographically minimal string rotation in O(|S|)
int booth(string S){
    S += S;  // Concatenate string to it self to avoid modular arithmetic
    int n = sz(S);
    vector<int>f(n,-1);
    int k = 0;  // Least rotation of string found so far
    forr(j,1,n){
        char sj = S[j];
        int i = f[j - k - 1];
        while (i != -1 and sj != S[k + i + 1]){
            if (sj < S[k + i + 1])
                k = j - i - 1;
            i = f[i];
        }
        if (sj != S[k + i + 1]){
            if (sj < S[k])  
                k = j;
            f[j - k] = -1;
        }
        else{
            f[j - k] = i + 1;
        }   
	}
    return k; // Lexicographically minimal string rotation's position
}
