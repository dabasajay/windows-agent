// #include<iostream>
// using namespace std;
// int main(){
// 	char ch;
// 	while(true){
// 		cout<<"Hello";
// 		cin>>ch;
// 		if(ch=='q')
// 			break;
// 	}
// }
#include<iostream>
#include <Windows.h>
using namespace std;
int main(){
	STARTUPINFO startInfo = {0};
	PROCESS_INFORMATION processInfo = {0};
	BOOL b5success = CreateProcess(TEXT("//DABASAJAY/test/s1.exe"),NULL,NULL,NULL,FALSE,FALSE,NULL,NULL,&startInfo,&processInfo);
	if(b5success){
		cout<<"Process Started\n";
		cout<<"Process ID : "<<processInfo.dwProcessId<<endl;
	}else{
		cout<<"Error to start the process : "<<GetLastError()<<endl;
	}
	cout<<"here now!";
	cout<<"here now!";
	cout<<"here now!";
	// cin.get();
	return 0;
}