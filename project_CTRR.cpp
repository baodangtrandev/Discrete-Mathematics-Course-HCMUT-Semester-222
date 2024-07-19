#include "project_CTRR.h"

int priority(char symbol)
{
    if (symbol == '^')
        return 3;
    else if (symbol == '*' || symbol == '/')
        return 2;
    else if (symbol == '+' || symbol == '-')
        return 1;
    else
        return -1; 
}

string Infix2Postfix(string infix)
{
    stack <char> stackk;              
    string postfix = "";        
    int length = infix.length(); 
    for (int k = 0; k < length; ++k)
    {char x = infix[k];
        if (isalnum(x))
        {postfix += x; 
        }
        else if (x == '(')stackk.push(x);
        else if (x == ')')
        {while (!stackk.empty() && stackk.top() != '(')
            {   postfix += ' ';
                postfix += stackk.top();
                stackk.pop();}
            if (!stackk.empty() && stackk.top() == '(')
                stackk.pop();}
        else
        {while (!stackk.empty() && priority(stackk.top()) >= priority(x))
            {
                postfix += ' ';
                postfix += stackk.top();
                stackk.pop();
            }
            postfix += ' ';
            stackk.push(x); }}
    while (!stackk.empty())
    {
        postfix += ' ';
        postfix += stackk.top();
        stackk.pop();
    }
    return postfix;
}

bool checkSymbol(char sym)
{
    return (sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '^');
}

int checkpriority(char sym)
{
    if (sym == '-' || sym == '+')
        return 1;
    else if (sym == '*' || sym == '/')
        return 2;
    else if (sym == '^')
        return 3;
    return 0;
}

string Infix2Prefix(string infix)
{
    vector<string> stackk;
    string Pre;

    for (int i = infix.size() - 1; i >= 0; i--)
    {
        char sym = infix[i];
        if (isalnum(sym)) Pre = sym + Pre;
        else if (sym == ')') stackk.push_back(")");
        else if (sym == '(')
        {   while (stackk.back() != ")")
            {   Pre = stackk.back() + " " + Pre;
                stackk.pop_back();}
            stackk.pop_back();}
        else if (checkSymbol(sym))
        {   while (!stackk.empty() && checkpriority(stackk.back()[0]) > checkpriority(sym))
            {   Pre = stackk.back() + " " + Pre;
                stackk.pop_back();}
            stackk.push_back(string(1, sym));
            Pre = " " + Pre;}}
    while (!stackk.empty())
    {   Pre = stackk.back() + " " + Pre;
        stackk.pop_back();}
    return Pre;
}

bool checksymbol(string sym)
{
    return (sym == "+" || sym == "-" || sym == "*" || sym == "/" || sym == "^");
}
vector <string> cutstring(const string &s, char space)
{   vector<string> str;
    stringstream ss(s);
    string string_x;
    while (getline(ss, string_x, space))
    {str.push_back(string_x);}
    return str;
}

