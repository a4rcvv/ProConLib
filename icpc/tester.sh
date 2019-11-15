#!/bin/bash
. ./config.txt
echo "main     : $main"
echo "greedy   : $greedy"
echo "generator: $generator"
loop_count=1
echo  "testing"
$generator >$testcase_path
while diff -q <($main <$testcase_path) <($greedy <$testcase_path)
do
  loop_count=$((++loop_count))
  echo -e "testing"
  $generator >$testcase_path
done
echo "diff output(left: main   right: greedy)"
diff --side-by-side <($main <$testcase_path) <($greedy <$testcase_path)
echo "test case:"
cat $testcase_path

# YOU SHOULD DO "chmod 755 tester.sh" ON A TERMINAL!!
