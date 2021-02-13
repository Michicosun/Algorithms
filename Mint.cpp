class Mint{
private:
    int x;
    inline static int mod = 1e9 + 9;
    int fastPow(int x, int p) const {
        if (p == 0) return 1;
        else if (p % 2 == 0) {
            auto ans = fastPow(x, p / 2);
            return ans * ans % mod;
        } else {
            auto ans = fastPow(x, p - 1);
            return ans * x % mod;
        }
    }
public:
    Mint() : x(0) {}
    Mint(int x) : x(x % mod) {}
    Mint(const Mint& other) {
        this->x = other.x;
        this->mod = other.mod;
    }
    Mint(Mint&& other) {
        swap(this->x, other.x);
        swap(this->mod, other.mod);
    }
    int getX() const {
        return x;
    }
    int getM() const {
        return mod;
    }
    int rev() const {
        return fastPow(x, mod - 2);
    }
    Mint operator= (const Mint& other) {
        this->x = other.x;
        return *this;
    }
    Mint operator= (Mint&& other) {
        swap(x, other.x);
        return *this;
    }
    Mint operator+ (const Mint& other) const {
        int nx = (x + other.x + mod) % mod;
        return Mint(nx);
    }
    Mint operator- (const Mint& other) const {
        int nx = (x - other.x + mod) % mod;
        return Mint(nx);
    }
    Mint operator* (const Mint& other) const {
        int nx = (x * other.x) % mod;
        return Mint(nx);
    }
    Mint operator/ (const Mint& other) const {
        int nx = (x * other.rev()) % mod;
        return Mint(nx);
    }
    void operator+= (const Mint& other) {
        *this = *this + other;
    }
    void operator-= (const Mint& other) {
        *this = *this - other;
    }
    void operator*= (const Mint& other) {
        *this = *this * other;
    }
    void operator/= (const Mint& other) {
        *this = *this / other;
    }
    bool operator== (const Mint& other) {
        return x == other.x;
    }
    bool operator!= (const Mint& other) {
        return x != other.x;
    }
    friend istream& operator>> (istream& in, Mint& a) {
        int nx; in >> nx;
        a = nx;
        return in;
    }
};

ostream& operator<< (ostream& out, const Mint& a) {
    return out << a.getX();
}

Mint operator+ (int A, const Mint& B) {
    int nx = (A + B.getX() + B.getM()) % B.getM();
    return Mint(nx);
}
Mint operator- (int A, const Mint& B) {
    int nx = (A - B.getX() + B.getM()) % B.getM();
    return Mint(nx);
}
Mint operator* (int A, const Mint& B) {
    int nx = (A * B.getX()) % B.getM();
    return Mint(nx);
}
Mint operator/ (int A, const Mint& B) {
    int nx = (A * B.rev()) % B.getM();
    return Mint(nx);
}
