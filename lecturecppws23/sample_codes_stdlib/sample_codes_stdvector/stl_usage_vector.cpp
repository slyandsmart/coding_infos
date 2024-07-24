/*
 * https://en.cppreference.com/w/cpp/algorithm/
 *
 */


#include <vector>
#include <algorithm>
#include <random>

#include <iostream>
#include <iterator>
#include <string>

// this is just a operator overload to print out std::pair<int, double>
std::ostream& operator<<(std::ostream& os, const std::pair<int, double>& obj)
{
    os << "(" << std::get<0>(obj) << "," << std::get<1>(obj) << ")";
    return os;
}

// helper function to print std::vector<>
template <typename T>
void printVec(const std::vector<T>& vec, const std::string& name) {
    std::cout << name << " : ";
    for(const auto& elem : vec){
        std::cout << "\"" << elem << "\" ";
    }
    std::cout << std::endl;
}

int main() {

    std::vector<int> a {1,9,3,7,5,6,4,8,2};
    std::vector<std::pair<int, double>> b {{1,5.0}, {2,4.0}, {3, 3.1}, {3, 3.05}, {5, 1.0}};
    std::vector<std::string> c;

    printVec(a, "a");
    std::for_each(a.begin(), a.end(), [](int &n){ n--; });
    printVec(a, "a");
    std::sort(a.begin(), a.end());
    printVec(a, "a");
    std::cout << std::endl;

    auto res1 = std::count(a.begin(),a.end(), 3);
    std::cout << "# of 3 in vector: " << res1 << std::endl;

    auto res2 = std::count_if(a.begin(),a.end(), [](const int& n){ return (n % 2) == 0; });
    std::cout << "# of even elements in vector: " << res2 << std::endl;

    auto a_copy = a;

    std::cout << std::endl;

    // NOTE: std::stable_sort()
    printVec(b, "b");
    std::sort(b.begin(), b.end());
    printVec(b, "b");
    std::sort(b.begin(), b.end(), [](const auto&a, const auto& b){ return std::get<1>(a) < std::get<1>(b);});
    printVec(b, "b");

    std::cout << std::endl;

    auto result_1 = std::find(a.begin(), a.end(), 6);
    auto result_2 = std::find_if(a.begin(), a.end(), [](auto i){ return i > 7; });

    if(result_1 != a.end()) {
        std::cout << "There was a 6 found." << std::endl;
    }

    if(result_2 != a.end()) {
        std::cout << "There was a number greater than 7 and it is " << *result_2 << "." << std::endl;
    }

    bool all_smaller = std::all_of(a.begin(), a.end(), [](int i){ return i < 10; });

    if (all_smaller) {
        std::cout << "All numbers are smaller than 10." << std::endl;
    }

    bool is_there_a_seven = std::any_of(a.begin(), a.end(), [](int i){ return i == 7; });

    if (all_smaller) {
        std::cout << "At least one number is 7." << std::endl;
    }

    auto last_one = *a.begin();

    bool no_big_gap = std::all_of(a.begin()+1, a.end(), [&](int i){ 
        if (abs(i-last_one) < 2) {
            last_one = i;
            return true; 
        } else {
            last_one = i;
            return false; 
        }
    });

    if (no_big_gap) {
        std::cout << "All gaps between the elements are smaller than 2." << std::endl;
    } else {
        std::cout << "There are gaps between the elements which are smaller or equal than 2." << std::endl;
    }

    std::cout << std::endl;

    printVec(a, "a");
    a.erase(std::remove_if(a.begin(), a.end(), [](auto x){return x%2 == 0;}), a.end());
    printVec(a, "a");
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(a.begin(), a.end(), g);
    printVec(a, "a");

    a = a_copy;
    std::cout << std::endl;

    bool toggle = false;
    std::transform(a.begin(), a.end(), a.begin(), [&](auto elem){ toggle = !toggle; return toggle ? elem + 1 : elem; });
    printVec(a, "a");
    auto res = std::unique(a.begin(), a.end());
    printVec(a, "a");
    a.erase(res, a.end());
    printVec(a, "a");

    a = a_copy;
    std::cout << std::endl;

    auto it = std::partition(a.begin(), a.end(), [](int elem){return elem % 2 == 0;});

    std::copy(a.begin(), it, std::ostream_iterator<int>(std::cout, " "));
    std::cout << " * " " ";
    std::copy(it, a.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl << std::endl;

    auto res_min_elem = std::min_element(a.begin(), a.end());
    auto res_max_elem = std::max_element(a.begin(), a.end());

    std::cout << "min_elem : " << *res_min_elem << std::endl;
    std::cout << "max_elem : " << *res_max_elem << std::endl;

    auto [min, max] = std::minmax_element(a.begin(), a.end());

    std::cout << "min      : " << *min << std::endl;
    std::cout << "max      : " << *max << std::endl;

    return EXIT_SUCCESS;
}