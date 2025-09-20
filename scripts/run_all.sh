#!/bin/bash

# Usage: ./run_all.sh <rng_repo: os|python|java> <test: chi|ks> <confidence: 0.95|0.99>

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <rng_repo: os|python|java> <test: chi|ks> <confidence: 0.95|0.99>"
    exit 1
fi

RNG=$1  #os, python, java
TEST=$2 #chi or ks
CONF=$3 #0.95 or 0.99

SEEDS=(101 202 303 404 505 606 707 808 909 1001 1101 1201 1301)

#Directory paths

RNG_DIR="../$RNG/$TEST"
RESULT_FILE="$RNG_DIR/${TEST}_results.txt"

#clear previous results.

>"$RESULT_FILE"

echo "Running $TEST test for $RNG  RNG with confidence $CONF..."

# Loop over seeds

for SEED in  "${SEEDS[@]}"; do
    # File name for current run
    if [ "$TEST" == "chi" ]; then
        FILE="$RNG_DIR/${TEST}_run${SEED}.txt"
        COUNT=5000
    else
        FILE="$RNG_DIR/${TEST}_run${SEED}.txt"
        COUNT=30
    fi

    # Generate RNG numbers
    case $RNG in
        os)
            ./rng_os "$SEED" "$FILE" "$TEST"
            ;;
        python)
            python3 ../python/rng_python.py "$SEED" "$FILE" "$TEST"
            ;;
        java)
            java -cp ../java rng_java "$SEED" "$FILE" "$TEST"
            ;;
        *)
            echo "Invalid RNG choice."
            exit 1
            ;;
    esac

    #Run test runner

    ./test_runner "$FILE" "$TEST" "$CONF" "$RESULT_FILE"

    echo "Seed $SEED done."
done
echo "All runs completed. Results in $RESULT_FILE"
