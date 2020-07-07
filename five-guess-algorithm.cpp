#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ctime>
#include <sstream>

using namespace std;

vector<int> getRandomCode();

void createSet();

void combinationRecursive(int combinationLength, int position, vector<int> &current, vector<int> &elements);

vector<int> reproduce(); // use everyone in the pop in pairs, replace half of the pop with the children
void fitness(int i, int g); // assign a fitness value to everyone in the pop
void getExperts(int max); //add the experts from this pop to the expert pool
vector<int> expertChoice(int i); // from the expert pool, wich is the most similar?

string checkCode(vector<int> guess, vector<int> code);

void removeCode(vector<vector<int>> &set, vector<int> code);

void pruneCodes(vector<vector<int>> &set, vector<int> code, string currentResponse);

vector<vector<int>> minmax();

int getMaxScore(map<string, int> inputMap);

int getMinScore(map<vector<int>, int> inputMap);

vector<int> getNextGuess(vector<vector<int>> nextGuesses);

static const int NUM_COLOURS = 6;
static const int CODE_LENGTH = 4;
static const int EXPERTS_PER_GEN = 7;
static const int GEN_SIZE = 50; // population size per generation
static const int NUM_OF_GEN = 10; // lol
static const int MAX_TURNS = 10;
static const double MUTATION_FREQ = 0.3; // how often to mutate 
static vector<vector<int>> combinations; //Master set of combinations 1111 to 6666
static vector<vector<int>> candidateSolutions;
static vector<vector<int>> nextGuesses;
static vector<vector<int>> previousGuesses; // got to keep track of this too now
static vector<int> fitness_ratings(GEN_SIZE, 0); // each member of candidateSolutions has a score at its index
static vector<int> similarity_scores((EXPERTS_PER_GEN * NUM_OF_GEN), 0); // to determine which expert should be the guess
static vector<int> code;
static vector<int> currentGuess;
static vector<string> responseCodes; // is this used?
static string responsePegs;
static bool won;
static int turn;

static vector<vector<int>> experts; // the most easily matched in a generation

