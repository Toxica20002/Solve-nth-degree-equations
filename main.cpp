#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <windows.h>
#include <conio.h>

#define openr(a) freopen(a, "r", stdin)
#define openw(a) freopen(a, "w", stdout)
#define reset(a) memset(a, 0, sizeof(a))
#define read(v) for(auto &x: v) cin >> x;
#define all(a) a.begin(),a.end()
#define fi first
#define se second
#define ordered_set tree<ii, null_type,less<ii>, rb_tree_tag,tree_order_statistics_node_update>
#define FASTIO ios::sync_with_stdio(0), cin.tie(0);

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef signed long long int sll;
typedef unsigned long long int ull;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef pair<sll, sll> sii;
typedef tuple<sll, sll, sll> siii;

const sll maxn= 1e6;
const sll inf= 1e18;
const sll MOD= inf + 7;

// knight moves
int xkt[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int ykt[] = {-1, 1, -2, 2, -2, 2, -1, 1};

// king moves
int xkg[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int ykg[] = {-1, 0, 1, -1, 1, -1, 0, 1};

// 4 directions
int dx[]= {0, 0, -1, 1};
int dy[]= {1, -1, 0, 0};
char dc[] = {'R', 'L', 'U', 'D'};

string superscript[]= {"⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹"};
int n;
vector<string> v_superscript;
vector<long double> v_parameter;

string convert_superscript(int n){
    string ans= "";
    if(n== 0) ans+= superscript[0];
    while(n){
        ans= superscript[n%10]+ans;
        n/=10;
    }
    return 'x'+ans;
}

long double f(vector<long double> &para, long double x, int n){
    long double ans= 0;
    long double product= 1;
    for(int i= 0; i<= n; i++){
        ans+= para[i]*product;
        product*= x;
    }
    return ans;
}

long double max_f(vector<long double> &para, int n, long double left, long double right) {

	int N_ITER = 100;
    long double u, v;
	for (int i = 0; i < N_ITER; i++) {
		long double x1 = left + (right - left) / 3.0;
		long double x2 = right - (right - left) / 3.0;
        u= f(para, x1, n); v= f(para, x2, n);
		if(u== 0) return x1;

		if(v== 0) return x2;

		if(u > v){
            if(v > 0) left= x2;
            else if(u < 0) right= x1;
            else{
                left= x1;
                right= x2;
            }
		}
		else{
            if(u > 0) right= x1;
            else if(v < 0) left= x2;
            else{
                left= x1;
                right= x2;
            }
		}
	}
    long double res= min(f(para, left, n), f(para, right, n)), x;
    if(res== f(para, left, n)) x= left;
    else x= right;
    return x;
}

set<long double> process(vector<long double> &para, int n){
    set<long double> x;
    if(n== 1){
        x.insert(-inf);
        x.insert(inf);
        if(para[1] != 0) x.insert(-para[0]/para[1]);
        return x;
    }

    vector<long double> d_para;
    for(int i= 1; i<= n; i++) d_para.push_back(i*para[i]);
    set<long double> extremums= process(d_para, n-1);

    auto it= extremums.begin();
    x.insert(*it);
    it++;
    while(it!= extremums.end()){
        long double left= *prev(it)+0.0001;
        long double right= *it;
        if(f(para, left, n)*f(para, right, n) > 0) {
            it++;
            continue;
        }
        else x.insert(max_f(para, n, left, right));
        it++;
    }
    x.insert(inf);
    return x;
}

int main(){
    SetConsoleOutputCP(65001);
    //openr("input.txt");
    //openw("output.txt");
    //FASTIO

    /* Input */
    cout << "Enter n: ";
    cin >> n;
    cout << "Enter parameters: \n";
    for(int i= n; i>= 0; i--) v_superscript.push_back(convert_superscript(i));
    for(auto &i: v_superscript){
        cout << "?" << i << "\t: ";
        sll x;
        cin >> x;
        v_parameter.push_back(x);
    }

    reverse(all(v_parameter));
    reverse(all(v_superscript));

    /* ANSWER */

    cout << "\n";
    set<long double> x= process(v_parameter, n);
    if((int)x.size()== 2) {
        cout << "X does not exist !";
    }
    else{
        vector<long double> vx;
        for(auto &i: x) vx.push_back(i);
        for(int i= 1; i< (int)vx.size()-1; i++){
            cout << fixed << setprecision(6) << "x\t=\t" << vx[i] << "\n";
        }
    }
    getch();
    return 0;
}
