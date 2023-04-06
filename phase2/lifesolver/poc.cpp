struct Foo {
    int *bar;
    Foo() { bar = new int[1]; }
    ~Foo() { delete[] bar; }
};

int main() {
    Foo f = Foo();
    f = Foo();
}