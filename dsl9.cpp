#include<iostream>
#include<queue>
using namespace std;

/* here 2 classes node and bst
member function independant functions
*/ 
class Node
{
    public :
        int  data;
        Node* left;
        Node* right;

        Node()
        {
            data = 0;
            left = right= NULL;
        }
        Node(int a)
        {
            data = a;
            left = right = NULL;
        }
        ~Node()
        {
            cout << data << " is Destroyed!" << endl;
        }
};

class BST
{
    private:
        Node* root;
    
    public :
        BST()
        {
            root = NULL;
        }

        void insert(int temp);
        void display_in_order();
        void display_pre_order();
        void display_post_order();
        void display_BFS();
        void longestpath();
        void min_node();
        void swap_LR();
        int search(int);

        ~BST();
};

void delete_tree(Node* node)
{
    if(node == NULL)
    {
        return;
    }
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}

Node* insert_Node(Node* node, int val)
{
    if(node == NULL)
    {
        Node*p = new Node(val);
        return p;
    }
    else
    {
        if(val < node -> data)
        {
            node->left = insert_Node(node->left, val);
        }
        else if(val > node->data)
        {
            node->right = insert_Node(node->right, val);
        }

        return node;
    }
}

void inorder(Node* node) //Left root right
{
    if(node == NULL)
    {
        return;
    }
    else
    {
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
}

void preorder(Node* node) //Root Left Right
{
    if(node == NULL)
    {
        return;
    }
    else
    {
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

void postorder(Node* node) //Left Right Root
{
    if(node == NULL)
    {
        return;
    }
    else
    {
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }
}

void levelorder(Node* node)
{
    if(node == NULL)
    {
        return;
    }

    Node* p = node;
    queue<Node*> que;

    que.push(p);
    while(!que.empty())
    {
        p = que.front();
        que.pop();
        cout << p -> data << " ";

        if(p -> left != NULL)
        {
            que.push(p->left);
        }
        if(p -> right != NULL)
        {
            que.push(p->right);
        }
    }

}

int longest_path(Node* node)
{
    if(node == NULL)
    {
        return 0;
    }
    else
    {
        int res1, res2;;
        res1 = longest_path(node -> left);
        res2 = longest_path(node -> right);

        if(res1 > res2)
        {
            return res1+1;
        }
        return res2+1;
    }
}

int minnode(Node * node)
{
    while(node -> left != NULL)
    {
        node = node -> left;
    }
    return node -> data;
}

void swap_LRnodes(Node* node)
{
    if(node == NULL)
    {
        return;
    }
    Node* temp = node -> left;
    node -> left = node -> right;
    node -> right = temp;

    swap_LRnodes(node -> left);
    swap_LRnodes(node -> right);
}

int search_node(Node* node, int key)
{
    if (node == NULL)
    {
        return 0;
    }
    if (node->data == key)
    {
        return 1;
    }
    else if (key < node->data)
    {
        return search_node(node->left, key);
    }
    else
    {
        return search_node(node->right, key);
    }
}

int main()
{
    BST bst;

    // int n,x,i;
    // cout << "Enter number of nodes : ";
    // cin >> n;

    // cout << "Enter " << n << " datas : \n";
    // for(i = 1; i <= n; i++)
    // {
    //     cin >> x;
    //     bst.insert(x);
    // }

    bst.insert(8);
    bst.insert(3);
    bst.insert(10);
    bst.insert(1);
    bst.insert(6);
    bst.insert(14);
    bst.insert(4);
    bst.insert(7);
    bst.insert(13);
    cout << "\nPreorder Traversal : ";
    bst.display_pre_order();
    
    cout << "\nInorder Traversal : ";
    bst.display_in_order();

    cout << "\nPostorder Traversal : ";
    bst.display_post_order();

    cout << "\nLevel order Traversal : ";
    bst.display_BFS();

    int key;
    cout << "\nEnter data to search : ";
    cin >> key;
    if (bst.search(key) == 1)
    {
        cout << "Node " << key << " found in the BST." << endl;
    }
    else
    {
        cout << "Node " << key << " not found in the BST." << endl;
    }

    cout << "\nLongest path from root to leaf : " ;
    bst.longestpath();

    cout << "\nMinimun value node : ";
    bst.min_node();

    cout << "\nSwapping left and right nodes (Preorder): ";
    bst.swap_LR();
    bst.display_pre_order();

    

}

void BST :: insert(int temp)
{
    root = insert_Node(root, temp);
}

void BST :: display_in_order()
{
    inorder(root);
    cout << endl;
}

void BST :: display_pre_order()
{
    preorder(root);
    cout << endl;
}

void BST :: display_post_order()
{
    postorder(root);
    cout << endl;
}

BST::~BST()
{
    cout << endl;
    delete_tree(root);
}

void BST :: display_BFS()
{
    levelorder(root);
    cout << endl;
}

void BST:: longestpath()
{
    cout << longest_path(root)-1;
    cout << endl;
}

void BST :: min_node()
{
    if(root == NULL)
    {
        return;
    }
    cout << minnode(root);
    cout << endl;
}

void BST :: swap_LR()
{
    swap_LRnodes(root);
}

int BST:: search(int key)
{
    return search_node(root, key);
}