//Programmer: Dhanush Patel
//Programmer ID: 1553428

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>
#include <stack>
using namespace std;

struct Node
{
  string name;

  bool isVisited;
  list<int> neighbors;
};

queue<int> doDepthFirstSearch(int iOriginNode, vector<Node>& database)
{
  //  create an empty result queue of ints to return at end of function call
  queue<int> searchOrder; // return this queue of indices
  // TO DO -- write this function
  //  create a stack of ints to store the "to-do" list
  stack<int> toDo;
  //  initialize each node in database: set to "not visited"
  for(int i = 0; i < database.size(); i++)
  {
    database[i].isVisited = false;
  }
  // push start node's index onto the "to-do" list
  toDo.push(iOriginNode);
  //  while the "to-do" list is not empty
  while(!toDo.empty())
  {
    //  peek/pop a node's index from the "to-do" list
    int i = toDo.top();
    toDo.pop();
    //  if that node has not yet been visited
    //  mark the node as visited
    //  push node's index onto the result queue
    if(!database[i].isVisited)
    {
      database[i].isVisited = true;
      searchOrder.push(i);
      //  for each of that node's neighbors (in reverse order)
      //  if neighbor has not yet been visited
      //  push neighbor's index onto the "to-do" list
      list<int> bors = database[i].neighbors;
      for (list<int>::reverse_iterator rit = bors.rbegin(); rit != bors.rend(); ++rit)
      {
        if(!database[*rit].isVisited)
        {
          toDo.push(*rit);
        }
      }
    }
  }
  //  return the result queue
  return searchOrder;
}

int main()
{
  cout << "Programmer: Dhanush Patel\n";
  cout << "Programmer's ID: 1553428\n";
  cout << "File: " << __FILE__ << "\n\n";

  ifstream fin;
  fin.open("cities.txt");
  if (!fin.good()) throw "I/O error";

  // process the input file
  vector<Node> database;
  while (fin.good()) // EOF loop
  {
    string fromCity, toCity;

    // read one edge
    getline(fin, fromCity);
    getline(fin, toCity);
    fin.ignore(1000, 10); // skip the line with distance
    fin.ignore(1000, 10); // skip the separator

    // add vertices for new cities included in the edge
    int iToNode = -1, iFromNode = -1, i;
    for (i = 0; i < database.size(); i++) // seek "to" city
      if (database[i].name == fromCity)
        break;
    if (i == database.size()) // not in database yet
    {
      // store the node if it is new
      Node fromNode = {fromCity};
      database.push_back(fromNode);
    }
    iFromNode = i;

    for (i = 0; i < database.size(); i++) // seek "from" city
      if (database[i].name == toCity)
        break;
    if (i == database.size()) // not in vector yet
    {
      // store the node if it is new
      Node toNode = {toCity};
      database.push_back(toNode);
    }
    iToNode = i;

    // store bi-directional edges
    database[iFromNode].neighbors.push_back(iToNode);
    database[iToNode].neighbors.push_back(iFromNode);
  }
  fin.close();
  cout << "Input file processed\n\n";

  while (true)
  {
    // get the start city for the search
    string startCity;
    cout << "\nEnter the start city [blank to exit]: ";
    getline(cin, startCity);
    if (startCity.length() == 0) break;

    // find the start city
    int i;
    for (i = 0; i < database.size(); i++)
      if (database[i].name == startCity)
        break;

    // DFS result by copy-pop
    cout << "DFS";
    for (queue<int> q = doDepthFirstSearch(i, database); !q.empty(); q.pop())
      cout  << '-'<< database[q.front()].name;
    cout << endl;
  }
}