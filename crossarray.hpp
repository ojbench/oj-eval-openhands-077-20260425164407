#ifndef SJTU_CROSSARRAY_HPP
#define SJTU_CROSSARRAY_HPP

namespace sjtu {
class CrossArray{
private:
    int **arrays;
    int *sizes;
    int capacity;
    int count; // number of inserted arrays (contiguous from 0)
public:
    explicit CrossArray(int lines)
        : arrays(nullptr), sizes(nullptr), capacity(lines), count(0) {
        if (capacity < 0) capacity = 0;
        arrays = new int*[capacity];
        sizes = new int[capacity];
        for (int i = 0; i < capacity; ++i) {
            arrays[i] = nullptr;
            sizes[i] = 0;
        }
    }

    CrossArray(const CrossArray & o)
        : arrays(nullptr), sizes(nullptr), capacity(o.capacity), count(o.count) {
        arrays = new int*[capacity];
        sizes = new int[capacity];
        for (int i = 0; i < capacity; ++i) {
            arrays[i] = nullptr;
            sizes[i] = 0;
        }
        for (int i = 0; i < count; ++i) {
            int sz = o.sizes[i];
            sizes[i] = sz;
            if (o.arrays[i] != nullptr && sz > 0) {
                arrays[i] = new int[sz];
                for (int j = 0; j < sz; ++j) arrays[i][j] = o.arrays[i][j];
            } else {
                arrays[i] = nullptr;
            }
        }
        // remaining beyond count already set to nullptr and 0
    }

    CrossArray & WhichGreater(CrossArray & o){
        long long a = 0, b = 0;
        for (int i = 0; i < count; ++i) a += sizes[i];
        for (int i = 0; i < o.count; ++i) b += o.sizes[i];
        return (a >= b) ? *this : o;
    }

    bool IsSame(const CrossArray & o){
        return this == &o;
    }

    bool InsertArrays(const int * Input, int size){
        if (count >= capacity) return false;
        if (size <= 0) {
            arrays[count] = nullptr;
            sizes[count] = 0;
            ++count;
            return true;
        }
        int *p = new int[size];
        for (int i = 0; i < size; ++i) p[i] = Input[i];
        arrays[count] = p;
        sizes[count] = size;
        ++count;
        return true;
    }

    void AppendArrays(const int * Input,int Line,int size){
        if (size <= 0) return;
        int oldsz = sizes[Line];
        int newsz = oldsz + size;
        if (oldsz == 0) {
            int *p = new int[size];
            for (int i = 0; i < size; ++i) p[i] = Input[i];
            arrays[Line] = p;
            sizes[Line] = size;
            return;
        }
        int *np = new int[newsz];
        for (int i = 0; i < oldsz; ++i) np[i] = arrays[Line][i];
        for (int i = 0; i < size; ++i) np[oldsz + i] = Input[i];
        delete [] arrays[Line];
        arrays[Line] = np;
        sizes[Line] = newsz;
    }

    void DoubleCrossLength(){
        int newcap = capacity * 2;
        if (newcap <= 0) newcap = (capacity == 0 ? 1 : capacity); // ensure progress
        int **nar = new int*[newcap];
        int *nsz = new int[newcap];
        for (int i = 0; i < newcap; ++i) { nar[i] = nullptr; nsz[i] = 0; }
        for (int i = 0; i < capacity; ++i) {
            nar[i] = arrays[i];
            nsz[i] = sizes[i];
        }
        delete [] arrays;
        delete [] sizes;
        arrays = nar;
        sizes = nsz;
        capacity = newcap;
    }

    const int * AtArray(int i){
        return arrays[i];
    }

    int & At(int i , int j){
        return arrays[i][j];
    }

    ~CrossArray(){
        if (arrays) {
            for (int i = 0; i < capacity; ++i) {
                if (arrays[i] != nullptr) {
                    delete [] arrays[i];
                    arrays[i] = nullptr;
                }
            }
            delete [] arrays;
            arrays = nullptr;
        }
        if (sizes) { delete [] sizes; sizes = nullptr; }
        capacity = 0;
        count = 0;
    }
};
}

#endif // SJTU_CROSSARRAY_HPP
