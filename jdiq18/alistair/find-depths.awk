# read a qrels file and then a set of runs
# for each run, compute the greatest depth up
# to which every document for every topic has been
# judged, on a per-run basis
#
# Usage, eg
#	awk -f find-depths.awk qrels.2004.robust.txt trec2004.rob/* | sort -k10,10nr -k13,13nr
#
# Note the three places where TREC13 appears in a comment, where topics might
# be restricted to 651-700
#
BEGIN {
	bigdepth = 1000
}
{
	if (NF==4) {
		# this is the qrels file
		topic = $1
		docid = $3
		rel = $4
		key = topic":"docid
		judged[key] = rel+1
		next
	}
	# ok, so must instead be in one of the run files
	topic = $1
	docid = $3
	runname = $6
	alltopics[topic] = 1
	allruns[runname] = 1
	if (topic!=oldtopic || runname!=oldrunname) {
		key = oldtopic":"oldrunname
		if (mindepth[key]==bigdepth) {
			mindepth[key] = depth+1
		}
		# TREC13 topics 651-700, take the first alternative line
		if (shortrun[oldrunname]>depth && oldtopic!=672 && oldtopic>650) {
		# if (shortrun[oldrunname]>depth) {
			shortrun[oldrunname] = depth
		}
		depth = 0
		key = topic":"runname
		mindepth[key] = bigdepth
		if (shortrun[runname]==0) {
			shortrun[runname] = bigdepth
		}
	}
	key = topic":"docid
	depth++
	# TREC13 topics 651-700, take the first alternative line
	if (judged[key]==0 && topic!=672 && topic>650) {
	# if (judged[key]==0 && topic!=672) {
		# document didn't get judged, topic 672 was deleted
		key = topic":"runname
		if (mindepth[key]==bigdepth) {
			# first unjudged document in this topic:run
			mindepth[key] = depth
			# printf "key = %s depth = %d\n", key, depth
		}
	}
	oldtopic = topic
	oldrunname = runname
}
END {
	for (runname in allruns) {
		sum = 0
		mind = 1000
		n = 0
		for (topic in alltopics) {
			# TREC13 topics 651-700, take the first alternative line
			if (topic==672 || topic<=650) continue
			# if (topic==672) continue
			key = topic":"runname
			n += 1
			sum += mindepth[key]
			if (mindepth[key]<mind) {
				mind = mindepth[key]
			}
			# printf "key = %s mind  = %d\n", key, mind
		}
		printf "%-12s %3d topics judgeddepth" \
			" avg = %5.1f min = %3d shortrun = %4d\n", \
			runname, n, 1.0*sum/n, mind, shortrun[runname]
	}
}

