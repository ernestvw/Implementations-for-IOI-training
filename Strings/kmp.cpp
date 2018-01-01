void process(string p, int M, int lps[]) {
	int len = 0;
	lps[0] = 0;
	int i = 1;
	while(i < M) {
		if(p[i] == p[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else {
			if(len != 0) len = lps[len-1];
			else lps[i] = 0, i++;
		}
	}
}

bool kmp(string p, string t) { // look for p in t
	int M = p.length(), N = t.length();
	int lps[M];
	process(p, M, lps);
	int i = 0, j = 0;
	while(i < N) {
		if(p[j] == t[i]) i++, j++;
		if(j == M) return true;
		else if(i < N && p[j] != t[i]) {
			if(j != 0) j = lps[j-1];
			else i++;
		}
	}
	return false;
}
