set -euo pipefail

make
time cat $1 | ./main.o > $2 2> $3
