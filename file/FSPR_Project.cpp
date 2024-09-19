#include<bits/stdc++.h>
using namespace std;

void PriorityScheduling(string get) {
    cout << "\nPriority Scheduling\n";
    ifstream input_file(get);
    vector<int> p, arv, bt, priority;
    vector<string> star, prcs;
    int id, arrival_time, burst_time, pt;
    string process_name, header;
    getline(input_file, header);
    int n = 0;
    while (input_file >> id >> process_name >> burst_time >> arrival_time >> pt) {
        n++;
        p.push_back(id);
        prcs.push_back(process_name);
        bt.push_back(burst_time);
        arv.push_back(arrival_time);
        priority.push_back(pt);
        string x(burst_time, '#');
        star.push_back(x);
    }
    input_file.close();

    vector<int> comp(n, 0), wt(n, 0), tat(n, 0);

    // Sort by priority (higher priority first)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (priority[j] < priority[j + 1]) {
                swap(arv[j], arv[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(prcs[j], prcs[j + 1]);
                swap(p[j], p[j + 1]);
                swap(star[j], star[j + 1]);
                swap(priority[j], priority[j + 1]);
            }
        }
    }

    comp[0] = arv[0] + bt[0];
    tat[0] = comp[0] - arv[0];
    wt[0] = tat[0] - bt[0];

    for (int i = 1; i < n; i++) {
        if (arv[i] > comp[i - 1]) comp[i] = arv[i] + bt[i];
        else comp[i] = comp[i - 1] + bt[i];
        tat[i] = comp[i] - arv[i];
        wt[i] = tat[i] - bt[i];
    }

    // Display results
    cout << "Display:\n";
    for (int i = 0; i < n; i++) {
        cout << prcs[i] << " " << star[i] << "\n";
    }

    int total_wt = 0, total_tat = 0;
    cout << "\nP\tAT\tBT\tPrt\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << prcs[i] << "\t" << arv[i] << "\t" << bt[i] << "\t" << priority[i] << "\t" << comp[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }
    printf("Average Waiting time: %.2lf\n", (double)total_wt / n);
    printf("Average Turnaround time: %.2lf\n", (double)total_tat / n);
}

