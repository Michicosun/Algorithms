#include<iostream>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<functional>
#include<regex>
#include<deque>
#include<unordered_map>
#include<string>
#include<vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::deque;
using std::pair;
using std::swap;
using std::string;
using std::unordered_map;
using std::reverse;
using std::min;

struct coord{
    long long int x, y;
    coord(long long int x = -1, long long int y = -1){
        this->x = x;
        this->y = y;
    }
};

struct Hash_2D{
    long long int p, q;
    long long int mod = 1275349729;
    vector<long long int> pows_p;
    vector<long long int> pows_q;
    vector<vector<long long int>> h;
    int n, m;
    Hash_2D(const vector<string> & board, int p, int q){
        this->p = p;
        this->q = q;
        n = (int)board.size();
        m = (int)board[0].size();
        pows_p.resize(n + 1, 1);
        pows_q.resize(m + 1, 1);
        h.resize(n + 1, vector<long long int>(m + 1, 0));
        for (int i = 1; i <= n; i++){
            pows_p[i] = (pows_p[i - 1] * p) % mod;
        }
        for (int i = 1; i <= m; i++){
            pows_q[i] = (pows_q[i - 1] * q) % mod;
        }
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= m; j++){
                long long int left = (h[i][j - 1] * q) % mod;
                long long int top = (h[i - 1][j] * p) % mod;
                long long int left_top = ((h[i - 1][j - 1] * p) % mod * q) % mod;
                h[i][j] = (left + top - left_top + board[i - 1][j - 1] + mod) % mod;
            }
        }
    }
    long long int get_sub_matrix(coord c1, coord c2){
        c1.x++; c1.y++; c2.x++; c2.y++;
        long long int p_p = pows_p[c2.x - c1.x + 1];
        long long int p_q = pows_q[c2.y - c1.y + 1];
        long long int left = (h[c2.x][c1.y - 1] * p_q) % mod;
        long long int top = (h[c1.x - 1][c2.y] * p_p) % mod;
        long long int left_top = ((h[c1.x - 1][c1.y - 1] * p_p) % mod * p_q) % mod;
        long long int now = h[c2.x][c2.y];
        return (now - left - top + left_top + 2 * mod) % mod;
    }
};

bool operator < (const coord & a, const coord & b){
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

struct triple{
    long long int k1, k2, x, y;
    triple(long long int k1 = -1, long long int k2 = -1, long long int x = -1, long long int y = -1){
        this->k1 = k1;
        this->k2 = k2;
        this->x = x;
        this->y = y;
    }
};

struct hash_table{
private:
    static const int mod = 997;
    vector<vector<vector<triple>>> t;
    
public:
    hash_table(){
        t.resize(mod, vector<vector<triple>>(mod));
    }
    void push(long long int arg1, long long int arg2, long long int x, long long int y){
        long long int ind1 = arg1 % mod;
        long long int ind2 = arg2 % mod;
        triple p(arg1, arg2, x, y);
        for (int i = 0; i < (long long int)t[ind1][ind2].size(); i++){
            if (t[ind1][ind2][i].k1 == p.k1 && t[ind1][ind2][i].k2 == p.k2 && t[ind1][ind2][i].x == p.x && t[ind1][ind2][i].y == p.y){
                return;
            }
        }
        t[ind1][ind2].push_back(p);
    }
    pair<long long int, long long int> get(long long int arg1, long long int arg2) const{
        long long int ind1 = arg1 % mod;
        long long int ind2 = arg2 % mod;
        for (int i = 0; i < (long long int)t[ind1][ind2].size(); i++){
            if (t[ind1][ind2][i].k1 == arg1 && t[ind1][ind2][i].k2 == arg2){
                return {t[ind1][ind2][i].x, t[ind1][ind2][i].y};
            }
        }
        return {-1, -1};
    }
};


pair<coord, coord> check(int mid, Hash_2D & h, Hash_2D & h2){
    hash_table mp;
    for (int i = 0; i <= h.n - mid; i++){
        for (int j = 0; j <= h.m - mid; j++){
            long long int ans_hash1 = h.get_sub_matrix({i, j}, {i + mid - 1, j + mid - 1});
            long long int ans_hash2 = h2.get_sub_matrix({i, j}, {i + mid - 1, j + mid - 1});
            if (mp.get(ans_hash1, ans_hash2).first == -1){
                mp.push(ans_hash1, ans_hash2, i, j);
            }else{
                auto p = mp.get(ans_hash1, ans_hash2);
                coord c1(p.first, p.second);
                coord c2(i, j);
                return {c1, c2};
            }
        }
    }
    return {{-1, -1}, {-1, -1}};
}

signed main(){
    std::ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<string> board(n);
    for (int i = 0; i < n; i++)cin >> board[i];
    Hash_2D h(board, 229, 313);
    Hash_2D h2(board, 401, 409);
    int l = 0, r = min(n, m) + 1;
    pair<coord, coord> it;
    while (r - l > 1){
        int mid = (l + r) / 2;
        it = check(mid, h, h2);
        if (it.first.x != -1){
            l = mid;
        }else{
            r = mid;
        }
    }
    cout << l << endl;
    if (l > 0){
        it = check(l, h, h2);
        cout << it.first.x + 1 << " " << it.first.y + 1 << endl;
        cout << it.second.x + 1 << " " << it.second.y + 1 << endl;
    }
    return 0;
}
