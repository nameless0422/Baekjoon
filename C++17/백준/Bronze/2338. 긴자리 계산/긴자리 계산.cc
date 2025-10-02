#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    int sign; // 1: 양수, -1: 음수, 0: 0
    vector<int> d; // 각 자리수를 0~9, 역순 저장

    BigInt(): sign(0) {}
    BigInt(string s) { fromString(s); }

    void fromString(const string& s) {
        sign = 1;
        d.clear();
        int i = 0;
        if (s[0] == '-') { sign = -1; i = 1; }
        else if (s[0] == '+') { i = 1; }
        while (i < (int)s.size() && s[i] == '0') i++;
        for (int j = (int)s.size()-1; j >= i; --j) d.push_back(s[j]-'0');
        if (d.empty()) sign = 0;
    }

    string toString() const {
        if (sign == 0) return "0";
        string s = (sign == -1 ? "-" : "");
        for (int i = (int)d.size()-1; i >= 0; --i) s.push_back('0'+d[i]);
        return s;
    }

    void trim() {
        while (!d.empty() && d.back()==0) d.pop_back();
        if (d.empty()) sign = 0;
    }

    // 절댓값 비교
    static int cmpAbs(const BigInt& a, const BigInt& b) {
        if (a.d.size() != b.d.size())
            return (a.d.size() < b.d.size()) ? -1 : 1;
        for (int i = (int)a.d.size()-1; i >= 0; --i) {
            if (a.d[i] != b.d[i])
                return (a.d[i] < b.d[i]) ? -1 : 1;
        }
        return 0;
    }

    // 절댓값 덧셈
    static BigInt addAbs(const BigInt& a, const BigInt& b) {
        BigInt c; c.sign = 1;
        int n = max(a.d.size(), b.d.size());
        c.d.resize(n);
        int carry = 0;
        for (int i = 0; i < n || carry; ++i) {
            if (i == (int)c.d.size()) c.d.push_back(0);
            int sum = carry;
            if (i < (int)a.d.size()) sum += a.d[i];
            if (i < (int)b.d.size()) sum += b.d[i];
            c.d[i] = sum % 10;
            carry = sum / 10;
        }
        c.trim();
        return c;
    }

    // 절댓값 뺄셈 (|a| >= |b|)
    static BigInt subAbs(const BigInt& a, const BigInt& b) {
        BigInt c; c.sign = 1;
        c.d = a.d;
        int borrow = 0;
        for (int i = 0; i < (int)c.d.size(); ++i) {
            int sub = c.d[i] - borrow - (i < (int)b.d.size()? b.d[i]:0);
            if (sub < 0) { sub += 10; borrow=1; } else borrow=0;
            c.d[i] = sub;
        }
        c.trim();
        return c;
    }

    // 덧셈
    static BigInt add(const BigInt& a, const BigInt& b) {
        if (a.sign==0) return b;
        if (b.sign==0) return a;
        BigInt res;
        if (a.sign==b.sign) {
            res = addAbs(a,b);
            res.sign = a.sign;
        } else {
            int cmp = cmpAbs(a,b);
            if (cmp==0) return BigInt("0");
            if (cmp>0) { res=subAbs(a,b); res.sign=a.sign; }
            else { res=subAbs(b,a); res.sign=b.sign; }
        }
        if (res.d.empty()) res.sign=0;
        return res;
    }

    // 뺄셈
    static BigInt sub(const BigInt& a, const BigInt& b) {
        BigInt tmp=b; tmp.sign*=-1;
        return add(a,tmp);
    }

    // ----- Karatsuba 곱셈 -----
    static vector<long long> karatsuba(const vector<long long>& a, const vector<long long>& b) {
        int n = 1;
        while (n < (int)max(a.size(), b.size())) n <<= 1;
        n <<= 1;
        vector<long long> A(n), B(n);
        for (size_t i=0;i<a.size();i++) A[i]=a[i];
        for (size_t i=0;i<b.size();i++) B[i]=b[i];

        function<vector<long long>(const vector<long long>&, const vector<long long>&, int)> kar;
        kar = [&](const vector<long long>& a, const vector<long long>& b, int n)->vector<long long>{
            vector<long long> res(n*2);
            if (n<=32) {
                for (int i=0;i<n;i++) for (int j=0;j<n;j++) res[i+j]+=a[i]*b[j];
                return res;
            }
            int k=n/2;
            vector<long long> a1(a.begin(), a.begin()+k), a2(a.begin()+k, a.begin()+n);
            vector<long long> b1(b.begin(), b.begin()+k), b2(b.begin()+k, b.begin()+n);

            auto a1b1=kar(a1,b1,k);
            auto a2b2=kar(a2,b2,k);

            for (int i=0;i<k;i++) a2[i]+=a1[i];
            for (int i=0;i<k;i++) b2[i]+=b1[i];

            auto r=kar(a2,b2,k);
            for (int i=0;i<(int)a1b1.size();i++) r[i]-=a1b1[i];
            for (int i=0;i<(int)a2b2.size();i++) r[i]-=a2b2[i];

            for (int i=0;i<(int)a1b1.size();i++) res[i]+=a1b1[i];
            for (int i=0;i<(int)a2b2.size();i++) res[i+n]+=a2b2[i];
            for (int i=0;i<(int)r.size();i++) res[i+k]+=r[i];
            return res;
        };

        auto r=kar(A,B,n);
        return r;
    }

    // 곱셈
    static BigInt mul(const BigInt& A, const BigInt& B) {
        if (A.sign==0 || B.sign==0) return BigInt("0");
        vector<long long> a(A.d.begin(), A.d.end());
        vector<long long> b(B.d.begin(), B.d.end());
        auto r=karatsuba(a,b);

        BigInt C;
        C.sign = A.sign * B.sign;
        long long carry=0;
        for (size_t i=0;i<r.size();i++) {
            long long cur=r[i]+carry;
            C.d.push_back(int(cur%10));
            carry=cur/10;
        }
        while (carry) { C.d.push_back(int(carry%10)); carry/=10; }
        C.trim();
        return C;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string sa,sb; 
    cin>>sa>>sb;
    BigInt A(sa),B(sb);

    BigInt sum = BigInt::add(A,B);
    BigInt diff = BigInt::sub(A,B);
    BigInt prod = BigInt::mul(A,B);

    cout<<sum.toString()<<"\n";
    cout<<diff.toString()<<"\n";
    cout<<prod.toString()<<"\n";
    return 0;
}
