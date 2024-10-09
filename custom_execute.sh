set -euo pipefail
TIMEOUT=${1:-2}

make
mkdir -p tmp
python3 make_case.py > tmp/in.txt
./execute.sh tmp/in.txt sample/out.txt sample/debug.txt
