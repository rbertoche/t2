#!/bin/bash

SCRIPT="$1"
EXEC=../Produto/rede_social
INPUT=../Scripts/$SCRIPT.input
OUTPUT=../Scripts/$SCRIPT.output
EXPECTED=../Scripts/$SCRIPT.expected

$EXEC -s <$INPUT >$OUTPUT
diff $EXPECTED $OUTPUT
