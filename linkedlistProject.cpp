#include <iostream>
#include <string>
using namespace std;

/*
Filename    : linkedlistProject.cpp
Author      : Juan Alvin S. S.
Description : Project to make linked list, add number to linked list, remove the number from linked list (numbers inserted into the linkedlist
              are sorted ascending)
(Introduction to Programming project)
(I try to use my own code, not relying on built functions such as power, converting string to double, converting string to int)
(I made this prog in 2021)
*/

// Function to do exponential/power operation
// used in this program to convert strings to int/double without the help of existing functions
int Power(int num, int power){
    int result = 1;
    for(int i = 0; i < power; i++){
        result = result * num;
    }
    return result;
}

// Function to convert string to double,--------- I use double data type to check integer overflow
double todoub (string x){
    int v = x.length()-1;  // index of last char of the string
    int ind = 0;
    double temp = 0;
    for (int i = v; i >= 0; i--){
        if((x[i]>='0' && x[i]<='9') && x[i]!='.'){
            double x1 = x[i]-48; // converting string/char to numeric based on ASCII Table
            temp = temp + x1 * Power(10, ind);
            ind++;
        } else if(i == 0 && x[i] == '-'){
            temp = temp * -1;  // if there is minus sign at the beginning, it means the number is negative
        }
    }
    return temp;
}

// Function to do Input Validation
// Check if the input characters are all numbers, or negative sign in the first index
bool validation (string x){
    bool temp = false;
    int counter = 0;
    for (int i = 0; i < x.length(); i++){
        if(x[i]>='0' && x[i]<='9'){
            temp = true;
        } else if(i == 0 && x[i] == '-'){
            temp = true;
        } else{
            counter++;  // if the string contain something that is not number (except minus sign at the beginning), it will increase the counter
        }
    }
    if (counter == 0){  // if the counter is zero, that means the input is valid since it only contains number or minus sign at the beginning
        temp = true;   // input valid
    }else {
        temp = false;  // input invalid
    }
    return temp;
}

// Function to convert string to integer, works exactly the same as the function to convert string to double
int toint (string x){
    int v = x.length()-1;
    int ind = 0;
    int temp = 0;
    for (int i = v; i >= 0; i--){
        if((x[i]>='0' && x[i]<='9') && x[i]!='.'){
            int x1 = x[i]-48;
            temp = temp + x1 * Power(10, ind);
            ind++;
        } else if(i == 0 && x[i] == '-'){
            temp = temp * -1;
        }
    }
    return temp;
}

// Function to print out the choices
void choicelist(){
    cout << "1. Enter a number" << endl;
    cout << "2. Remove a number" << endl;
    cout << "3. Exit" << endl;
    cout << endl;
    cout << "Please select an option = ";
}

// Class to make node, it contains a number(integer) and a memory address
class node{
public:
    int number;
    node *next = nullptr;
};

// Class Linkedlist
class linkedlist{
    public:
        node *head = nullptr;
        node *tail = nullptr;

        linkedlist(){
            head = NULL;
            tail = NULL;
        }
        void relocatetail(){ // function to relocate tail after removing element
            node *temp = head;
            if (head->next == NULL){
                tail = head;
            } else {
                while(temp->next != NULL){
                    temp = temp->next;
                    tail = temp;
                } 
            }
        }
        // Function to print out all element in the linked list
        void print(){
            cout << "Your Linked-List is updated: ";
            node *tmp = head;
            while(tmp != nullptr){ // while the node is not empty, print the element and go to the next node
                cout << tmp->number << ", ";
                tmp = tmp->next;
            }
            cout << endl;
        }
        // Function to add a new node (option 1)
        void addnode(int x){
            node *temp = new node; // make a new node in a new memory address
            temp->number = x; // put an integer into the node
            temp->next = NULL;
            if (head == NULL){ // if head is empty, means linked list is empty, so both head and tail have the same element since there is only one node
                head = temp;
                tail = temp;
            } else { // if there is already a node or more in the linked list
                tail->next = temp;
                tail = tail->next;
            }
        }
        // Function to sort the numbers in ascending order
        void sortlist(){
            node *current = head;
            node *after = NULL;
            int tempo = 0;

            while(current != NULL){      // going through every node, while the node is not empty
                after = current->next;  // get the memory address of the next node
                while (after != NULL){
                    if (current->number > after->number ){ // if the number in the current node is bigger than the number in the next node, they swap numbers
                        tempo = current->number;
                        current->number = after->number;
                        after->number = tempo;
                    }
                    after = after->next; //get the next memory address
                }
                current = current->next;  //get the next memory address
            }
        }
        // function to search if the input number exist in the linked list ( for option 2)
        bool searchnode (int x){
            node *temp;
            temp = head;
            if (head == NULL){
                cout << "Your Linked-list is empty" << endl;
                return false;
            }
            else {
                while (temp != NULL){
                    if (temp->number == x){  // if the node contains the input number
                        return true;
                        break;
                    }
                    temp = temp->next;
                }
                return false;  //  if the linked-list does not have the input number
            }
        }
        // function to remove node (option 2)
        void removenode(int x){
            node *temp;
            temp = head;
            node *temp2;
            while (temp != NULL){ // while the node is not empty
                if (head->number == x){ // if the removed number is the first node / the head
                    head = head->next; // the new head will be the element after the old head
                    break; // break out of loop
                } else if (temp->next->number == x){ // if the removed number is the next number from the current node
                    temp->next = temp ->next->next;  //  the next memory address will be set to the memory address after the next one
                    break; // break out of loop
                }
                temp = temp->next; // to go to the next node
            }
        }
};

