// Description: Advising_Assistance_Program.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Author: Anthony.Fillmore@SNHU.edu
// Date: 10/13/2023

#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm> 

using namespace std;

// CLASS Definitions
//
//Class that defines Course object setup and interactions
class Course {
private:
    string course_number;
    string course_title;
    vector<string> prerequisites;

public:
    // Default Constructor
    Course() : course_number(""), course_title(""), prerequisites({}) {}

    // Settors
    // 
    //Course class method to set course number
    //@param constant string reference course number
    //@returns - NA
    void set_course_number(const string& course_number) {
        this->course_number = course_number;
    }

    //Course class method to set course title
    //@param constant string reference course title
    //@returns - NA
    void set_course_title(const string& course_title) {
        this->course_title = course_title;
    }

    //Course class method to set prerequisites
    //@param constant string vector reference prerequisites
    //@returns - NA
    void set_prerequisites(const vector<string>& prerequisites) {
        this->prerequisites = prerequisites;
    }

    // Accessors
    // 
    //Course class method to get course number
    //@param NA
    //@returns - string course number 
    string get_course_number() const {
        return course_number;
    }

    //Course class method to get course title
    //@param NA
    //@returns - string course title
    string get_course_title() const {
        return course_title;
    }

    //Course class method to get prerequisites
    //@param NA
    //@returns - vector of prerequisites
    const vector<string>& get_prerequisites() const {
        return prerequisites;
    }
};

//Class that handles BinarySearchTree details and methods
class BinarySearchTree {
public:
    // public because we have print functions outside the class that rely on traversing the tree
    struct TreeNode {
        Course data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(const Course& value) : data(value), left(nullptr), right(nullptr) {}
    };
    TreeNode* root;

    // Default Constructor
    BinarySearchTree() : root(nullptr) {}

    //Binary Search Tree class method to insert into the tree
    //@param constant string reference course number, constant reference to a Course object
    //@returns - NA
    void insert(const string& course_number, const Course& course) {
        insertHelper(root, course_number, course);
    }

    //Binary Search Tree class method to get_root tree object
    //@param NA
    //@returns - return root of BST object
    TreeNode* get_root() const {
        return root;
    }

    //Binary Search Tree class method to insert into the tree
    //@param constant string reference course number
    //@returns - result of find course - Course object
    const Course return_course_object(const string& course_number) const {
        return find_course(root, course_number);
    }

private:
    //Binary Search class method to find a course in the binary tree
    //@param constant TreeNode object pointer, constant string reference to search on
    //@returns - A populated Course object if found, otherwise default Course object
    const Course find_course(const TreeNode* node, const string& search_key) const {
        if (!node) {
            return Course();  // default course object if we didn't find a course
        }
        // perfect match return that
        if (search_key == node->data.get_course_number()) {
            return node->data;
        }
        // return left node object if key is less than 
        else if (search_key < node->data.get_course_number()) {
            return find_course(node->left, search_key);
        }
        // return right object if key is greater than
        else {
            return find_course(node->right, search_key);
        }
    }
    
    //Helper method for Binary Tree class insert action
    //@param reference to TreeNode pointer object, constant reference string, constant course object reference
    //@returns - NA
    void insertHelper(TreeNode*& node, const string& course_number, const Course& course) {
        // if our tree is empty
        if (!node) {
            node = new TreeNode(course);
            return;
        }
        // if course number is less than the pointer to nodes course number
        if (course_number < node->data.get_course_number()) {
            insertHelper(node->left, course_number, course);
        }
        // if course number is greater than the pointer to nodes course number
        else if (course_number > node->data.get_course_number()) {
            insertHelper(node->right, course_number, course);
        }
    }
};

// Methods specific to Advising Assistance Application but dont belong in BST/Course classes

//A method that will recursively in-order traverse a binary search tree and print course data along the way
//@param constant pointer to TreeNode object
//@returns - NA
void in_order_traversal(const BinarySearchTree::TreeNode* node) {
    if (node) {
        // recursive walk down the left tree
        in_order_traversal(node->left);

        cout << node->data.get_course_number() << ", " << node->data.get_course_title() << endl;

        // next recursive walk down the right tree
        in_order_traversal(node->right);
    }
}

// Wrapper method that prints all courses in a binary search tree
//@param constant reference to BinarySearchTree object
//@returns - NA
void print_all_courses(const BinarySearchTree& bst) {
    cout << endl;
    in_order_traversal(bst.get_root());
    cout << endl;
}

//A method that will split lines based on provided character
//@param constant string reference to the line, the character to split on
//@returns - a vector of elements
vector<string> split_line(const string& line, char delimiter) {
    vector<string> elements;
    istringstream stream(line);
    string token;

    // loop while we have things to loop on
    while (getline(stream, token, delimiter)) {
        elements.push_back(token);
    }

    return elements;
}

