#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void readData(std::istream &input, 
	      int &numOfBuses,
	      int &capacity,
		  int &numOfPassengers,
		  std::vector<short> &volume) {
	input >> numOfBuses >> capacity >> numOfPassengers;
	volume.resize(numOfPassengers);
	for (int i = 0; i < numOfPassengers; ++i) {
		input >> volume[i];
	}
}

void fillFirstDynamicLevel(std::vector<std::vector<std::vector<short>>> &table,
	                  std::vector<short> &volume,
					  int &capacity,
					  int &numOfPassengers) {
	for (int pass_inx = 1; pass_inx <= numOfPassengers; ++pass_inx) {
		for (int k = 1; k <= capacity; ++k) {
			table[0][pass_inx][k] = std::max(table[0][pass_inx - 1][k],
				table[0][pass_inx][k - 1]);
			if (k >= volume[pass_inx - 1]) {
				table[0][pass_inx][k] = std::max(table[0][pass_inx][k],
					(short)(1 + table[0][pass_inx - 1][k - volume[pass_inx - 1]]));
			}
		}
	}
}

void fillAllDynamic(std::vector<std::vector<std::vector<short>>> &table,
					std::vector<short> &volume,
					int &numOfBuses,
					int &capacity,
					int &numOfPassengers) {
	for (int bus_inx = 1; bus_inx < numOfBuses; ++bus_inx) {
		for (int pass_inx = 1; pass_inx <= numOfPassengers; ++pass_inx) {
			for (int k = 0; k <= capacity; ++k) {
				if (k == 0) {
					table[bus_inx][pass_inx][k] = table[bus_inx - 1][pass_inx][capacity];
				}
				else {
					table[bus_inx][pass_inx][k] = std::max(table[bus_inx][pass_inx - 1][k],
						table[bus_inx][pass_inx][k - 1]);
					if (k >= volume[pass_inx - 1]) {
						table[bus_inx][pass_inx][k] = std::max(table[bus_inx][pass_inx][k],
							(short)(1 + table[bus_inx][pass_inx - 1][k - volume[pass_inx - 1]]));
					}
				}
			}
		}
	}

}

short getResult(std::vector<std::vector<std::vector<short>>> &table,
			  int &numOfBuses,
	          int &capacity,
	          int &numOfPassengers) {
	return table[numOfBuses - 1][numOfPassengers][capacity];
}

void writeResult(std::ostream &output, short result) {
	output << result;
}

int main() {
    std::ifstream input("c.in");
	int numOfBuses, capacity, numOfPassengers;
	std::vector<short> volume;

	readData(input, numOfBuses, capacity, numOfPassengers, volume);
    input.close();

    std::vector<std::vector<std::vector<short>>> table(
        numOfBuses,
        std::vector<std::vector<short>>(
        numOfPassengers + 1,
        std::vector<short>(capacity + 1, 0)));

	fillFirstDynamicLevel(table, volume, numOfBuses, capacity);
	fillAllDynamic(table, volume, numOfBuses, capacity, numOfPassengers);
    
	short result = getResult(table, numOfBuses, capacity, numOfPassengers);
    std::ofstream output("c.out");

	writeResult(output, result);
    output.close();
}


