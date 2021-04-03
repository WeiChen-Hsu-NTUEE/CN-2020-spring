//PREPEND BEGIN
#include <iostream>
//PREPEND BEGIN
#include <iostream>
#include <iomanip>
#include <string>

// uncomment line below if you use dev-c++
// 若使用 dev-c++ 請取消註解下面這行
//#include <stdint.h>

using namespace std;

// range of uint64_t is 0 ~ 18,446,744,073,709,551,615
// define 10^19-1 as the max value in single element
// which means we can have 19 '9's
// the U added at the end means this is an unsigned number
const uint64_t CARRY = 10000000000000000000U;
const uint64_t CARRY_LENGTH = 19U;

// 本次 HugeInteger 使用的基數是 uint64_t
// 他的儲存範圍是 0 ~ 18,446,744,073,709,551,615
// 所以取 10^19-1 (也就是最大是19個9) 當作"一格"的最大值
// 變數後面加一個大 U 是指這是無號數的意思。

class HugeInteger {
public:
    HugeInteger();                     // default constructor
    HugeInteger(const string& s);      // constructor with value
    HugeInteger(const HugeInteger& n); // copy constructor
    ~HugeInteger();                    // destructor

    void resize(); // double the length of data array (請參考下方說明)

    //HugeInteger addition(HugeInteger& n);    // add
    //HugeInteger subtraction(HugeInteger& n); // minus

    bool isEqualTo(HugeInteger& n);     // ==
    bool isNotEqualTo(HugeInteger& n);  // !=
    bool isGreaterThan(HugeInteger& n); // >
    bool isLessThan(HugeInteger& n);    // <

    void input(const string& s); // input a number
    void print();                // display the number

private:
    bool            _sign; // false for positive ; true for negative (正負號)
    int           _length; // length of data array (總共由幾個 uint64_t 串接起來)
    uint64_t*        data; // integer array holding the huge integer (儲存在陣列)
    static int max_length; // max length of data array in exist HugeInteger(s)
    // 以上這個變數的意義是，所有的 HugeInteger 中，最大的 _length 之值。
    // 因為要將兩個 HugeInteger 做運算，需要統一 _length，所以我們統一在做運算前，
    // 將 _length 更新到最長
};

//PREPEND END

//TEMPLATE BEGIN

//TODO 1
int HugeInteger::max_length=1;
HugeInteger::HugeInteger(){
    // TODO 2
    _length=max_length;
    data = new uint64_t[_length];
    for(int i=0;i<_length;i++) data[i]=0;
    _sign=false;
}

HugeInteger::HugeInteger(const string& s){
    _length = max_length;
    data = new uint64_t[_length];
    input(s);
}

HugeInteger::HugeInteger(const HugeInteger& n){
    // TODO 3
    _sign=n._sign;
    _length=n._length;
    data=new uint64_t[_length];
    for(int i=0;i<_length;i++) data[i]=n.data[i];
}

HugeInteger::~HugeInteger(){
    // TODO 4
    delete []data;
}//maybe not necessary

void HugeInteger::resize(){
    if(max_length == _length) return;
    uint64_t* temp = data;
    data = new uint64_t[max_length];
    for(int i = 0 ; i < max_length-_length; ++i)
        data[i] = 0;
    for(int i = max_length-_length ; i < max_length; ++i)
        data[i] = temp[i+_length-max_length];
    delete [] temp;
    _length = max_length;
    return;
}

bool HugeInteger::isEqualTo(HugeInteger& n){
    this->resize(); n.resize();
    // TODO 5
    for(int i=0;i<_length;i++) if(data[i]!=n.data[i]) return false;
    if(_sign!=n._sign) return false;
    return true;
}
bool HugeInteger::isNotEqualTo(HugeInteger& n){
    this->resize(); n.resize();
    // TODO 6
    for(int i=0;i<_length;i++) if(data[i]!=n.data[i]) return true;
    if(_sign!=n._sign) return true;
    return false;
}
bool HugeInteger::isGreaterThan(HugeInteger& n){
    this->resize(); n.resize();
    // TODO 7
    if(_sign==false&&n._sign==true) return true;
    if(_sign==true&&n._sign==false) return false;
    for(int i=0;i<_length;i++){
            if(data[i]>n.data[i]){
        if(_sign) return false;
        else return true;
    }
        if(data[i]<n.data[i]){
            if(_sign) return true;
            else return false;
        }
    }
    return false;
}
bool HugeInteger::isLessThan(HugeInteger& n){
    this->resize(); n.resize();
    // TODO 8
    if(_sign==false&&n._sign==true) return false;
    if(_sign==true&&n._sign==false) return true;
    for(int i=0;i<_length;i++){
            if(data[i]>n.data[i]){
        if(_sign) return true;
        else return false;
    }
        if(data[i]<n.data[i]){
            if(_sign) return false;
            else return true;
        }
    }
    return false;
}

void HugeInteger::input(const string& s){
    // TODO 9
    while( s.length() > max_length*CARRY_LENGTH )
        max_length <<= 1;
    _length = max_length;
    delete [] data;
    data = new uint64_t[_length];
    for(int i = 0 ; i < _length; ++i)
        data[i] = 0;
    if(s.length() == 0) return;
    _sign = (s[0] == '-');
    for(int i = (_sign?1:0) ; i < s.length() ; ++i){
        data[(CARRY_LENGTH*_length+i-s.length())/CARRY_LENGTH] *= 10;
        data[(CARRY_LENGTH*_length+i-s.length())/CARRY_LENGTH] += (uint64_t)((char)s[i]-'0');
    }
    return;
}
void HugeInteger::print(){
    // TODO 10
    // hint: 會用到 setw(), setfill('0'), 並且請十分注意cout之控制
    //negative
    for(int i=0;i<_length;i++){
        if(data[i]!=0) break;
        if(i+1==_length){
            cout<<"0";
            return;
        }
    }
    bool out=false;
    if(_sign) cout<<"-";
    for(int i=0;i<_length;i++){
        if(out) cout<<setfill('0')<<setw(CARRY_LENGTH)<<data[i];
        else if(data[i]!=0){
            cout<<data[i];
            out=true;
        }
    }
    return;
}

//APPEND BEGIN
int main(){
    string s1, s2;
    cin >> s1 >> s2;
    HugeInteger n1;
    n1.input(s1);
    HugeInteger n2(s2);
    HugeInteger n3(n1);
    HugeInteger n4;
    n4.input(s2);

    n1.print();
    cout << endl;
    n2.print();
    cout << endl;
    n3.print();
    cout << endl;
    n4.print();
    cout << endl;

    cout << (n3.isEqualTo(n1)?"Yes":"No") << endl;
    cout << (n4.isEqualTo(n2)?"Yes":"No") << endl;
    n4.input(s1);
    n4.print();
    cout << endl;

    cout << (n1.isGreaterThan(n2)?"Yes":"No") << endl;
    cout << (n1.isEqualTo(n2)?"Yes":"No") << endl;
    cout << (n1.isLessThan(n2)?"Yes":"No") << endl;
    return 0;
}
//APPEND END