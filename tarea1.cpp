#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>


void txt_time(const std::string& filename, std::vector<std::chrono::duration<double>> duration) {
    std::ofstream file(filename);
    for (int i = 0; i < duration.size(); i++) {
        file << duration[i].count() << std::endl;
    }
}

// Assuming getFile and readLines are defined somewhere
std::ifstream getFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        
    } 
    return file;
}

std::vector<std::string> readLines(std::ifstream& file) {
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}




// Secuential search function
void AS(std::vector<std::string> list, std::vector<std::string> query) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < query.size(); i++) {
        for (int j = 0; j < list.size(); j++) {
            if (list[j] == query[i]) {
                continue;
            }

        }
        
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "AS function took " << duration.count() << " seconds." << std::endl;
}




// Binary search function implementing radix sort and all the radix sort functions like getMaxLen and countingSort
int getMaxLen(const std::vector<std::string>& list) {
    int maxLen = 0;
    for (const std::string& str : list) {
        if (str.length() > maxLen) {
            maxLen = str.length();
        }
    }
    return maxLen;
}

// Function to perform counting sort based on a specific character position
void countingSort(std::vector<std::string>& list, int pos) {
    std::vector<std::string> output(list.size());
    int count_instances[256] = {0};

    //first loop count every character in and add a number to the position corresponding to the character
    for (int i = 0; i < list.size(); i++){
        int countIndex;
        if (list[i].length() < pos){
            countIndex = 0;
        }
        else{
            countIndex = list[i][pos];
        }
        count_instances[countIndex]++;
    }

    //second make the count instances list a cumulative one
    for (int i = 1; i < 256; i++){
        count_instances[i] += count_instances[i - 1];
    }

    //third loop make the output list
    for (int i = list.size() - 1; i >= 0; i--){
        int countIndex;
        if (list[i].length() < pos){
            countIndex = 0;
        }
        else{
            countIndex = list[i][pos];
        }
        output[count_instances[countIndex] - 1] = list[i];
        count_instances[countIndex]--;
    }

    //final loop make the list equal to the output list
    for (int i = 0; i < list.size(); i++){
        list[i] = output[i];
    }
}

