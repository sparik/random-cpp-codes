for i in {1..100}
do
    infile="tests/$i.in"
    outfile="output/$i.out"
    ./main < $infile > $outfile &
done