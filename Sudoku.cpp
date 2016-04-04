#include"Sudoku.h"
using namespace std;
void Sudoku::giveQuestion()
{
   int init_map[81]=
   {0,0,7,0,1,6,0,0,2,
    0,8,9,0,0,0,0,0,0,
    3,1,0,7,0,0,5,0,0,
    0,0,8,0,9,4,0,0,1,
    1,0,0,6,0,7,0,0,3,
    9,0,0,1,3,0,7,0,0,
    0,0,4,0,0,1,0,2,9,
    0,0,0,0,0,0,4,1,0,
    2,0,0,4,7,0,3,0,0};
    for(int i=0;i<sudokusize;i++)map[i]=init_map[i];
    for(int i=0;i<81;i++)
    {
       cout<<map[i]<<" ";
       if(i%9==8)cout<<endl;
    }
}
void Sudoku::readIn()
{
  int input[81];
  for(int i=0;i<81;i++)
  {
    cin>>input[i];
    rdinmp[i]=input[i];
  }
}
void Sudoku::transform()
{
  change();
  printOut();
}
void Sudoku::change()
{
  srand(time(NULL));
  changeNum(rand()%9+1,rand()%9+1);
  changeRow(rand()%3,rand()%3);
  changeCol(rand()%3,rand()%3);
  rotate(rand()%101);
  flip(rand()%2);
}