//A method that creates a course class object
//@param constant reference string course number, course title and a string vector of prerequisites
//@returns - course object
Course create_course(const string& course_number, const string& course_title, const vector<string> prerequisites) {
    // instantiate course object calling default constructor
    Course course = Course();

    // set course object details
    course.set_course_number(course_number);
    course.set_course_title(course_title);
    course.set_prerequisites(prerequisites);

    return course;
}

//A method that prints course by course number
//@param constant reference to BST object, constant string reference course number
//@returns - NA
void print_course_by_number(const BinarySearchTree& bst, const string& course_number) {
    // get the course object from the binary search tree
    Course foundCourse = bst.return_course_object(course_number);

    // if we find the course, do work
    if (foundCourse.get_course_title() != "") {
        cout << foundCourse.get_course_number() << ", " << foundCourse.get_course_title() << endl;

        cout << "Prerequisites: ";
        const vector<string>& prerequisites = foundCourse.get_prerequisites();
        for (const string& prereq : prerequisites) {
            cout << prereq << " ";
        }

        cout << endl;
    }

    else {
        // Course not found
        cout << "Course Not Found." << endl;
    }
    cout << endl;
}

//A method to load course data from an input file
//@param constant string reference file path, reference to BinarySearchTree object
//@returns - NA
void load_course_data(const string& file_path, BinarySearchTree& bst) {

    // protect our program with try/catch
    try {
        ifstream inputFile(file_path);

        if (!inputFile.is_open())
        {
            throw runtime_error("Could not open the file");
        }

        string line;
        // loop while there is work to do
        while (getline(inputFile, line)) {
            //# Split the line on commas
            vector<string> elements = split_line(line, ',');

            // Check if each line has less than 2 elements
            if (elements.size() < 2) {
                cout << "Not enough elements: " << line << endl;
                continue;
            }

            // set course information from the elements vector we created
            string course_number = elements[0];
            string course_title = elements[1];

            // Initialize prerequisites as an empty vector
            vector<string> prerequisites;

            // Check for prereqs
            if (elements.size() > 2) {
                for (size_t i = 2; i < elements.size(); ++i) {
                    string prereq = elements[i];

                    // check the course object from the BST for prereqs, add to prereqs vector if its not already there
                    if (bst.return_course_object(prereq).get_course_title() != "") {
                        cout << "Prequisite does not exist: " << prereq << endl;
                        prerequisites.push_back(prereq);
                    }
                }
            }
            // Create our course object
            Course course;
            course.set_course_number(course_number);
            course.set_course_title(course_title);
            course.set_prerequisites(prerequisites);



            // Add the course object to the binary search tree
            bst.insert(course_number, course);
        }
        // Clean up after ourselves
        inputFile.close();
    }
    catch (const ifstream::failure& e) {
        cerr << "Exception opening/reading/closing file: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

//A method that provides our application main menu
//@param NA
//@returns - NA
void mainMenu() {
    int choice = 0;
    string userCourse;
    const int LOAD_DATA_STRUCTURE = 1;
    const int PRINT_COURSE_LIST = 2;
    const int PRINT_COURSE = 3;
    const int EXIT_APP = 4;
    const string error = "Error: Please choose an number between 1 and 4.";
    bool exitProgram = false;
    string input;

    // Initialize our binary search tree
    BinarySearchTree bst = BinarySearchTree();

    do {
        cout << "------ Main Menu ------" << endl;
        cout << LOAD_DATA_STRUCTURE << ". Load source data" << endl;
        cout << PRINT_COURSE_LIST << ". Print a list of courses" << endl;
        cout << PRINT_COURSE << ". Print a course" << endl;
        cout << EXIT_APP << ". Exit" << endl;
        cout << "Enter your choice (1-4): ";

        getline(cin, input);

        // protect our main menu from incorrect inputs
        try {
            choice = stoi(input);

            if (choice < 1 || choice > 4) {
                cerr << error << endl;
                continue;
            }
        }
        catch (const exception& e) {
            cerr << error << endl;
            continue;
        }

        switch (choice) {
        case LOAD_DATA_STRUCTURE:
            load_course_data("input.txt", bst);

            break;
        case PRINT_COURSE_LIST:
            cout << "Here is a sample schedule: " << endl;
            print_all_courses(bst);

            break;
        case PRINT_COURSE:
            cout << "What course do you want to know about? ";
            cin >> userCourse;

            print_course_by_number(bst, userCourse);

            break;
        case EXIT_APP:
            cout << "Thank you for using the course planner!" << endl;
            exitProgram = true;
            break;
        }

        if (!exitProgram) {
            cout << "Press 'Enter' to return to the main menu...";
            // clear cin buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    } while (!exitProgram);
}

//A method that invokes our application
//@param NA
//@returns - exit code 0
int main() {
    mainMenu();
    return 0;
}

