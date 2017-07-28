
# Murphy_CSCI2270_FinalProject

Summary:

For my project I decided to make a simple relational database using a graph. I implemented the graph with nodes that represent either a person or a grouping(such as a project group or office location) additionally each node can store other individual or project specific information of the users choosing. I have populated my test data with phone numbers and email addresses. My database allows for multi parameter searches to discover the intersection of an arbitrary number of groups. Additionally i have implemented file read and write to output and input the graph nodes and their edges.

How to Run:

Put all the files together in a folder and runn the Source.cpp file;


Instructions:
The program will start by asking if you want to run the trial data set. This is by far the easiest way to test. 
After choosing whether to load the trial data you will be at the main menu with the following options:
1. Add person.  
(This option allows you to add a new person(node) to the graph 

2. Add data to person.(This option allows you to add data to a person node, it is interfacing with a linked list to store the data in the node.)

3. Add a group.(This function allows you to rapidly group existing nodes into a working group it will ask for a group name and then a list of people. It can also be used to make one to one connections and will creat the first node 

4. Print a node.
(This option will print a node with all of its data and list all of its connections.)

5. Calculate group intersections.
(This option prints out the people who are members are of all the groups specified)

6. Write to file.
(This option will output the graph as a text file)

7. Read from file.
(This option will read a saved graph back in)

8. Print all nodes
(This will print an alphabetic list of all the nodes in the graph)

9. Search for an employee
(This function will search for the best match in the graph to collection of space seperated words. It is case dependent so be sure to capatalize)
10. Quit

Things to try:

All of the following are using the trial data.

Try adding another person named "John Black" using option 1.

Use option 2 to give "John Black" a "Telephone" number try "404-999-2876"

Use option 8 to see that John Black exists

Use option 4 to see his telephone number.
Use option 3 to create a group with "John Black" and some other people of your choice from option 8's output

Use option 9 to search for a John try "John Boulder", "John Denver Email" etc. it is case sensitive, also the weighting is heavily name skewed and it is intentionally limited to 3 results.

System Requirements:

Should work on all systems file reading may get screwy across systems. Developed and tested on Windows 10.

Developed By:
Ryan Murphy 

Open Bugs:
Occasionally loses its data pointer especially if numerous data points are added to a node, I think this has something to do with the stack not compensating correctly for the expansion of the node in memory as the linked list gets bigger. I believe i have it corrected.
