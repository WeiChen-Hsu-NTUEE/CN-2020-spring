//PREPEND BEGIN
#include <iostream>
#include <string>
using namespace std;
//PREPEND END
//TEMPLATE BEGIN
class Polynomial{
  public:
  //add any member function as you like.
  void init(int coefficient[], int n){
    class_n = n;
    ptr = new int [n];
    for (int i=0;i<n;i++)
    {
        ptr[i] = coefficient[i];
    }
  }
  void print(){
    for(int i=class_n-1;i>1;i--)
    {
        if(ptr[i]>0) cout<<"+"<<ptr[i]<<"x^"<<i;
        if(ptr[i]<0) cout<<ptr[i]<<"x^"<<i;

    }
    if(ptr[1]>0) cout<<"+"<<ptr[1]<<"x";
    if(ptr[1]<0) cout<<ptr[1]<<"x";
    if(ptr[0]>0) cout<<"+"<<ptr[0];
    if(ptr[0]<0) cout<<ptr[0];
    cout<<endl;
  }

  Polynomial add(Polynomial *poly2){
    Polynomial pptr;

    if(class_n > poly2->class_n)
    {
      pptr.class_n = class_n;
      pptr.ptr = new int[class_n];

      for(int i=0;i < poly2->class_n; i++){
        pptr.ptr[i] = ptr[i] + poly2->ptr[i];
      }

      for(int i=poly2->class_n; i<class_n; i++){
        pptr.ptr[i] = ptr[i];
      }
    }
    if(class_n < poly2->class_n)
    {
      pptr.class_n = poly2->class_n;
      pptr.ptr = new int[poly2->class_n];

      for(int i=0; i<class_n; i++){
        pptr.ptr[i] = ptr[i] + poly2->ptr[i];
      }

      for(int i=class_n; i<poly2->class_n; i++){
        pptr.ptr[i] = poly2->ptr[i];
      }
    }
    if(class_n == poly2->class_n)
    {
      pptr.class_n = class_n;
      pptr.ptr = new int[class_n];

      for(int i=0; i<class_n; i++){
        pptr.ptr[i] = ptr[i] + poly2->ptr[i];
      }
    }

    return pptr;
  }

  Polynomial multiply(Polynomial *poly2){
     Polynomial pptr;
     pptr.class_n = class_n + poly2->class_n - 1;
     pptr.ptr = new int [pptr.class_n];
     pptr.ptr[pptr.class_n] = {0}; 

     for(int i=0; i<class_n; i++)
     {
       for(int j=0; j<poly2->class_n; j++)
       {
         pptr.ptr[i+j] += ptr[i] * poly2->ptr[j];
       }
     }

     return pptr;
  }

private:
  int *ptr; int class_n;

};
//TEMPLATE END
//APPEND BEGIN
void test() {
    int n, m;
    int cmds, cmd, pid, pid2;
    int v[4096];
    cin >> n;
    Polynomial *p = new Polynomial[n];
    for (int i = 0; i < n; i++) {
        cin >> m;
        for (int j = 0; j < m; j++)
            cin >> v[j];
        p[i].init(v, m);
    }
    cin >> cmds;
    for (int i = 0; i < cmds; i++) {
        cin >> cmd >> pid;
        if (cmd == 1) {
            p[pid].print();
        } else if (cmd == 2) {
            cin >> pid2;
            Polynomial ret = p[pid].add(&p[pid2]);
            ret.print();
        } else if (cmd == 3) {
            cin >> pid2;
            Polynomial ret = p[pid].multiply(&p[pid2]);
            ret.print();
        }
    }
}
int main() {
    test();
    return 0;
}
//APPEND END
