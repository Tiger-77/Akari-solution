#include<iostream>
#include<string.h>
#include<Windows.h>
using namespace std;

#define N 9
struct element{
	int flag;        //����Ϊ1��δ��-1 
	bool arr[N];   //�������������1�����ܾ���0�� 
	int count;
	int data;
};  

class sudoku{
private:
	element a[N][N];
	int num;                //һ�������˶������� 
public:
	sudoku(){    //�չ��캯���������� 
	}
	sudoku(string m){      //���캯�������������� 
		int row=0;
		int col=0;
		num=0;
		for(int i=0;i<81;i++){
			row=i/9;
			col=i%9;
			if(m[i]!='.'){     //��ȷ������ 
				a[row][col].flag=1;
				int tmp=m[i]-'0';
				a[row][col].data=tmp;
				num++;
			}
			else{
				for(int k=0;k<N;k++){
					a[row][col].arr[k]=true;     //һ�н��п���	
				}
				a[row][col].count=9;
				a[row][col].data=0;
				a[row][col].flag=-1;
			}	
		}
	}
	void FirstFill(){        //��ʣ�µ�������ȫ�������� 
		int k=0;
		int row=0;
		int col=0;
		while(k!=81){  //��a[row][col]��һ�����ų������ܵ�ֵ 
			row=k/9;
			col=k%9;
			if(a[row][col].flag==-1){   //��û�� 
				for(int i=0;i<N;i++){    //��һ�е��ų�
					if(a[row][i].flag==1){   //�����֣������ų�һ�� 
						(a[row][col].count)--;
						a[row][col].arr[(a[row][i].data)-1]=false;
					}
				}
				
				for(int j=0;j<N;j++){    //��һ�е��ų�
					if(a[j][col].flag==1){   //�����֣������ų�һ�� 
						if(a[row][col].arr[a[j][col].data-1]==true){  //��һ�����ֻ�û�ų� 
							(a[row][col].count)--;
							a[row][col].arr[a[j][col].data-1]=false;
						}
					}
				}
				
				int f1=row/3*3;
				int f2=col/3*3;    //�ҵ����ڵĸ��Ӷ��� 
				for(int m=f1;m<f1+3;m++){
					for(int mm=f2;mm<f2+3;mm++){
						if(a[m][mm].flag==1){   //�����֣������ų�һ�� 
							if(a[row][col].arr[(a[m][mm].data)-1]==true){  //��һ�����ֻ�û�ų� 
							(a[row][col].count)--;
							a[row][col].arr[(a[m][mm].data)-1]=false;	
							}
						}
					}
				}
				k++;
			}
			else
			k++;
		}
		k=0;
		while(k!=81){
			row=k/9;
			col=k%9;
			if((a[row][col].flag==-1)&&a[row][col].count==1){
			for(int x=0;x<N;x++){
				if(a[row][col].arr[x]==true){
					a[row][col].data=x+1;
					a[row][col].flag=1;
					num++;
					break;
				}
			}
		    ReFillCol(row,col);
			ReFillRow(row,col);
			ReFillGr(row,col);
			}
			k++;
		}
	}
	
	void Judging1(int x,int y){     //��һ��������������or��or�Ź������������Ψһ�������벢refill�� 
	int m=0;
		int tag=0;   //��� 
		int i,k;
		for(i=0;i<N;i++){     //���Ƿ�Ψһ 
		tag=0;
			if(a[x][y].arr[i]==true){   //��������� 
				for(k=0;k<N;k++){//������һ�� 
					if(a[x][k].flag==-1&&k!=y){
						if(a[x][k].arr[i]==true){    //����Ψһ�ģ�Ҳ�������ڣ�x��k�� 
							tag=1;
							break;
						}
					}
				}
			if(tag==0&&k==N)
				break;
			}
		}
		if(k==N&&tag==0){//����һ������Ψһ�ģ��������� 
			num++;
			a[x][y].data=i+1;
			a[x][y].flag=1;
			ReFillCol(x,y);
			ReFillGr(x,y);
			return;
		}
		
		for(i=0;i<N;i++){     //���Ƿ�Ψһ
		tag=0;
			if(a[x][y].arr[i]==true){   //��������� 
				for(k=0;k<N;k++){   //������һ�п��ǲ���ֻ�������� 
					if(a[k][y].flag==-1&&k!=x){
						if(a[k][y].arr[i]==true){    //����Ψһ�ģ�Ҳ�������ڣ�x��k�� 
							tag=1;
							break;
						}
					}
				}
			}
			if(tag==0&&k==N)
			break;
		}
		if(k==N&&tag==0){//����һ������Ψһ�ģ��������� 
			num++;
			a[x][y].data=i+1;
			a[x][y].flag=1;
			ReFillRow(x,y);
			ReFillGr(x,y);
			return;
		}
		
		int f1=x/3*3,f2=y/3*3;
		int b,bb;
		for(i=0;i<N;i++){//���Ź������ǲ���Ψһ�� 
		tag=0;
			if(a[x][y].arr[i]==true){
				for(b=f1;b<f1+3;b++){  
					for(bb=f2;bb<f2+3;bb++){
						if(a[b][bb].flag==-1&&(b!=x||bb!=y)){
							if(a[b][bb].arr[i]==true){//�������Ҳ�����������ʧ�ܣ� 
								tag=1;
								break;
							}
						}
					}
					if(tag==1)
					break;
				}
				if(tag==0&&(b==f1+3)&&(bb==f2+3)){
					num++;
					a[x][y].data=i+1;
					a[x][y].flag=1;
					ReFillCol(x,y);
					ReFillRow(x,y);
					return;
				}
			}
		}
		return;
	}
	
