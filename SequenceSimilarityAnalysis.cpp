#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

double getScore(char a, char b){
  if (a == b){
    return 1.0;
  }
  if((a == 'A' && b == 'G') || (a == 'G' && b=='A')) { 
    return -0.1;
  }
  if ((a == 'A' && b == 'C') || (a == 'C' && b=='A')){
      return -0.1;
  }
  if ((a == 'G' && b == 'T') || (a == 'T' && b=='G')){
      return -0.1;
  }
  if ((a == 'C' && b == 'T') || (a == 'T' && b=='C')){
      return -0.1;
  }
  if((a == 'A' && b == 'T') || (a == 'T' && b == 'A')){
      return -0.15;
  }
  if ((a == 'G' && b == 'C') || (a == 'C' && b == 'G')){
    return -0.15;
  }
  
    return -0.2;
}

int main() 
{
  //take in input strings
  string x, y;
  cin >> x;
  cin >> y;


  if (x.size() < 5 || x.size() > 100 || y.size() < 5 || y.size() > 100)
  {
    cout << "Error: sizes must be between 5 and 100 inclusive." << endl;
    return 0;
  }
  
    int rows = x.size(); //rows = size of x
    int cols = y.size(); //cols = size of y

  // Create matrix for float values
  vector<vector<double> > matrix(rows+1, vector<double>(cols+1));

  // V(0,0) = 0
  matrix[0][0] = 0.0;

  // fill in left column: V(i,0) = V(i-1,0) + -0.2
  for (int i = 1; i <= rows; ++i)
    {
      matrix[i][0] = matrix[i-1][0] - 0.2;
    }
  
  // fill in top row: V(0,j) = V(0,j-1) + -0.2
  for (int j = 1; j <= cols; ++j)
    {
      matrix[0][j] = matrix[0][j-1] - 0.2;
    }
  
  
  
  // fill in rest of matrix
  for (int i = 1; i <= rows; ++i) 
  {
    for (int j = 1; j <= cols; ++j) 
    {
      double diagonal = matrix[i-1][j-1] + getScore(x[i-1], y[j-1]);
      double top = matrix[i-1][j] - 0.2;
      double left = matrix[i][j-1] - 0.2;
      matrix[i][j] = max(diagonal, max(top, left));

    }
  }
    //printing alignment
    string newX = "";
    string newY = "";
    int i = rows;
    int j = cols;
    while(i>0 && j>0){
        double score = matrix[i][j];
        double diag = matrix[i-1][j-1]; // match or mismatch
        double up = matrix[i-1][j]; // deletion
        double left = matrix[i][j-1]; // insertion
        if(score == left - 0.2){
            newX = '-' + newX;
            newY = y[--j] + newY;
        }
        else if(score == up - 0.2){
            newX = x[--i] + newX;
            newY = '-' + newY;
        }
        else if(score == diag + getScore(x[i-1],y[j-1])){
            newX = x[--i] + newX;
            newY = y[--j] + newY;
        } 
    }
    //make sure we go through all characters just in case strings are different sizes(while loop wont finish the larger string)
    while(i>0){
        newX = x[--i] + newX;
        newY = '-' + newY;
    }
     while(j>0){
        newX = '-' + newX;
        newY = y[--j] + newY;
    }

    //Print Similarity Score
    double similarityScore = matrix[rows][cols];
    cout << similarityScore << endl;
    cout<<newX<<endl;
    cout<<newY<<endl;
  /*
  // print matrix
  for (int i = 0; i <= rows; ++i) 
  {
    for (int j = 0; j <= cols; ++j) 
    {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
  */

  

    return 0;
}





