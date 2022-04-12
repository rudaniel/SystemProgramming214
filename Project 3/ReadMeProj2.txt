Name: Daniel Lopez NetID: ddl59
Name: Manav Bali NetId: mb1841

For our testing strategy, we used a wide range of misaligned files in an attempt
to break our code in any way possible. We started testing files and directories 
to see if our code does the correct operation. Our code will only work with files
or directories. We also give the users the ability to type text if they don't have a file.
Any other input would be considered a user error and was coded to show
an error message. We tested out code against empty files, files with a bunch of 
spaces in between words, and also new lines, no matter how many are in a row, our code gives
the correct file output. Files that already exist will be overwritten. We used a random
text generator to test for edge cases and such.

Tests For Txt Files:
We ensured that the user's width was respected and displayed corrected on the 
standard output. The printed output will be a normalized txt file with no fault.
We can determine our code is correct if no matter the file altercations, our code will always
output a normalized txt file. If there are too many white spaces between two words, our code 
will put those words together, removing all unnecessary white spaces. Also, if there are multiple
newlines with no words, our code will only output one line. We also tested for if a word is given that is too 
large for the width. When that happens, the word shouldn't be split up but instead given its own line. 
Also, if a normalized file gets imputed, the same exact file should be outputted. 

Test For Directories:
We know our code is correct if, when given a directory, we look at all of the txt files within 
that directory and wrap those files based on user input of width. We make new files in the same directory
with the wrapped contents; that new file will have the word-wrap in front of it. Each wrapped file
will be set to the same standards as the Test For Txt Files due to the code for just txt files being 
very similar to the one for writing into new files. If the directory that is given has files that 
aren't txt files, our code should be able to skip by them, but that should try to be avoided. Files
that already start with . or wrap. will not be rewrapped but instead ignored.

When testing edge cases, we tried txt files with nothing and txt files that have a large amount of 
text on a single line. We needed to test our buffer, so we also ran test cases with multiple long
paragraphs and a large number of errors within the file. Since our code reads the input a byte at a 
time, our buffer is able to still work perfectly even at length 1.