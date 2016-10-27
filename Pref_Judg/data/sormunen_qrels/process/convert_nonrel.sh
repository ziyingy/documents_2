awk '{
	printf "%-3s 0 %20s 0\n", $1, $2
}' sormunen_nonrel_orig/qrels_nonrel
