//============================================================================
// Name        : digital-wallet.cpp
// Author      : 
// Version     :
// Copyright   : Made by Saeid Hashemi
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <cstdlib>

using namespace std;

struct payment {
  string time, message;
  long id1, id2;
  double amount;
}inputPayment;

/*struct userType {
	long id;
	list<long> friends;
};*/

struct link;

struct graphNode {
	long id;
	link *firstOut;
	graphNode *prevNode, *nextNode;
};

struct link {
	graphNode *dest;
	link *nextLink;
};

class myGraph {
private:
    graphNode *firstNode, *lastNode;
    graphNode* getNode(long id); //doesn't add
    graphNode* addNode(long id);
public:
	myGraph();
	virtual ~myGraph();
    void addFriend(long id1, long id2);
    int isFriend(long id1, long id2, int degree);
};
myGraph::myGraph() {
	this->firstNode = new graphNode;
	firstNode->id = 1;
	firstNode->firstOut = NULL;
	firstNode->prevNode = NULL;
	firstNode->nextNode = NULL;
	this->lastNode = this->firstNode;
}
myGraph::~myGraph() {
	// TODO Auto-generated destructor stub
}
graphNode* myGraph::getNode(long id) {
    graphNode *iterateNode = this->firstNode;
    if (iterateNode->id == id)
    	return iterateNode;
    while (iterateNode != this->lastNode) {
    	iterateNode = iterateNode->nextNode;
    	if (iterateNode->id == id)
    	    return iterateNode;
    }
    return NULL;
}
graphNode* myGraph::addNode(long id) {
	graphNode *newNode = new graphNode;
	newNode->id = id;
	newNode->firstOut = NULL;
	newNode->nextNode = NULL;
	newNode->prevNode = NULL;

	graphNode *iterateNode = this->firstNode;
	if (iterateNode->id > id) {
		newNode->nextNode = this->firstNode;
	    this->firstNode->prevNode = newNode;
	    this->firstNode = newNode;
	    return newNode;
	}
	while (iterateNode != this->lastNode) {
	   	iterateNode = iterateNode->nextNode;
	   	if (iterateNode->id > id) {
	   		newNode->nextNode = iterateNode;
	   		newNode->prevNode = iterateNode->prevNode;
	   		iterateNode->prevNode->nextNode = newNode;
	   		iterateNode->prevNode = newNode;
	   		return newNode;
	   	}
	}
	newNode->prevNode = this->lastNode;
	this->lastNode->nextNode = newNode;
	this->lastNode = newNode;
	return newNode;

}
void myGraph::addFriend(long id1, long id2) {

	graphNode *node1 = this->getNode(id1);
	if (node1 == NULL)
		node1 = this->addNode(id1);
	graphNode *node2 = this->getNode(id2);
	if (node2 == NULL)
		node2 = this->addNode(id2);
	if (this->isFriend(id1, id2, 1)){
		return;
	}
	link *newLink1 = new link;
	newLink1->dest = node2;
	newLink1->nextLink = NULL;
	link *newLink2 = new link;
	newLink2->dest = node1;
	newLink2->nextLink = NULL;
	if (node1->firstOut == NULL){
		node1->firstOut = newLink1;
	} else {
		link *linkIterator = node1->firstOut;
		while(linkIterator->nextLink != NULL)
			linkIterator = linkIterator->nextLink;
		linkIterator->nextLink = newLink1;
	}
	if (node2->firstOut == NULL){
		node2->firstOut = newLink2;
	} else {
		link *linkIterator = node2->firstOut;
		while(linkIterator->nextLink != NULL)
			linkIterator = linkIterator->nextLink;
		linkIterator->nextLink = newLink2;
	}
	return;
}
int myGraph::isFriend(long id1, long id2, int degree) { //add another for the case that we have pointers to the nodes instead of id

	if ((id1 == id2) || (degree == 0))
		return 0;

	graphNode *searchNode = this->getNode(id1);
	if (searchNode == NULL)
		return 0;

	// Breadth first search
	int searchDegree = 1;
	// int seenDistance[lastNode->id] = {};
	vector<int> seenDistance(lastNode->id);
	// graphNode *queue[lastNode->id] = {};
	vector<graphNode*> queue(lastNode->id);
	int queueIn = 0;
	int queueOut = 0;

	link *linkIterator;

	linkIterator = searchNode->firstOut;
	while (linkIterator != NULL) {
		if (linkIterator->dest->id == id2)
			return searchDegree;
		if (seenDistance[linkIterator->dest->id] == 0){
			seenDistance[linkIterator->dest->id] = searchDegree;
			queue[queueIn] = linkIterator->dest;
			queueIn++;
		}
		linkIterator = linkIterator->nextLink;
	}
	while (queueIn != queueOut) {
		searchNode = queue[queueOut];
		queueOut++;
		searchDegree = seenDistance[searchNode->id] + 1;
		if (searchDegree > degree)
			return 0;

		linkIterator = searchNode->firstOut;
		while (linkIterator != NULL) {
			if (linkIterator->dest->id == id2)
				return searchDegree;
			if (seenDistance[linkIterator->dest->id] == 0){
				seenDistance[linkIterator->dest->id] = searchDegree;
				queue[queueIn] = linkIterator->dest;
				queueIn++;
			}
			linkIterator = linkIterator->nextLink;
		}
	}



	return 0;
}

