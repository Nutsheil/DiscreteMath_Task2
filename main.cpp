#include <iostream>
#include <vector>

#include "combinatorics.h"

using namespace std;

bool IsDigits(string& s)
{
    for (auto& i : s)
        if (!isdigit(i))
            return false;
    return true;
}

UI GetNum(string str)
{
    double num = stod(str);

    if (num < 0)
        throw runtime_error("Negative number entered");
    if (num > UINT_MAX)
        throw runtime_error("Too large number entered");

    return num;
}

vector<string> MySplit(string& s)
{
    vector<string> splited;
    string tmp;

    for (auto &i : s)
    {
        if (i < 0)
            throw runtime_error("do not use Russian letters");
        if (isspace(i) || i == ',' || i == '(' || i == ')')
        {
            if (!tmp.empty())
            {
                splited.push_back(tmp);
                tmp.clear();
            }
        }
        else
            tmp.push_back(i);
    }
    if (!tmp.empty())
        splited.push_back(tmp);

    return splited;
}

void PrintHelp()
{
    cout << "--------------------------------------" << endl;
    cout << "This program is designed to accurately calculate combinatorial numbers" << endl;
    cout << "You can use the following commands:" << endl;
    cout << "U(m,n) - number of placements WITH repetitions of 'n' elements per 'm'" << endl;
    cout << "A(m,n) - number of placements WITHOUT repetitions from 'n' elements by 'm'" << endl;
    cout << "P(n) - number of permutations of 'n' elements" << endl;
    cout << "C(m,n) - number of combinations of 'n' elements per 'm'" << endl;
    cout << "S(m,n) - Stirling number of the second kind from 'n' elements by 'm'" << endl;
    cout << "B(n) - Bell's number of 'n' elements" << endl;
    cout << "Q - shutting down the program" << endl;
    cout << "H - show a list of available commands" << endl;
    cout << "--------------------------------------" << endl;
}

void Dialog()
{
    cout << "Hello!" << endl;
    cout << "You can use 'H' for more information" << endl;
    cout << "--------------------------------------" << endl;

    string s;
    while (getline(cin, s))
    {
        vector<string> splited;
        try {
            splited = MySplit(s);
        } catch (runtime_error& error) {
            cout << error.what() << endl;
            continue;
        }

        UI m = 0;
        UI n = 0;

        int size = splited.size();
        if (size == 0)
            continue;
        else if (size == 2)
        {
            if (!IsDigits(splited.at(1)))
            {
                cout << "Wrong input" << endl;
                continue;
            }

            try {
                n = GetNum(splited.at(1));
            } catch (runtime_error& error) {
                cout << error.what() << endl;
                continue;
            }
        }
        else if (size == 3)
        {
            if (!IsDigits(splited.at(1)) || !IsDigits(splited.at(2)))
            {
                cout << "Wrong input" << endl;
                continue;
            }

            try {
                m = GetNum(splited.at(1));
                n = GetNum(splited.at(2));
            } catch (runtime_error& error) {
                cout << error.what() << endl;
                continue;
            }
        }

        string keyWord = splited.at(0);
        UI res = 0;

        if (keyWord == "U")
        {
            if (splited.size() != 3)
                cout << "Wrong input" << endl;
            else
            {
                try {
                    res = U(m, n);
                    cout << res << endl;
                } catch (runtime_error& error) {
                    cout << error.what() << endl;
                }
            }
        }
        else if (keyWord == "A")
        {
            if (splited.size() != 3)
                cout << "Wrong input" << endl;
            else
            {
                try {
                    res = A(m, n);
                    cout << res << endl;
                } catch (runtime_error& error) {
                    cout << error.what() << endl;
                }
            }
        }
        else if (keyWord == "P")
        {
            if (splited.size() != 2)
                cout << "Wrong input" << endl;
            else
            {
                try {
                    res = P(n);
                    cout << res << endl;
                } catch (runtime_error& error) {
                    cout << error.what() << endl;
                }
            }
        }
        else if (keyWord == "C")
        {
            if (splited.size() != 3)
                cout << "Wrong input" << endl;
            else
            {
                try {
                    res = C(m, n);
                    cout << res << endl;
                } catch (runtime_error& error) {
                    cout << error.what() << endl;
                }
            }
        }
        else if (keyWord == "S")
        {
            if (splited.size() != 3)
                cout << "Wrong input" << endl;
            else
            {
                try {
                    res = S(m, n);
                    cout << res << endl;
                } catch (runtime_error& error) {
                    cout << error.what() << endl;
                }
            }
        }
        else if (keyWord == "B")
        {
            if (splited.size() != 2)
                cout << "Wrong input" << endl;
            else
            {
                try {
                    res = B(n);
                    cout << res << endl;
                } catch (runtime_error& error) {
                    cout << error.what() << endl;
                }
            }
        }
        else if (keyWord == "H")
        {
            PrintHelp();
        }
        else if (keyWord == "Q")
        {
            cout << "--------------------------------------" << endl;
            cout << "Goodbye my friend" << endl;
            cout << "Have a nice day and be happy!!" << endl;
            return;
        }
        else
        {
            cout << "Wrong input" << endl;
        }
    }
}

int main()
{
    Dialog();
    return 0;
}