int main() {

  srand(time(0));

    turn = 1;
    won = false;

    code = getRandomCode();

    //Create the set of 1296 possible codes
    createSet();
    vector<int> rands;
    int e = GEN_SIZE; // ensure that we get 50 elements out of the fully enumerated set... oops this is a weird way to do this
    for (int p = 0; p < e; p++){
      int r = rand() % 1295;
      if (!count(rands.begin(), rands.end(), r)){ // while count is not 0, do the stuff in the if
	rands.push_back(r);
	candidateSolutions.push_back(combinations[r]);
      } else {
	e++;
      }
    }

    // candidateSolutions.insert(candidateSolutions.end(), combinations.begin(), combinations.end());

    cout<<"csol size: ";
    cout <<candidateSolutions.size()<<endl;
    cout << "Code: ";
    for (int i = 0; i < code.size(); ++i) {
        cout << code[i] << " ";
    }
    cout << endl;

    while (turn < MAX_TURNS && !won) {
      cout<<"turn begin : "<<turn<<endl;

      // we want to do this NUM_OF_GEN number of times
      int cur_gen = 0;
      while((cur_gen < NUM_OF_GEN) && (turn != 1)){
	// in this loop, we
	// reproduce, mutate, and remove to keep stable population
	// determine fitness of each individual in the population
	// get this generation's experts

	cout<<"**************************************************"<<endl;
	cout<<"current generation : "<<cur_gen<<endl;

	// each pair in the population will have a child so divide by 2
	for(int a = 0; a < (GEN_SIZE/2); a++) {
	  // return one of the parents and get rid of them to keep population size stable
	  // should this be more random than this? i dont think so...
	  vector<int> one_parent = reproduce();
	  removeCode(candidateSolutions, one_parent); // no longer a candidate
	  // fitness rating will just get replaced for the deleted s
	}
	//cout<<"size of candidateSolns : "<<candidateSolutions.size()<<endl;

	//cout<<"1 do i get in here?"<<endl;

	// for each generation do this
	fitness((candidateSolutions.size()-1), (previousGuesses.size()-1)); // rate every s belonging to S and store it in fitness_ratings
	  
	//cout<<"AND HERE WE AREE ============================="<<endl;
	
	int max = (int) *max_element(fitness_ratings.begin(), fitness_ratings.end());;
	
	cout<<"8 do i get in here?"<<endl;
	
	getExperts(max); // then we determine which ones are experts
	
	//cout<<"i feel like we get stuck in getExperts"<<endl;

	cur_gen++;
      }// end generation

      //cout<<"inf do i get in here?"<<endl;

      if (turn != 1) { // totally messy but this is also not going to be necessary on first turn
	// currentGuess is just the expert-est expert
	currentGuess = expertChoice(experts.size()-1);
      } else {
	currentGuess = {1, 1, 2, 2}; //1122
      }

      //cout<<"EXPERT SIZE BEFORE CLEAR : "<<experts.size()<<endl;
      // clear out the expert pool
      experts.clear();
      cout<<"EXPERS SIZE AFTER CLEAR : "<<experts.size()<<endl;
      
      //Play the guess to get a response of colored and white pegs
      responsePegs = checkCode(currentGuess, code);
      
      // done with this one now
      previousGuesses.push_back(currentGuess);
      // record the response
      responseCodes.push_back(responsePegs);

      cout << "Turn: " << turn << endl;
      cout << "Guess: ";
      for (int i = 0; i < currentGuess.size(); ++i) {
	cout << currentGuess[i] << " ";
      }
      cout << "= " << responsePegs << endl;

      //If the response is four colored pegs, the game is won
      if (responsePegs == "BBBB") {
	won = true;
	cout << "Game Won!" << endl;
	break;
      }

      cout<<"do we get here before things are slow?"<<endl;

      //Remove from candidateSolutions,
      //any code that would not give the same response if it were the code
      //      pruneCodes(candidateSolutions, currentGuess, responsePegs);
      
      //Calculate Minmax scores
      //      nextGuesses = minmax();
      
      //Select next guess
      // currentGuess = getNextGuess(nextGuesses);
      
      turn++; // only take a turn after 20 generations have passed
    } // end game
    return 0;
}

vector<int> getRandomCode() {

    vector<int> code;
    int max = NUM_COLOURS;
    int min = 1;
    int random;
    //Returns the number of seconds since the UNIX epoch for a seed
    srand(time(0));

    for (int i = 0; i < CODE_LENGTH; ++i) {

        random = min + (rand() % (max - min + 1));
        code.push_back(random);
    }

    return code;
}

void createSet() {

    vector<int> current(CODE_LENGTH, 0);
    vector<int> elements;

    for (int i = 1; i <= NUM_COLOURS; ++i) {
        elements.push_back(i);
    }

    cout<<"in here"<<endl;
    cout<<elements.size()<<endl;

    combinationRecursive(CODE_LENGTH, 0, current, elements);
}

void combinationRecursive(int combinationLength, int position, vector<int> &current, vector<int> &elements) {

    if (position >= combinationLength) {
        combinations.push_back(current);
        return;
    }

    for (int j = 0; j < elements.size(); ++j) {
        current[position] = elements[j];
        combinationRecursive(combinationLength, position + 1, current, elements);
    }
    return;
}

