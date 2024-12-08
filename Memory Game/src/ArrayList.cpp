
template <typename T> class ArrayList {
    private:
        T* array;
        int size;
        int capacity;
    public:
        ArrayList();
        ~ArrayList();
        void add(T element);
        T get(int index);
        int getSize();
        void clear();
        bool equals(ArrayList<T> list);
};

template <typename T> ArrayList<T>::ArrayList() {
    size = 0;
    capacity = 10;
    array = new T[capacity];
}

template <typename T> ArrayList<T>::~ArrayList() {
    delete[] array;
}

template <typename T> void ArrayList<T>::add(T element) {
    if (size == capacity) {
        capacity *= 2;
        T* newArray = new T[capacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
    array[size] = element;
    size++;
}

template <typename T> T ArrayList<T>::get(int index) {
    return array[index];
}

template <typename T> int ArrayList<T>::getSize() {
    return size;
}

template <typename T> void ArrayList<T>::clear() {
    delete[] array;
    size = 0;
    capacity = 10;
    array = new T[capacity];
}

template <typename T> bool ArrayList<T>::equals(ArrayList<T> list) {
    if (size != list.getSize()) {
        return false;
    }
    for (int i = 0; i < size; i++) {
        if (array[i] != list.get(i)) {
            return false;
        }
    }
    return true;
}