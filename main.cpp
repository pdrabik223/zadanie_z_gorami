#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>
#include <chrono>
#include <fstream>

#define MLN *1000000

// naive approach of the worst case complexity n^k, where n = first_array.size, k = second_array.size
unsigned bubble_search(std::vector<int> &first_array, std::vector<int> &second_array);

unsigned hash_table_based_approach_but_better(std::vector<int> &first_array, std::vector<int> &second_array);

void test_me_baby_one_more_time();

void safe_to_file(int i, double timer, double timer_2);

void create_table(std::vector<int> &first_table, std::vector<int> &second_table, int size_of_em);


int main() {
    std::cout << "testing";
    test_me_baby_one_more_time();
    std::cout << "done \a\a\a\a";


    return 0;
}

unsigned bubble_search(std::vector<int> &first_array, std::vector<int> &second_array) {
    unsigned result = abs(first_array[0] - second_array[0]);

    for (auto i:first_array)
        for (auto j:second_array) {
            if (abs(i - j) < result) result = abs(i - j);
        }
    return result;
}


void add(char *hash_table, int value) {

    hash_table[value] = 1;

}


unsigned hash_table_based_approach(std::vector<int> &first_array, std::vector<int> &second_array) {

    char *first_hash_table = new char[1 MLN];
    memset(first_hash_table, -1, sizeof(char) * first_array.size());

    char *second_hash_table = new char[1 MLN];
    memset(second_hash_table, -1, sizeof(char) * first_array.size());


    for (auto i:first_array) add(first_hash_table, i);
    for (auto j:second_array) add(second_hash_table, j);

    unsigned result = 1 MLN;
    unsigned pretender;
    int i = 0, j = 0;

    for (; i < 1 MLN; i++) {
        // todo unlikely  to speed it up
        if (first_hash_table[i] != -1) {

            for (; j < 1 MLN; j++) {

                if (second_hash_table[j] != -1) {

                    pretender = abs(i - j);

                    if (pretender < result) result = pretender;
                    j++;

                    break;

                }
            }
        }


    }
    delete[]first_hash_table;
    delete[]second_hash_table;

    return result;
}


unsigned hash_table_based_approach_but_better(std::vector<int> &first_array, std::vector<int> &second_array) {

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
                    pretender = 1;
                }
                last_value_checked = 1;
                break;
            case 2:
                if (last_value_checked != 2) {
                    if (pretender < result) result = pretender;
                    pretender = 1;
                }
                last_value_checked = 2;

                break;
            default:

                printf("%d\t", i);
                assert (false);

                break;

        }

    }
    delete[] hash_table;
    return result;
}


void test_me_baby_one_more_time() {
    std::ofstream myfile;
    myfile.open("output.txt", std::ios::trunc);

    myfile << "table's size\ttime\ttime_2\n";
    myfile.close();


    size_t min_table_size = 5;
    size_t max_table_size = 1000;
    size_t step = 5;
    size_t repetitions = 100;

    double timer = 0, timer_2 = 0;

    std::vector<int> first_table, second_table;

    for (int i = min_table_size; i < max_table_size; i += step) {

        for (int k = 0; k < repetitions; ++k) {
            create_table(first_table, second_table, i);

        }
        auto start = std::chrono::steady_clock::now();

        bubble_search(first_table, second_table);

        auto end = std::chrono::steady_clock::now();

        timer += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        start = std::chrono::steady_clock::now();

        hash_table_based_approach_but_better(first_table, second_table);

        end = std::chrono::steady_clock::now();

        timer_2 += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();


        safe_to_file(i, timer / repetitions, timer_2 / repetitions);
        timer = 0;
        timer_2 = 0;
    }


}

void create_table(std::vector<int> &first_table, std::vector<int> &second_table, int size_of_em) {
    first_table.reserve(size_of_em);
    second_table.reserve(size_of_em);

    for (int i = 0; i < size_of_em; i++)
        first_table[i] = 2 * rand() % 500000;

    for (int i = 0; i < size_of_em; i++)
        second_table[i] = 2 * (rand() % 500000 - 1) + 1;
}

void safe_to_file(int i, double timer, double timer_2) {
    std::ofstream myfile;
    myfile.open("output.txt", std::ios::app);
    myfile << i << "\t\t" << time << "\t" << timer_2 << "\n";
    myfile.close();
}
