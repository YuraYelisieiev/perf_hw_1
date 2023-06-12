#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

#include <cpr/cpr.h>
#include <iostream>

struct Timer {
    Timer() {
        start_time = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration =
                std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << " seconds (" << duration.count() / 1000.f / 1000.f << ")" << std::endl;
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

unsigned int fib(int N) {
    std::vector<unsigned int> fibs {0, 1};
    for (int i = 2; i <= N; ++i) {
        fibs.push_back(fibs[i-1] + fibs[i-2]);
    }
    return fibs[N];
}

void calculate_fib(int N) {
    Timer timer;
    std::vector<unsigned int> fibs(N);
    for (auto order = 0; order < N; ++order) {
        fibs[order] = fib(order);
    }

    for (const auto &number : fibs) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

void sleep_say() {
    Timer timer;
    const std::chrono::seconds kSleepForDuration(5);
    std::this_thread::sleep_for(kSleepForDuration);
}

void dum_writer() {
    Timer timer;

    const std::string kFilename = "some_file.txt";
    std::ofstream file(kFilename);

    const auto start = std::chrono::high_resolution_clock::now();
    const auto kStopAfter = std::chrono::seconds(3); // 3 seconds
    const char kCharacter = 'A'; // Character to be written
    while (std::chrono::high_resolution_clock::now() - start < kStopAfter) {
        file << kCharacter;
        file.flush(); // Flush after every write operation
    }

    file.close();
}


void download() {
    Timer timer;
    const std::string link = "https://archive.ics.uci.edu/ml/machine-learning-databases/covtype/covtype.data.gz";
    cpr::Response response = cpr::Get(cpr::Url{link});

    if (response.error) {
        std::cout << "An error occurred: " << response.error.message << std::endl;
    } else {
        std::cout << "downloaded_bytes " << response.downloaded_bytes << std::endl;
    }
}

int main() {
    std::cout << "Calculating fibonacci" << std::endl;
    calculate_fib(30);
    std::cout << "Sleeeping Zzzzz!" << std::endl;
    sleep_say();
    std::cout << "Writing to some file" << std::endl;
    dum_writer();
    std::cout << "Download" << std::endl;
    download();
    return 0;
}
