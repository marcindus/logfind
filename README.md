# logfind


First project from book "Learn C The Hard Way" by Zed A. Shaw

Exercise 26. Project logfind, requirements from book:


1. This tool takes any sequence of words and assumes I mean “and” for them. 
So logfind zedshaw smart guy will find all files that have zedshaw and smart and guy in them.

2. It takes an optional argument of -o if the parameters are meant to be or logic.

3. It loads the list of allowed log files from ~/.logfind.

4. The list of file names can be anything that the glob function allows. 
Refer to man 3 glob to see how this works. 
I suggest starting with just a flat list of exact files, and then add glob functionality.

5. You should output the matching lines as you scan, and try to match them as fast as possible.
