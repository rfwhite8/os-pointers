// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <ctype.h>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);
int count = 0;

int main(int argc, char **argv)
{
    Student student;
    double average = 0;
    student.f_name = new char[127];
    student.l_name = new char[127];

    // Sequence of user input -> store in fields of `student`
    student.id = promptInt("Please enter the student's id number: ", 0, 999999999);

    //student firstname call
    std::cout << "Please enter the student's first name: ";
    std::cin >> student.f_name;
    
    //student lastname call
    std::cout << "Please enter the student's last name: ";
    std::cin >> student.l_name;
    
    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 0, 134217728);
    std::cout << "\n\n";
    count = student.n_assignments;

    student.grades = new double[student.n_assignments];    
    int i;
    std::string message = new char[45];
    for(i = 0; i < student.n_assignments; i++){
        message = "";
        message += "Please enter grade for assignment ";
        message += std::to_string(i);
        message += ": ";
        student.grades[i] = promptDouble(message, 0, 1000.0);
    }
    std::cout << "\n";
    std::cout << "Student: " << student.f_name << " " << student.l_name << " " << "[" << student.id << "]";
    std::cout << "\n";
    // Call `CalculateStudentAverage(???, ???)`
    calculateStudentAverage(student.grades,&average);
    // Output `average`
    std::cout << "  Average grade: " << average << "\n";

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    std::string input;
    bool isInt = false;
    int intInput;

    // Code to prompt user for an int
    while(!isInt){
        isInt = true;
        std::cout << message;
        std::cin >> input;
        if(input.find_first_not_of("0123456789") != std::string::npos){
            isInt = false;
            std::cout << "Sorry, I cannot understand your answer\n";
        }
        else if(std::stoi(input) < min || std::stoi(input) > max){
            std::cout << "Sorry, I cannot understand your answer\n";
            isInt = false;
        }
        else{
            intInput = std::stoi(input);
        }
    }
    return intInput;
}
/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    std::string input;
    bool isDouble = false;
    double doubleInput;

    //double returnDouble = 0;
    // Code to prompt user for a double
    while(!isDouble){
        int periodCount = 0;
        isDouble = true;
        std::cout << message;
        std::cin >> input;
        if(input.size() == 1 && input.find_first_of(".") != std::string::npos){
            std::cout << "Sorry, I cannot understand your answer\n";
            isDouble = false;
        }
        else{
            if(input.find_first_not_of(".0123456789") != std::string::npos){
                isDouble = false;
                std::cout << "Sorry, I cannot understand your answer\n"; 
            }
            else if(std::stod(input) < min || std::stod(input) > max){
                std::cout << "Sorry, I cannot understand your answer\n";
                isDouble = false;
            }
            else{
                for(int i = 0; i < input.length(); i++){
                    if (input[i] == '.'){
                        periodCount++;
                    }
                }
                if(periodCount > 1){
                    continue;
                }
                doubleInput = std::stod(input);
            }
        }
    }
    return doubleInput;
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade
    double total = 0;
    int j;

    for(j = 0; j < count; j++){
        total = total + ((double*)object)[j];
    }

    total = total/(double)count;
    *avg = double(int(total*10+0.5))/10;
}