double CalculatePostandPre(string exp)
{
    stack<double> stackk; 
    char space = ' ';
    vector<string> symbol = cutstring(exp, space); 
    vector<string> temp;
    int count = symbol.size();
    if (symbol[0] == "+" || symbol[0] == "-" || symbol[0] == "*" || symbol[0] == "/" || symbol[0] == "^")
    {
        for (int i = 0; i < count / 2; i++)
        {
            string temp = symbol[i];
            symbol[i] = symbol[count - 1 - i];
            symbol[count - 1 - i] = temp;
        }
        for (int i = 0; i < count; ++i)
        {
            if (!checksymbol(symbol[i]))
                stackk.push((double)stoi(symbol[i]));
            else
            {   double value1 = stackk.top();
                stackk.pop();
                double value2 = stackk.top();
                stackk.pop();
                if (symbol[i] == "+")
                {   stackk.push(value1 + value2);
                    continue;
                }else if (symbol[i] == "-")
                {   stackk.push(value1 - value2);
                    continue;
                } else if (symbol[i] == "*")
                {   stackk.push(value1 * value2);
                    continue;
                }else if (symbol[i] == "/")
                {   stackk.push(value1 / value2);
                    continue;
                }else if (symbol[i] == "^")
                {   stackk.push(pow(value1, value2));
                    continue;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < count; ++i)
        {if (!checksymbol(symbol[i]))
                stackk.push((double)stoi(symbol[i]));
            else
            {   double value1 = stackk.top();
                stackk.pop();
                double value2 = stackk.top();
                stackk.pop();
                if (symbol[i] == "+")
                {stackk.push(value2 + value1);
                    continue;
                }else if (symbol[i] == "-")
                {stackk.push(value2 - value1);
                    continue;
                }else if (symbol[i] == "*")
                {stackk.push(value2 * value1);
                    continue;
                }else if (symbol[i] == "/")
                {stackk.push(value2 / value1);
                    continue;
                }else if (symbol[i] == "^")
                {stackk.push(pow(value2, value1));
                    continue;
                }
            }
        }
    }
    return round(stackk.top() * 10000) / 10000;
}
string PostfixPrefixCalculator(string input)
{
    double result = CalculatePostandPre(input);
    string str = to_string(result);
    for (int i = str.length() - 1; i >= 0; i--)
    {if (str[i] != '0' && str[i] != '.')
        {   str.erase(i + 1, str.length() - i - 1);
            break;
        }else if (str[i] != '0' && str[i] == '.')
        {str.erase(i, str.length() - i);
            break;}
    }
    cout << str;
    return "";
}

bool checksym_Logics(string string1)
{return (string1 == "&" || string1 == "|" || string1 == "-" || string1 == "~" || string1 == "<" || string1 == ">" || string1 == ")" || string1 == "(");
}

int priority_logic(string c)
{
    if (c == "~")return 4; 
    else if (c == "&" || c == "|")return 3;                  
    else if (c == "-" || c == "->") return 2;
    else if (c == "<" || c == "<->")return 1;
    else return -1; 
}

string removeSpaces(const string &str)
{
    string result;
    for (char x : str)
    {   if (x != ' ')
        {result += x;
        }
    }
    return result;
}

string LogicInfix2Prefix(string infix)
{
    stack<string> stackk;
    string prefix = "";
    infix = removeSpaces(infix);

    for (int i = infix.size() - 1; i >= 0; i--)
    {
        string c(1, infix[i]);
        string cc(1, infix[i - 1]);
        if (!checksym_Logics(c))
            prefix = c + prefix;
        else if (c == ")")
            stackk.push(")");
        else if (c == "(")
        {   while (stackk.top() != ")")
            {   prefix = stackk.top() + prefix;
                stackk.pop();
            }stackk.pop();
        }
        else if (checksym_Logics(c) && c != "-" && c != "<" && c != ">")
        {
            while (!stackk.empty() && priority_logic(stackk.top()) > priority_logic(c))
            {   prefix = stackk.top() + prefix;
                stackk.pop();
            }
            stackk.push(c);
        }else if (c == "-" && cc != "<")
        {
            while (!stackk.empty() && priority_logic(stackk.top()) > priority_logic(c))
            {   prefix = stackk.top() + prefix;
                stackk.pop();
            }
            stackk.push("->");
        }   else if (c == "<")
        {   while (!stackk.empty() && priority_logic(stackk.top()) > priority_logic(c))
            {
                prefix = stackk.top() + prefix;
                stackk.pop();
            }
            stackk.push("<->");
        }
    }
    while (!stackk.empty())
    {
        prefix = stackk.top() + prefix;
        stackk.pop();
    }
    return prefix;
}

string LogicInfix2Postfix(string infix)
{   stack<string> stackk;
    string posfix = "";
    infix = removeSpaces(infix); 
    int length = infix.length();
    for (int i = 0; i < length; i++)
    {
        string temp(1, infix[i]);
        if (!checksym_Logics(temp))
        {
            posfix += temp;
        }
        else if (temp == "(")
            stackk.push(temp); 
        else if (temp == ")")
        {
            while (!stackk.empty() && stackk.top() != "(")
            {   posfix += stackk.top();
                stackk.pop();
            }
            if (!stackk.empty() && stackk.top() == "(")
                stackk.pop(); 
        }
        else if (temp != "-" && temp != "<")
        {
            while (!stackk.empty() && priority_logic(stackk.top()) >= priority_logic(temp))
            {

                posfix += stackk.top();
                stackk.pop();
            }
            stackk.push(temp);
        }
        else if (temp == "-")
        {
            while (!stackk.empty() && priority_logic(stackk.top()) >= priority_logic(temp))
            {
                posfix += stackk.top();
                stackk.pop();
            }
            stackk.push("->");
            ++i;
        }
        else if (temp == "<")
        {
            while (!stackk.empty() && priority_logic(stackk.top()) >= priority_logic(temp))
            {
                posfix += stackk.top();
                stackk.pop();
            }
            stackk.push("<->"); 
            i += 2;
        }
    }
    while (!stackk.empty())
    {
        posfix += stackk.top();
        stackk.pop();
    }
    return posfix;
}


bool check_Logics(string s)
{
    return (s == "&" || s == "|" || s == "-" || s == "~" || s == "<" || s == ">" || s == "<->" || s == "->");
}

vector<string> cut_logic_string(string str)
{
    vector<string> temp;
    int length = str.size();
    for (int i = 0; i < length; ++i)
    {
        string c(1, str[i]);
        if (!check_Logics(c))
        {
            temp.push_back(c);
        }
        else
        {
            if (c == "<")
            {
                temp.push_back("<->");
                i += 2;
            }
            else if (c == "-")
            {
                temp.push_back("->");
                i += 1;
            }
            else
            {
                temp.push_back(c);
            }
        }
    }
    return temp;
}


string change_NUM(string str, string value)
{
    value = removeSpaces(value);
    int length = value.size();
    for (int i = 0; i < length / 2; i++)
    {
        char search = value[i];
        char replace = value[i + length / 2];
        size_t findd = str.find(search);
        while (findd != string::npos)
        {
            str.replace(findd, 1, 1, replace);
            findd = str.find(search, findd + 1);
        }
    }
    return str;
}

int Calculate_Logic(string str, string value)
{
    stack<int> stackk; 
    str = change_NUM(str, value);
    vector<string> symbol = cut_logic_string(str); 
    vector<string> temp;
    int num = symbol.size();
    if (check_Logics(symbol[0]))
    {
        for (int i = 0; i < num / 2; i++)
        {
            string temp = symbol[i];
            symbol[i] = symbol[num - 1 - i];
            symbol[num - 1 - i] = temp;
        }
        for (int i = 0; i < num; ++i)
        {
            if (!check_Logics(symbol[i]))
                stackk.push(stoi(symbol[i]));
            else
            {
                if (symbol[i] == "~")
                {
                    int valuee = stackk.top();
                    stackk.pop();
                    stackk.push(1 - valuee);
                }
                else
                {
                    int valuee1 = stackk.top();
                    stackk.pop();
                    int valuee2 = stackk.top();
                    stackk.pop();
                    if (symbol[i] == "|")
                    {
                        bool temp = valuee1 || valuee2;
                        stackk.push(temp);
                        continue;
                    }
                    else if (symbol[i] == "&")
                    {
                        bool temp = valuee1 && valuee2;
                        stackk.push(temp);
                        continue;
                    }
                    else if (symbol[i] == "->")
                    {
                        bool temp = (1 - valuee1) || valuee2;
                        stackk.push(temp);
                        continue;
                    }
                    else if (symbol[i] == "<->")
                    {
                        bool temp = (valuee1 && valuee2) || ((1 - valuee1) && (1 - valuee2));
                        stackk.push(temp);
                        continue;
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < num; ++i)
        {
            if (!check_Logics(symbol[i]))
                stackk.push(stoi(symbol[i]));
            else
            {
                if (symbol[i] == "~")
                {
                    int valuee = stackk.top();
                    stackk.pop();
                    stackk.push(1 - valuee);
                }
                else
                {
                    int valuee1 = stackk.top();
                    stackk.pop();
                    int valuee2 = stackk.top();
                    stackk.pop();
                    if (symbol[i] == "|")
                    {
                        bool temp = valuee1 || valuee2;
                        stackk.push(temp);
                        continue;
                    }
                    else if (symbol[i] == "&")
                    {
                        bool temp = valuee1 && valuee2;
                        stackk.push(temp);
                        continue;
                    }
                    else if (symbol[i] == "->")
                    {
                        bool temp = (1 - valuee2) || (valuee1);
                        stackk.push(temp);
                        continue;
                    }
                    else if (symbol[i] == "<->")
                    {
                        bool temp = (valuee1 && valuee2) || ((1 - valuee2) && (1 - valuee1));
                        stackk.push(temp);
                        continue;
                    }
                }
            }
        }
    }
    return stackk.top();
}

string LogicPostfixPrefixCalculator(string str, string value)
{
    bool result = Calculate_Logic(str, value);
    if (result)
        cout << "TRUE";
    else
        cout << "FALSE";
    return "";
}