// for every 2 elements in combinations, make a baby and delete one of the parents from the 
// gene pool to maiintain population size
vector<int> reproduce() {
  
  int g;
  int p0, p1, p2, p3;
  int r0, r1;
  vector<int> mum, pa, baby;

  // again with the (pseudo)random numbers, lets do two at a time this time.
  // loop unroll this bad boy
  // we use two members every time so GEN_SIZE divided by 2

  r0 = rand() % GEN_SIZE;
  r1 = rand() % GEN_SIZE;
  while (r0 == r1) { // you're not allowed to reproduce w yourself
    r1 = rand() % GEN_SIZE; // another chance to get a r0 != r1
  }
  
  mum = candidateSolutions[r0]; 
  pa = candidateSolutions[r1]; 
  
  p0 = rand() % CODE_LENGTH; // position 1
  p1 = rand() % CODE_LENGTH; 
  p2 = rand() % CODE_LENGTH; 
  p3 = rand() % CODE_LENGTH; 
  
  baby.push_back((p0 | 1) ? mum[p0] : pa[p0]); // if this position is odd, mum o.w. pa 
  baby.push_back((p1 | 1) ? mum[p1] : pa[p1]); 
  baby.push_back((p2 | 1) ? mum[p2] : pa[p2]); 
  baby.push_back((p3 | 1) ? mum[p3] : pa[p3]); 
  
  // will we mutate this time? 
  g = rand() % 1000;
  if (g < (MUTATION_FREQ * 1000)) {
    // we're resusing these variables
    r0 = rand() % CODE_LENGTH; // some spot to mutate at
    r1 = rand() % NUM_COLOURS; // and some value to mutate to
    baby[r0] = r1; // do the replacement
  }
  
  // the baby is now a part of the gene pool
  candidateSolutions.push_back(baby);

  /*
  for(int u = 0; u < (GEN_SIZE / 2); u++){
    r0 = rand() % GEN_SIZE;
    r1 = rand() % GEN_SIZE;
    if (r0 == r1) { // you're not allowed to reproduce w yourself
      u--; // another chance to get a r0 != r1
    }

    mum = candidateSolutions[r0]; 
    pa = candidateSolutions[r1]; 
    
    p0 = rand() % CODE_LENGTH; // position 1
    p1 = rand() % CODE_LENGTH; 
    p2 = rand() % CODE_LENGTH; 
    p3 = rand() % CODE_LENGTH; 

    baby.push_back((p0 | 1) ? mum[p0] : pa[p0]); // if this position is odd, mum o.w. pa 
    baby.push_back((p1 | 1) ? mum[p1] : pa[p1]); 
    baby.push_back((p2 | 1) ? mum[p2] : pa[p2]); 
    baby.push_back((p3 | 1) ? mum[p3] : pa[p3]); 

    // will we mutate this time? 
    g = rand() % 1000;
    if (g < (MUTATION_FREQ * 1000)) {
      // we're resusing these variables
      r0 = rand() % CODE_LENGTH; // some spot to mutate at
      r1 = rand() % NUM_COLOURS; // and some value to mutate to
      baby[r0] = r1; // do the replacement
    }

    // the baby is now a part of the gene pool
    candidateSolutions.push_back(baby);

  }
  */

  // this will be the parent we get rid of
  return (g | 0 ? mum : pa); // if g is even, mum o.w. pa

}

