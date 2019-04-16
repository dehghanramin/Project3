//Filename: main.cpp
//Programmer:  Ramin Dehghan                                      CSCI 123, Spring 2019
//Project #3                                                      Instructor:  Timothy Mai
//Due Date:  04/06/2019                                           Date Submitted: 
//Program Description: A referee listing program with various different ways to display content it is holding. CAn add, remove, list, ...
//referees. All search algorithms written in linear time.



#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iomanip>



enum RefereeGrade {UNKNOWN, CLUB, STATE, NATIONAL, FIFA};
enum State {EXACT, ID, HIGHER, LOWER, NAME};



struct SReferee
{
    std::string id;
    std::string first_name;
    std::string last_name;
    RefereeGrade grade;
};



int menu();
std::string convertGradeToString(RefereeGrade const&);
SReferee* findslot(std::string const&);
std::string getFirstName();
std::string getLastName();
std::string getID();
RefereeGrade getGrade();
void print(std::ofstream*);
void print(State const&, RefereeGrade const& = UNKNOWN, std::string const& = "0000", std::string const& = "None", std::string const& = "None");
void printheader(std::ofstream*);
void checkOutput(bool const&);
void listAllReferees();
void ListRefereesOfSpecificGrade();
void listRefereesWithGradeHigherThanSpecifiedGrade();
void listRefereesWithGradeLowerThanSpecifiedGrade();
void listRefereeInfoWithId();
void listRefereeInfoWithNames();
void addNewReferee();
void removeReferee();
void updateRefereeGrade();
void Quit();
void output(SReferee*, std::ofstream*);
void outputFile();



SReferee referees[10] = {
    {"0001", "Mike", "Apple", CLUB},
    {"0012", "Josh", "Boeing", STATE},
    {"0103", "Linda", "Intel", STATE},
    {"0084", "John", "Rambus", NATIONAL},
    {"0205", "Becky", "Sirius", CLUB},
    {"0807", "Kevin", "Suzuki", NATIONAL},
    {"0074", "Henry", "Xilinx", STATE},
    {"0000", "None", "None", UNKNOWN},
    {"0000", "None", "None", UNKNOWN}
};



const SReferee* END = &referees[9];



int main(void)
{
    int choice;
    do
    {
        choice = menu();
        system("clear");
        switch (choice)
        {
            case 1:
                listAllReferees();
                break;
            case 2:
                ListRefereesOfSpecificGrade();
                break;
            case 3:
            listRefereesWithGradeHigherThanSpecifiedGrade();
                break;
            case 4:
                listRefereesWithGradeLowerThanSpecifiedGrade();
                break;
            case 5:
                listRefereeInfoWithId();
                break;
            case 6:
                listRefereeInfoWithNames();
                break;
            case 7:
                addNewReferee();
                break;
            case 8:
                removeReferee();
                break;
            case 9:
                updateRefereeGrade();
                break;
            case 10:
                Quit();
                break;
            default:
                std::cout << "Invalid Entry!" << std::endl;
                break;
        }
    } while (choice > 0 && choice < 10);
    
    return 0;
}



int menu()
{
    short option;
    std::cout << "\n\tREFEREE ASSIGNING SYSTEM\n\n";
    std::cout << "1. List All Referees.\n"
              << "2. List All Referees Of A Specific Grade.\n"
              << "3. List All Referees With Grade Higher Than A Specific Value.\n"
              << "4. List All Referees With Grade Lower Than A specific Value.\n"
              << "5. List Referee Information With ID.\n"
              << "6. List Referee Information With Names.\n"
              << "7. Add New Referee.\n"
              << "8. Remove Referee.\n"
              << "9. Update Referee Grade.\n"
              << "10. Quit.\n" << std::endl
              << "Please select your option: ";
    std::cin >> option;
    while (option < 1 || option > 10)
    {
        std::cout << "Invalid Entry, Please Try Again!" << std::endl;
        std::cin >> option;
    }
    return option;
}



void listAllReferees()
{
    print(nullptr);
}



void ListRefereesOfSpecificGrade()
{
    print(EXACT, getGrade());
}



void listRefereesWithGradeHigherThanSpecifiedGrade()
{
    print(HIGHER, getGrade());
}



void listRefereesWithGradeLowerThanSpecifiedGrade()
{
    print(LOWER, getGrade());
}



void listRefereeInfoWithId()
{
    print(ID, UNKNOWN, getID());
}



void listRefereeInfoWithNames()
{
    print(NAME, UNKNOWN, "0000", getFirstName(), getLastName());
}



void addNewReferee()
{
    if (SReferee* referee = findslot("0000"))
    {
        referee->first_name = getFirstName();
        referee->last_name = getLastName();
        referee->id = getID();
        referee->grade = getGrade();
    }
    else
    {
        std::cout << "Error: No empty slots or invalid entry!" << std::endl;
    }
}



void removeReferee()
{
    if (SReferee* referee = findslot(getID()))
    {
        referee->first_name = "None";
        referee->last_name = "None";
        referee->id = "0000";
        referee->grade = UNKNOWN;
        std::cout << "Referee Removed!" << std::endl;
    }
    else
    {
        std::cout << "Wrong input try again!" << std::endl;
    }
}



void updateRefereeGrade()
{
    if (SReferee* referee = findslot(getID()))
    {
        referee->grade = getGrade();
        std::cout << "Grade Updated!" << std::endl;
    }
    else
    {
        std::cout << "Wrong input! Try again." << std::endl;
    }
}



void Quit()
{
    std::cout << "Quitting....." << std::endl;
    outputFile();
}

