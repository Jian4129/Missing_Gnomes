#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <string_view>
#include <charconv>
#include <vector>
#include <algorithm>

//extract two integer from string
std::tuple<int, int> splitString(std::string& input) {
	int spaceIndex = input.find(" ");
	std::string_view originalGnomesCount(input.c_str(), spaceIndex);
	std::string_view remindingGnomesCount(input.c_str() + spaceIndex + 1, input.size() - spaceIndex);

	//convert extracted string into integer type
	int temp1, temp2;
	auto result = std::from_chars(originalGnomesCount.data(), 
		originalGnomesCount.data() + originalGnomesCount.size(), temp1);
	result = std::from_chars(remindingGnomesCount.data(), 
		remindingGnomesCount.data() + remindingGnomesCount.size(), temp2);
	return {temp1, temp2};

}

//reading the rest of the input
void readRemindingGnomes(std::vector<int>& remindingGnomes, int remindingGnomesCount) {
	std::string input = " ";
	for (int i = 0; i < remindingGnomesCount; i++) {
		std::getline(std::cin, input);
		remindingGnomes.push_back(std::stoi(input));
	}
}

//compute the missing Gnomes
void ComputeMissingGnomes(std::vector<int>& missingGnomes, std::vector<int>& remindingGnomes, 
	int originalGnomesCount) {
	for (int i = 1; i < originalGnomesCount + 1; i++) {
		if (std::find(remindingGnomes.begin(), remindingGnomes.end(), i) == remindingGnomes.end()) {
			missingGnomes.push_back(i);
		}
	}
}

//the missing Gnomes is always smaller than its successor
void ComputeOriginalGnomes(std::vector<int>& missingGnomes, std::vector<int>& remindingGnomes,
	std::vector<int>& originalGnomes, int originalGnomesCount) {
	unsigned int missingGnomesIndex = 0;
	unsigned int remindingGnomesIndex = 0;
	int size = missingGnomes.size();
	for (int i = 0; i < originalGnomesCount; i++) {
		if ((missingGnomesIndex < missingGnomes.size()) && 
			(remindingGnomesIndex == remindingGnomes.size() ||
			(missingGnomes[missingGnomesIndex] < remindingGnomes[remindingGnomesIndex]))) {
			originalGnomes.push_back(missingGnomes[missingGnomesIndex]);
			missingGnomesIndex++;
		}
		else {
			originalGnomes.push_back(remindingGnomes[remindingGnomesIndex]);
			remindingGnomesIndex++;
		}
	}
}
int main() {
	//read the first input, which specific the number of original Gnomes and reminding Gnomes
	std::string input = " ";
	std::getline(std::cin, input);
	auto [originalGnomesCount, remindingGnomesCount] = splitString(input);

	std::vector<int> missingGnomes;
	std::vector<int> remindingGnomes;

	readRemindingGnomes(remindingGnomes, remindingGnomesCount);
	ComputeMissingGnomes(missingGnomes, remindingGnomes, originalGnomesCount);

	//print the output
	std::vector<int> originalGnomes;
	ComputeOriginalGnomes(missingGnomes, remindingGnomes, originalGnomes, originalGnomesCount);
	for (int i : originalGnomes) {
		std::cout << i << std::endl;
	}

	return 1;
}