// give every s in candidateSolutions a fitness rating at the same index in fitness_ratings variable
void fitness(int i, int g) {

  vector<int> s = candidateSolutions[i];

  int score = 0;                                                                                                                                                                 
  int color_score = 0;                                                                                                                                                           
  int spots_score = 0;

  for(int i = 0; i < GEN_SIZE; i++) {

    for(int g = 0; g < previousGuesses.size(); g++) {

      // check how many colors s and i-1 have in common
      for (int y = 0 ; y < CODE_LENGTH; y++) { 
	color_score += count(s.begin(), s.end(), previousGuesses[g][y]);                                                                                                                }
      
      // check how many of those colors are in the right spots
      for (int z = 0; z < CODE_LENGTH; z++) {
	spots_score += ((s[z] == previousGuesses[g][z]) ? 1 : 0); 
      }
      
      // the number of return pegs is the number of correct colors. avg this and that
      // the number of "W"s in the response code is the number of colors in the right spot. again, avg this and that
      score += (responseCodes[g].size() + color_score) / 2;
      score += (count(responseCodes[g].begin(), responseCodes[g].end(), 'W') + spots_score) / 2;
      
      // this candidate will get reevaluated each generation
      // was += but i dont think that was right...
      fitness_ratings[i] = score;

    }

  }
  /*  
  // i is where we are in candidateSolutions
  // g is where we are in the previousGuesses

  // check that i has (i-1).colors == cur_guess.colors and that (i-1).spots == cur_guess.spots
  // so if it complies, score increases and if it doesn't, score stays same

  if (!i && !g) { // when we hit the very bottom, 
    return; // stop
  }
  
  if (g == 0) { // when we've checked all the guesses on this s,
    i--; // go down to the next s in candidateSolutions
    g = previousGuesses.size()-1; // reset g for the next s in candidateSolutions 
  }

  //cout<<"i : "<<i<<endl;
  cout<<"begin g : "<<g<<endl;

  vector<int> s = candidateSolutions[i];

  int score = 0;
  int color_score = 0;
  int spots_score = 0;

  // check how many colors s and i-1 have in common
  for (int y = 0 ; y < CODE_LENGTH; y++) {
    color_score += count(s.begin(), s.end(), previousGuesses[g][y]);
  }
  
  // check how many of those colors are in the right spots
  for (int z = 0; z < CODE_LENGTH; z++) {
    spots_score += ((s[z] == previousGuesses[g][z]) ? 1 : 0); 
  }
  
  // the number of return pegs is the number of correct colors. avg this and that
  // the number of "W"s in the response code is the number of colors in the right spot. again, avg this and that
  score += (responseCodes[g].size() + color_score) / 2;
  score += (count(responseCodes[g].begin(), responseCodes[g].end(), 'W') + spots_score) / 2;

  // this candidate will get reevaluated each generation
  // was += but i dont think that was right...
  fitness_ratings[i] = score;

  g--;
  
  //cout<<"around the fitness loop again"<<endl;
  cout<<"g : "<<g<<endl;
  fitness(i, g); // compare with the next oldest guess
  */
}

void getExperts(int max) {

  // i keeps track of when we have enough experts
  // max goes down from the actual max of fitness_ratings to whenever the set is full

  // randomly sift through candidateSolutions, see if you can get EXPERTS_PER_GEN
  // number of max score candidates
  /*
  int r0 = rand() % candidateSolutions.size();
  vector<int> used_rands;

  //cout<<"here we start out"<<endl;

  if (!count(used_rands.begin(), used_rands.end(), r0)) { // if count is 0
    if (fitness_ratings[r0] == max) {
      // if this candidate's score is one of the max, its an expert
      experts.push_back(candidateSolutions[r0]);
    }
  }

  //cout<<"experts.size() : "<<experts.size()<<endl;
  //cout<<"max : "<<max<<endl;

  if ((experts.size() != EXPERTS_PER_GEN) && (max != 0)) { // while there are still spots open for experts of this generation, 
    getExperts(max--);
  }

  return; // once the number of experts we've got is the same as the number we need per gen, stop
  */

  // so basically this but lets find the ones with the best fitness ratings
  
  int r0, e, max_ind;
  int i = 0;
  vector<int> used_rands;

  vector<int>::iterator first = fitness_ratings.begin();  
  vector<int>::iterator last = fitness_ratings.end();


  while (e < EXPERTS_PER_GEN) {
    //cout<<"we've got "<<e<<" experts so far and r0 : "<<r0<<" and max : "<<max<<endl;
    i++;
    //r0 = rand() % GEN_SIZE;
    //if (!count(used_rands.begin(), used_rands.end(), r0)) {
      if (count(first, last, max)) {
	max_ind = distance(first, max_element(first, last));
	experts.push_back(candidateSolutions[max_ind]);
	e++;
      }

      /*
      if (fitness_ratings[r0] == max) {
	experts.push_back(candidateSolutions[r0]);
	e++;
      }
      */
      //} 

      if (i == GEN_SIZE) {
	max--;
      }
  }

}

