#! /bin/csh -bf
set colls = "trec07ahc trec08ahc trec13rob"
set colls = "trec13rob"
set pools = "10 20 30 40 50"
foreach coll ( $colls )

  if ( $coll == "trec07ahc" ) then
    set topics = "351-400"
  else if ( $coll == "trec08ahc" ) then
    set topics = "401-450"
  else if ( $coll == "trec13rob" ) then
    set topics = "651-700"
  else 
    echo "Collection not known"
    exit 1
  endif

  foreach pool ( $pools )
    echo "coll = $coll, pool = $pool"
    awk -v poolto=$pool -f make-reduced-qrels.awk $coll-deepruns.txt \
            $coll-runs-sorted/input* $coll-qrels-$topics.txt \
	            > $coll-qrels-$topics-r$pool.txt
  end
end
exit 0

