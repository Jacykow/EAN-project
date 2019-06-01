#include <SFML/Graphics.hpp>
#include "Interval.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;
using namespace interval_arithmetic;

class MyInterval : public Interval<double>{
    public:
        MyInterval(double v):Interval(v,v){};
        MyInterval() : Interval(){};
        MyInterval(double a, double b) : Interval(a,b){};
        MyInterval(Interval<double> f){
            a=f.a;
            b=f.b;
        }
        bool operator==(const MyInterval& i){
            return a==i.a && b==i.b;
        }
        bool operator!=(const MyInterval& i){
            return a!=i.a || b!=i.b;
        }
        double middle(){
            return (a+b)/2;
        }
};

typedef vector<MyInterval> row;

class GaussJordanMatrix{
    public:
        int m;
        int n;
        vector<row> matrix;
        vector<row> matrix2;

        GaussJordanMatrix(){
            m=1;
            n=2;
        }
        GaussJordanMatrix(string fileName){
            fstream in;
            in.open(fileName,ios::in);

            in>>m;
            n=m+1;
            string v;

            MyInterval zero = MyInterval(0.0);
            MyInterval one = MyInterval(1.0);
            for(int y=0;y<m;y++){
                row r;
                row r2;
                for(int x=0;x<n;x++){
                    MyInterval i;
                    in>>v;
                    i=(MyInterval)MyInterval::IntRead(v);
                    r.push_back(i);

                    if(x==y){
                        r2.push_back(one);
                    }
                    else{
                        r2.push_back(zero);
                    }
                }
                matrix.push_back(r);
                matrix2.push_back(r2);
            }
            in.close();
        }
        void calculate(){
            MyInterval zero = MyInterval(0.0);
            MyInterval one = MyInterval(1.0);
            for(int a=0;a<n-1;a++){
                int b=a;
                while(b<m){
                    if(matrix[b][a]!=zero){
                        break;
                    }
                    b++;
                }
                if(b>a){
                    cout<<"swapping: "<<a<<" and "<<b<<endl;
                    row temp = matrix[b];
                    matrix[b] = matrix[a];
                    matrix[a] = temp;

                    temp = matrix2[b];
                    matrix2[b] = matrix2[a];
                    matrix2[a] = temp;
                }
                if(b>=m){
                    cout<<a<<endl;
                    throw "Empty column!";
                }

                for(int x=0;x<n-1;x++){
                    matrix2[b][x]=matrix2[b][x]/matrix[b][a];
                }
                for(int x=a+1;x<n;x++){
                    matrix[b][x]=matrix[b][x]/matrix[b][a];
                }
                matrix[b][a]=one;

                for(int y=0;y<m;y++){
                    if(y==b)continue;
                    for(int x=0;x<n-1;x++){
                        matrix2[y][x]=matrix2[y][x]-matrix[y][a]*matrix2[b][x];
                    }
                }
                for(int y=0;y<m;y++){
                    if(y==b)continue;
                    for(int x=a+1;x<n;x++){
                        matrix[y][x]=matrix[y][x]-matrix[y][a]*matrix[b][x];
                    }
                    matrix[y][a]=zero;
                }
            }
        }
        int matrixSize(){
            return m*n;
        }
        void show(){
            cout<<"\nCurrent matrix:\n";
            for(int y=0;y<m;y++){
                for(int x=0;x<n;x++){
                    cout<<matrix[y][x].middle()<<"\t";
                }
                cout<<endl;
            }
            cout<<"Current matrix reversed:\n";
            for(int y=0;y<m;y++){
                for(int x=0;x<n-1;x++){
                    cout<<matrix2[y][x].middle()<<"\t";
                }
                cout<<endl;
            }
        }
};

int main()
{
    // Create the main window
    RenderWindow app(VideoMode(800, 600), "SFML window");

    Text text;
    Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setString("asdf");
    text.setFillColor(Color::Red);

    GaussJordanMatrix matrix("data.in");

    fstream out;
    out.open("data.out",ios::out);
    try{
        matrix.show();
        matrix.calculate();
        matrix.show();

        vector<row> temp = matrix.matrix;
        matrix.matrix = matrix.matrix2;
        matrix.matrix2 = temp;

        matrix.show();
        matrix.calculate();
        matrix.show();
    }
    catch(char const* message){
        cout<<"Error: "<<message<<endl;
    }

    out.close();

    string input="as";

    /*
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed){
                app.close();
            }

            if(event.type==Event::TextEntered){
                input+=static_cast<char>(event.text.unicode);
            }


        }
        app.clear(Color::White);

        text.setString(input);
        app.draw(text);

        app.display();
    }
    */

    return EXIT_SUCCESS;
}
