

***** KMP ******

string  (N)  =>		abdabcddabcbc abcddabcc
pattern (M)  =>		   abcddabcc
prefix table =>   	   000001230

navie: O(MN)
KMP: O(M+N) N >> M  => O(N)

