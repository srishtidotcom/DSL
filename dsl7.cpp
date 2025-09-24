#include <iostream>
using namespace std;

class Expression {
public:
    char infix[20];
    char postfix[20];
    int top;
    char stack[20];

    Expression() {
        top = -1;
    }

    void input() {
        cout << "Enter the Infix Expression: ";
        cin >> infix;
    }

    void push(char ch) {
        if(top < 19) stack[++top] = ch;
    }

    char pop() {
        if(top >= 0) return stack[top--];
        return '\0';
    }

    char peek() {
        if(top >= 0) return stack[top];
        return '\0';
    }

    int isOperator(char ch) {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
    }

    int precedence(char op) {
        if(op == '+' || op == '-') return 1;
        if(op == '*' || op == '/') return 2;
        return 0;
    }

    int isOperand(char ch) {
        return (ch >= 'a' && ch <= 'z'); // Only lowercase letters
    }

    void convert_to_Postfix() {
        int k = 0;
        for(int i = 0; infix[i] != '\0'; i++) {
            char ch = infix[i];

            if(isOperand(ch)) {
                postfix[k++] = ch;
            } else if(ch == '(' || ch == '[') {
                push(ch);
            } else if(ch == ')' || ch == ']') {
                while(top != -1 && peek() != '(' && peek() != '[') {
                    postfix[k++] = pop();
                }
                pop(); // Remove '(' or '['
            } else if(isOperator(ch)) {
                while(top != -1 && precedence(peek()) >= precedence(ch)) {
                    postfix[k++] = pop();
                }
                push(ch);
            }
        }

        while(top != -1) {
            postfix[k++] = pop();
        }
        postfix[k] = '\0';

        cout << "The Postfix Expression is: " << postfix << endl;
    }

    int Operand_value(char x) {
        int val;
        cout << "Enter the value of Operand " << x << ": ";
        cin >> val;
        return val;
    }

    void Postfix_Evaluation() {
        int evalStack[20];
        int evalTop = -1;

        for(int i = 0; postfix[i] != '\0'; i++) {
            char ch = postfix[i];

            if(isOperand(ch)) {
                evalStack[++evalTop] = Operand_value(ch);
            } else if(isOperator(ch)) {
                int val2 = evalStack[evalTop--];
                int val1 = evalStack[evalTop--];

                switch(ch) {
                    case '+': evalStack[++evalTop] = val1 + val2; break;
                    case '-': evalStack[++evalTop] = val1 - val2; break;
                    case '*': evalStack[++evalTop] = val1 * val2; break;
                    case '/': evalStack[++evalTop] = val1 / val2; break;
                }
            }
        }

        cout << "Result of Postfix Evaluation = " << evalStack[evalTop] << endl;
    }
};

int main() {
    cout << "Infix-to-Postfix Conversion & Postfix Evaluation\n";
    Expression exp;
    exp.input();
    exp.convert_to_Postfix();
    exp.Postfix_Evaluation();
    return 0;
}