vector<int> expertChoice(int i) {
  cout<<"begin expert choice"<<endl;

  // fuck it. we're going to say if the strings are the same, sim_score get
  // incremented, if not then not
  vector<string> strings_of_experts;
  for (int m = 0; m < GEN_SIZE; m += 5) {
    // make ints into strings
    for (int r = 0; r < 5; r++) {
      ostringstream osss;
      osss << experts[m+r][0];
      osss << experts[m+r][1];
      osss << experts[m+r][2];
      osss << experts[m+r][3];
      string s0(osss.str());
      cout<<"adding "<<s0<<endl;
      strings_of_experts.push_back(s0); 
    }
    /*
    string tr = to_string(experts[m+0][0]);
    cout<<" this is s0 plain : "<<tr<<endl;
    cout<<experts[m+0][1]<<experts[m+0][2]<<experts[m+0][3]<<endl;
    strings_of_experts.push_back(s0); 
    vector<char> c1;
    c1.push_back((char)experts[m+1][0]);
    c1.push_back((char)experts[m+1][1]);
    c1.push_back((char)experts[m+1][2]);
    c1.push_back((char)experts[m+1][3]);
    string s1(c1.begin(), c1.end());
    strings_of_experts.push_back(s1);
    vector<char> c2;
    c2.push_back((char)experts[m+2][0]);
    c2.push_back((char)experts[m+2][1]);
    c2.push_back((char)experts[m+2][2]);
    c2.push_back((char)experts[m+2][3]);
    string s2(c2.begin(), c2.end());
    strings_of_experts.push_back(s2);
    vector<char> c3;
    c3.push_back((char)experts[m+3][0]);
    c3.push_back((char)experts[m+3][1]);
    c3.push_back((char)experts[m+3][2]);
    c3.push_back((char)experts[m+3][3]);
    string s3(c3.begin(), c3.end());
    strings_of_experts.push_back(s2);
    vector<char> c4;
    c4.push_back((char)experts[m+4][0]);
    c4.push_back((char)experts[m+4][1]);
    c4.push_back((char)experts[m+4][2]);
    c4.push_back((char)experts[m+4][3]);
    string s4(c4.begin(), c4.end());
    strings_of_experts.push_back(s4);
    */

    string s0 = strings_of_experts[m+0];
    string s1 = strings_of_experts[m+1];
    string s2 = strings_of_experts[m+2];
    string s3 = strings_of_experts[m+3];
    string s4 = strings_of_experts[m+4];

    if (s0.compare(s1) == 0){
      similarity_scores[m+0]++;
      similarity_scores[m+1]++;
    } 
    if (s0.compare(s2) == 0){
      similarity_scores[m+0]++;
      similarity_scores[m+2]++;
    } 
    if(s0.compare(s3) == 0){
      similarity_scores[m+0]++;
      similarity_scores[m+3]++;
    } 
    if(s0.compare(s4) == 0){
      similarity_scores[m+0]++;
      similarity_scores[m+4]++;
    }
    
    if (s1.compare(s2) == 0){
      similarity_scores[m+1]++;
      similarity_scores[m+2]++;
    } 
    if(s1.compare(s3) == 0){
      similarity_scores[m+1]++;
      similarity_scores[m+3]++;
    }
    if(s1.compare(s4) == 0){
      similarity_scores[m+1]++;
      similarity_scores[m+4]++;
    }
    
    if (s2.compare(s3) == 0){
      similarity_scores[m+2]++;
      similarity_scores[m+3]++;
    }
    if (s2.compare(s4) == 0) {
      similarity_scores[m+2]++;
      similarity_scores[m+4]++;
    }
  
    if (s3.compare(s4) == 0){
      similarity_scores[m+3]++;
      similarity_scores[m+4]++;
    }
  }

  vector<int>::iterator first = similarity_scores.begin();
  vector<int>::iterator last = similarity_scores.end();
  int max_index = distance(first, max_element(first, last));

  // print out what the similarity scores are for each
  for (int p = 0; p < GEN_SIZE; p++) {
    cout<<"p : "<<p<<endl;
    cout<<strings_of_experts[p]<<" : "<<similarity_scores[p]<<endl;
  }
  
  return experts[max_index];

}

