#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <cmath>
using namespace std;

unsigned int numBuffers, bufferSize;

class Block {
    // each block has at max (bufferSize/4) numbers and the possibility of putting one overflow block
    vector<int> records;
    Block *overflow;

    public:
    Block() {
        overflow = NULL;
        records.clear();
    }

    bool isPresent(int x) {
        Block *node = this;
        while(node) {
            for(unsigned int i = 0; i < node->records.size(); i++) {
                if(node->records[i] == x) {
                    return true;
                }
            }
            node = node->overflow;
        }
        return false;
    }

    void add(int x) {
        // as sizeof(int) is 4
        if(records.size() < (bufferSize / 4)) {
            records.push_back(x);
        }
        else {
            if(overflow == NULL) {
                overflow = new Block();
            }
            overflow->add(x);
        }
    }

    void clearElements(vector<int> &v) {
        for(unsigned int i = 0; i < records.size(); i++) {
            v.push_back(records[i]);
        }
        records.clear();
        if(overflow) {
            overflow->clearElements(v);
            delete overflow;
            overflow = NULL;
        }
    }

    void print() {
        Block *node = this;
        while(node) {
            for(unsigned int i = 0; i < node->records.size(); i++) {
                cout << node->records[i] << ' ';
            }
            node = node->overflow;
        }
        cout << '\n';
    }

};

class HashTable {
    int numRecords, numBits;
    vector<Block *> buckets;

    public:
    HashTable() {
        // initial configuration of Hash table
        numRecords = 0;
        numBits = 1;
        buckets.push_back(new Block());
        buckets.push_back(new Block());
    }

    unsigned int hash(int x) {
        unsigned int mod = (1 << numBits);
        return (unsigned int)(x % mod + mod) % mod;
    }

    int occupancy() {
        // as sizeof(int) is 4
        double ratio = 1.0 * numRecords / buckets.size();
        return (int)(100 * (ratio / (bufferSize / 4)));
    }

    bool isPresent(int x) {
        unsigned int k = hash(x);
        if(k >= buckets.size()) {
            k -= (1 << (numBits - 1));
        }
        if(buckets[k]->isPresent(x)) {
            return true;
        }
        return false;
    }

    void insert(int x) {
        unsigned int k = hash(x);
        if(k >= buckets.size()) {
            k -= (1 << (numBits - 1));
        }
        buckets[k]->add(x);
        numRecords++;
        while(occupancy() >= 75) {
            buckets.push_back(new Block());
            numBits = ceil(log2((double)buckets.size()));
            // split old bucket and rehash
            k = buckets.size() - 1 - (1 << (numBits - 1));
            vector<int> v;
            buckets[k]->clearElements(v);
            for(unsigned int i = 0; i < v.size(); i++) {
                buckets[hash(v[i])]->add(v[i]);
            }
        }
        //print();
    }

    void print() {
        for(unsigned int i = 0; i < buckets.size(); i++) {
            cout << i << " -> ";
            buckets[i]->print();
        }
        cout << '\n';
    }

};
HashTable h;

// Buffered IO
queue<int> inputBuffer, outputBuffer;
unsigned int inputSize, outputSize;

void clearOutput() {
    int ox;
    while(!outputBuffer.empty()) {
        ox = outputBuffer.front();
        outputBuffer.pop();
        cout << ox << '\n';
    }
}

void clearInput() {
    int ix;
    while(!inputBuffer.empty()) {
        ix = inputBuffer.front();
        inputBuffer.pop();
        if(!h.isPresent(ix)) {
            h.insert(ix);
            if(outputBuffer.size() == outputSize) {
                clearOutput();
            }
            outputBuffer.push(ix);
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc < 4) {
        cout << "Usage : ./a.out <filename> <numBuffers> <bufferSize>\n";
        exit(-1);
    }
    ifstream input(argv[1]);
    numBuffers = atoi(argv[2]); //Must be >=2
    bufferSize = atoi(argv[3]); // Must be >=4
    if(numBuffers < 2 || bufferSize < 4) {
        cout << "Ensure that M>=2 and B>=4\n";
        exit(-1);
    }

    // as sizeof(int) is 4
    inputSize = (numBuffers - 1) * (bufferSize / 4);
    outputSize = bufferSize / 4;
    int x;
    while(input >> x) {
        if(inputBuffer.size() < inputSize) {
            inputBuffer.push(x);
        }
        else {
            clearInput();
            inputBuffer.push(x);
        }
    }
    clearInput();
    clearOutput();
    return 0;
}
