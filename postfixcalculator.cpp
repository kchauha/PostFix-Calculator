#include<iostream>
#include<stack>
#include<string>
#include<unistd.h>
#include<stdlib.h>
using namespace std;


int parseExpression(string expression);
int postfixOperation(char operation, int op1, int op2);
bool IsOperator(char c);
bool IsNumber(char c);
void print_usage()
{
    cout<<"Usage: -e expression"<<endl;
}

int parseExpression(string expression)  //Parsing the expression for operator and Numbers
{
	
	stack<int> s;

	for(int i = 0;i< expression.length();i++) 
	{
		
		if(expression[i] == ' ' || expression[i] == ',') continue; 
		
		else if(IsOperator(expression[i])) 
		{
                     
			if(s.size()<2)
                         return -1;
			    
			int op2 = s.top(); 
			s.pop();
			int op1 = s.top(); 
			s.pop();			
			int res = postfixOperation(expression[i], op1, op2);			
			s.push(res);
		}
		else if(IsNumber(expression[i]))
		{
			int op = 0; 
			while(i<expression.length() && IsNumber(expression[i])) 
			{
				
                                //cout<<expression[i]<<endl;
				op= (op*10) + (expression[i] - '0'); 
				i++;
			}
			
			i--;

			 
			s.push(op);
		}
              
	}
         
	if(s.size()==1)
	return s.top();
        else return -1;
}

int postfixOperation(char op, int op1, int op2)      //Performing Operation
{
	if(op == '+') return op1 +op2;
	else 
	if(op == '-') return op1 - op2;
	else 
	if(op == '*') return op1 * op2;
	else 
	if(op == '/') return op1 / op2;

	else cout<<"Invalid Symbol \n";
	return -1; 
}


bool IsOperator(char c)                            // Checking if Operator
{
	if((c == '+') || (c == '-') || (c == '*') || (c == '/'))
		return true;

	return false;
}

bool IsNumber(char c)                              //  Checking if number
{
	if((c >= '0') && (c <= '9')) 
          return true;
	return false;
}

int main(int argc, char * argv[]) 
{
	char c;
	string expression;         	
        while((c=getopt(argc, argv, "e:"))!= -1)
        {
            switch(c)
          {
            case 'e':
                      expression=optarg;
                      break;
           default:   print_usage();                      
                      exit(EXIT_FAILURE);
          }
        }
	int res = parseExpression(expression);
        if(res==-1)
        cout<<"Enter Valid postfix expression"<<endl;
        else
	cout<<"RESULT OF EVALUATED EXPRESSION = "<<res<<"\n";
}