//Outputs formatted text.

void output(SReferee* referee, std::ofstream* handle)
{
    if (handle)
    {
        (*handle)
              << "| " << std::setw(12) << referee->id << " |" << std::setw(12)
              << referee->first_name << " |" << std::setw(12)
              << referee->last_name << " |" << std::setw(12)
              << convertGradeToString(referee->grade) << " |" << std::endl
              << std::endl;
    }
    else if (referee)
    {
        std::cout
              << "| " << std::setw(12) << referee->id << " |" << std::setw(12)
              << referee->first_name << " |" << std::setw(12)
              << referee->last_name << " |" << std::setw(12)
              << convertGradeToString(referee->grade) << " |" << std::endl
              << std::endl;
    }
}

//Helper function: returns a pointer to a slot with a specif ID.

SReferee* findslot(std::string const& s)
{
    for (SReferee* pR = referees; pR != END; ++pR)
    {
        if (pR->id == s)
        {
            return pR;
        }
    }
    return nullptr;
}



std::string getFirstName()
{
    std::string input;
    std::cout << "Enter First Name: ";
    std::cin >> input;
    std::cout << std::endl;
    return input;
}



std::string getLastName()
{
    std::string input;
    std::cout << "Enter Last Name: ";
    std::cin >> input;
    std::cout << std::endl;
    return input;
}



std::string getID()
{
    std::string input;
    std::cout << "Enter ID: ";
    std::cin >> input;
    std::cout << std::endl;
    return input;
}



RefereeGrade getGrade()
{
    std::cout << "Select Grade:\n"
              << "1. CLUB\n"
              << "2. STATE\n"
              << "3. NATIONAL\n"
              << "4. FIFA" << std::endl;
    short grade;
    std::cin >> grade;
    switch (grade)
    {
    case 1:
        return CLUB;
        break;
    case 2:
        return STATE;
        break;
    case 3:
        return NATIONAL;
        break;
    case 4:
        return FIFA;
        break;
    default:
        std::cout << "Wrong format: please try again!" << std::endl;
        return getGrade();
        break;
    }
}

//Print helper function: used to output to a file.

void outputFile()
{
    std::ofstream outStream;
    outStream.open("Referees.dat");
    print(&outStream);
    outStream.close();
}

//Convert's internal grade to string representations for output.

std::string convertGradeToString(RefereeGrade const& grade)
{
    switch (grade)
    {
    case UNKNOWN:
        return "UNKNOWN";
        break;
    case CLUB:
        return "CLUB";
        break;
    case STATE:
        return "STATE";
        break;
    case NATIONAL:
        return "NATIONAL";
        break;
    case FIFA:
        return "FIFA";
        break;
    default:
        std::cout << "Error in conversion!" << std::endl;
        return "UNKNOWN";
        break;
    }
}

//Print helper function: detects if no output has been made.

void checkOutput(bool const& parity)
{
    if (!parity)
    {
        std::cout << "|               Sorry! Nothing to show here              |" << std::endl;
    }
}

//General print function used for outputting all referees.

void print(std::ofstream* handle)
{
    printheader(handle);
    for (SReferee* pR = referees; pR != END; ++pR)
    {
        if (pR->id != "0000")
        {
            output(pR, handle);
        }
    }

}

//General print function to output referees based on State.

void print(State const& state, RefereeGrade const& grade, std::string const& cond, std::string const& first, std::string const& last)
{
    bool found = false;
    switch (state)
    {
    case ID:
        printheader(nullptr);
        if (SReferee* ref = findslot(cond))
        {
            output(ref, nullptr);
            found = true;
        }
        break;
    case HIGHER:
        printheader(nullptr);
        for (SReferee* pR = referees; pR != END; ++pR)
        {
            if (pR->grade > grade)
            {
                output(pR, nullptr);
                found = true;
            }
        }
        break;
    case LOWER:
        printheader(nullptr);
        for (SReferee* pR = referees; pR != END; ++pR)
        {
            if ((pR->grade < grade) && (pR->grade != UNKNOWN))
            {
                output(pR, nullptr);
                found = true;
            }
        }
        break;
    case EXACT:
        printheader(nullptr);
        for (SReferee* pR = referees; pR != END; ++pR)
        {
            if (pR->grade == grade)
            {
                output(pR, nullptr);
                found = true;
            }
        }
        break;
    case NAME:
        printheader(nullptr);
        for (SReferee* pR = referees; pR != END; ++pR)
        {
            if ((pR->first_name == first) || (pR->last_name == last))
            {
                output(pR, nullptr);
                found = true;
            }
        }
        break;
    default:
        std::cout << "Error in conversion!" << std::endl;
        break;
    }
    checkOutput(found);
}

//Print Header Information for output.

void printheader(std::ofstream* handle)
{
    if (handle)
    {
        (*handle)
              << "|" <<std::string(56, '-') << "|" << std::endl
              << "| " << std::setw(12) << "ID" << " |" << std::setw(12)
              << "Fisrt Name" << " |" << std::setw(12)
              << "Last Name" << " |" << std::setw(12)
              << "Grade" << " |"
              << std::endl
              << "|" <<std::string(56, '-') << "|" << std::endl;
    }
    else
    {
        std::cout
              << "|" <<std::string(56, '-') << "|" << std::endl
              << "| " << std::setw(12) << "ID" << " |" << std::setw(12)
              << "Fisrt Name" << " |" << std::setw(12)
              << "Last Name" << " |" << std::setw(12)
              << "Grade" << " |"
              << std::endl
              << "|" <<std::string(56, '-') << "|" << std::endl;
    }
}