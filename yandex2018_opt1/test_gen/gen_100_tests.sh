for i in {1..100}
do
    test_file_name="$i.in"
    test_file_path="tests/$test_file_name"
    python3 gen.py > $test_file_path
    echo $i
done