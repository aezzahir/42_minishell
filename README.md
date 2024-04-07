### MINISHELL 
  - 42 project
1) Tokenazitions
The first step is to tokenaize our command line, for this purpuse we have to take care of " ' | > >> < << $ and so one.
we will tokenize it using two variables int start, int end,
which they will endicates the start and the end of each tokens.
and we have helpers functions like handle quote and handle env variables.
These tokens should be saved in a linked list so they can be parsed later to cmds.
3) Parsing.
