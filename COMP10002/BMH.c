
***** BMH *****

string  (N)=> WE HOLD THESE TRUTHS TO BE SELF-EVIDENT
pattern (M)=>            TRUTH

O(M+N)

  T R U T H
i 0 1 2 3 4

=> length - i - 1
=> last letter => length (if not already defined; otherwise, leave)

Bad Match Table
---------------
Index	Value
---------------
  T       1		5 - 3 - 1
  R       3		5 - 1 - 1
  U       2		5 - 2 - 1
  H       5
  *		  5


