#include <iostream>
#include <math.h>
#include <algorithm>
#include <chrono>
using namespace std::chrono;

using namespace std;
int snail_amount;

void merge(double* array, int start, int mid, int end){
    int n1 = mid - start + 1;
    int n2 = end - mid;

    double* leftArray = new double[n1];
    double* rightArray = new double[n2];

    for (int i = 0; i < n1; i++)
        leftArray[i] = array[start + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = start;

    while (i < n1 && j < n2){
        if (leftArray[i] <= rightArray[j]){
            array[k] = leftArray[i];
            i++;
        }
        else{
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        array[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < n2){
        array[k] = rightArray[j];
        j++;
        k++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(double* array, int l, int r){
    if (l < r){
        int m = l + (r - l) / 2;
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);

        merge(array, l, m, r);
    }
}

struct Snail{
    double x, y;
    double* paths = new double[snail_amount - 1];
    bool confusion = false;
    void if_confusion(){
        //auto start = high_resolution_clock::now();
        mergeSort(paths, 0, snail_amount - 2);
        //auto stop = high_resolution_clock::now();
        //auto duration = duration_cast<microseconds>(stop - start);
        //cout << "âðåìÿ âûïîëíåíèÿ " << duration.count();
        if (paths[0] == paths[1])
            this->confusion = true;
    }
};

double pathlength(double x1, double y1, double x2, double y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main()
{
    setlocale(0, "RUS");

    cout << "Ââåäèòå êîë-âî óëèòîê: ";
    cin >> snail_amount;
    if(snail_amount == 1){
        cout << "Улитка в замешательстве: ";
    }
    else{
    Snail* snails = new Snail[snail_amount];

    for (int i = 0; i < snail_amount; i++){
        cout << "óëèòêà " << i << ":  ";
        cin >> snails[i].x;
        cin >> snails[i].y;
        cout << endl;
    }
    double shortest_path = 141422;
    double temp = 0;
    int ways = 0;
    for (int i = 0; i < snail_amount; i++){
        for (int j = 0; j < snail_amount; j++){
            if (i != j){
                temp = pathlength(snails[i].x, snails[i].y, snails[j].x, snails[j].y);
                snails[i].paths[ways] = temp;
                if (temp < shortest_path)
                    shortest_path = temp;
                ways++;
            }
        }
        snails[i].if_confusion();
        ways = 0;
    }

    int k = 0;
    for (int i = 0; i < snail_amount; i++){
        if (snails[i].confusion){
            cout << "Óëèòêà " << i << " â çàìåøàòåëüñòâå\n";
            k++;
        }
    }
    if (k != snail_amount) {
        cout << "êðàò÷àéøåå âðåìÿ = " << shortest_path / 2 << endl << endl;
    }
    }
    system("pause");
    return 0;
}
