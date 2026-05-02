#!/bin/bash

PASS=0
FAIL=0

run_test() {
    local desc="$1"
    local input="$2"
    local expected="$3"

    echo "$input" > test_input.txt
    ./vaja test_input.txt 2>/dev/null
    actual=$(cat out.txt 2>/dev/null)

    if [ "$actual" = "$expected" ]; then
        echo "PASS: $desc"
        PASS=$((PASS + 1))
    else
        echo "FAIL: $desc (pricakovano: '$expected', dobljeno: '$actual')" >&2
        FAIL=$((FAIL + 1))
    fi
}

run_test "Osnovno sortiranje" "5,3,1,4,2" "1,2,3,4,5"
run_test "En element" "42" "42"
run_test "Ze sortirano" "1,2,3,4,5" "1,2,3,4,5"
run_test "Obratno sortirano" "255,200,100,50,10" "10,50,100,200,255"
run_test "Z niclo" "0,5,3,0,1" "0,0,1,3,5"
run_test "Podvojeni elementi" "3,1,3,2,1" "1,1,2,3,3"
run_test "Mejne vrednosti" "255,0,128,64" "0,64,128,255"
run_test "Daljsi seznam" "9,8,7,6,5,4,3,2,1,0" "0,1,2,3,4,5,6,7,8,9"

rm -f test_input.txt out.txt

echo ""
echo "Rezultati: $PASS uspesnih, $FAIL neuspesnih"

if [ $FAIL -gt 0 ]; then
    exit 1
fi
exit 0
