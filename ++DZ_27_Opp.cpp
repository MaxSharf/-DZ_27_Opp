#include <iostream>
using namespace std;

template<class t>
class unique_ptr_1 {
    t* ptr;
public:
    unique_ptr_1() : ptr(nullptr) {}
    unique_ptr_1(const unique_ptr_1& sp) = delete;
    unique_ptr_1(t* p) {
        ptr = p;
    }
    ~unique_ptr_1() {
        delete ptr;
    }

    t& operator* () {
        return *ptr;
    }

    t* get() {
        return ptr;
    }
    void reset() {
        delete ptr;
        ptr = nullptr;
    }
    void realese() {
        ptr = nullptr;
    }
    void swap(unique_ptr_1<t>& up) {
        std::swap(ptr, up.ptr);
    }
};

template<class t>
class shared_ptr_1 {
    t* ptr = nullptr;
    size_t* count = nullptr;
public:
    shared_ptr_1() : ptr(nullptr), count(nullptr) {}
    shared_ptr_1(const shared_ptr_1& sp) {
        ptr = sp.ptr;
        count = sp.count;
        *count++;
    };
    shared_ptr_1(t* p) {
        ptr = p;
        count = new size_t(1);
    }

    ~shared_ptr_1() {
        if ((*count) > 0) {
            (*count)--;
            return;
        }
        delete ptr;
        delete count;
    }

    t& operator* () {
        return *ptr;
    }
    t* operator->() {
        return ptr;
    }
    void operator == (shared_ptr_1<t>& up) {
        up.ptr = ptr;
        *(count)++;
    }

    t* get() {
        return ptr;
    }
    void reset() {
        delete ptr;
        ptr = nullptr;
    }
    void swap(shared_ptr_1<t>& up) {
        std::swap(ptr, up.ptr);
    }
    size_t use_count() {
        return *count;
    }
};


int main()
{

    shared_ptr_1<int> p3(new int(5));
    shared_ptr_1<int> p4;
    cout << p3.use_count() << endl;
    p4 = p3;
    cout << p3.use_count() << endl;

    shared_ptr_1<int> x;
    x = p4;
    cout << p3.use_count() << endl;

    return 0;
}