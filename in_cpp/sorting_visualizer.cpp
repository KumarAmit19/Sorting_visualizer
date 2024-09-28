#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <Windows.h>

using namespace std;

const int LIST_SIZE = 20;
const int MIN_VALUE = 1;
const int MAX_VALUE = 100;
const int WIDTH = 80;
const int HEIGHT = 20;

struct DrawInfo {
    int width;
    int height;
    vector<int> lst;
    int min_val;
    int max_val;
    int block_width;
    int block_height;
    int start_x;
    int padding_sides;
    int padding_top;

    DrawInfo(int width, int height, vector<int> lst) : width(width), height(height), lst(lst) {
        min_val = *min_element(lst.begin(), lst.end());
        max_val = *max_element(lst.begin(), lst.end());
        block_width = (width - padding_sides) / lst.size();
        block_height = (height - padding_top) / (max_val - min_val);
        start_x = padding_sides / 2;
    }
};

void draw(DrawInfo& draw_info, string algo_name, bool ascending) {
    // Clear screen
    system("cls");

    // Draw title
    cout << algo_name << (ascending ? " - Ascending" : " - Descending") << endl;

    // Draw controls
    cout << "R - Reset | SPACE - Start Sorting | A - Ascending | D - Descending" << endl;
    cout << "I - Insertion Sort | B - Bubble Sort | Q - Quick Sort | M - Merge Sort | S - Selection Sort" << endl;

    // Draw list
    for (int i = 0; i < draw_info.lst.size(); i++) {
        int val = draw_info.lst[i];
        int x = draw_info.start_x + i * draw_info.block_width;
        int y = draw_info.height - (val - draw_info.min_val) * draw_info.block_height;
        cout << "(" << x << ", " << y << ")" << endl;
    }

    // Update screen
    cout << flush;
}

vector<int> generate_starting_list(int n, int min_val, int max_val) {
    vector<int> lst;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(min_val, max_val);
    for (int i = 0; i < n; i++) {
        lst.push_back(dist(mt));
    }
    return lst;
}

vector<int> bubble_sort(DrawInfo& draw_info, bool ascending) {
    vector<int> lst = draw_info.lst;
    for (int i = 0; i < lst.size() - 1; i++) {
        for (int j = 0; j < lst.size() - 1 - i; j++) {
            if ((lst[j] > lst[j + 1] && ascending) || (lst[j] < lst[j + 1] && !ascending)) {
                swap(lst[j], lst[j + 1]);
                draw_info.lst = lst;
                draw(draw_info, "Bubble Sort", ascending);
                this_thread::sleep_for(chrono::milliseconds(100));
            }
        }
    }
    return lst;
}

vector<int> insertion_sort(DrawInfo& draw_info, bool ascending) {
    vector<int> lst = draw_info.lst;
    for (int i = 1; i < lst.size(); i++) {
        int current = lst[i];
        int j = i - 1;
        while (j >= 0 && ((lst[j] > current && ascending) || (lst[j] < current && !ascending))) {
            lst[j + 1] = lst[j];
            j--;
        }
        lst[j + 1] = current;
        draw_info.lst = lst;
        draw(draw_info, "Insertion Sort", ascending);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    return lst;
}

vector<int> selection_sort(DrawInfo& draw_info, bool ascending) {
    vector<int> lst = draw_info.lst;
    for (int i = 0; i < lst.size(); i++) {
        int min_idx = i;
        for (int j = i + 1; j < lst.size(); j++) {
            if ((lst[j] < lst[min_idx] && ascending) || (lst[j] > lst[min_idx] && !ascending)) {
                min_idx = j;
            }
        }
        swap(lst[i], lst[min_idx]);
        draw_info.lst = lst;
        draw(draw_info, "Selection Sort", ascending);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    return lst;
}

int partition(vector<int>& lst, int low, int high, bool ascending) {
    int pivot = lst[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if ((lst[j] < pivot && ascending) || (lst[j] > pivot && !ascending)) {
            i++;
            swap(lst[i], lst[j]);
        }
    }
    swap(lst[i + 1], lst[high]);
    return i + 1;
}

void quicksort_recursive(vector<int>& lst, int low, int high, bool ascending, DrawInfo& draw_info) {
    if (low < high) {
        int pivot = partition(lst, low, high, ascending);
        draw_info.lst = lst;
        draw(draw_info, "Quick Sort", ascending);
        this_thread::sleep_for(chrono::milliseconds(100));
        quicksort_recursive(lst, low, pivot - 1, ascending, draw_info);
        quicksort_recursive(lst, pivot + 1, high, ascending, draw_info);
    }
}

vector<int> quick_sort(DrawInfo& draw_info, bool ascending) {
    vector<int> lst = draw_info.lst;
    quicksort_recursive(lst, 0, lst.size() - 1, ascending, draw_info);
    return lst;
}
vector<int> merge_sort(vector<int>& lst, bool ascending) {
    static vector<int> merge(vector<int>& left, vector<int>& right, bool ascending) {
        // implementation of merge function
    }

    if (lst.size() <= 1) {
        return lst;
    }
    int mid = lst.size() / 2;
    vector<int> left(lst.begin(), lst.begin() + mid);
    vector<int> right(lst.begin() + mid, lst.end());
    left = merge_sort(left, ascending);
    right = merge_sort(right, ascending);
    return merge(left, right, ascending);
}

int main() {
    vector<int> lst = generate_starting_list(LIST_SIZE, MIN_VALUE, MAX_VALUE);
    DrawInfo draw_info(WIDTH, HEIGHT, lst);
    bool ascending = true;
    bool running = true;
    while (running) {
        draw(draw_info, "Sorting Visualizer", ascending);
        char input;
        cin >> input;
        switch (input) {
            case 'r':
                lst = generate_starting_list(LIST_SIZE, MIN_VALUE, MAX_VALUE);
                draw_info.lst = lst;
                break;
            case ' ':
                // Start sorting
                if (ascending) {
                    // bubble_sort(draw_info, ascending);
                    // insertion_sort(draw_info, ascending);
                    // selection_sort(draw_info, ascending);
                    quick_sort(draw_info, ascending);
                    // lst = merge_sort(draw_info.lst, ascending);
                } else {
                    // bubble_sort(draw_info, ascending);
                    // insertion_sort(draw_info, ascending);
                    // selection_sort(draw_info, ascending);
                    quick_sort(draw_info, ascending);
                    // lst = merge_sort(draw_info.lst, ascending);
                }
                break;
            case 'a':
                ascending = true;
                break;
            case 'd':
                ascending = false;
                break;
            case 'i':
                insertion_sort(draw_info, ascending);
                break;
            case 'b':
                bubble_sort(draw_info, ascending);
                break;
            case 'q':
                quick_sort(draw_info, ascending);
                break;
            case 'm':
                lst = merge_sort(draw_info.lst, ascending);
                draw_info.lst = lst;
                break;
            case 's':
                selection_sort(draw_info, ascending);
                break;
            default:
                running = false;
                break;
        }
    }
    return 0;
}