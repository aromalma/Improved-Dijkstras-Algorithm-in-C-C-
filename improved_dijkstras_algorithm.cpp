#include<stdio.h>

#include<conio.h>

#include<iostream>

#define start 900
#define path 0
#define end 999
#define wall 966
#define bes 922

int putv(int, int);
int found(int, int);
using namespace std;
int a[250][250], aa[250][250];
int c = 0, rmax, kmax, x, y, x1, y1;
int xx[2][400], yy[2][400];
int cou[2], count;

void copy() {
  for (int i = 0; i <= kmax; i++) {
    for (int j = 0; j <= rmax; j++) {
      aa[i][j] = a[i][j];
    }
  }
}

void dispa() { //cout<<;
  for (int i = 0; i <= kmax + 1; i++) {
    for (int j = 0; j <= rmax; j++) { //   char hg=a[i][j]+96;
      if (i == kmax + 1) cout << char(j + 97) << " ";
      //if (i==kmax+1)cout<<j<<" ";
      else if (aa[i][j] == start) cout << "I ";
      else if (aa[i][j] == path) cout << ". ";
      else if (aa[i][j] == end) cout << "F ";
      else if (aa[i][j] == wall) cout << "X ";
      else if (aa[i][j] == bes) cout << "@ ";
      //else if(a[i][j]==bes)cout<<"o ";

      else cout << ". ";
    }
    cout << char(i + 97) << " ";
    cout << "\n";
  }
  cout << "\n";
}
void disp() { //cout<<;
  char hg;
  for (int i = 0; i <= kmax + 1; i++) {
    for (int j = 0; j <= rmax; j++) {
      if (i == kmax + 1) cout << char(j + 97) << " ";
      //if (i==kmax+1)cout<<j<<" ";
      else if (a[i][j] == start) cout << "I ";
      else if (a[i][j] == path) cout << ". ";
      else if (a[i][j] == end) cout << "F ";
      else if (a[i][j] == wall) cout << "X ";
      else if (a[i][j] == bes) cout << "@ ";
      //else if(a[i][j]==bes)cout<<"o ";

      else cout << ". ";
    }
    cout << char(i + 97) << " ";
    cout << "\n";
  }
  cout << "\n";
}

int spread() {
  count = 0;
  if (cou[0] == 0 && cou[1] == 0) {
    return 0;
  }
  for (int i = 0; i < cou[c]; i++) {

    //cout<<x1<<" "<<y1<<"\n";
    if (putv(xx[c][i], yy[c][i]) == 1) {
      xx[c][i] = 0;
      yy[c][i] = 0;
    }
  }
  cou[c] = 0;
  if (c == 1) {
    c = 0;
  } else {
    c = 1;
  }
  cou[c] = count; //disp();
  return 1;
}
int putv(int x, int y) { //disp();//cout<<".."<<x<<" "<<y;
  int ret = 0;
  int c_;
  if (c == 1) {
    c_ = 0;
  } else {
    c_ = 1;
  }
  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      if ((i != x || j != y) && i >= 0 && j >= 0 && a[i][j] < 900 && i <= kmax && j <= rmax) { //cout<<a[i][j]<<" ";
        if (a[i][j] == 0) {
          a[i][j] = a[x][y] + 1;
          ret = 1;
          xx[c_][count] = i;
          yy[c_][count] = j;
          count++;
        } //xx[c][]cou[c]++	}
        else if (a[i][j] > a[x][y] + 1) {
          a[i][j] = a[x][y] + 1;
          ret = 1;
          xx[c_][count] = i;
          yy[c_][count] = j;
          count++;
        }
      }
    }
  } //disp();
  return ret;
}

void pour() {
  cou[0] = 0;
  c = 0;
  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) { //disp();
      if (i >= 0 && j >= 0)
        if (a[i][j] == 0) {
          a[i][j] = 1;
          xx[c][count] = i;
          yy[c][count] = j;
          count++;
        }
    } //cou[0]=count;
  }
  cou[0] = count; //dis();
}

int back() {
  bool static f = 0;
  int t;
  int bv = 10000;
  int x2, y2;
  int re = 0;
  while (re <= 1) {
    for (int i = x1 - 1; i <= x1 + 1; i++) {
      for (int j = y1 - 1; j <= y1 + 1; j++) {
        if ((re == 0 && (i == x1 || j == y1)) || (re == 1 && (i != x1 && j != y1))) {
          if (a[i][j] == end) {
            aa[x1][y1] = bes;
            f = 0;
            return 1;
          }
          if (i >= 0 && j >= 0 && (i != x1 || j != y1) && a[i][j] < 900 && a[i][j] > 0) {
            if (bv > a[i][j]) {
              bv = a[i][j];
              x2 = i;
              y2 = j;
            }
          }
        }
      }
    }
    re++;
  }
  if (bv != 10000) {
    if (f == 1) {
      aa[x1][y1] = bes;
    }
    f = 1;
    x1 = x2;
    y1 = y2;
  } //disp();
  return 0;
}

int main() {
  FILE * fp;
  char ch, c1, c2;
  int r = 0, k = 0;
  int vv, bb;
  int g = 4;
  fp = fopen("path.txt", "r");

  while ((ch = getc(fp)) != EOF) {
    if (ch == '\n') {
      k++;
      rmax = r;
      r = 0;
    }
    if (ch == 'F') {
      a[k][r] = end;
      x = k;
      y = r;
      r++;
    }
    if (ch == '.') {
      a[k][r] = path;
      r++;
    }
    if (ch == 'X') {
      a[k][r] = wall;
      r++;
    }
  }

  rmax--;
  kmax = k;
  disp(); //x1=x;y1=y;
  fclose(fp);
  c = 1; //a[x1+1][y1]=5;
  pour(); //disp();//cout<<x1<<" "<<y1;found(x1,y1);

  while (spread() == 1) {} //disp();cout<<x1<<".. "<<y1;
  int queries = 0;
  cout << "Input no of Queries: ";
  cin >> queries;
  queries = int(queries);
  for (; queries > 0; queries--) {
    copy();
    cout << "Input y value from last column:";
    cin >> c1;
    cout << "Input x value from last row:";
    cin >> c2;
    x1 = int(c1) - 97;
    y1 = int(c2) - 97;

    aa[x1][y1] = start;
    while (back() == 0) {}
    cout << "\nPATH \n";
    dispa();
  }
  queries--;
  getch();

}
