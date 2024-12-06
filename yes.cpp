#include <iostream>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// 7. Copy file using system calls
void copyFile(const char* source, const char* destination) {
    ifstream src(source, ios::binary);
    ofstream dest(destination, ios::binary);
    
    if (src && dest) {
        dest << src.rdbuf();
        cout << "File copied successfully." << endl;
    } else {
        cout << "Error opening file!" << endl;
    }
}

// 8. FCFS Scheduling Algorithm
void fcfsScheduling(vector<pair<int, int>> processes) {
    sort(processes.begin(), processes.end());
    int totalWT = 0, totalTAT = 0;

    for (int i = 0; i < processes.size(); i++) {
        int wt = (i == 0) ? 0 : processes[i - 1].first + processes[i - 1].second;
        int tat = wt + processes[i].second;
        totalWT += wt;
        totalTAT += tat;
        cout << "Process " << processes[i].first << " | Waiting time: " << wt << " | Turnaround time: " << tat << endl;
    }
    cout << "Average Waiting Time: " << totalWT / processes.size() << endl;
    cout << "Average Turnaround Time: " << totalTAT / processes.size() << endl;
}

// 9. SJF Scheduling Algorithm
void sjfScheduling(vector<pair<int, int>> processes) {
    sort(processes.begin(), processes.end(), [](pair<int, int>& a, pair<int, int>& b) {
        return a.second < b.second; // Sort by burst time
    });

    int totalWT = 0, totalTAT = 0;

    for (int i = 0; i < processes.size(); i++) {
        int wt = (i == 0) ? 0 : processes[i - 1].first + processes[i - 1].second;
        int tat = wt + processes[i].second;
        totalWT += wt;
        totalTAT += tat;
        cout << "Process " << processes[i].first << " | Waiting time: " << wt << " | Turnaround time: " << tat << endl;
    }
    cout << "Average Waiting Time: " << totalWT / processes.size() << endl;
    cout << "Average Turnaround Time: " << totalTAT / processes.size() << endl;
}

// 10. Non-Preemptive Priority Scheduling Algorithm
void priorityScheduling(vector<pair<int, pair<int, int>>>& processes) { // <priority, <arrival time, burst time>>
    sort(processes.begin(), processes.end(), [](auto& a, auto& b) {
        return a.first < b.first; // Sort by priority
    });

    int totalWT = 0, totalTAT = 0;

    for (int i = 0; i < processes.size(); i++) {
        int wt = (i == 0) ? 0 : processes[i - 1].second.second + processes[i - 1].second.first;
        int tat = wt + processes[i].second.second;
        totalWT += wt;
        totalTAT += tat;
        cout << "Process with Priority " << processes[i].first << " | Waiting time: " << wt << " | Turnaround time: " << tat << endl;
    }
    cout << "Average Waiting Time: " << totalWT / processes.size() << endl;
    cout << "Average Turnaround Time: " << totalTAT / processes.size() << endl;
}

// 11. SRTF Scheduling Algorithm
void srtfScheduling(vector<pair<int, int>>& processes) {
    // Shortest Remaining Time First (SRTF) requires sorting by burst time.
    sort(processes.begin(), processes.end(), [](pair<int, int>& a, pair<int, int>& b) {
        return a.second < b.second; // Sort by burst time
    });

    int totalWT = 0, totalTAT = 0;

    for (int i = 0; i < processes.size(); i++) {
        int wt = (i == 0) ? 0 : processes[i - 1].first + processes[i - 1].second;
        int tat = wt + processes[i].second;
        totalWT += wt;
        totalTAT += tat;
        cout << "Process " << processes[i].first << " | Waiting time: " << wt << " | Turnaround time: " << tat << endl;
    }
    cout << "Average Waiting Time: " << totalWT / processes.size() << endl;
    cout << "Average Turnaround Time: " << totalTAT / processes.size() << endl;
}

// 12. Sum of n numbers using Pthreads
struct SumData {
    vector<int> numbers;
    int sum;
};

void* sumThread(void* arg) {
    SumData* data = (SumData*) arg;
    int partialSum = 0;
    for (int num : data->numbers) {
        partialSum += num;
    }
    data->sum = partialSum;
    return NULL;
}

void sumUsingThreads(vector<int> numbers) {
    int mid = numbers.size() / 2;
    SumData data1, data2;
    data1.numbers = vector<int>(numbers.begin(), numbers.begin() + mid);
    data2.numbers = vector<int>(numbers.begin() + mid, numbers.end());

    pthread_t t1, t2;
    pthread_create(&t1, NULL, sumThread, &data1);
    pthread_create(&t2, NULL, sumThread, &data2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    int totalSum = data1.sum + data2.sum;
    cout << "Total sum of numbers: " << totalSum << endl;
}

// 13. Memory allocation strategies (First-fit, Best-fit, Worst-fit)
void memoryAllocation(int blockSize[], int processSize[], int m, int n) {
    // First-Fit
    cout << "First Fit Allocation: " << endl;
    vector<int> firstFit(m, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i] && firstFit[j] == -1) {
                firstFit[j] = i;
                cout << "Process " << i << " allocated to block " << j << endl;
                break;
            }
        }
    }

    // Best-Fit
    cout << "\nBest Fit Allocation: " << endl;
    vector<int> bestFit(m, -1);
    for (int i = 0; i < n; i++) {
        int minIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i] && (minIdx == -1 || blockSize[j] < blockSize[minIdx])) {
                minIdx = j;
            }
        }
        if (minIdx != -1) {
            bestFit[minIdx] = i;
            cout << "Process " << i << " allocated to block " << minIdx << endl;
        }
    }

    // Worst-Fit
    cout << "\nWorst Fit Allocation: " << endl;
    vector<int> worstFit(m, -1);
    for (int i = 0; i < n; i++) {
        int maxIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i] && (maxIdx == -1 || blockSize[j] > blockSize[maxIdx])) {
                maxIdx = j;
            }
        }
        if (maxIdx != -1) {
            worstFit[maxIdx] = i;
            cout << "Process " << i << " allocated to block " << maxIdx << endl;
        }
    }
}

int main() {
    // Test File Copy
    copyFile("source.txt", "destination.txt");

    // Test FCFS Scheduling
    vector<pair<int, int>> fcfsProcesses = {{0, 6}, {1, 8}, {2, 7}};
    fcfsScheduling(fcfsProcesses);

    // Test SJF Scheduling
    vector<pair<int, int>> sjfProcesses = {{0, 6}, {1, 8}, {2, 7}};
    sjfScheduling(sjfProcesses);

    // Test Non-Preemptive Priority Scheduling
    vector<pair<int, pair<int, int>>> priorityProcesses = {{1, {0, 6}}, {2, {1, 4}}, {3, {2, 3}}};
    priorityScheduling(priorityProcesses);

    // Test SRTF Scheduling
    vector<pair<int, int>> srtfProcesses = {{0, 6}, {1, 8}, {2, 7}};
    srtfScheduling(srtfProcesses);

    // Test Sum using Pthreads
    vector<int> numbers = {1, 2, 3, 4, 5};
    sumUsingThreads(numbers);

    // Test Memory Allocation
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    memoryAllocation(blockSize, processSize, 5, 4);

