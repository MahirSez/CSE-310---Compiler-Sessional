

int f(int u) {


    int x[17] , ara[89] , z;

    ara[89] = u;

    return ara[89];

}

int g(int x) {

    return f(x);
}

int main(){

    int a , ara[58] , b;

    b = -56;
    b++;

    ara[8] = g(-b);

    ara[9] = ara[8];
 
    a = ara[9];

    println(a);
    
    
    b = !a;

    a++;
    println(a);
    println(b);

    return 0;

}