void RoundRobin(string get) {
    cout << "\nRound Robin\n";
    ifstream input_file(get);
    vector<int> p, arv, bt, quantum;
    vector<string> star, prcs;
    int id, arrival_time, burst_time, time_quantum;
    string process_name, header;
    getline(input_file, header);
    int n = 0;
    while (input_file >> id >> process_name >> burst_time >> arrival_time >> time_quantum) {
        n++;
        p.push_back(id);
        prcs.push_back(process_name);
        bt.push_back(burst_time);
        arv.push_back(arrival_time);
        quantum.push_back(time_quantum);
        string x(burst_time, '#');
        star.push_back(x);
    }
    input_file.close();

    vector<int> comp(n, 0), wt(n, 0), tat(n, 0);
    int remaining_time[n];
    for (int i = 0; i < n; i++) remaining_time[i] = bt[i];

    int time = 0;
    queue<int> process_queue;
    process_queue.push(0);

    while (!process_queue.empty()) {
        int current_process = process_queue.front();
        process_queue.pop();

        if (remaining_time[current_process] > quantum[current_process]) {
            time += quantum[current_process];
            remaining_time[current_process] -= quantum[current_process];
        } else {
            time += remaining_time[current_process];
            remaining_time[current_process] = 0;
            comp[current_process] = time;
        }

        for (int i = 0; i < n; i++) {
            if (arv[i] <= time && remaining_time[i] > 0 && i != current_process) {
                process_queue.push(i);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        tat[i] = comp[i] - arv[i];
        wt[i] = tat[i] - bt[i];
    }

    // Display results
    cout << "Display:\n";
    for (int i = 0; i < n; i++) {
        cout << prcs[i] << " " << star[i] << "\n";
    }

    int total_wt = 0, total_tat = 0;
    cout << "\nP\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << "P" << p[i] << "\t" << arv[i] << "\t" << bt[i] << "\t" << comp[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }
    printf("Average Waiting time: %.2lf\n", (double)total_wt / n);
    printf("Average Turnaround time: %.2lf\n", (double)total_tat / n);
}

void FirstComeFirstServe(string get) {
    cout << "\nFirst Come First Serve\n";
    ifstream input_file(get);
    vector<int> p, arv, bt;
    vector<string> star, prcs;
    int id, arrival_time, burst_time, pt;
    string process_name, header;
    getline(input_file, header);
    int n = 0;
    while (input_file >> id >> process_name >> burst_time >> arrival_time >> pt) {
        n++;
        p.push_back(id);
        prcs.push_back(process_name);
        bt.push_back(burst_time);
        arv.push_back(arrival_time);
        string x(burst_time, '*');
        star.push_back(x);
    }
    input_file.close();

    vector<int> comp(n, 0), wt(n, 0), tat(n, 0);

    // Sort by arrival time
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arv[j] > arv[j + 1]) {
                swap(arv[j], arv[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(prcs[j], prcs[j + 1]);
                swap(p[j], p[j + 1]);
                swap(star[j], star[j + 1]);
            }
        }
    }

    comp[0] = arv[0] + bt[0];
    tat[0] = comp[0] - arv[0];
    wt[0] = tat[0] - bt[0];

    for (int i = 1; i < n; i++) {
        if (arv[i] > comp[i - 1]) comp[i] = arv[i] + bt[i];
        else comp[i] = comp[i - 1] + bt[i];
        tat[i] = comp[i] - arv[i];
        wt[i] = tat[i] - bt[i];
    }

    // Display results
    cout << "-------------Process Displaying-------------\n";
    for (int i = 0; i < n; i++) {
        cout << prcs[i] << " " << star[i] << "\n";
    }

    int total_wt = 0, total_tat = 0;
    cout << "\nP\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << prcs[i] << "\t" << arv[i] << "\t" << bt[i] << "\t" << comp[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }
    printf("Avg Waiting time: %.2lf\n", (double)total_wt / n);
    printf("Avg Turnaround time: %.2lf\n", (double)total_tat / n);
}

void ShortestJobFirst(string get) {
    cout << "\nShortest Job First Method\n";
    ifstream input_file(get);
    vector<int> p, arv, bt;
    vector<string> star, prcs;
    int id, arrival_time, burst_time, pt;
    string process_name, header;
    getline(input_file, header);
    int n = 0;
    while (input_file >> id >> process_name >> burst_time >> arrival_time >> pt) {
        n++;
        p.push_back(id);
        prcs.push_back(process_name);
        bt.push_back(burst_time);
        arv.push_back(arrival_time);
        string x(burst_time, '#');
        star.push_back(x);
    }
    input_file.close();

    vector<int> comp(n, 0), wt(n, 0), tat(n, 0);

    // Sort by burst time
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (bt[j] > bt[j + 1]) {
                swap(arv[j], arv[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(prcs[j], prcs[j + 1]);
                swap(p[j], p[j + 1]);
                swap(star[j], star[j + 1]);
            }
        }
    }

    comp[0] = arv[0] + bt[0];
    tat[0] = comp[0] - arv[0];
    wt[0] = tat[0] - bt[0];

    for (int i = 1; i < n; i++) {
        if (arv[i] > comp[i - 1]) comp[i] = arv[i] + bt[i];
        else comp[i] = comp[i - 1] + bt[i];
        tat[i] = comp[i] - arv[i];
        wt[i] = tat[i] - bt[i];
    }

    // Display results
    cout << "-------------Process Displaying-------------\n";
    for (int i = 0; i < n; i++) {
        cout << prcs[i] << " " << star[i] << "\n";
    }

    int total_wt = 0, total_tat = 0;
    cout << "\nP\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << prcs[i] << "\t" << arv[i] << "\t" << bt[i] << "\t" << comp[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }
    printf("Avg Waiting time: %.2lf\n", (double)total_wt / n);
    printf("Avg Turnaround time: %.2lf\n", (double)total_tat / n);
}

int main() {
    string fname;
    cout << "Enter the file name: ";
    cin >> fname;

    int ch;
    cout << "Select an option:\n1. First Come First Serve\n2. Shortest Job First\n3. Priority Scheduling\n4. Round Robin\n";
    cout << "Enter choice: ";
    cin >> ch;

    switch (ch) {
        case 1:
            FirstComeFirstServe(fname);
            break;
        case 2:
            ShortestJobFirst(fname);
            break;
        case 3:
            PriorityScheduling(fname);
            break;
        case 4:
            RoundRobin(fname);
            break;
        default:
            cout << "Invalid choice\n";
            break;
    }
    return 0;
}

