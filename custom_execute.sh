set -euo pipefail
TIMEOUT=${1:-2}

make
mkdir -p tmp
python3 make_case.py > tmp/in.txt
time cat tmp/in.txt | ./main.o > sample/out.txt 2> debug.txt
