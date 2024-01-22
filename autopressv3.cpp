

#include <iostream>
#include <Windows.h>
#include <cctype>
using namespace std;

void keyOutlineCLICK(char inputstartstop, int speedSet, int choiceKey)
{
    DWORD keyActA;
    DWORD keyActB;
    if (choiceKey == 1)
    {
        keyActA = MOUSEEVENTF_LEFTDOWN;
        keyActB = MOUSEEVENTF_LEFTUP;
    }
    else if (choiceKey == 2)
    {
        keyActA = MOUSEEVENTF_RIGHTDOWN;
        keyActB = MOUSEEVENTF_RIGHTUP;
    }

    bool press = false;

    while (true){
        if (GetAsyncKeyState(inputstartstop) & 1)
            press = !press;
        if (press == false){
            mouse_event(keyActA, 0, 0, 0, 0);
            mouse_event(keyActB, 0, 0, 0, 0);
            Sleep(speedSet);
        }
    }
}

void keyOutlinePRESSONE(char inputstartstop, int speedSet, char specKey)
{
    bool press = false;
    char code = VkKeyScan(specKey);

    while (true)
    {
        if (GetAsyncKeyState(inputstartstop) & 1)
            press = !press;
        if (press == false)
        {
            keybd_event(code, WM_KEYDOWN, 0, 0);
            Sleep(speedSet);
        }
    }
}

void keyOutlinePRESSCOMB(char inputstartstop, int speedSet)
{
    int numofkeys;
    cout << "Number of combination keys: ";
    cin >> numofkeys;
    char keyList[numofkeys];
    for (int i = 1; i < numofkeys + 1; i++)
    {
        cout << "Input key #" << i << ": ";
        cin >> keyList[i];
    }

    bool press = false;

    while (true)
    {
        if (GetAsyncKeyState(inputstartstop) & 1)
            press = !press;
        if (press == false)
        {
            for (int k = 1; k < numofkeys + 1; k++)
            {
                keybd_event((VkKeyScan(keyList[k])), WM_KEYDOWN, 0, 0);
                Sleep(speedSet);
            }
        }
    }
}

char lowertoupper(char anyKey)
{
    char upperanyKey = toupper(anyKey);
    return upperanyKey;
}

int main()
{
    char inputstartstopkey;
    int speedSet;
    int choiceKey;
    cout << "=== Choose a button to autopress === " << endl;
    cout << "1: LMB" << endl << "2: RMB" << endl;
    cout << "3: One Specific Key" << endl << "4: Combination of Keys" << endl;
    cout << ">> ";
    cin >> choiceKey;
    cout << "Input start/stop key: ";
    cin >> inputstartstopkey;
    char inputstartstop = lowertoupper(inputstartstopkey);
    cout << "Input speed: ";
    cin >> speedSet;

    if ((choiceKey == 1)||(choiceKey == 2))
    {
        keyOutlineCLICK(inputstartstop, speedSet, choiceKey);
    }

    else if (choiceKey == 3)
    {
        char specanyKey;
        cout << "Input specified key: ";
        cin >> specanyKey;
        char specKey = lowertoupper(specanyKey);
        keyOutlinePRESSONE(inputstartstop, speedSet, specKey);
    }

    else if (choiceKey == 4)
    {
        keyOutlinePRESSCOMB(inputstartstop, speedSet);
    }
}
