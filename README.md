Antifraud, by Saeid Hashemi


Requirements:

This code is based on the C++ standard libraries and does not require anything else. It will compile with g++.

Structure:

There is a graph class written which uses a sorted double linked list to keep all users with their id as well as a single linked list to their friend list for each user.

The graph class has two public functions used which are for building the graph and tracing it. The other private functions are to find a user's pointer in the double linked list.

I used a breadth first search with a maximum distance to check for a friend link between two users. 
