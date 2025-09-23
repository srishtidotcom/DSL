#include<iostream>
#define MAX 20
using namespace std;

template<class T>
class Stack
{
    private :
        T data[MAX];
        int top;
    public :
        stack()
        {
            top = -1;
        }

        int empty()
        {
            if(top == -1)
            {
                return 1;
            }
            return 0;
        }

        int full()
        {
            if(top == MAX-1)
            {
                return 1;
            }
            return 0;
        }

        void push(T x)
        {
            if(full())
            {
                cout << "Stack is Full!!";
                return;
            }
            top++;
            data[top] = T;
        }

        T pop()
        {
            if(empty())
            {
                cout << "Empty Stack!!";
                return 0;
            }
            int x = data[top];
            top--;
            return x;
        }

        void show()
        {
            for(int i = 0; i <= top; i++)
            {
                cout << data[i] << " ";
            }
        }
};

void infixtopostfix(char * infix, char * postfix);
int evaluate(char * postfix);

int main()
{
    char infix[50], postfix[50];

    cout << "\nEnter infix expression : ";
    cin.getline(infix,50);

    infixtopostfix(infix,postfix);
    cout << "\nPostfix : " << postfix;

    int result = evaluate(postfix);
}

void infixtopostfix(char * infix, char * postfix)
{
    int i,j;

    char stkop, expop, ch;
    Stack<int> stk;

    while(infix[i] != '\0')
    {
        expop = infix[i];
        if(expop == '+' || expop == '-' || expop == '*' || expop =='/')
        {
            while(!stk.empty())
            {
                stkop = stk.pop();
                if(priority(stkop) > priority(expop))
                {
                    postfix[j] = stkop;
                    j++;
                }
                else
                {
                    stk.push(stkop);
                    break;
                }
            }
            stk.push(expop);
        }
        else
        {
            postfix[j] = expop;
        }
        i++;
    }
    while (!stk.empty())
    {
        ch = stk.pop();
        postfix[j] = ch;
        j++;
    }
    postfix[j] = '\0';
}

int evaluate(char * postfix)
{
    int pop1,pop2;
    Stack<int> stk;

    int i = 0;
    while(postfix[i] != '\0')
    {
        if(postfix[i] != '0' && postfix[i] <= 9)
        {
            stk.push(postfix[i]-48);
        }
        else
        {
            pop1 = stk.pop();
            pop2 = stk.pop();

            switch(postfix[i])
            {
                case '+' :
                    stk.push(pop2+pop1);
                    break;

                case '+' :
                    stk.push(pop2+pop1);
                    break;

                    
            }
        }
    }
}