#include<iostream>
#include<cstdlib>
class Sudoku
{
	   public:
          int one_number_rest(int arr[]);
           void scan_row(int row);
           void scan_col(int col);
           void scan_team();
           void row_col_team();
           void solve();
           void try_to_fill_col();
           void try_to_fill_team();
           void team_one_possible();
           static const int sudokusize=81;
           int rdinmp[sudokusize];
           bool check_blank_space();
           void try_to_fill();
           bool count(int arr[],int possible_answer);
           int suitable_site(int zero_site,int possible_answer);
           void color();
           void giveQuestion();
           void readIn();
           void transform();
           int map[sudokusize];
           void change();
           void changeNum(int a,int b);
           void changeRow(int a,int b);
           void changeCol(int a,int b);
           void rotate(int n);
           void flip(int n);
           bool unsolveable1(); 
           bool unsolveable2();
           bool unsolveable3();
           void too_many_answer();
           void printOut();
									                
};