int main( int argc, char *argv[] ) {

	myGraph socialNet;
	string inputLine, inputField;
	int line = 0;
//	istringstream readInputLine(inputLine);
//	vector<userType> users;

	if (argc < 6) {
		cout << "Please provide all necessary files." << endl;
		return 1;
	}

	ifstream batchPayments(argv[1]);
	if (batchPayments.is_open()) {

		// Throw away first line
		if (!batchPayments.eof()) {
			getline(batchPayments, inputLine);
			cout << inputLine << endl;
			line++;
		}

		// Parse comma separated fields
		while (!batchPayments.eof()) {

			getline(batchPayments, inputPayment.time, ',');

			getline(batchPayments, inputField, ',');
			inputPayment.id1 = atol(inputField.c_str());
			inputField.clear();

			getline(batchPayments, inputField, ',');
			inputPayment.id2 = atol(inputField.c_str());
			inputField.clear();

			getline(batchPayments, inputField, ',');
			inputPayment.amount = atof(inputField.c_str());
			inputField.clear();

			getline(batchPayments, inputPayment.message);

			if ((inputPayment.time.empty()) || (inputPayment.id1==0) || (inputPayment.id2==0) || (inputPayment.amount==0.0))
				continue;

			/*cout << "adding friends " << id1 << " " << id2 << endl;
			socialNet.addFriend(inputPayment.id1, inputPayment.id2);

			cout << "line " << line << endl << "time: " << inputPayment.time << endl << "id1: " << inputPayment.id1 << endl << "id2: " << inputPayment.id2 << endl << "amount: " << inputPayment.amount << endl << "message: " << inputPayment.message << endl;
			line++;*/
		}
		cout << "done reading at line " << line << endl;
		// Close file stream
		batchPayments.close();
		cout << "closing batchpayments file" << endl;
	} else {
		cout << "Unable to open file " << argv[1] << endl;
		return 1;
	}


	ifstream streamPayments(argv[2]);
	ofstream output1(argv[3]);
	ofstream output2(argv[4]);
	ofstream output3(argv[5]);
	if (streamPayments.is_open() && output1.is_open() && output2.is_open() && output3.is_open()) {

		// Throw away first line
		if (!streamPayments.eof()) {
			getline(streamPayments, inputLine);
		}

		// Parse comma separated fields
		while (!streamPayments.eof()) {
			getline(streamPayments, inputPayment.time, ',');

			getline(streamPayments, inputField, ',');
			inputPayment.id1 = atol(inputField.c_str());
			inputField.clear();

			getline(streamPayments, inputField, ',');
			inputPayment.id2 = atol(inputField.c_str());
			inputField.clear();

			getline(streamPayments, inputField, ',');
			inputPayment.amount = atof(inputField.c_str());
			inputField.clear();

			getline(streamPayments, inputPayment.message);

			if ((inputPayment.time.empty()) || (inputPayment.id1==0) || (inputPayment.id2==0) || (inputPayment.amount==0.0))
				continue;

			if (socialNet.isFriend(inputPayment.id1, inputPayment.id2, 1) != 0) {
				output1 << "trusted" << endl;
			} else {
				output1 << "unverified" << endl;
			}
			if (socialNet.isFriend(inputPayment.id1, inputPayment.id2, 2) != 0) {
				output2 << "trusted" << endl;
			} else {
				output2 << "unverified" << endl;
			}
			if (socialNet.isFriend(inputPayment.id1, inputPayment.id2, 4) != 0) {
				output3 << "trusted" << endl;
			} else {
				output3 << "unverified" << endl;
			}
		}
		// Close file stream
		streamPayments.close();
		output1.close();
		output2.close();
		output3.close();
	} else {
		cout << "Unable to open file " << endl;
		return 1;
	}

	return 0;
}
