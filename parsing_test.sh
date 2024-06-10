#!/bin/bash

# Function to print colored output
print_colored() {
    echo -e "\033[1;$1m$2\033[0m"
}

# Test cases
test_cases=(
    'echo $"HOME"123$"HOME"$"HOME"'
    'echo $"HOME"123$"HOME"$"HOME"$USER'
    'echo $"HOME"123$"HOME"$"HOME"$USER$LOGNAME'
    'echo $"HOME"123$"HOME"$"HOME"$USER$LOGNAME$SHELL'
    'echo $"HOME"123$"HOME"$"HOME"$USER$LOGNAME$SHELL$TERM'
    'echo $"HOME"123$"HOME"$"HOME"$USER$LOGNAME$SHELL$TERM$PATH'
    'echo $"HOME"123$"HOME"$"HOME"$USER$LOGNAME$SHELL$TERM$PATH$LANG'
    'echo $"HOME"123$"HOME"$"HOME"$USER$LOGNAME$SHELL$TERM$PATH$LANG$LC_COLLATE'
    'echo $"HOME"123$"HOME"$"HOME"$USER$LOGNAME$SHELL$TERM$PATH$LANG$LC_COLLATE$LC_CTYPE'
    'echo $"HOME"123$"HOME"$"HOME"$USER$LOGNAME$SHELL$TERM$PATH$LANG$LC_COLLATE$LC_CTYPE$LC_MESSAGES'
    'echo "$"HOME"123$"HOME"$"HOME""'
    'echo "$USER$LOGNAME$SHELL"'
    'echo "$USER$"LOGNAME"$SHELL"'
    'echo "Hello $USER! Welcome to $SHELL."'
    'echo "$USER@$HOSTNAME"'
    'echo "$USER_$LOGNAME_$SHELL"'
    'echo "${USER}123${LOGNAME}456${SHELL}"'
    'echo "$PATH:$HOME/bin"'
    'echo "$$USER $$LOGNAME $$SHELL"'
    'echo "$$$USER $$$LOGNAME $$$SHELL"'
    'echo "$""USER $""LOGNAME $""SHELL"'
    'echo "$"USER $"LOGNAME $"SHELL"'
    'echo "$USER$UNDEFINED_VAR$LOGNAME"'
    'echo "$USER$$LOGNAME$$SHELL"'
    'echo "$(echo "Hello, $USER!")"'
)

# Iterate over test cases
for test_case in "${test_cases[@]}"
do
    # Run the test case in Bash and capture the output
    bash_output=$(echo "$test_case" | ./mezzine)
    # Run the test case in your minishell and capture the output
    minishell_output=$(echo "$test_case" | ./minishell)

    # Compare the outputs
    if [ "$bash_output" == "$minishell_output" ]; then
        print_colored "32" "Test passed: Output matches Bash"
        echo "Command: $test_case"
        echo "Output:"
        print_colored "34" "$bash_output"
    else
        print_colored "31" "Test failed: Output differs from Bash"
        echo "Command: $test_case"
        echo "Bash output:"
        print_colored "34" "$bash_output"
        echo "Minishell output:"
        print_colored "34" "$minishell_output"
    fi

    echo "---"
done