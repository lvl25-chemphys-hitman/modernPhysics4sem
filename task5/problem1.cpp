#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

int main()
{
	string names = "<person>ren@edu.edu\n"
				  "<first>Ivan@ed</first>,re\n"
				  "<last>Josuttis@ph.edu.du </last>\n";

	regex sep("[a-zA-Z0-9_\\.]+@([a-zA-Z0-9]+\\.+[a-zA-Z]{2,4})");
	sregex_iterator pos(names.begin(), names.end(), sep);
	sregex_iterator end;
	for_each(pos, end, [](const smatch &m)
	{
		for(int i = 0; i<m.size();i++)
			cout << m[i].str() << '\t';
		cout << endl;
	});
}
