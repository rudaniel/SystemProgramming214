Test 1:
Testing adding to the linked list file using assert to make sure adding is correct.

Test 2:
Test adding to directory linked list using assert. We also test deleting in both this 
test case and test case 1.

Test 3:
We are testing that when given a directory we will have the right number of directories 
come through and files. 

Test 4:
We tested regular wrapping with just one thread to do the reading and wrapping. We use 
times to show that more threads will result in better time.

Test 5:
We added more directions which tested out multiple threads for the project. The time that 
was taken was cut in half.

Test 6:
We tested with the exact amount of directories and files that we have giving
It the most optimum output in theory.

Test 7:
We are testing with more read and wrapping treads than are necessary. This make result in a 
slightly worse time than test case 6 due to having to wait for the extra treads to close.

Conclusion:
Multithreading is faster than single-threading. In our tests, we saw the code for multithreading
run double the speed of the single threading case.