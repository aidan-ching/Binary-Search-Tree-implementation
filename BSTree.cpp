#include "BSTree.h"

BSTree::BSTree()
{
    root = nullptr;
}

BSTree::~BSTree()
{
    destroy(root);
}

void BSTree::destroy(Node *abc) const
{
    if (abc)
    {
        destroy(abc->left);
        destroy(abc->right);
        abc = nullptr;
        delete abc;
    }
}

void BSTree::insert(const string &newString)
{
    if (root == nullptr)
    {
        Node *temp = new Node(newString);
        root = temp;
        root->addCounter();
    }

    else
    {
        Node *newNode = new Node(newString);
        Node *currentNode = root;
        newNode->addCounter();

        while (currentNode != nullptr)
        {
            if (newNode->getString() < currentNode->getString())
            {

                if (currentNode->left == nullptr)
                {
                    currentNode->left = newNode;
                    currentNode = nullptr;
                }

                else
                {
                    currentNode = currentNode->left;
                }
            }

            else if (newNode->getString() > currentNode->getString())
            {
                if (currentNode->right == nullptr)
                {
                    currentNode->right = newNode;
                    currentNode = nullptr;
                }
                else
                {
                    currentNode = currentNode->right;
                }
            }

            else if (newNode->getString() == currentNode->getString())
            {
                currentNode->addCounter();
                currentNode = nullptr;
            }
        }
    }
}

Node *BSTree::search(Node *abc, const string &key) const
{
    if (abc == nullptr)
    {
        return nullptr;
    }
    else if (abc->getString() == key)
    {
        return abc;
    }
    else if (abc->getString() > key)
    {
        return search(abc->left, key);
    }
    else
    {
        return search(abc->right, key);
    }
}

bool BSTree::search(const string &key) const
{
    Node *curr = search(root, key);
    if (curr == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void BSTree::remove(const string &key)
{
    Node *parent = nullptr;
    Node *curr = root;

    while (curr != nullptr)
    {
        if (curr->getString() == key) //Node Found
        {
            if (curr->getCounter() > 1)
            {
                curr->decreaseCounter();
            }

            else if (curr->left == nullptr && curr->right == nullptr) //no children leaf nodes
            {
                if (parent == nullptr) //remove root
                {
                    root = nullptr;
                }
                else if (parent->left == curr)
                {
                    parent->left = nullptr;
                }
                else
                {
                    parent->right = nullptr;
                }
            }

            else if (curr->left != nullptr) //there is a left subnode
            {
                parent = curr;
                Node *replace = curr->left;
                
                while (replace->right != nullptr)
                {
                    parent = replace;
                    replace = replace->right;
                }

                curr->setCounter(replace->getCounter());
                curr->setString(replace->getString());

                remove(replace, parent);
            }

            else
            {
                parent = curr;
                Node *replace = curr->right;
                while (replace->left != nullptr)
                {
                    parent = replace;
                    replace = replace->left;
                }

                curr->setCounter(replace->getCounter());
                curr->setString(replace->getString());

                remove(replace, parent);
            }

            return;
        }

        else if (curr->getString() < key)
        {
            parent = curr;
            curr = curr->right;
        }

        else
        {
            parent = curr;
            curr = curr->left;
        }
    }

    return; // node not found
}

void BSTree::remove(Node *curr, Node *parent)
{
    if (curr->left == nullptr && curr->right == nullptr)
    {
        if (parent->left == curr)
        {
            parent->left = nullptr;
            curr = nullptr;
            delete curr;
        }

        if (parent->right == curr)
        {
            parent->right = nullptr;
            curr = nullptr;
            delete curr;
        }
    }

    else if (curr->left != nullptr) //there is a left subnode
    {
        parent = curr;
        Node *replace = curr->left;
        while (replace->right != nullptr)
        {
            parent = replace;
            replace = replace->right;
        }

        curr->setCounter(replace->getCounter());
        curr->setString(replace->getString());

        remove(replace, parent);
    }

    else
    {
        parent = curr;
        Node *replace = curr->right;
        while (replace->left != nullptr)
        {
            parent = replace;
            replace = replace->left;
        }

        curr->setCounter(replace->getCounter());
        curr->setString(replace->getString());

        remove(replace, parent);
    }

    return;
}

string BSTree::largest() const
{
    if (root == nullptr)
    {
        return "";
    }
    else
    {
        Node *curr = root;
        while (curr->right != nullptr)
        {
            curr = curr->right;
        }
        return curr->getString();
    }
}

string BSTree::smallest() const
{
    if (root == nullptr)
    {
        return "";
    }
    else
    {
        Node *curr = root;
        while (curr->left != nullptr)
        {
            curr = curr->left;
        }
        return curr->getString();
    }
}

void BSTree::inOrder() const
{
    inOrder(root);
    cout << endl;
}

void BSTree::inOrder(Node *abc) const
{
    if (abc)
    {
        inOrder(abc->left);
        cout << abc->getString() << "(" << abc->getCounter() << "), ";
        inOrder(abc->right);
    }
}

void BSTree::postOrder() const
{
    postOrder(root);
    cout << endl;
}

void BSTree::postOrder(Node *abc) const
{
    if (abc)
    {
        postOrder(abc->left);
        postOrder(abc->right);
        cout << abc->getString() << "(" << abc->getCounter() << "), ";
    }
}

void BSTree::preOrder() const
{
    preOrder(root);
    cout << endl;
}

void BSTree::preOrder(Node *abc) const
{
    if (abc)
    {
        cout << abc->getString() << "(" << abc->getCounter() << "), ";
        preOrder(abc->left);
        preOrder(abc->right);
    }
}

int BSTree::height(const string &key)
{

    if (!search(key))
    {
        return -1; //not found!
    }
    Node *abc = root;

    while (abc != nullptr)
    {
        if (abc->getString() == key)
        {
            break;
        }

        else if (abc->getString() < key)
        {
            // abc = abc->left;
            abc = abc->right;
        }

        else
        {
            // abc = abc->right;
            abc = abc->left;
        }
    }
    return heightHelper(abc);
}

int BSTree::findMax(int a, int b)
{
    if (a > b)
    {
        return a;
    }

    else
    {
        return b;
    }
}

int BSTree::heightHelper(Node *curr)
{

    if (curr == nullptr)
    {
        return -1;
    }
    int leftHeight = heightHelper(curr->left);
    int rightHeight = heightHelper(curr->right);
    return 1 + findMax(leftHeight, rightHeight);
}
