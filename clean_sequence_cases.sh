#!/bin/bash
set -euo pipefail

for i in `seq 5`; do
  cp /dev/null samples/in${i}.txt
  cp /dev/null samples/out${i}.txt
done