void radixSort(std::vector<std::string>& list) {
    auto start = std::chrono::high_resolution_clock::now();
    int maxLen = getMaxLen(list);
    for (int pos = maxLen - 1; pos >= 0; pos--) {
        countingSort(list, pos);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "radixSort function took " << duration.count() << " seconds." << std::endl;
}
  

void BS_radix(std::vector<std::string> list, std::vector<std::string> query) {
    auto start = std::chrono::high_resolution_clock::now();
    radixSort(list);
    for (int i = 0; i < query.size(); i++){
        int start = 0;
        int end = list.size() - 1;
        while (start <= end) {
            int objective = start + (end - start) / 2;
            if (list[objective] == query[i]) {
                break;
            } else if (list[objective] < query[i]) {
                start = objective + 1;
            } else {
                end = objective - 1;
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "BS_radix function took " << duration.count() << " seconds." << std::endl;
}




// Binary search function implementing selection sort

void selectSort (std::vector<std::string>& list) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < list.size(); i++) {
        int min = i;
        for (int j = i + 1; j < list.size(); j++) {
            if (list[j] < list[min]) {
                min = j;
                
            }
        }
        std::swap(list[i], list[min]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "selectSort function took " << duration.count() << " seconds." << std::endl;
}



void BS_selection(std::vector<std::string> list, std::vector<std::string> query) {
    auto start = std::chrono::high_resolution_clock::now();
    selectSort(list);
    for (int i = 0; i < query.size(); i++){
        int start = 0;
        int end = list.size() - 1;
        while (start <= end) {
            int objective = start + (end - start) / 2;
            if (list[objective] == query[i]) {
                break;
            } else if (list[objective] < query[i]) {
                start = objective + 1;
            } else {
                end = objective - 1;
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "BS_selection function took " << duration.count() << " seconds." << std::endl;}


// get the time of sorts


std::vector<std::chrono::duration<double>> getradix_time(std::vector<std::string>& list) {
    std::vector<std::chrono::duration<double>> times;
    std::chrono::high_resolution_clock::time_point time;
    int maxLen = getMaxLen(list);
    auto start = std::chrono::high_resolution_clock::now();
    for (int pos = maxLen - 1; pos >= 0; pos--) {
        time = std::chrono::high_resolution_clock::now();
        countingSort(list, pos);
        std::chrono::duration<double> actual = time - start;
        times.push_back(actual);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;


    }
    
    
    return times;
} 

std::vector<std::chrono::duration<double>> getselect_time(std::vector<std::string>& list) {
    std::vector<std::chrono::duration<double>> times;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < list.size(); i++) {
        int min = i;
        for (int j = i + 1; j < list.size(); j++) {
            if (list[j] < list[min]) {
                min = j;
                
            }
        }
        std::swap(list[i], list[min]);
        auto time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> actual = time - start;
        times.push_back(actual);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return times;
}

int main() {
    // 10000
    std::cout << "--------------10000------------------" << std::endl;
    std::ifstream file = getFile("D10000.txt");
    std::vector<std::string> dictionary = readLines(file);
    file.close();
    std::ifstream file_query = getFile("Nc.txt");
    std::vector<std::string> query = readLines(file_query);
    file_query.close();


    BS_selection(dictionary, query);
    BS_radix(dictionary, query);

    std::vector<std::chrono::duration<double>> times_radix = getradix_time(dictionary);
    std::vector<std::chrono::duration<double>> times_select = getselect_time(dictionary);
    txt_time("radix_time_1.txt", times_radix);
    txt_time("select_time_1.txt", times_select);

    AS(dictionary, query);



    // 50000
    std::cout << "--------------50000------------------" << std::endl;
    std::ifstream file2 = getFile("D50000.txt");
    std::vector<std::string> dictionary2 = readLines(file2);
    file2.close();
    std::ifstream file_query2 = getFile("Nc.txt");
    std::vector<std::string> query2 = readLines(file_query2);
    file_query2.close();


    BS_selection(dictionary2, query2);
    BS_radix(dictionary2, query2);

    std::vector<std::chrono::duration<double>> times_radix2 = getradix_time(dictionary2);
    std::vector<std::chrono::duration<double>> times_select2 = getselect_time(dictionary2);
    txt_time("radix_time_2.txt", times_radix2);
    txt_time("select_time_2.txt", times_select2);

    AS(dictionary2, query2);

    std::cout << "--------------100000------------------" << std::endl;
    // 100000
    std::ifstream file3 = getFile("D100000.txt");
    std::vector<std::string> dictionary3 = readLines(file3);
    file3.close();
    std::ifstream file_query3 = getFile("Nc.txt");
    std::vector<std::string> query3 = readLines(file_query3);
    file_query3.close();


    BS_selection(dictionary3, query3);
    BS_radix(dictionary3, query3);

    std::vector<std::chrono::duration<double>> times_radix3 = getradix_time(dictionary3);
    std::vector<std::chrono::duration<double>> times_select3 = getselect_time(dictionary3);
    txt_time("radix_time_3.txt", times_radix3);
    txt_time("select_time_3.txt", times_select3);

    AS(dictionary3, query3);

    std::cout << "--------------200000------------------" << std::endl;
    // 200000
    std::ifstream file4 = getFile("D200000.txt");
    std::vector<std::string> dictionary4 = readLines(file4);
    file4.close();
    std::ifstream file_query4 = getFile("Nc.txt");
    std::vector<std::string> query4 = readLines(file_query4);
    file_query4.close();


    BS_selection(dictionary4, query4);
    BS_radix(dictionary4, query4);

    std::vector<std::chrono::duration<double>> times_radix4 = getradix_time(dictionary4);
    std::vector<std::chrono::duration<double>> times_select4 = getselect_time(dictionary4);
    txt_time("radix_time_4.txt", times_radix4);
    txt_time("select_time_4.txt", times_select4);

    AS(dictionary4, query4);

    std::cout << "--------------400000------------------" << std::endl;
    // 400000
    std::ifstream file5 = getFile("D400000.txt");
    std::vector<std::string> dictionary5 = readLines(file5);
    file5.close();
    std::ifstream file_query5 = getFile("Nc.txt");
    std::vector<std::string> query5 = readLines(file_query5);
    file_query5.close();


    BS_selection(dictionary5, query5);
    BS_radix(dictionary5, query5);

    std::vector<std::chrono::duration<double>> times_radix5 = getradix_time(dictionary5);
    std::vector<std::chrono::duration<double>> times_select5 = getselect_time(dictionary5);
    txt_time("radix_time_5.txt", times_radix5);
    txt_time("select_time_5.txt", times_select5);

    AS(dictionary5, query5);


    return 0;
}