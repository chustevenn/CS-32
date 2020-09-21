#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int evaluate(string infix, string& postfix, bool& result)
{
  postfix = "";
  if(infix.length() == 0)
    return 1;

  for(int i = 0; i < infix.length()-1; i++)
    {
      if(infix.at(i) == '(' && (infix.at(i+1) == '&' || infix.at(i+1) == '^' || infix.at(i+1) == ')'))
	return 1;
    }

  stack<char> operators;
  char lastChar = 'N';
  for(int i = 0; i < infix.length(); i++)
    {
      switch(infix.at(i))
	{
	case 'T':
	  postfix += infix.at(i);
	  break;
	case 'F':
	  postfix += infix.at(i);
	  break;
	case '(':
	  operators.push(infix.at(i));
	  break;
	case ')':
	  while(!operators.empty() && operators.top() != '(')
	    {
	      postfix += operators.top();
	      operators.pop();
	    }
	  if(operators.empty())
	    return 1;
	  else
	    operators.pop();
	  break;
	case '&':
	  while(!operators.empty() && operators.top() != '(' && (operators.top() == '&' || operators.top() == '!'))
	    {
	      postfix += operators.top();
	      operators.pop();
	    }
	  operators.push(infix.at(i));
	  break;
	case '^':
	  while(!operators.empty() && operators.top() != '(' && (operators.top() == '&' || operators.top() == '^' || operators.top() == '!'))
	    {
	      postfix += operators.top();
	      operators.pop();
	    }
	  operators.push(infix.at(i));
	  break;
	case '!':{
	  while(!operators.empty() && operators.top() != '(' && operators.top() == '!')
	    {
	      if(lastChar == '!')
		break;
	      postfix += operators.top();
	      operators.pop();
	    }
	  bool operandPresent = false;
	  for(int j = i+1; j < infix.length(); j++)
	    {
	      if(infix.at(j) == 'T' || infix.at(j) == 'F')
		operandPresent = true;
	    }
	  if(!operandPresent)
	    return 1;
	  operators.push(infix.at(i));
	  lastChar = '!';
	  break;
	}
	case ' ':
	  break;
	default:
	  return 1;
	}
    }

  while(!operators.empty())
    {
      if(operators.top() == '('){return 1;}
      postfix += operators.top();
      operators.pop();
    }

  stack<char> operands;
  for(int i = 0; i < postfix.length(); i++)
    {
      switch(postfix.at(i))
	{
	case 'T':
	  operands.push(postfix.at(i));
	  break;
	case 'F':
	  operands.push(postfix.at(i));
	  break;
	case '!':
	  if(operands.size() >= 1)
	    {
	      bool operand = false;
	      if(operands.top() == 'T')
		operand = true;
	      if(operands.top() == 'F')
		operand = false;
	      operands.pop();
	      bool eval = (!operand);
	      if(eval)
		operands.push('T');
	      if(!eval)
		operands.push('F');
	    }
	  else return 1;
	break;
	case '&':
	  if(operands.size() >= 2)
	    {
	      bool operand1 = false;
	      if(operands.top() == 'T')
		operand1 = true;
	      if(operands.top() == 'F')
		operand1 = false;
	      operands.pop();
	      bool operand2 = false;
	      if(operands.top() == 'T')
		operand2 = true;
	      if(operands.top() == 'F')
		operand2 = false;
	      operands.pop();

	      bool eval = (operand1 && operand2);
	      if(eval)
		operands.push('T');
	      if(!eval)
		operands.push('F');
	    }
	  else return 1;
	break;
	case '^':
	  if(operands.size() >= 2)
	    {
	      bool operand1 = false;
	      if(operands.top() == 'T')
		operand1 = true;
	      if(operands.top() == 'F')
		operand1 = false;
	      operands.pop();
	      bool operand2 = false;
	      if(operands.top() == 'T')
		operand2 = true;
	      if(operands.top() == 'F')
		operand2 = false;
	      operands.pop();

	      if((operand1 && !operand2) || (!operand1 && operand2))
		operands.push('T');
	      else
		operands.push('F');
	    }
	  else return 1;
	  break;
	}
    }
  if(operands.size() == 1)
    {
      if(operands.top() == 'T')
	result = true;
      else if(operands.top() == 'F')
	result = false;
      else return 1;
    }
  else
    return 1;

  return 0;
}

int main()
{}
  
