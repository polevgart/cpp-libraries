#include <iostream>
#include <array>
#include <cassert>

template<typename T, int N>
class PascalLine {
public:
    using TElement = T;
private:
    typedef std::array<TElement, N> TLine;
    TLine line;
public:
    constexpr PascalLine(): line(TLine{}) {
        line[0] = 1;
    }
    
    constexpr PascalLine(const PascalLine& PrevPascalLine): line(TLine{}) {
        line[0] = 1;
        for (int i = 1; i < N; ++i) {
            line[i] = PrevPascalLine[i - 1] + PrevPascalLine[i];
        }
    }
    
    constexpr TElement operator[](int i) const {
        return line[i];
    }
    
};

template<typename T, int N>
void PrintPascalLine(const PascalLine<T, N>& pl) {
    for (int i = 0; i < N; ++i) {
        std::cout << pl[i] << ' ';
    }
    std::cout << std::endl;
}

template<typename T, int N>
class PascalTriangle {
private:
    using TLine = PascalLine<T, N>;
    using TElement = typename PascalLine<T, N>::TElement;
    std::array<TLine, N> pascalTriangle;
public:
    constexpr PascalTriangle(): pascalTriangle(std::array<TLine, N>{}) {
        for (int i = 1; i < N; ++i) {
            pascalTriangle[i] = TLine(pascalTriangle[i - 1]);
        }
    }
    
    constexpr const TLine& operator[](int i) const {
        return pascalTriangle[i];
    }
    
    constexpr TElement Get(int n, int k) const {
        return n < 0 || k < 0 ? 0 : pascalTriangle[n][k];
    }
};

template<typename T, int N>
void PrintPascalTriangle(const PascalTriangle<T, N>& pt) {
    for (int i = 0; i < N; ++i) {
        PrintPascalLine(pt[i]);
    }
}

template<int N>
void test1() {
    static_assert(N >= 3, "Wrong test case");
    constexpr auto line1 = PascalLine<int64_t, N>();
    static_assert(line1[0] == 1);
    static_assert(line1[1] == 0);
    static_assert(line1[2] == 0);
    for (int i = 3; i < N; ++i) {
        assert(line1[i] == 0);
    }
    
    constexpr auto line2 = PascalLine<int64_t, N>(line1);
    static_assert(line2[0] == 1);
    static_assert(line2[1] == 1);
    static_assert(line2[2] == 0);
    for (int i = 3; i < N; ++i) {
        assert(line1[i] == 0);
    }
    
    constexpr auto line3 = PascalLine<int64_t, N>(line2);
    static_assert(line3[0] == 1);
    static_assert(line3[1] == 2);
    static_assert(line3[2] == 1);
    for (int i = 3; i < N; ++i) {
        assert(line1[i] == 0);
    }
    
    if (N == 5) {
        PrintPascalLine(line1);
        PrintPascalLine(line2);
        PrintPascalLine(line3);
        std::cout << std::endl;
    }
}

int main() {
    test1<5>();
    test1<6>();
    test1<7>();
    
    constexpr auto C = PascalTriangle<int64_t, 10>();
    PrintPascalTriangle(C);
    
    constexpr auto c_3_5 = C.Get(5, 3);
    constexpr auto c_undef = C.Get(-1, 1);
    
    static_assert(c_3_5 == 10);
    static_assert(c_undef == 0);
    
    std::cout << std::endl << c_3_5 << ' ' << c_undef << std::endl;
    return 0;
}
