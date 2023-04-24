#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>

using namespace std;

#define CAMWIDTH 1280 //Resolution of camera
#define CAMHEIGHT 720 //Resolution of camera
#define PIXSIZE 32 //Size in bits of one pixel
#define FILESIZE CAMHEIGHT*CAMWIDTH*PIXSIZE/8 //Size of one file in MB
#define NUMFILES 100 // Number of files to create
#define BUFSIZE 4096 //Size of buffer which is equal to EXT4 block size
#define BENCHNUM 10 // How many times will benchmark rerun

void create_files(){
    char filename[20];
    char buffer[BUFSIZE];
    for (int i = 0; i < NUMFILES; i++){
        sprintf(filename, "file%d.dat", i);
        ofstream fout(filename, ios::binary);
        for(int j = 0; j < FILESIZE/BUFSIZE; j++) {
            fout.write(buffer, BUFSIZE);
        }
        fout.close();
    }
}

void delete_files(){
    char filename[20];
    for (int i = 0; i < NUMFILES; i++){
        sprintf(filename, "file%d.dat", i);
        remove(filename);
    }
}

double benchmark_read(){
    char filename[20];
    char buffer[BUFSIZE];
    double time_used = 0.0;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < NUMFILES; i++){
        sprintf(filename, "file%d.dat", i);
        ifstream fin(filename, ios::binary);
        for(int j = 0; j < FILESIZE/BUFSIZE; j++) {
            fin.read(buffer, BUFSIZE);
        }
        fin.close();
    }
    auto end = chrono::high_resolution_clock::now();
    time_used = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    return time_used;
}

int main(int argc, char *argv[]){
    create_files();
    ofstream results_file("benchmark_results.txt");
    for (int i = 0; i < BENCHNUM; i++){
        double read_time = benchmark_read();
        results_file << "Read time: " << read_time << " seconds" << endl;
    }
    results_file.close();
    delete_files();
    return 0;
}