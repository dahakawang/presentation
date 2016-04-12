#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
using namespace std;

void fill(char* data, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = 0; //rand();
    }
}

void fill_data(const string& filename, size_t size, size_t cache_size) {
    int fd = open(filename.c_str(), O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0) {
        perror("error open file");
    }

    char* buffer = (char*) malloc(cache_size);
    size_t cur_size = 0;
    while (cur_size < size ) {
        size_t block_size = (cur_size + cache_size > size)? size - cur_size : cache_size;
        fill(buffer, block_size);

        if (write(fd, buffer, block_size) != (int) block_size) {
            perror("error write");
            free(buffer);
            return;
        }

        cur_size += block_size;
    }
    free(buffer);
}

int main_writer(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "error argument" << std::endl;
        return 1;
    }

    int64_t size = (int64_t)atoi(argv[2]) * 1024 * 1024;
    int cache_size = atoi(argv[3]);
    std::cout << size << std::endl;
    fill_data(argv[1], size, cache_size);

    return 0;
}

int main_mmap(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "wrong argument" << std::endl;
        return 1;
    }

    struct stat file_info;
    if (stat(argv[1], &file_info) < 0) {
        perror("error get file size");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("error open file");
        return 1;
    }

    char* mapped =(char*)  mmap(NULL, file_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    int64_t total = 0;
    for (size_t i = 0; i < (size_t) file_info.st_size; ++i) total += mapped[i];
    std::cout << (file_info.st_size / 1024 / 1024 / 1024 )<< " GB processed" << std::endl;
    std::cout << total << std::endl;

    close(fd);
    return 0;;
}

int main_read(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "wrong argument" << std::endl;
        return 1;
    }

    int cache_size = atoi(argv[2]);
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("error open file");
        return 1;
    }

    int64_t total = 0;
    char* buffer = (char*) malloc(cache_size);
    ssize_t ret, total_size = 0;
    while(( ret = read(fd, buffer, cache_size) ) > 0) {
        total_size += ret;
        for(int i = 0; i < ret; ++i) total += buffer[i];
    }
    if (ret != 0) {
        perror("error reading");
        free(buffer);
        close(fd);
        return 1;;
    }
    std::cout << (total_size / 1024 / 1024 / 1024) << " GB read" << std::endl;
    std::cout << total << std::endl;

    free(buffer);
    close(fd);
    return 0;;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "wrong argument"  << std::endl;
        return 1;
    }

    string subcommand = argv[1];
    vector<char*> sub_argv; sub_argv.reserve(argc - 1);
    sub_argv.push_back(argv[0]);
    std::copy(argv + 2, argv + argc, back_inserter(sub_argv));

    if (subcommand == "writer") {
        return main_writer(sub_argv.size(), sub_argv.data());
    } else if (subcommand == "reader") {
        return main_read(sub_argv.size(), sub_argv.data());
    } else if (subcommand == "mmap") {
        return main_mmap(sub_argv.size(), sub_argv.data());
    } else {
        std::cerr << "undefined subcommand" << std::endl;
        return 1;
    }
    return 0;
}

