#! /bin/csh -bf
set out = pool-depths.csv
set tmp = newttnewttnewtt
/bin/rm -f $tmp $out
foreach f ( *rels*-r*.txt )
  echo "adding $f"
  awk -f count-multiples.awk $f \
    | sed '/^#/d;s/-.*-r/, /;s/\.txt//' \
    | col 1 3 2 4 5 \
    | sed 's/	/ /g' \
    >> $tmp
end
echo "collection,topic,depth,pooled,relevant" > $out
sort $tmp >> $out
/bin/rm $tmp
exit 0
