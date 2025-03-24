1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**:  fgets() is a good choice because it prevents buffer overflows, so the user's input is read safely. It also handles input with spaces (not to mention the end of new lines) well, which works well when processing command lines.

2. You needed to use `malloc()` to allocte memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**:  malloc() is used for dynamic memory allocation, which is needed because we will not know the input size at compile time. So we're not wasting memory with oversized arrays, and we're avoiding the possibility of a stack overflow.

3. In `dshlib.c`, the function `build_cmd_list(`)` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**:  This mainly accounts for accidental whitespace input by the user, which a normal CLI usually does. If we didn't trim the space we would either have execution errors or some commands might be misterpreted.

4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**:  1. Output Redirection (>): Challenge: The shell must correctly open or create the target file and redirect the command's STDOUT to it without affecting STDERR. 2. Input Redirection (<): Challenge: The shell must properly open the input file and ensure the command reads from it instead of STDIN. 3. Error Redirection (2>): Challenge: Managing STDERR redirection separately from STDOUT requires setting up the correct file descriptors to avoid mixing outputs unintentionally.

- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**:  Mainly, redirection deals with static files, while piping is more of a dynamic thing, linking commands' streams of input and output. They work in different ways. Redirection involves sending the output or input of a command to a file (like ls > file.txt). Piping works by connecting the output of one command directing to the input of another, so the second command processes the first in real time.

- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**:  This lets us tell the difference between normal output and error messages, which make it easier to handle outputs (like when we redirect only errors).

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > **Answer**:  The custom shell should detect non-zero exit statuses to identify failures and print appropriate error messages to STDERR. Yes, we shouldalso support merging STDOUT and STDERR so users can collect all of the output together if they want. We would use the 2>&1 syntax
