#include <iostream>

using namespace std;

class Data{
private:
    int value;

public:

    Data(int val)
    {
        this->value = val;
    }
    int getValue()
    {
        return value;
    }

    void setValue(int val)
    {
        value = val;
    }
    void print()
    {
        cout<<value<<" "<<endl;
    }
};

template <typename T> class Node{

private:
    T *data;
     Node<T>* leftChild;
     Node<T>* rightChild;
     Node<T>* parent;


public:
    Node(T *value)
    {
       data = value;
       leftChild = nullptr;
       rightChild = nullptr;
       parent = nullptr;
    }

    void print(){
            cout<<parent<<endl;
    }

    T* getData()
    {
        return data;
    }

    void setData(T * data)
    {
        this->data = data;
    }

    Node<T> *getLeftChild() {
        return leftChild;
    }
    void setLeftChild(Node<T> *value) {
        leftChild=value;
    }
    Node<T> *getRightChild(){
        return rightChild;
    }
    void setRightChild(Node<T> *value){
        rightChild=value;
    }
    Node<T> * getParent(){
        return parent;
    }
    void setParent(Node<T> * value){
        parent = value;
    }
};

template<typename T> class BinarySearchTree{
private:
    Node<T>* root;
    int numberOfElements;
    int height;

public:

    BinarySearchTree(T* value)
    {
        root->setData(value);
        height = 1;
        numberOfElements = 1;
    }

    ~BinarySearchTree()
    {
        Node<T> *temp = root;
        Node<T> *temp2 = root;

        while(temp->getLeftChild()||temp2->getRightChild())
        {
            temp =temp->getLeftChild();
            delete temp;

            temp2 =temp2->getRightChild();
            delete temp2;

        }
    }

    Node<T> * getRoot()
    {
        return root;
    }
    void setRoot(T * value)
    {
        root = value;
    }
    int getNumberOfElements()
    {
        return numberOfElements;
    }
    void setNumberOfElements(int val)
    {
        numberOfElements= val;
    }
    int getHeight()
    {
        return height;
    }
    void setHeight(int val)
    {
        height = val;
    }


    void insertElement(Data* d)
    {

        Node<T>* newNode = new Node<T>(d);
        bool go = true;


        if(root== nullptr)
        {
            root = newNode;
            return;
        }

        Node<T> *curr = root;
        while(go)
        {
            if(compareTo(d,curr->getData())==-1)
            {
                if(curr->getLeftChild()==nullptr)
                {
                    curr->setParent(curr);
                    curr->setLeftChild(newNode);
                    go = false;
                }
                curr= curr->getLeftChild();
            }
            else{
                if(curr->getRightChild()==nullptr)
                {
                    curr->setParent(curr);
                    curr->setRightChild(newNode);
                    go= false;
                }
                curr=curr->getRightChild();
            }
        }
        numberOfElements++;

        //do height
    }

    int compareTo(T * val1, T * val2)
    {
        if(val1>val2)
            return 1;
        else if(val1==val2)
            return 0;
        else
            return -1;
    }

    void deleteElement(T * val)
    {
        this->root = helperDelete(this->root, val);
        if(root == NULL)
            cout<<"This value does not exist"<<endl;
        numberOfElements--;
        //do height
    }

    Node<T>* helperDelete(Node<T>* temp, T* val)
    {
        if(temp==nullptr)
            return NULL;

        if(compareTo(val, temp->getData())==-1)
        {
            temp->setLeftChild((helperDelete(temp->getLeftChild(),val)));
        }
        else if(compareTo(val, temp->getData())==1)
        {
            temp->setRightChild((helperDelete(temp->getRightChild(),val)));
        }
        else{
            if(temp->getLeftChild()==nullptr)
                return temp->getRightChild();

            if(temp->getRightChild()==nullptr)
                return temp->getLeftChild();

            Node<T>* nextNode = helperFindSmallest(temp->getRightChild());
            temp->setData(nextNode->getData()) ;//mahybe fix findsmallest

            temp->setRightChild((helperDelete(temp->getRightChild(),nextNode->getData())));
        }
        return temp;
    }
    void print()
    {
        helperPrint(root);
    }

    void helperPrint(Node<T>* top)
    {

        Node<T> *large = helperFindBiggest();

        if(top==nullptr)
            return;

        if(top->getData()->getValue()==large->getData()->getValue())
            cout<<top->getData()->getValue()<< " "<< endl;
        else{
            cout<<top->getData()->getValue() <<", "<< endl; //maybe fix
        }
        helperPrint(top->getLeftChild());
        helperPrint(top->getRightChild());
    }

    void findKthElement(int k)
    {
        int count=1;
        Node<T> * temp = root;

        if(k<numberOfElements&&k>0) {
            if (k == 1) {
                cout << root->getData();
            }
            else {
                for (int i = 2; i <= k; i++) {
                    if (count % 2 == 0) {
                        temp = temp->getRightChild();
                        count++;
                    } else {
                        temp = temp->getLeftChild();
                        count++;
                    }
                }
            }
            cout<<temp->getData()->getValue()<<endl;
        }
        else{
            cout<<"Number does not exist";
        }
    }

    void findSmallest()
    {
        Node<T>* temp=root;
        while(temp->getLeftChild()!=nullptr){
            temp = temp->getLeftChild();
        }
        cout<<temp->getData()->getValue()<<endl;
    }

    Node<T>* helperFindSmallest(Node<T>* smol)
    {
        while(smol->getLeftChild()!= nullptr)
        {
            smol = smol->getLeftChild();
        }
        return smol;
    }

    void findBiggest()
    {
        Node<T>* temp= root;
        while(temp->getRightChild()!=nullptr){
            temp = temp->getRightChild();
        }
        cout<<temp->getData()->getValue()<<endl;
    }

    Node<T>* helperFindBiggest()
    {
        Node<T>* temp= root;
        while(temp->getRightChild()!=nullptr){
            temp = temp->getRightChild();
        }
        return temp;
    }

    void sortAscending()
    {
       helperSortAscending(root);
    }

     void helperSortAscending(Node<T> * first)
    {
        Node<T> *large = helperFindBiggest();
        if(first==nullptr) {
            return;
        }

        helperSortAscending(first->getLeftChild());

        if(first->getData()->getValue()==large->getData()->getValue())
        {
            cout<<first->getData()->getValue()<<" ";
        }
        else{
            cout<<first->getData()->getValue()<<", "; // maybe fix maybe call get biggests and check is comma is needed
        }
        helperSortAscending(first->getRightChild());

    }

    void sortDescending()
    {
        helperSortDescending(helperFindBiggest());
    }

    void helperSortDescending(Node<T>* right)
    {

        Node<T>* smol = helperFindSmallest(root);
        if(right==root)
            cout<<root;

        helperSortDescending(right->getParent());
        if(right->getData()->getValue()==smol->getData()->getValue())
        {
            cout<<right->getData()->getValue()<<" ";
        }
        else{
            cout<<right->getData()->getValue()<<", ";
        }
        helperSortDescending(right->getParent()->getLeftChild());


    }
};

int main() {
    int a[] = {10,45,23,67,89,34,12,99};
    Data* newData = new Data(a[0]);
    BinarySearchTree<Data>* newBST = new BinarySearchTree<Data>(newData);
    for(int i=1;i< (sizeof(a)/sizeof(int));i++)
    {
        newData = new Data(a[i]);
        newBST->insertElement(newData);
    }
    newBST->print();
    newBST->findSmallest();
    newBST->findBiggest();
    newData = new Data(10);
    newBST->deleteElement(newData); // delete root
    newBST->print();
    newData = new Data(45);
    newBST->deleteElement(newData); //delete with two children
    newBST->print();
    newData = new Data(12);
    newBST->deleteElement(newData); //delete with one child
    newBST->print();
    newData = new Data(10);
    newBST->deleteElement(newData); // delete a number that doesnt exist. What will you print?
    newBST->print();
    newBST->findKthElement(1); //first element
    newBST->findKthElement(newBST->getNumberOfElements()); //last element
    newBST->findKthElement(3); // some element in between
    newBST->findKthElement(7); // Edge case where item does not exist. What will you print?
    newBST->findSmallest();
    newBST->findBiggest();
    newBST->sortAscending();
    newBST->sortDescending();
    return 0;
}
