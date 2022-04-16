Name: Daniel Lopez NetID: ddl59
Name: Manav Bali NetId: mb1841

For our test strategy, we decided to test our project in parts rather than looking
at it as a whole. This makes testing more simple and guarantees our code works before
continuing to other parts.

Storing Directories/Files:
We decided to use a linked list storage type that acts as a queue for both storing
directories and storing files. So we have two linked lists. The user gives the original first directory, 
and from there, we will store all of its files within the files linked list. The linked
list that is filled with the files is then processed through our wrapping function therefore
wrapping all of the files within subdirectories. When treads are later introduced in Part 2/3 we
will be using threads to make the looking up of files and the wrapping of files happens at a much
faster speed.

Part I:
We know our code is correct for Part I; when called with a directory, we can wrap all of 
the files within that directory and any subdirectories as well. Since we reused our wrapping code
from Project 2, we can assume that all of the rules from Project 2 will be followed within
Project 3 as well. We tested our code with random mixtures of directories within one another.
We tested directories that have multiple subdirectories as well, and it is still able to go within
those and wrap all of its files.

Part II:
In Part 2, we introduce a set number of threads N that will be used to read the linked list that is 
filled with files and process them through our wrapper function. Part 2 should be giving the same results 
as Part 1, except it should be getting done by multiple threads instead of a single one like in the first part.
We had to create a number of locks and unlocks to keep the treads from doing an action that would prevent the 
ability of other threads to do their work correctly. We knew our thread code was correct because we printed 
the pthread ids to make sure that multiple threads were, in fact, working at the same time.

Part III:
Now in Part 3, we are introducing the idea of threads reading the directories and filling in the file linked 
list. And we also have another set of threads that will be going through all of the files in the linked list
and running them through the wrapper function. Very similar to Part 2, to check if our threads are 
,in fact, reading the directories, we printed out the pthreads ids to make sure that each thread is doing
its jobs at the same time. When testing this code, we were able to determine that all threads were working, and we were getting 
the same results that we got in Part 1 when we weren't using more than 1 thread. 