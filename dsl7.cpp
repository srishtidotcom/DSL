#include <iostream>
#include <string>
using namespace std;

// ---------------- Stack for Characters ----------------
class Stack {
private:
    int top;
    int size;
    char *arr;

public:
    Stack(int s = 100) {
        size = s;
        arr = new char[size];
        top = -1;
    }

    ~Stack() { delete[] arr; }

    void push(char x) {
        if (top == size - 1)
            cout << "Stack Overflow\n";
        else
            arr[++top] = x;
    }

    char pop() {
        if (top == -1)
            return '\0';
        else
            return arr[top--];
    }

    char peek() {
        if (top == -1)
            return '\0';
        return arr[top];
    }

    bool isEmpty() {
        return top == -1;
    }
};

// ---------------- Stack for Integers ----------------
class IntStack {
private:
    int top;
    int size;
    int *arr;

public:
    IntStack(int s = 100) {
        size = s;
        arr = new int[size];
        top = -1;
    }

    ~IntStack() { delete[] arr; }

    void push(int x) {
        if (top == size - 1)
            cout << "Stack Overflow\n";
        else
            arr[++top] = x;
    }

    int pop() {
        if (top == -1)
            return 0;
        else
            return arr[top--];
    }

    bool isEmpty() {
        return top == -1;
    }
};

// ---------------- Utility Functions ----------------
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool isAlphabet(char ch) {
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}

// ---------------- Infix to Postfix Conversion ----------------
string infixToPostfix(string infix) {
    Stack st(infix.length());
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];
        if (ch == ' ') continue;

        if (isAlphabet(ch) || isDigit(ch)) {
            postfix += ch; // Operand
        }
        else if (ch == '(') {
            st.push(ch);
        }
        else if (ch == ')') {
            while (!st.isEmpty() && st.peek() != '(') {
                postfix += st.pop();
            }
            st.pop(); // remove '('
        }
        else if (isOperator(ch)) {
            while (!st.isEmpty() && precedence(st.peek()) >= precedence(ch)) {
                postfix += st.pop();
            }
            st.push(ch);
        }
    }

    while (!st.isEmpty()) {
        postfix += st.pop();
    }

    return postfix;
}

// ---------------- Postfix Evaluation ----------------
int evaluatePostfix(string postfix) {
    IntStack st(postfix.length());

    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];

        if (isDigit(ch)) {
            st.push(ch - '0');
        }
        else if (isOperator(ch)) {
            int val2 = st.pop();
            int val1 = st.pop();
            int result = 0;

            if (ch == '+') result = val1 + val2;
            else if (ch == '-') result = val1 - val2;
            else if (ch == '*') result = val1 * val2;
            else if (ch == '/') result = val1 / val2;
            else if (ch == '^') result = power(val1, val2);

            st.push(result);
        }
    }

    return st.pop();
}

// ---------------- Main Function ----------------
int main() {
    string infix;
    cout << "Enter an infix expression (single-digit operands only): ";
    getline(cin, infix);

    string postfix = infixToPostfix(infix);
    cout << "Postfix Expression: " << postfix << endl;

    bool numeric = true;
    for (int i = 0; i < infix.length(); i++) {
        if (isAlphabet(infix[i])) {
            numeric = false;
            break;
        }
    }

    if (numeric)
        cout << "Evaluation Result: " << evaluatePostfix(postfix) << endl;
    else
        cout << "Cannot evaluate: expression contains variables." << endl;

    return 0;
}