int main()
{
    linkedlist linkedlist1; // create a linked list

    int put_in_node = 0; // number to put in linked list or number to remove from linked list
    double overcheck = 0; // double to check integer overflow
    bool inputvalid = false; // to check input validation
    bool inputvalid2 = false;
    double minover = 2147483648; // lower limit of signed integer, supposed to be negative, but when it tried it, it doesnt include the negative (it says unsigned long), so i make it negative in the if statement below. This problem only happens in vs code. I tried using CodeBlocks and run the program with the negative sign and it worked fine.
    double maxover = 2147483647; // upper limit of signed integer
    string choice = "";
    string inputnum = "";
    // -- the program will keep on running until the user choose 3(exit)
    while (choice != "3"){
        choicelist();    // to print out the choices
        cin >> choice;     // ask for choice input
        while (choice != "1" && choice != "2" && choice != "3"){  // input validation for choice
            cout << choice << " is not a valid option" << endl;
            choicelist();
            cin >> choice;
        }
        // ------- CHOICE 1 (ADD TO LIST) -----------
        if (choice == "1"){
            inputnum = "";
            cout << "Enter a number: ";
            cin >> inputnum;    // ask for the number to add to linked list
            inputvalid = validation(inputnum);   // input validation
            if (inputvalid == true){
                overcheck = todoub(inputnum);  // if input is valid (contain numbers or minus sign at the beginning), convert it to double
            }
            
            if (overcheck < (minover*-1) || overcheck > maxover){  // checking for integer overflow
                inputvalid = false; // if value is out of integer range, input is not valid
            }
            while (inputvalid == false){ // keep on repeating if the input is invalid
                cout << inputnum << " is not a valid number" << endl;
                inputnum = "";
                cout << "Enter a number: ";
                cin >> inputnum;
                inputvalid = validation(inputnum);
                if (inputvalid == true){
                    overcheck = todoub(inputnum);
                }
                if (overcheck < (minover*-1) || overcheck > maxover){
                    inputvalid = false;
                }
            }
            put_in_node = toint(inputnum);   // if the input is finally valid, all numbers and no overflow, convert the input string to int
            linkedlist1.addnode(put_in_node); // add the int to the linked list
            linkedlist1.sortlist(); // sort the numbers in the linked list
            linkedlist1.print(); // print all the numbers in the linked list
            cout << endl;
        }
        else if (choice == "2" && linkedlist1.head == NULL){  //  if user choose to remove a number but the linked list is empty
            cout << "Your Linked-list is empty!" << endl;
        }
// ------- CHOICE 2 (REMOVE FROM LIST) -----------
        else if (choice == "2" && linkedlist1.head != NULL){  //  if user choose to remove a number but the linked list is not empty
            inputnum = "";    // proses for validation similar to choice 1
            cout << "Enter a number: ";
            cin >> inputnum;
            inputvalid = validation(inputnum);
            if (inputvalid == true){
                overcheck = todoub(inputnum);
            }
            if (overcheck < (minover*-1) || overcheck > maxover){
                inputvalid = false;
            }
            if (inputvalid == true){
                put_in_node = toint(inputnum);
                inputvalid2 = linkedlist1.searchnode(put_in_node);  // this is to check if the number exist in the linked list
            }
            if (inputvalid2 == false){  // if the number is not in the linked list, input is invalid
                inputvalid = false;
            }
            while (inputvalid == false){  // repeat the input process if it is not valid
                if (linkedlist1.head == NULL){
                    break;
                }
                cout << inputnum << " is not a valid number" << endl;
                inputnum = "";
                cout << "Enter a number: ";
                cin >> inputnum;
                inputvalid = validation(inputnum);
                if (inputvalid == true){
                    overcheck = todoub(inputnum);
                }
                if (overcheck < (minover*-1) || overcheck > maxover){
                    inputvalid = false;
                }
                if (inputvalid == true){
                    put_in_node = toint(inputnum);
                    inputvalid2 = linkedlist1.searchnode(put_in_node);
                }
                if (inputvalid2 == false){
                    inputvalid = false;
                }
            }
            linkedlist1.removenode(put_in_node);  // remove the number from the list
            if (linkedlist1.head != NULL){
                linkedlist1.relocatetail(); // to relocate tail
            }
            linkedlist1.print();  // print out the list
            cout << endl;
        }

// ------- CHOICE 3 (EXIT) ----------------------
        else if (choice == "3"){
            cout << "3 is chosen, exiting program";
        }
    }
}
// indicator of empty linked list in if(choice == 2 && ll.head != NULL) is not very necessary since there is already if(choice == 2 && ll.head == NULL)
