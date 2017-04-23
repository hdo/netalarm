//============================================================================
// Name        : main.cpp
// Author      : Huy Do (huydo1@gmail.com)
// Version     : 2017-04-22
// Description : Net Alarm Test for DAHUA NVR
//============================================================================

#include <iostream>
#include <unistd.h> // for sleep
#include <string>
#include "dhnetsdk.h"
using namespace std;

LLONG m_lLoginHandle;

void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    cout << "Callback DisConnect" << endl;
    return;
}

void init()
{
    cout << "init" << endl;
    bool success = CLIENT_Init(DisConnectFunc, (LDWORD) 0);
    if (success) 
    {
        cout << "init ok" << endl;
    }
    else
    {
        cout << "init failed" << endl;
    }
}


bool login(string destip, long port, string username, string password)
{
    cout << "login" << endl;
    int error = 0;
    NET_DEVICEINFO deviceInfo = {0};


    m_lLoginHandle = CLIENT_Login(destip.c_str(), port, username.c_str(), password.c_str(),  &deviceInfo, &error);
    if(m_lLoginHandle == 0)
    {
        if(error != 255)
        {
            cout << "login failed with code " << error << endl;
        }
        else
        {
            cout << "login also failed" << endl;
        }
        return false;
    }
    else
    {
        cout << "login ok" << endl;
        return true;
    }

}

void logout()
{
    cout << "logout" << endl;
    bool success = CLIENT_Logout(m_lLoginHandle);
    if(success)
    {
        cout << "logout ok" << endl;
    }
    else
    {
        cout << "logout failed" << endl;
    }
}

void triggerAlarm(int alarmIndex, int action)
{
    if (action > 1) 
    {
        cout << "invalid action" << endl;
        return;
    }
    cout << "trigger alarm: " << alarmIndex << " -> " << action << endl;
    if(0 != m_lLoginHandle)
    {
           ALARMCTRL_PARAM alarmParam = {0};
           alarmParam.dwSize = sizeof(ALARMCTRL_PARAM);
           alarmParam.nAlarmNo = alarmIndex;
           alarmParam.nAction = action;

           BOOL bSuccess = CLIENT_ControlDevice(m_lLoginHandle, DH_TRIGGER_ALARM_IN, &alarmParam);
           if(bSuccess)
           {
               cout << "ok" << endl;
           }
           else
           {
               cout << "failed" << endl;
           }
    }
    else
    {
        cout << "invalid login" << endl;
    }
}

void alarmInStart(int alarmIndex)
{
    cout << "alarm start" << endl;
    if(0 != m_lLoginHandle)
    {
           ALARMCTRL_PARAM alarmParam = {0};
           alarmParam.dwSize = sizeof(ALARMCTRL_PARAM);
           alarmParam.nAction = 1;
           alarmParam.nAlarmNo = alarmIndex;

           BOOL bSuccess = CLIENT_ControlDevice(m_lLoginHandle, DH_TRIGGER_ALARM_IN, &alarmParam);
           if(bSuccess)
           {
               cout << "ok" << endl;
           }
           else
           {
               cout << "failed" << endl;
           }
    }
    else
    {
        cout << "invalid login" << endl;
    }
}

void alarmInStop()
{
    cout << "alarm stop" << endl;
    if(0 != m_lLoginHandle)
    {
           ALARMCTRL_PARAM alarmParam = {0};
           alarmParam.dwSize = sizeof(ALARMCTRL_PARAM);
           alarmParam.nAction = 0;
           alarmParam.nAlarmNo = 0;

           BOOL bSuccess = CLIENT_ControlDevice(m_lLoginHandle, DH_TRIGGER_ALARM_IN, &alarmParam);
           if(bSuccess)
           {
               cout << "ok" << endl;
           }
           else
           {
               cout << "failed" << endl;
           }
    }
    else
    {
        cout << "invalid login" << endl;
    }
}

int main(int argc, char* argv[]) {
	cout << "Dahua Net Alarm Test" << endl; 
    if (argc != 6) 
    {
    	cout << "Usage: netalarm <host ip> <port> <username> <password> <alarm channel>" << endl;             
        return 1;
    }
  
    init();
    bool log_ok = login(argv[1], std::stol(argv[2]), argv[3], argv[4]);
    if (!log_ok) 
    {
        return 2;
    }
  
    int alarmIndex = std::stoi(argv[5]);  
    triggerAlarm(alarmIndex, 1);
    sleep(2);
    triggerAlarm(alarmIndex, 0);
    logout();
	return 0;
}

