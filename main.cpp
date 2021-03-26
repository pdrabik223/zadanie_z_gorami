#include <iostream>
#include <vector>
#include <cstring>

#define MLN *1000000

unsigned hash_table_based_approach(std::vector<int> &first_array, std::vector<int> &second_array);


int main() {
int number_of_tests;
int first_table_size;
int second_table_size;
std::vector<int> tab1,tab2;
std::cin>>number_of_tests;
for(int i=0;i<number_of_tests;i++) {
    std::cin >> first_table_size;
    tab1.reserve(first_table_size);
    do {
        int temp;
        std::cin >> temp;
        tab1.push_back(temp);
    } while (--first_table_size);

    std::cin >> second_table_size;
    tab2.reserve(second_table_size);
    do {
        int temp;
        std::cin >> temp;
        tab2.push_back(temp);
    } while (--second_table_size);


    std::cout << hash_table_based_approach(tab1, tab2)<<std::endl;
    tab1.clear();
    tab2.clear();
}

    return 0;
}



unsigned hash_table_based_approach(std::vector<int> &first_array, std::vector<int> &second_array) {

    char *hash_table = new char[1 MLN];
    memset(hash_table, 0, sizeof(char) * 1 MLN);

    for (auto i:first_array)
        hash_table[i] = 1;


    for (auto j:second_array)
        if (hash_table[j] == 0) hash_table[j] = 2;
        else if (hash_table[j] == 1) return 0;


    unsigned result = 1 MLN;
    unsigned pretender = 1 MLN;
    char last_value_checked = 0;


    for (int i = 0; i < 1 MLN; i++) {
        switch (hash_table[i]) {
            case 0:
                ++pretender;
                break;
            case 1:
                if (last_value_checked != 1) {
                    if (pretender < result) result = pretender;
                }
                
                pretender = 1;
                last_value_checked = 1;
                break;
            case 2:
                if (last_value_checked != 2) {
                    if (pretender < result) result = pretender;
                }
                
                pretender = 1;
                last_value_checked = 2;
                break;
            default:
              // never happens
                break;

        }

    }
    delete[] hash_table;
    return result;
}