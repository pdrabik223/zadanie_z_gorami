#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>
#include <chrono>
#include <fstream>
#include <time.h>
#include <assert.h>

#define MLN *1000000





// naive approach of the worst case complexity n^k, where n = first_array.size, k = second_array.size
unsigned bubble_search(std::vector<int> &first_array, std::vector<int> &second_array);

unsigned hash_table_based_approach(std::vector<int> &first_array, std::vector<int> &second_array);

void test_me_baby_one_more_time();

void test_me_baby_one_more_time_only_hash();

void safe_to_file(int i, double timer, double timer_2);

void create_table(std::vector<int> &first_table, std::vector<int> &second_table, int size_of_em);

// do :
#define DEBUG false
#define TESTS false
#define RELEASE true


int main() {
    srand(time(0));
#if RELEASE
int number_of_tests;
int first_table_size;
int second_table_size;
std::vector<int> tab1,tab2;
std::cin>>number_of_tests;
for(int i=0;i<number_of_tests;i++){
    std::cin>>first_table_size;
    tab1.reserve(first_table_size);
    do{
        int temp;
        std::cin>>temp;
        tab1.push_back(temp);
    }while(--first_table_size);

    std::cin>>second_table_size;
    tab2.reserve(second_table_size);
    do{
        int temp;
        std::cin>>temp;
        tab2.push_back(temp);
    }while(--second_table_size);


    std::cout<<hash_table_based_approach(tab1,tab2);
    tab1.clear();
    tab2.clear();
}

#endif
    #if TESTS
    std::cout << "testing\n";
    test_me_baby_one_more_time();
    std::cout << "done \a\a\a\a";
    std::cout << "testing 2 \n";
    test_me_baby_one_more_time_only_hash();
    std::cout << "done \a\a\a\a";
#endif
    #if DEBUG
    std::vector<int> first_table, second_table;
    create_table(first_table, second_table, 5);

    if(bubble_search(first_table, second_table) !=
       hash_table_based_approach(first_table, second_table))
    {
        // break me baby!
        for(auto i:first_table) std::cout<<i<<"\t";
        printf("\n");
        for(auto i:second_table) std::cout<<i<<"\t";
        printf("nie kysz");
        std::cout<<bubble_search(first_table, second_table)<<std::endl;
        std::cout<<hash_table_based_approach_but_better(first_table, second_table)<<std::endl;




    }
    std::cout<<"kysz";
    system("pause");
#endif



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
    size_t max_table_size = 100;
    size_t step = 10;
    size_t repetitions = 10;

    double timer = 0, timer_2 = 0;

    std::vector<int> first_table, second_table;

    for (int i = min_table_size; i < max_table_size; i += step) {

        for (int k = 0; k < repetitions; ++k) {
            create_table(first_table, second_table, i);


            auto start = std::chrono::steady_clock::now();

            unsigned counter = bubble_search(first_table, second_table);

            auto end = std::chrono::steady_clock::now();

            timer += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();


            start = std::chrono::steady_clock::now();

            if (counter != hash_table_based_approach(first_table, second_table)) {
                std::cout << counter << "\t" << hash_table_based_approach(first_table, second_table)
                          << std::endl;
                std::cout << counter << "\t" << hash_table_based_approach(first_table, second_table)
                          << std::endl;

                system("pause");

            }

            end = std::chrono::steady_clock::now();

            timer_2 += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        }
        safe_to_file(i, timer / repetitions, timer_2 / repetitions);
        timer = 0;
        timer_2 = 0;
    }


}

void test_me_baby_one_more_time_only_hash() {
    size_t min_table_size = 100;
    size_t max_table_size = 1000;
    size_t step = 10;
    size_t repetitions = 10;

    double timer = 0;

    std::vector<int> first_table, second_table;

    for (int i = min_table_size; i < max_table_size; i += step) {

        for (int k = 0; k < repetitions; ++k) {
            create_table(first_table, second_table, i);

            auto start = std::chrono::steady_clock::now();

            hash_table_based_approach(first_table, second_table);

            auto end = std::chrono::steady_clock::now();

            timer += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        }


        safe_to_file(i, -1, timer / repetitions);
        timer = 0;

    }


}

void create_table(std::vector<int> &first_table, std::vector<int> &second_table, int size_of_em) {
    first_table.reserve(size_of_em);
    second_table.reserve(size_of_em);

    for (int i = 0; i < size_of_em; i++)
        first_table.push_back(2 * rand() % 500000);

    for (int i = 0; i < size_of_em; i++)
        second_table.push_back(2 * (rand() % 500000 - 1) + 1);
}

void safe_to_file(int i, double timer, double timer_2) {
    std::ofstream myfile;
    myfile.open("output.txt", std::ios::app);
    myfile << i << "\t" << timer << "\t" << timer_2 << "\n";
    myfile.close();
    printf("saving %d\t%f\t%f\n", i, timer, timer_2);
}
