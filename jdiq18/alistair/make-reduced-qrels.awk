BEGIN {
	# depth to build pool to
	if (poolto==0) {
		poolto = 50
	}
}
{
	if (NF==1) {
		# if here, gathering the run names
		collect[$1] = 1
		totsys += 1
		next
	}
	if (NF==6) {
		# if here, have an entry from a run, eg
		# 351  Q0  FT934-4848 1  0.495821  INQ501
		topic = $1
		systm = $6
		docid = $3
		if (topic!=oldtopic || systm!=oldsystm) {
			depth = 0
		}
		depth++
		if (collect[systm] && depth<=poolto) {
			# run is wanted, and within pooldepth, let's track it
			votes += 1
			key = topic":"docid
			# and record the last vote for this document
			novel[key] = systm
			count[key]++
		}
		oldsystm = systm
		oldtopic = topic
		totdocs += 1
		next
	}
	if (NF==4) {
		# if here, then have an existing qrel, eg
		# 351 0 FBIS3-10411 0
		topic = $1
		docid = $3
		qrel = $4
		key = topic":"docid
		if (count[key]) {
			# want to retain this qrel
			if (count[key]==1) {
				systmstr = novel[key]
			} else {
				systmstr = sprintf("multiple%02d", count[key])
			}
			printf "%3d %s %s %s\n", \
				topic, systmstr, docid, qrel
			retain += 1
			if (qrel) {
				relret += 1
			}
			if (count[key]==1) {
				singles += 1
				if (qrel) {
					singrel += 1
				}
			}
		}
		totqrels += 1
		next
	}
}
END {
	# and that's all!
	printf "# systems in pool : %7d\n", totsys
	printf "# total docs      : %7d\n", totdocs
	printf "# total votes     : %7d\n", votes
	printf "# total unique    : %7d\n", retain
	printf "# rel. retained   : %7d\n", relret
	printf "# single votes    : %7d\n", singles
	printf "# rel. singles    : %7d\n", singrel
}