string checkCode(vector<int> guess, vector<int> code) {

    string result;

    //Get black/coloured - number of colors in the right spot
    for (int i = 0; i < CODE_LENGTH; ++i) {

        if (guess[i] == code[i]) {
            result.append("B");
	    // why multiply by -1?
            guess[i] *= -1;
            code[i] *= -1;
        }
    }

    //Get white - number of colors correct
    for (int i = 0; i < CODE_LENGTH; ++i) {

      // oh, this is why multiply by -1
        if (code[i] > 0) {

            vector<int>::iterator it = find(guess.begin(), guess.end(), code[i]);
            int index;
            if (it != guess.end()) {

                index = distance(guess.begin(), it);
                result.append("W");
		// and then you put it back
                guess[index] *= -1;
            }
        }
    }

    // returns the response, duh
    return result;
}

void removeCode(vector<vector<int>> &set, vector<int> currentCode) {

  // cout<<"remove : "<<currentCode[0]<<currentCode[1]<<endl;
    int index;
    for (auto it = set.begin(); it != set.end(); it++) {
        index = distance(set.begin(), it);

        if (set[index] == currentCode) {
            set.erase(set.begin() + index);
            break;
        }
    }
}

void pruneCodes(vector<vector<int>> &set, vector<int> currentCode, string currentResponse) {

    int index;
    vector<vector<int>>::iterator it = set.begin();

    while (it != set.end()) {
        index = distance(set.begin(), it);

        if (currentResponse != checkCode(currentCode, set[index])) {
            it = set.erase(set.begin() + index);
        } else {
            it++;
        }
    }
}

vector<vector<int>> minmax() {

    map<string, int> scoreCount;
    map<vector<int>, int> score;
    vector<vector<int>> nextGuesses;
    int max, min;

    for (int i = 0; i < combinations.size(); ++i) {

        for (int j = 0; j < candidateSolutions.size(); ++j) {

            string pegScore = checkCode(combinations[i], candidateSolutions[j]);
            if (scoreCount.count(pegScore) > 0) {
                scoreCount.at(pegScore)++;
            } else {
                scoreCount.emplace(pegScore, 1);
            }
        }

        max = getMaxScore(scoreCount);
        score.emplace(combinations[i], max);
        scoreCount.clear();
    }

    min = getMinScore(score);

    for (auto elem : score) {
        if (elem.second == min) {
            nextGuesses.push_back(elem.first);
        }
    }

    return nextGuesses;
}

int getMaxScore(map<string, int> inputMap) {

    int max = 0;
    for (auto elem : inputMap) {
        if (elem.second > max) {
            max = elem.second;
        }
    }

    return max;
}

int getMinScore(map<vector<int>, int> inputMap) {

    int min = numeric_limits<int>::max();
    for (auto elem : inputMap) {
        if (elem.second < min) {
            min = elem.second;
        }
    }

    return min;
}

vector<int> getNextGuess(vector<vector<int>> nextGuesses) {

    vector<int> nextGuess;

    for (int i = 0; i < nextGuesses.size(); ++i) {
        if (find(candidateSolutions.begin(), candidateSolutions.end(), nextGuesses[i]) != candidateSolutions.end()) {
            return nextGuesses[i];
        }
    }
    for (int j = 0; j < nextGuesses.size(); ++j) {
        if (find(combinations.begin(), combinations.end(), nextGuesses[j]) != combinations.end()) {
            return nextGuesses[j];
        }
    }

    return nextGuess;
}
