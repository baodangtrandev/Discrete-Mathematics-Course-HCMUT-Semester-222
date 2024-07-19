#include <hamcon.h>



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