#! /bin/csh -bf
set coll = "trec2004.rob"
set loc = ${coll}.loc
/bin/rm -rf $loc
mkdir $loc
foreach f ( $coll/input.* )
  echo -n $f
  set dst = `basename $f`
  cp $f $loc/$dst
  sort -o $loc/$dst -k1,1n -k5,5gr -k4,4n -k3,3 $loc/$dst
  cmp  $f $loc/$dst > /dev/null
  if ( $status ) then
    echo -n "	altered"
  endif
  echo ""
end
exit 0