void Sudoku::printOut()
{
  for(int i=0;i<81;i++)
  {
    cout<<rdinmp[i]<<" ";
    if(i%9==8)cout<<endl;
  }
}
void Sudoku::changeNum(int a,int b)
{
  int i,k=0,n=0,site_a[9],site_b[9];
  for(i=0;i<9;i++)//初始0
  {
    site_a[i]=0;
    site_b[i]=0;
  }
  for(i=0;i<81;i++)//那些位置存取a,b
  {
    if(rdinmp[i]==a)site_a[k++]=i+1;
    if(rdinmp[i]==b)site_b[n++]=i+1;
  }
   for(i=0;i<9;i++)
   {
     if(site_a[i]!=0)rdinmp[site_a[i]-1]=b;
     if(site_b[i]!=0)rdinmp[site_b[i]-1]=a;
   }

}
void Sudoku::changeRow(int a,int b)
{
   int temp[81],i,j;
   for(i=0;i<81;i++)temp[i]=rdinmp[i];
   if(a==0&&b==1||a==1&&b==0)
   {
     for(i=0;i<27;i=i+9)
     {
        for(j=0;j<9;j++)
        {
           rdinmp[i+j]=temp[i+j+27];
           rdinmp[i+j+27]=temp[i+j];
         }
     }
   }
   if(a==0&&b==2||a==2&&b==0)
   {
     for(i=0;i<27;i=i+9)
     {
        for(j=0;j<9;j++)
        {
           rdinmp[i+j]=temp[i+j+54];
           rdinmp[i+j+54]=temp[i+j];
         }
      }
    }
    if(a==1&&b==2||a==2&&b==1)
    {
       for(i=27;i<54;i=i+9)
       {
          for(j=0;j<9;j++)
          {
            rdinmp[i+j]=temp[i+j+27];
            rdinmp[i+j+27]=temp[i+j];
            }
        }
    }
}
void Sudoku::changeCol(int a,int b)
{
    int i,temp[81],j;
    for(i=0;i<81;i++)temp[i]=rdinmp[i];
    if(a==0&&b==1||a==1&&b==0)
    {
     for(i=0;i<3;i++)
     {
       for(j=0;j<81;j=j+9)
       {
        rdinmp[i+j]=temp[i+j+3];
        rdinmp[i+j+3]=temp[i+j];
        }
      }
    }
    if(a==0&&b==2||a==2&&b==0)
    {
      for(i=0;i<3;i++)
      {
        for(j=0;j<81;j=j+9)
        {
          rdinmp[i+j]=temp[i+j+6];
          rdinmp[i+j+6]=temp[i+j];
         }
      }
    }
    if(a==1&&b==2||a==2&&b==1)
    {
      for(i=3;i<6;i++)
      {
        for(j=0;j<81;j=j+9)
       {
           rdinmp[i+j]=temp[i+j+3];
           rdinmp[i+j+3]=temp[i+j];
        }
      }
	}
}
void Sudoku::flip(int n)
{
   int i,temp[81],j;
   for(i=0;i<81;i++)temp[i]=rdinmp[i];
   if(n==1)//水平左右
   {
     for(i=0;i<9;i++)
     {
      for(j=0;j<81;j=j+9)
      {
        rdinmp[i+j]=temp[8-i+j];
      }
     }
   }
   if(n==0)//垂直上下
   {
     for(i=0;i<81;i=i+9)
     {
        for(j=0;j<9;j++)
        {
           rdinmp[i+j]=temp[72-i+j];
        }
      }
   }
}
void Sudoku::rotate(int n)
{
   int i,temp[81],k,j;
   for(i=0;i<81;i++)temp[i]=rdinmp[i];
   if(n%4==1)
   {
     k=0;
      for(i=0;i<9;i++)
      {
        for(j=72;j>=0;j=j-9)
        {
          rdinmp[k++]=temp[i+j] ;
        }
      }
   }
    if(n%4==2)
        {
           for(i=0;i<81;i++)
           {
              rdinmp[i]=temp[80-i];
            }
        }
    if(n%4==3)
    {
       k=0;
       for(i=0;i<9;i++)
       {
        for(j=8;j<81;j=j+9)
        {
          rdinmp[k++]=temp[j-i];
        }
       }
    }
}
void Sudoku::solve()
{ 
  too_many_answer();
}
bool Sudoku::unsolveable1()//某格不能填任何數字 
{
    int i,j,number_exist[9],possible_answer[9],zero_site[9],compare[9],k,u,m,suit,n,a,exist_number[9];
    for(i=0;i<81;i=i+9)//row
    {
      for(m=0;m<9;m++)
     {
        for(j=0;j<9;j++)
        {
           number_exist[j]=0;
           compare[j]=0;
           possible_answer[j]=0;
           zero_site[j]=0;
        }
        suit=0;
        n=0;
        for(j=i;j<i+9;j++)
            {
              if(rdinmp[j]!=0)number_exist[n++]=rdinmp[j];
            }
        for(j=0;j<9;j++)
            {
              if(number_exist[j]!=0)compare[number_exist[j]-1]++;
            }
        n=0;
        for(j=0;j<9;j++)
           {
             if(compare[j]==0)possible_answer[n++]=j+1;//找出此行剩餘數字
            }
        n=0;
        for(j=i;j<i+9;j++)
           {
              if(rdinmp[j]==0)zero_site[n++]=j+1;
            }
        for(j=0;j<9;j++)//此剩餘數字無合適空位可填 
           {
             if(zero_site[j]!=0&&possible_answer[m]!=0)
             {
			if(suitable_site(zero_site[j]-1,possible_answer[m])==1)break;//此數字找到可填位置
		        if(suitable_site(zero_site[j]-1,possible_answer[m])==0&&(j<8&&zero_site[j+1]==0))//一整行到底都無合適的位置 
			    {
			         return true;
			    } 
			    if(suitable_site(zero_site[j]-1,possible_answer[m])==0&&j==8)
			    {
                               return true;
			    }
			 }
		   }           
      }
    }
    for(i=0;i<9;i++)//col 
    {
       for(m=0;m<9;m++)
       {
         for(j=0;j<9;j++)
         {
            number_exist[j]=0;
            compare[j]=0;
            possible_answer[j]=0;
            zero_site[j]=0;
         }
        n=0;
        for(j=i;j<81;j=j+9)
        {
          if(rdinmp[j]!=0)number_exist[n++]=rdinmp[j];
        }
        for(j=0;j<9;j++)
        {
          if(number_exist[j]!=0)compare[number_exist[j]-1]++;
        }
        n=0;
       for(j=0;j<9;j++)
       {
         if(compare[j]==0)possible_answer[n++]=j+1;
       }
       n=0;
       for(j=i;j<81;j=j+9)
       {
          if(rdinmp[j]==0)zero_site[n++]=j+1;
       }
       for(j=0;j<9;j++)//此剩餘數字無空位可填 
       {
          if(zero_site[j]!=0&&possible_answer[m]!=0)
          {
		    if(suitable_site(zero_site[j]-1,possible_answer[m])==1)break;
	        if(suitable_site(zero_site[j]-1,possible_answer[m])==0&&(j<8&&zero_site[j+1]==0))
		    {
			   cout<<"col1";
               return true;
			}
			if(suitable_site(zero_site[j]-1,possible_answer[m])==0&&j==8)
			{
			   cout<<"col";
               return true;
			}
		
		  }
       }

    }
  }
   for(i=0;i<9;i++)//team宮
   {
     for(a=0;a<9;a++)
     {
	   n=0,k=0;
       for(j=0;j<9;j++)
       {
         exist_number[j]=0;
         zero_site[j]=0;
         possible_answer[j]=0;
         compare[j]=0;
       }
       for(j=(i/3)*27+(i%3)*3;j<=(i/3)*27+(i%3)*3+18;j=j+9)
       {
         for(m=j;m<j+3;m++)
         {
           if(rdinmp[m]!=0){exist_number[n++]=rdinmp[m];}
           else{zero_site[k++]=m+1;}
          }
       }
       for(j=0;j<9;j++)
       {
         if(exist_number[j]!=0)compare[exist_number[j]-1]++;
       }
       n=0;
       for(j=0;j<9;j++)
       {
         if(compare[j]==0)possible_answer[n++]=j+1;
       }         
       for(j=0;j<9;j++)
       {
         if(zero_site[j]!=0&&possible_answer[a]!=0)
         {
            if(suitable_site(zero_site[j]-1,possible_answer[a])==1)break;
		    if((j<8&&zero_site[j+1]==0)&&suitable_site(zero_site[j]-1,possible_answer[a])==0)
			{
			    return true;
			}
			if(suitable_site(zero_site[j]-1,possible_answer[a])==0&&j==8)
			{
			   return true;
			}
         }
       }
         
          
    }
  }
return false;
}
bool Sudoku::unsolveable2()//0過多提示過少 
{	
  int hint=0;
  for(int i=0;i<81;i++)	
	{
	  if(rdinmp[i]!=0)hint++;
  	}
  if(hint<17){return true;}
  else {return false;}
}
bool Sudoku::unsolveable3()//本身題目有問題 
{  
  if(unsolveable2()==false)
  { 
    int compare_row[9][9],compare_col[9][9],compare_team[9][9];
    for(int i=0;i<9;i++)
    {
      for(int j=0;j<9;j++)
      {
         compare_row[i][j]=0;
         compare_col[i][j]=0;
         compare_team[i][j]=0;       
      }
    }
 	for(int i=0;i<81;i++)
 	{
      if(rdinmp[i]!=0)//計算數字在某行某列某格出現次數    
	  {
	    compare_row[i/9][rdinmp[i]-1]++;
	    compare_col[i%9][rdinmp[i]-1]++;
	    compare_team[3*(i/27)+(i%9)/3][rdinmp[i]-1]++;
          }
	} 
    for(int i=0;i<9;i++)
	{
	  for(int j=0;j<9;j++)//出現數字重複了
	  {
	  	if(compare_row[i][j]>1||compare_col[i][j]>1||compare_team[i][j]>1)return true;
	  }
	}
	return false;

  }return true;
}
int Sudoku::one_number_rest(int arr[9])//唯一法
{
    int counter[9],i,k=0,rest[9];
    for(i=0;i<9;i++)
    {
      counter[i]=0;
    }
    for(i=0;i<9;i++)
    {
      ++counter[arr[i]-1];
    }
    int x=0;
    for(i=0;i<9;i++)
    {
      if(counter[i]==0)
      {
              k++;         //剩餘空白個數
              rest[x++]=i+1;   //紀錄未填數字
        }
    }
    if(k==1)return rest[0];   //剩下的那個未填數字
    else return 0;
}
void Sudoku::scan_row(int row)//唯一法//剩一格直接填
{
   int i,compare[9],k=0,zero_site[9],x=0;
   for(i=9*row;i<9*row+9;i++)
   {
      compare[x++]=rdinmp[i];
      if(rdinmp[i]==0)
      {
        zero_site[k++]=i;
      }
   }
   if(k==1){rdinmp[zero_site[0]]=one_number_rest(compare);}//只剩一個空格直接填
}
void Sudoku::scan_col(int col)//唯一法
{
    int i,compare[9],k=0,zero_site[9],x=0;
    for(i=col;i<=9*8+col;i=i+9)
    {
       compare[x++]=rdinmp[i];
       if(rdinmp[i]==0)
       {
          zero_site[k++]=i;
       }
    }
    if(k==1){rdinmp[zero_site[0]]=one_number_rest(compare);}//只剩一個空格直接填
}
void Sudoku::scan_team()//唯一法
{
    int i,j,site,compare[9],u,x,zero_site[9];
    for(i=0;i<9;i++)
    {
       x=0;
       for(j=0;j<9;j++)
       {
          site=27*(i/3)+3*(i%3)+9*(j/3)+(j%3);
          compare[j]=rdinmp[site];
       }
       for(u=0;u<9;u++)//計算這行有多少0(未填)
       {
          if(compare[u]==0)
          {
             zero_site[x++]=27*(i/3)+3*(i%3)+9*(u/3)+(u%3);
          }
        }
       if(x==1){rdinmp[zero_site[0]]=one_number_rest(compare);}//只剩一個空格直接填
    }
}
void Sudoku::row_col_team()//數對唯餘法//行列宮交差點若剩餘唯一數字直接填
{
    int i,zero_site[81],a=0,j,site,k,compare[9],answer[9];
    for(i=0;i<81;i++)
    {
        zero_site[i]=0;
    }
    for(i=0;i<81;i++)
    {
       if(rdinmp[i]==0) {zero_site[a++]=i;} //記0位
    }
    for(a=0;a<81;a++)
    {
       for(i=0;i<9;i++){compare[i]=0;}
       if(zero_site[a]==0&&a!=0){break;}
       for(i=9*(zero_site[a]/9);i<9*(zero_site[a]/9)+9;i++)
       {
          switch(rdinmp[i])
          {
            case 1:compare[0]++;break;
            case 2:compare[1]++;break;
            case 3:compare[2]++;break;
            case 4:compare[3]++;break;
            case 5:compare[4]++;break;
            case 6:compare[5]++;break;
            case 7:compare[6]++;break;
            case 8:compare[7]++;break;
            case 9:compare[8]++;break;
            default:break;
          }
       }
       for(i=(zero_site[a]%9);i<9*8+(zero_site[a]%9);i=i+9)
       {
         switch(rdinmp[i])
         {
            case 1:compare[rdinmp[i]-1]++;break;
            case 2:compare[rdinmp[i]-1]++;break;
            case 3:compare[rdinmp[i]-1]++;break;
            case 4:compare[rdinmp[i]-1]++;break;
            case 5:compare[rdinmp[i]-1]++;break;
            case 6:compare[rdinmp[i]-1]++;break;
            case 7:compare[rdinmp[i]-1]++;break;
            case 8:compare[rdinmp[i]-1]++;break;
            case 9:compare[rdinmp[i]-1]++;break;
            default:break;
          }
       }
       for(i=zero_site[a]-(zero_site[a]%3)-9*((zero_site[a]/9)%3);i<=zero_site[a]-(zero_site[a]%3)-9*((zero_site[a]/9)%3)+18;i=i+9)
       {
           for(j=i;j<i+3;j=j+1)
           {
              switch(rdinmp[j])
              {
                 case 1:compare[rdinmp[j]-1]++;break;
                 case 2:compare[rdinmp[j]-1]++;break;
                 case 3:compare[rdinmp[j]-1]++;break;
                 case 4:compare[rdinmp[j]-1]++;break;
                 case 5:compare[rdinmp[j]-1]++;break;
                 case 6:compare[rdinmp[j]-1]++;break;
                 case 7:compare[rdinmp[j]-1]++;break;
                 case 8:compare[rdinmp[j]-1]++;break;
                 case 9:compare[rdinmp[j]-1]++;break;
                 default:break;
              }
           }
       }
       k=0;
       for(i=0;i<9;i++)
       {
          if(compare[i]==0)
          {
             answer[k++]=i+1;
          }
        }
        if(k==1)
        {
           rdinmp[zero_site[a]]=answer[0];
        }
   }

}
bool Sudoku::check_blank_space()//還有空位
{
   for(int i=0;i<81;i++)
   {
     if(rdinmp[i]==0)return true;

   }
   return false;
}
void Sudoku::try_to_fill()//列屏除
{
    int i,j,k,u,n,number_exist[9],possible_answer[9],m,suit=0,zero_site[9],site[9],compare[9];
    for(i=0;i<81;i=i+9)
    {
      for(j=0;j<9;j++)
      {
        number_exist[j]=0;
        possible_answer[j]=0;
        zero_site[j]=0;
        site[j]=0;
        compare[j]=0;
      }
      k=0,u=0,m=0;
      for(j=0;j<9;j++)      //找出可能答案
      {
        if(rdinmp[i+j]==0){zero_site[k++]=i+j+1;}
        else{number_exist[u++]=rdinmp[i+j];}
      }
      for(j=0;j<9;j++)
      {
       if(number_exist[j]!=0)compare[number_exist[j]-1]++;
      }
      for(j=0;j<9;j++)
      {
        if(compare[j]==0)possible_answer[m++]=j+1;//可能答案
      }
      for(n=0;n<9;n++)
      {
        k=0;
        for(j=0;j<9;j++){zero_site[j]=0;}
        for(j=0;j<9;j++)
        {
          if(rdinmp[i+j]==0){zero_site[k++]=i+j+1;}
        }
        suit=0;
        for(j=0;j<9;j++)
        {
          if(zero_site[j]!=0&&possible_answer[n]!=0)
          {
            suit=suit+suitable_site(zero_site[j]-1,possible_answer[n]);
          }
        }
        if(suit==1)//此數字在此行出現的位置唯一!!!
        {
           for(j=0;j<9;j++)
           {
              if(suitable_site(zero_site[j]-1,possible_answer[n])==1)break;
           }
           rdinmp[zero_site[j]-1]=possible_answer[n];
        }
     }
  }
}
void Sudoku::try_to_fill_col()//行屏除
{
   int i,m,j,n,suit,number_exist[9],compare[9],possible_answer[9],zero_site[9];
   for(i=0;i<9;i++)
   {
      for(m=0;m<9;m++)
      {
         for(j=0;j<9;j++)
        {
           number_exist[j]=0;
           compare[j]=0;
           possible_answer[j]=0;
           zero_site[j]=0;
        }
       suit=0;
       n=0;
       for(j=i;j<81;j=j+9)
       {
         if(rdinmp[j]!=0)number_exist[n++]=rdinmp[j];
        }
       for(j=0;j<9;j++)
       {
         if(number_exist[j]!=0)compare[number_exist[j]-1]++;
       }
       n=0;
       for(j=0;j<9;j++)
       {
         if(compare[j]==0)possible_answer[n++]=j+1;
       }
       n=0;
       for(j=i;j<81;j=j+9)
       {
         if(rdinmp[j]==0)zero_site[n++]=j+1;
        }
       for(j=0;j<9;j++)
       {
         if(zero_site[j]!=0&&possible_answer[m]!=0)
         {suit=suit+suitable_site(zero_site[j]-1,possible_answer[m]);}
       }
       if(suit==1)
       {
          for(j=0;j<9;j++)
          {
             if(suitable_site(zero_site[j]-1,possible_answer[m])==1)break;
          }
         rdinmp[zero_site[j]-1]=possible_answer[m];
       }
    }
  }
}
bool Sudoku::count(int arr[],int possible_answer)//傳入的此數字在此陣列中是否為可填數字
{
   int counter[9];
   for(int i=0;i<9;i++)counter[i]=0;
   for(int i=0;i<9;i++)++counter[arr[i]-1];
   if(possible_answer!=0&&counter[possible_answer-1]==0)return true;
   return false;
}
int Sudoku::suitable_site(int zero_site,int possible_answer)
{
   int arr[9],site,k,j,i;
   for(j=0;j<9;j++)//判斷行可填
   {
       arr[j]=rdinmp[(zero_site-zero_site%9)+j];
   }
   if(count(arr,possible_answer)==false)return 0;
   for(j=0;j<9;j++)//判斷列可填
   {
       arr[j]=rdinmp[(zero_site%9)+9*j];
   }
   if(count(arr,possible_answer)==false)return 0;
   k=0;
   for(j=zero_site-(zero_site%3)-9*((zero_site/9)%3);j<=zero_site-(zero_site%3)-9*((zero_site/9)%3)+18;j=j+9)//判斷宮可填
   {
      for(i=0;i<3;i++)
      {
        arr[k++]=rdinmp[i+j];
      }
   }
   if(count(arr,possible_answer)==false)return 0;
   return 1;
}
void Sudoku::try_to_fill_team()//宮屏除
{
        int i,a,n,k,j,m,exist_number[9],zero_site[9],possible_answer[9],compare[9],suit;
   for(i=0;i<9;i++)
   {
     for(a=0;a<9;a++)
     {
	   n=0,k=0;
       for(j=0;j<9;j++)
       {
        exist_number[j]=0;
        zero_site[j]=0;
        possible_answer[j]=0;
        compare[j]=0;
       }
       for(j=(i/3)*27+(i%3)*3;j<=(i/3)*27+(i%3)*3+18;j=j+9)
       {
         for(m=j;m<j+3;m++)
         {
           if(rdinmp[m]!=0){exist_number[n++]=rdinmp[m];}
           else{zero_site[k++]=m+1;}
          }
       }
       for(j=0;j<9;j++)
       {
         if(exist_number[j]!=0)compare[exist_number[j]-1]++;
       }
       n=0;
       for(j=0;j<9;j++)
       {
         if(compare[j]==0)possible_answer[n++]=j+1;
       }
       suit=0;
       for(j=0;j<9;j++)
       {
        if(zero_site[j]!=0&&possible_answer[a]!=0)
        {
          suit=suit+suitable_site(zero_site[j]-1,possible_answer[a]);
        }
       }
       if(suit==1)//此數字在此宮可填位置唯一
       {
         for(j=0;j<9;j++)
         {
           if(suitable_site(zero_site[j]-1,possible_answer[a])==1)break;
         }
         rdinmp[zero_site[j]-1]=possible_answer[a];
       }
    }
  }
} 
void Sudoku::team_one_possible()//此位子可填數唯一
{
  int i,a,n,k,j,m,exist_number[9],zero_site[9],possible_answer[9],compare[9],suit;
  for(i=0;i<9;i++)
  {
    for(a=0;a<9;a++)
    {
	  n=0,k=0;
      for(j=0;j<9;j++)
      {
       exist_number[j]=0;
       zero_site[j]=0;
       possible_answer[j]=0;
       compare[j]=0;
      }
      for(j=(i/3)*27+(i%3)*3;j<=(i/3)*27+(i%3)*3+18;j=j+9)
      {
        for(m=j;m<j+3;m++)
       {
         if(rdinmp[m]!=0){exist_number[n++]=rdinmp[m];}
         else{zero_site[k++]=m+1;}
       }
      }
      for(j=0;j<9;j++)
      {
       if(exist_number[j]!=0)compare[exist_number[j]-1]++;
      }
      n=0;
      for(j=0;j<9;j++)
      {
       if(compare[j]==0)possible_answer[n++]=j+1;
      }
      suit=0;
      for(j=0;j<9;j++)
      {
        if(zero_site[j]!=0&&possible_answer[a]!=0)
        {
          suit=suit+suitable_site(zero_site[a]-1,possible_answer[j]);
        }
      }
      if(suit==1)
      {
        for(j=0;j<9;j++)
        {
          if(suitable_site(zero_site[a]-1,possible_answer[j])==1)break;
        }
        rdinmp[zero_site[a]-1]=possible_answer[j];
      }
    }
  }
}
void Sudoku::color()//若候補數都在同行 鄰宮的此行候補數取消
{
  int i,a,j,n,k,u,p,answer[81][9],zero_site[81],temp[81],count_row[9],two_way[9],count_team[9],count_col[9];
    for(i=0;i<81;i++)
     {
       for(a=0;a<9;a++)answer[i][a]=0;
     }
  for(a=0;a<9;a++)
  {
     k=0;
     for(i=0;i<81;i++)
     {
       zero_site[i]=0;
       if(rdinmp[i]==0)zero_site[k++]=i+1;//空位
     }
   
     for(j=0;j<81;j++)
     {
       if(zero_site[j]!=0)
       {
          if(suitable_site(zero_site[j]-1,a+1)==1)
          {
            answer[zero_site[j]-1][a]=-1;//標記-1,位置zero_site[j]可填a+1
          }
        }
     }
    for(i=0;i<9;i++)//第幾宮格
    {
       int number_in_team=0,row[9],col[9];
       for(j=0;j<9;j++)
       {
         row[j]=0;
         col[j]=0;
       }
       for(j=(i/3)*27+(i%3)*3;j<=(i/3)*27+(i%3)*3+18;j=j+9)
       {
         for(u=j;u<j+3;u++)
         {
          if(answer[u][a]==-1)
          {
            number_in_team++;//數字a在宮個出現次數
          }
         }
       }
       if(number_in_team==1||number_in_team==2||number_in_team==3)//判斷同行
       {
         for(j=(i/3)*27+(i%3)*3;j<=(i/3)*27+(i%3)*3+18;j=j+9)
         {
            for(u=j;u<j+3;u++)
            {
              if(answer[u][a]==-1)
              {
                row[u/9]++;
                col[u%9]++;
              }
            }
          }
       }
       j=((i/3)*27+(i%3)*3)/9;//此宮格起頭行
       if(row[j+1]+row[j+2]==0&&row[j]!=0)//如果候補數都在同行
       {      //cout<<"row[j+1]+row[j+2]"<<endl;
         for(u=(i/3)*3;u<(i/3)*3+3;u++)//同行宮格
         {
            if(u!=(i/3)*3+i%3)
            {
              for(k=(u/3)*27+(u%3)*3;k<=(u/3)*27+(u%3)*3+18;k=k+9)
              {
                 for(p=0;p<3;p++)
                 {
                   if((p+k)/9==j)
                   {
                     if(answer[p+k][a]==-1)
                     {
                       answer[p+k][a]=0;
                     }
                   }
                 }
              }
            }
          }
       }
       if(row[j]+row[j+2]==0&&row[j+1]!=0)
       {
          for(u=(i/3)*3;u<(i/3)*3+3;u++)
          {
            if(u!=(i/3)*3+i%3)
            {
               for(k=(u/3)*27+(u%3)*3;k<=(u/3)*27+(u%3)*3+18;k=k+9)
               {
                  for(p=0;p<3;p++)
                  {
                     if((p+k)/9==j+1)
                     {
                        if(answer[p+k][a]==-1)
                        {
                           answer[p+k][a]=0;
                        }
                     }
                  }
               }
             }
          }
       }
       if(row[j]+row[j+1]==0&&row[j+2]!=0)
       {
          for(u=(i/3)*3;u<(i/3)*3+3;u++)
          {
             if(u!=(i/3)*3+i%3)
             {
                for(k=(u/3)*27+(u%3)*3;k<=(u/3)*27+(u%3)*3+18;k=k+9)
                {
                  for(p=0;p<3;p++)
                  {
                    if((p+k)/9==j+2)
                    {
                      if(answer[p+k][a]==-1)
                      {
                        answer[p+k][a]=0;
                      }
                    }
                  }
                }
              }
           }
       }
       j=((i/3)*27+(i%3)*3)%9;       //宮格起頭列
       if(col[j+1]+col[j+2]==0&&col[j]!=0)
       {
         for(u=i%3;u<=(i%3)+2*3;u=u+3)//同一直排宮格
         {
            if(u!=i%3+(i/3)*3)
            {
              for(k=(u/3)*27+(u%3)*3;k<=(u/3)*27+(u%3)*3+18;k=k+9)
              {
                for(p=0;p<3;p++)
                {
                   if((p+k)%9==j)
                   {
                      if(answer[p+k][a]==-1)
                      {
                        answer[p+k][a]=0;
                      }
                    }
                }
              }
           }
        }
     }
     if(col[j]+col[j+2]==0&&col[j+1]!=0)
     {
       for(u=i%3;u<=(i%3)+2*3;u=u+3)
       {
          if(u!=i%3+(i/3)*3)
          {
            for(k=(u/3)*27+(u%3)*3;k<=(u/3)*27+(u%3)*3+18;k=k+9)
            {
               for(p=0;p<3;p++)
               {
                 if((p+k)%9==j+1)
                 {
                    if(answer[p+k][a]==-1)
                    {
                      answer[p+k][a]=0;
                    }
                 }
               }
            }
          }
        }
     }
     if(col[j]+col[j+1]==0&&col[j+2]!=0)
     {
        for(u=i%3;u<=(i%3)+2*3;u=u+3)
        {
          if(u!=i%3+(i/3)*3)
          {
            for(k=(u/3)*27+(u%3)*3;k<=(u/3)*27+(u%3)*3+18;k=k+9)
            {
              for(p=0;p<3;p++)
              {
                if((p+k)%9==j+2)
                {
                  if(answer[p+k][a]==-1)
                  {
                    answer[p+k][a]=0;
                   }
                }
              }
            }
          }
       }
     }
   }
  }
   for(i=0;i<81;i++)
    {
	  k=0;
      for(j=0;j<9;j++)
      {
        if(answer[i][j]==-1)k++;
      }
      if(k==1)
      {
        for(j=0;j<9;j++)
        {
          if(answer[i][j]==-1)break;
        }
        if(suitable_site(i,j+1)==1)rdinmp[i]=j+1;
      }
    }

}
void Sudoku::too_many_answer()
{
   int i,j,k,u,m,sum,count[10],n,zero_site[81],temp[81];
   k=0;
    if(unsolveable3()||unsolveable1())//事先檢查題型是否無解 
    {
      cout<<"0"<<endl;
      exit(0);
    } 
    for(j=0;j<10;j++)
   { 
  	 for(i=0;i<9;i++)
     {
        scan_row(i);
        scan_col(i);
     }
     scan_team() ;
     row_col_team();
     color();
     try_to_fill();
     try_to_fill_col();
     try_to_fill_team();
     team_one_possible();
     color();
   }
     	
	 k=0;
     for(i=0;i<81;i=i+9)
     {
       sum=0;
       for(j=i;j<i+9;j++)
	   {
	      sum=sum+rdinmp[j];
	   } 
	   if(sum!=45)break;
	   if(sum==45)k++;
     }
	 if(k==9)
     {
		cout<<"1"<<endl;//唯一解 
		for(i=0;i<81;i++)
		{
		  cout<<rdinmp[i]<<" ";
		  if(i%9==8)cout<<endl;	
		} 
		exit(0);
	 }
   	if(unsolveable1())//在判斷一次是否無解
	{
	  cout<<"0"<<endl;
 	  exit(0);
    }
    cout<<"2"<<endl;//排除無解唯一解即多解
    exit(0);
      
}
