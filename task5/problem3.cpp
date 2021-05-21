#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <map>

using namespace std;


int main(){
	setlocale(LC_ALL, "Russian");
	map<char,string> letters = {
	{'а', "a"}, {'б', "b"}, {'в', "v"}, {'г', "g"},
	{'д', "d"}, {'е', "e"}, {'ж', "gh"}, {'з', "z"},
	{'и', "i"}, {'й', "j"}, {'к', "k"}, {'л', "l"},
	{'м', "m"}, {'н', "n"}, {'о', "o"}, {'п', "p"},
	{'р', "r"}, {'с', "s"}, {'т', "t"}, {'у', "u"},
	{'ф', "f"}, {'х', "h"}, {'ц', "c"}, {'ч', "ch"},
	{'ш', "sh"}, {'щ', "sch"}, {'ы', "y"}, {'э', "e"},
	{'ю', "yu"}, {'я', "ya"}
	};

	string name = "миша";

	for(int i=0; i<int(name.length()); i++) {
		char element = name[i];
		auto j = letters.find(elem);
		if ( j == letters.end()) {
			cout << element;
		} else cout << j-> second;

	}

}
