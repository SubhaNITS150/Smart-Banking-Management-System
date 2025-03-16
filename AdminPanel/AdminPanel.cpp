
#include <iostream>
#include "AdminPanel.h"
using namespace std;

int main()
{
    AdminPanel newPanel;

    string password = newPanel.getPassword();

    if (password == "Subha@2910")
    {
        cout << "You are authorized! " << endl;
        newPanel.showAdminPanel();
    }

    else
    {
        cout << "You are not an admin!" << endl;
    }

    return 0;
}