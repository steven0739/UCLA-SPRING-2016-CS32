//
//  eval.cpp
//
//  Created by 杨博超 on 16/4/26.
//  Copyright © 2016年 杨博超. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>
#include <cassert>
using namespace std;

bool checkvalidity(string infix);
int precedence(char ch);
string convertInfixToPostfix(string infix, string& postfix);
int evaluate(string infix, string& postfix, bool& result);

int evaluate(string infix, string& postfix, bool& result)
{
    if (checkvalidity(infix))
    {
        postfix = convertInfixToPostfix(infix, postfix);
        stack<bool> operandStack;
        
        for (int i = 0; i < postfix.length(); i++)
        {
            char ch = postfix[i];
            if (ch == 'T')
                operandStack.push(true);
            else if (ch == 'F')
                operandStack.push(false);
            else if(ch == '!')
            {
                bool temp = operandStack.top();
                operandStack.pop();
                operandStack.push(!temp);
            }
            else
            {
                bool operand2 = operandStack.top();
                operandStack.pop();
                if (operandStack.empty())
                    return 1;
                bool operand1 = operandStack.top();
                operandStack.pop();
                if (postfix[i] == '|')
                {
                    if (operand1 || operand2)
                        operandStack.push(true);
                    else
                        operandStack.push(false);
                }
                if (postfix[i] == '&')
                {
                    if (operand1 && operand2)
                        operandStack.push(true);
                    else
                        operandStack.push(false);
                }
            }
        }
        result = operandStack.top();
        return 0;
    }
    return 1;
}


bool checkvalidity(string infix)
{
    if (infix.length()==0)
    {
        return 0;
    }
    
    char prev='!',cur;
    int num=0;
    
    for (int i=0; i<infix.length(); i++)
    {
        cur=infix[i];
        switch (cur)
        {
            case ' ':
                break;
                
            case 'F':
            case 'T':
            case '!':
                if (prev==')' || prev=='F' || prev=='T')
                {
                    return 0;
                }
                prev=cur;
                break;
                
            case '&':
            case '|':
                if (prev=='|' || prev=='&' || prev=='(' || prev=='!')
                {
                    return 0;
                }
                prev=cur;
                break;
                
            case '(':
                if (prev==')' || prev=='F' || prev=='T')
                {
                    return 0;
                }
                prev=cur;
                num++;
                break;
                
            case ')':
                if (prev=='|' || prev=='&' || prev=='(' || prev=='!')
                {
                    return 0;
                }
                prev=cur;
                num--;
                break;
                
            default:
            {
                return 0;
            }
                break;
        }
    }
    
    if (prev=='|' || prev=='&' || prev=='(' || prev=='!')
    {
        return 0;
    }
    
    if (num)
    {
        return 0;
    }
    
    return 1;
}

int precedence(char ch)
{
    switch (ch)
    {
        case '!':
            return 3;
        case '&':
            return 2;
        case '|':
            return 1;
        default:
            return 0;
    }
}


string convertInfixToPostfix(string infix, string& postfix)
{
    postfix = "";
    stack<char> operatorStack;
    for (int i = 0; i < infix.size(); i++)
    {
        char ch = infix[i];
        switch (ch)
        {
            case 'T':
            case 'F':
            {
                postfix += ch;
            }
                break;
            
            case '(':
            {
                operatorStack.push(ch);
            }
                break;
            
            case ')':
                while (operatorStack.top() != '(')
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();
                break;
            
            case '!':
            case '&':
            case '|':
                while (!operatorStack.empty() && operatorStack.top() != '(' &&
                       precedence(ch) <= precedence(operatorStack.top()))
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;
            
            default:
                break;
        }
    }
    while (!operatorStack.empty())
    {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    return postfix;
}

int main()
{
    string pf;
    bool answer;
    assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&|"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    cout << "Passed all tests" << endl;
}