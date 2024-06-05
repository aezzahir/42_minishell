#!/bin/bash

# Simple Heredoc Test
cat << EOF
This is a test.
EOF

echo

# Multiple Heredoc Inputs
cat << EOF1 << EOF2
First heredoc input.
EOF1
Second heredoc input.
EOF2

echo

# Heredoc with Special Characters
variable="special"
cat << EOF
This line has a $variable.
This line has a backslash \ character.
EOF

echo

# Heredoc with Empty Input
cat << EOF
EOF

echo

# Heredoc with Quotes in Delimiter
cat << "EOF"
This is a quoted delimiter.
EOF

echo

# Heredoc with Indentation
cat <<- EOF
"script.sh" 63L, 746B
