#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

int main()
{
	string names = "1999.12.01<person>ren@0000.11.05edu.edu\n"
				  "<first>11:30:12Ivan@ed</first>,re\n"
				  "<last>Josuttis.bet@ph.edu.du00:00:00 </last>\n";

	//regex sep("[a-zA-Z0-9_\\.]+@([a-zA-Z0-9]+\\.+[a-zA-Z]{2,4})");
	regex year("([0-9]{1,4}+\\.+[01]+[1-9]+\\.+[0-3]+[0-9])");
	sregex_iterator pos(names.begin(), names.end(), year);
	sregex_iterator end;
	cout << "Years:" << endl;
	for_each(pos, end, [](const smatch &m)
	{
		cout << m.str();
		cout << endl;
	});

	regex time("([0-2]+[0-9]+\\:+[0-5]+[0-9]+\\:+[0-5]+[0-9])");
	sregex_iterator t(names.begin(), names.end(), time);
	//sregex_iterator end;
	cout << "Times:" << endl;
	for_each(t,end, [](const smatch &m)
	{
		cout << m.str();
		cout << endl;
	});
}
