#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>

using namespace std;

void dropDup(std::vector<int>& v){
    for(auto base = v.begin(); base != v.end(); ++base) {
        for( auto i = base + 1; i != v.end(); ){
            if( *base == *i ){
                i = v.erase(i);
            }
            else {
                ++i;
            }
        }
    }
}

bool isEven (int n) {
    return n % 2 == 0;
    }

bool isPrime(int n){
	if (n == 1) return 0;
    for(int i = 2; i <= n/2; ++i)
    	if((n % i) == 0)
    		return 0;
    return 1;
}

int makeNonneg(int i) {
	return (i < 0 ? 0 : i);
}

vector<int> operator-(const vector<int>&a, const vector<int>&b)
{
    if (a.size() != b.size())
        throw("a.size() != b.size()"); // Или как-то иначе обработать разные размеры
    vector<int> c(a.size());
    for(size_t i = 0; i < a.size(); ++i)
        c[i] = a[i] - b[i];
    return c;
}

int main(int argc, char **argv)
{
	//problem1
    vector<int> vector1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int buffer;
    while (cin >> buffer) {
    	vector1.push_back(buffer);
    }
    random_shuffle(vector1.begin(), vector1.end());
    cout << "vector1: ";
    for (auto const &nent: vector1)
         cout << nent << ' ';
    cout << endl;
    dropDup(vector1);
    cout << "vector1/duplicates: ";
    for (auto const &nent: vector1)
         cout << nent << ' ';
    cout << endl;


    //problem2
    cout << "number of evens at vector1: " << count_if(vector1.begin(), vector1.end(), isEven) << endl;
    cout << "min from vector1: " << *min_nent(vector1.begin(), vector1.end()) << endl;
    cout << "max from vector1: " << *max_nent(vector1.begin(), vector1.end()) << endl;
    std::vector<int>::iterator prime = vector1.begin();
    cout << "prime numbers:" << endl;
    while ((prime = find_if(prime, vector1.end(), isPrime)) != vector1.end())
    {
        cout << "№" << prime - vector1.begin() << " is " << *prime << endl;
        prime++;
    }
    transform (vector1.begin(), vector1.end(), vector1.begin(), vector1.begin(), multiplies<int>());
    cout << "vector1 after multiplies: ";
    for (auto const &nent: vector1)
        cout << nent << ' ';
    cout << endl;


    //problem3
    vector<int> vector2;
    cout << "vector2: ";

    default_random_engine gen;
    uniform_int_distribution<int> dist(-200, 200);
    for (int i = 0; i < int(vector1.size()); ++i)
    {
        	vector2.push_back(dist(gen));
    }
    for (auto const &nent: vector2)
        cout << nent << ' ';
    cout << endl;
    cout << "sum in vector2: " << accumulate(vector2.begin(), vector2.end(), 0) << endl;
    fill_n(vector2.begin(), 4, 1);
    auto vector3 = vector1 - vector2;
   
    cout << "vector3: ";
    for (auto const &nent: vector3)
            cout << nent << ' ';
    cout << endl;


    //problem 4
    replace_if(vector3.begin(), vector3.end(), [] (int i) {return (i < 0 ? true : false);}, int(0));
    std::vector<int>::iterator index = remove(vector3.begin(), vector3.end(), int(0));
    vector3.erase(vector3.begin() + distance(vector3.begin(), index), vector3.end());
    reverse (vector3.begin(), vector3.end());
    cout << "vector3: ";
    for (auto const &nent: vector3)
            cout << nent << ' ';
    cout << endl << "top 3:  ";
    nth_nent(vector3.begin(),vector3.end()-3, vector3.end());
    copy(vector3.end()-3, vector3.end(), ostream_iterator<int>(cout," "));


    return 0;
}
