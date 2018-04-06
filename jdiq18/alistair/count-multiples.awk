function convert(votes) {
	if (votes==1) return 0
	if (votes==2) return 1
	if (votes<=4) return 2
	if (votes<=8) return 3
	if (votes<=16) return 4
	if (votes<=32) return 5
	if (votes<=64) return 6
	# ahhh, whatever, put the rest in the last bucket too
	return 6
}
/^#/ {
	next
}
{
	topic = $1
	qrel = $4
	thingy = $2
	if (thingy ~ "multiple") {
		# multiple votes for this judgment
		votes = 1*substr(thingy,9,2)
	} else {
		# just a single vote for this one
		votes = 1
	}
	cat = convert(votes)
	count[cat] += 1
	rel[cat] += (qrel>=1)
	topcnt[topic] += 1
	relcnt[topic] += (qrel>=1)
}
END {
	tot = 7
	for (cat=0; cat<=tot; cat++) {
		printf "# %2d,%6d & %9.5f\n", \
			cat, count[cat], \
			100.0*rel[cat]/count[cat]
		# ok, so this is a bit grotty, but it works!
		count[tot] += count[cat]
		rel[tot] += rel[cat]
	}
	for (topic=0; topic<=1000; topic++) {
		# ok, so that's a bit of overkill that makes life easier
		if (topcnt[topic]>0) {
			printf "%s, %3d, %5d, %3d\n", \
				FILENAME, topic, topcnt[topic], relcnt[topic]
		}
	}
}
