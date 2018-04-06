# generate a per-topic listing of how many relevant documents there are
# on a per-topic basis
# 
{
	topic = $1
	qrel = $NF
	count[topic] ++
	relvnt[topic] += qrel
}
END {
	for (topic in relvnt) {
		printf "topic %3d  jud = %4d  rel = %3d\n", \
			topic, count[topic], relvnt[topic]
	}
}
		
