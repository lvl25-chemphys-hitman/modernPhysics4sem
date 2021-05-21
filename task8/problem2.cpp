#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

template <typename T>
inline void PRINT_ELEMENTS (const T& coll, const std::string& optstr="", const std::string& delim=" "){
    std::cout << optstr;
    for (const auto&  elem : coll) {
        std::cout << elem << delim;
    }
    std::cout << std::endl;
}

using namespace std;

const size_t seqLENGTH = 10000;
mutex pvmutex;

string randomDNAseq(size_t length){
    auto randchar = []() -> char
    {
        const char charset[] = "ATGC";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    string str(length,0);
    generate_n( str.begin(), length, randchar );
    return str;
}

void save_position(vector<size_t>& positions, size_t pos, const string& seq, const string& subseq){
	size_t seqLen = seq.size();
	size_t subseqLen = subseq.size();
	size_t i = 0;

	while (pos < seqLen && i < subseqLen)
	{
		if(seq[pos] != subseq[i])
		{
			break;
		}
		++i;
		++pos;
	}
	if(i >= subseqLen)
	{
		lock_guard<mutex> lg(pvmutex);
		positions.push_back(pos - subseqLen);
	}
}

void findAllEntries(vector<size_t>& positions, string& seq, string& subseq)
{
	vector<thread> threads;

	size_t seqLen = seq.size();
	for (size_t i = 0; i < seqLen; ++i)
	{
		if(seq[i] == subseq[0])
		{
			threads.push_back(std::thread(save_position, std::ref(positions), i,
					std::ref(seq), std::ref(subseq)));
		}
	}
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

int main() {
	std::string DNA_seq = randomDNAseq(seqLENGTH);
	std::cout << "DNA sequence for " << seqLENGTH << " elements\n";
	PRINT_ELEMENTS(DNA_seq, "", "");

	std::string seq;
	std::cout << "Enter the sequence: ";
	std::cin >> seq;

	vector<size_t> positions;
	findAllEntries(positions, DNA_seq, seq);
	PRINT_ELEMENTS(positions, "Positions: ", ", ");

	std::cout << positions.size() << " positions found\n";

	return 0;
}

