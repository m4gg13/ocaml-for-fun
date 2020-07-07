/*
MEDIAN OF MEDIANS ALGORITHM

written in cpp since i need to use it in cpp
i can't quite figure out how to apply this alg in complicated code so i figured i'd isolate it first
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int ham_dist(string s0, string s1); // find hamming distance between 2 strings
string mom(int m, int g, vector<string> arr, vector<string> next_arr);

int main() {

  cout<<"hello world"<<endl;

  vector<string> experts = 
    {"1112","2231","4425","1546","3516",
     "6666","2664","5121","5611","3336",
     "5455","2333","1356","3125","6541",
     "4365","6555","6111","2244","1532",
     "6543","1532","4122","5131","5334"};
  vector<string> next_arr;
  string mo = mom(0, 5, experts, next_arr);

  cout<<"this is the median : "<<mo<<endl;

}

int ham_dist(string s0, string s1) {

  int dist = 0;
  for (int i = 0; i < s0.size(); i++) {
    if (s0[i] != s1[i]) {
      dist++;
    }
  }
  return dist;

}

string compare(int i, int n, vector<string> arr, vector<int> sim_scores) {
  // i - index into arr
  // n - how many elements we have left to compare
  // arr - the elements in question
  // sim_scoress - the similarity scores for these elements

  cout<<"CLEANUP TIME BABEY"<<endl;

  int score = 0;
  for (int y = 1; y < n; y++) {
    score = ham_dist(arr[i], arr[i-y]);
    sim_scores[i] += score;
    sim_scores[i-y] += score;
  }

  if (n == 1) {
    // if there's nothing else to look at, return the element with the lowest score... like golf
    // (the smallest distance and therefore the highest similarity)
    vector<int>::iterator first = sim_scores.begin();
    vector<int>::iterator last = sim_scores.end();
    int min_index = distance(first, min_element(first, last));
    string min = arr[i+min_index];
    cout<<"everything is fine up to here"<<endl;
    cout<<min<<endl;
    return min;
  }else {
    return compare(--i, --n, arr, sim_scores);
  }

}

string mom(int m, int g, vector<string> arr, vector<string> next_arr) {
  // m - starting index of this group of 5
  // g - size of this group... usually 5
  // arr - the elements in question
  // next_arr - the medians of each group

  cout<<"+++++++++++++++++++++++++"<<endl;
  cout<<"this round's elements :"<<endl;
  cout<<arr[m+0]<<endl;
  cout<<arr[m+1]<<endl;
  cout<<arr[m+2]<<endl;
  cout<<arr[m+3]<<endl;
  cout<<arr[m+4]<<endl;
  cout<<"m : "<<m<<endl;
  cout<<"contents of next_arr :"<<endl;
  for (int i =0; i < next_arr.size(); i++) {
    cout<<next_arr[i]<<endl;
  }

  if (m+5 >= arr.size()) {

    int leftover = arr.size()%5;
    if (leftover != 0) {
      g = leftover;
    }

    if (next_arr.size() == 1) {
      // the last median
      return next_arr[0];
    }
  }

  vector<int> scores(g, 0);
  string mog = compare(m, g, arr, scores); // median of this group
  cout<<"error before or after this?"<<endl;
  next_arr.push_back(mog);

  cout<<"median for this round : "<<mog<<endl;

  if (m+g == arr.size()) {
    vector<string> next_next_arr(5,0);
    return mom((m+5), g, next_arr, next_next_arr);
  }

  return mom((m+5), g, arr, next_arr);

}
