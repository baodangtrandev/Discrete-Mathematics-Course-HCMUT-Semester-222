#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <math.h>
#include <iomanip>

using namespace std;

int priority(char );
string Infix2Postfix(string);
bool checkSymbol(char );
int checkpriority(char );
string Infix2Prefix(string ); 
bool checksymbol(string );
vector <string> cutstring(const string &, char );
double CalculatePostandPre(string );
string PostfixPrefixCalculator(string );
bool checksym_Logics(string );
int priority_logic(string );
string removeSpaces(const string &);
string LogicInfix2Postfix(string infix);
string LogicInfix2Prefix(string infix);
bool check_Logics(string );
vector<string> cut_logic_string(string );
string change_NUM(string , string );
int Calculate_Logic(string , string );
string LogicPostfixPrefixCalculator(string , string );