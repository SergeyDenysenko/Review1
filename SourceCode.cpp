#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream input("c.in");
    short numOfBuses, capacity, numOfPassengers;
    input >> numOfBuses >> capacity >> numOfPassengers;
    std::vector<short> volume(numOfPassengers);
    for (short i = 0; i < numOfPassengers; ++i) {
        input >> volume[i];
    }
    input.close();

    std::vector<std::vector<std::vector<short>>> table(
        numOfBuses,
        std::vector<std::vector<short>>(
        numOfPassengers + 1,
        std::vector<short>(capacity + 1, 0)));
    for (short pass_inx = 1; pass_inx <= numOfPassengers; ++pass_inx) {
        for (short k = 1; k <= capacity; ++k) {
            table[0][pass_inx][k] = std::max(table[0][pass_inx - 1][k],
                table[0][pass_inx][k - 1]);
            if (k >= volume[pass_inx - 1]) {
                table[0][pass_inx][k] = std::max(table[0][pass_inx][k],
                    (short)(1 + table[0][pass_inx - 1][k - volume[pass_inx - 1]]));
            }
        }
    }
    for (short bus_inx = 1; bus_inx < numOfBuses; ++bus_inx) {
        for (short pass_inx = 1; pass_inx <= numOfPassengers; ++pass_inx) {
            for (short k = 0; k <= capacity; ++k) {
                if (k == 0) {
                    table[bus_inx][pass_inx][k] = table[bus_inx - 1][pass_inx][capacity];
                } else {
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

    std::ofstream output("c.out");
    output << table[numOfBuses - 1][numOfPassengers][capacity];
    output.close();
}