	void Judging(){    //��ÿһ�����ӽ���Judging1(int x,int y)������ 
		int k=0;
		int i,j;
		while(k!=81&&num!=81){
			i=k/9;j=k%9;
			if(a[i][j].flag==-1)
			Judging1(i,j);
			k++;
		}
	}
	
	bool check(int x,int y){   //����ʱ���ĳһ��������Ƿ�Ϸ�
		for(int k=0;k<N;k++){//�еļ�� 
			if(a[x][k].data!=0&&a[x][k].data==a[x][y].data&&k!=y)
			return false;
		}
		
		for(int g=0;g<N;g++){//�еļ�� 
			if(a[g][y].data!=0&&a[g][y].data==a[x][y].data&&x!=g)
			return false;
		}
		
		int f1=x/3*3,f2=y/3*3;//�Ź����� 
		int m,n;
		for(m=f1;m<f1+3;m++){
			for(n=f2;n<f2+3;n++){
				if(a[x][y].data==a[m][n].data&&(m!=x||n!=y))
				return false;
			}
		}
		return true;
	}
	
	void Recusive(int x){	//���� 
		int r,c,i;
		if(x==81){
			cout<<"--------------The Final Sudoku--------------"<<endl;
			SudokuPrint();
		}
		else{
			r=x/9;
			c=x%9;
			if(a[r][c].data!=0)
			Recusive(x+1);
			else{      //��δ�������� 
				for(i=0;i<N;i++){
					if(a[r][c].arr[i]==true){
						a[r][c].data=i+1;
						if(check(r,c)){
							Recusive(x+1);
						}
						a[r][c].data=0;
					}
				}
			}
		}
	}
	
	void ReFillRow(int x,int y){//�����е�Ԫ�� 
		int ele=a[x][y].data;
		for(int k=0;k<N;k++){       
			if(a[x][k].flag==-1){
				if(a[x][k].arr[ele-1]==true){
					a[x][k].arr[ele-1]=false;
					(a[x][k].count)--;
				}
			}
			if(a[x][k].flag==-1&&a[x][k].count==1){
				for(int m=0;m<N;m++){
					if(a[x][k].arr[m]==true){
						a[x][k].data=m+1;
						num++;
						a[x][k].flag=1;
					}
				}
				ReFillRow(x,k);
				ReFillCol(x,k);
				ReFillGr(x,k);
			}
		}
	}
	
	void ReFillCol(int x,int y){//�����е�Ԫ��
		int ele=a[x][y].data;
		for(int k=0;k<N;k++){        
			if(a[k][y].flag==-1){
				if(a[k][y].arr[ele-1]==true){
					a[k][y].arr[ele-1]=false;
					(a[k][y].count)--;
				}
			}
			if(a[k][y].flag==-1&&a[k][y].count==1){
				for(int m=0;m<N;m++){
					if(a[k][y].arr[m]==true){
						a[k][y].data=m+1;
						num++;
						a[k][y].flag=1;
					}
				}
				ReFillRow(k,y);
				ReFillCol(k,y);
				ReFillGr(k,y);
			}
		}
	}
	
	void ReFillGr(int x,int y){//���¾Ź����Ԫ�� 
		int ele=a[x][y].data;
		int f1=x/3*3,f2=y/3*3;
		for(int c=f1;c<f1+3;c++){       
			for(int cc=f2;cc<f2+3;cc++){
				if(a[c][cc].flag==-1&&(a[c][cc].arr[ele-1]==true)){
						a[c][cc].arr[ele-1]=false;
						(a[c][cc].count)--;
				}
				if(a[c][cc].flag==-1&&a[c][cc].count==1){
					for(int m=0;m<N;m++){
						if(a[c][cc].arr[m]==true){
							a[c][cc].data=m+1;
							num++;
							a[c][cc].flag=1;
						}
					}
					ReFillRow(c,cc);
					ReFillCol(c,cc);
					ReFillGr(c,cc);
				}
			}
		}
	}
	
	void SudokuPrint(){         //������� 
		int i=0;
		int row=0;
		int col=0;
		while(i!=81){
			row=i/9;col=i%9;
			cout<<a[row][col].data<<" ";
			if((col+1)%9==0)
			cout<<endl;
			if(((col+1)%3==0)&&((col+1)%9!=0))
			cout<<" ";
			if((i+1)%27==0)
			cout<<endl;
			i++;
		}
	}
	
	void Solution(){
		cout<<"--------------The Original Sudoku--------------"<<endl;
		SudokuPrint();
		FirstFill();
		Judging();
		if(num!=81)
		Recusive(0);
		else{
			cout<<"--------------The Final Sudoku--------------"<<endl;
			SudokuPrint();
		}
	}
};

int main(){
	DWORD startTime = GetTickCount();
	string s1="..8...2...3.8.2.6.7...9...5.5.....1...4...6...2.....7.4...8...6.7.1.3.9...1...8..";
	string s2="8..........36......7..9.2...5...7.......457.....1...3...1....68..85...1..9....4..";
	string s3="....24.59.4.9..1...3...............73.7.9..2.4...36.....9..1.42.5.......2.3.6.79.";
	sudoku a1(s3);
	a1.Solution();
	DWORD endTime = GetTickCount();//��ʱ����
    cout << "The run time is:" << endTime - startTime << "ms" << endl;
    system("pause");
	return 0;
}
