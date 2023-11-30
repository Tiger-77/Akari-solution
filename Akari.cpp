#include<iostream>
#include<string.h>
#include <iomanip>
using namespace std;

struct LightUp{
	int type;        //����ǽ/����/����ǽ 
	bool SGrid=false;   //�ж��Ƿ���ǽ��Χ�ĸ��ӣ� 
	bool Lightup=false;	//�Ƿ񱻵��� 
	int Spo=-1;		//�������Ŀ����� ��SGrid���������Ҳ��� 
	bool IsLight=false;	//�׸����ǲ��ǵ� 
	bool CanBulb=true;	//�׸����ܲ����ǵ� 
};  

struct NumWall{
	int type;		//���� 
	int avai=0;		//ʣ�µ�û�д��ĸ��� 
	int Bulbs=0;		//��¼�Ѿ��ŵĵ������� 
	bool finish=false;
};

class Akari{
private:
	int row;		//�� 
	int column;    //�� 
	NumWall** Walls;
	LightUp** map;
public:
	Akari(){
		
	}
	Akari(string m,int r,int c){
		column=c;
		row=r;
		Walls=new NumWall* [r];
		map=new LightUp* [r];
		for(int i=0;i<r;i++){
			map[i]=new LightUp [c];
		}
		for(int i=0;i<r;i++){
			Walls[i]=new NumWall [c];
		}
		//map���Ƕ�ά���� 
		int tt=0;
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++,tt++){
				if(m[tt]=='.'){		//�׸��� 
				map[i][j].type=5;
				}
				else if(m[tt]=='X'){		//��ǽ 
				map[i][j].type=-1;
				map[i][j].Lightup=true;
				map[i][j].CanBulb=false;
				}
				else{		//����ǽ 
				map[i][j].type=m[tt]-'0';
				map[i][j].Lightup=true;
				map[i][j].CanBulb=false;
				}
			}
		}
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				if(map[i][j].type==5||map[i][j].type==-1) continue;
				Walls[i][j].type=map[i][j].type;
				int left=j-1,right=j+1,down=i+1,up=i-1;//�ҳ����������Ƿ���ţ�ư׸��ӣ�ע����ޣ� 
				if(left>=0){
					if(map[i][left].type==5){
						Walls[i][j].avai++;
				  	    map[i][left].SGrid=true;
				  	    map[i][left].Spo=0;
					}
				}
				if(right<c){
					if(map[i][right].type==5){
						Walls[i][j].avai++;
						map[i][right].SGrid=true;
						map[i][right].Spo=0;
					}
				}
				if(up>=0){
					if(map[up][j].type==5){
						Walls[i][j].avai++;
						map[up][j].SGrid=true;
						map[up][j].Spo=0;
					}
				}
				if(down<r){
					if(map[down][j].type==5){
						Walls[i][j].avai++;
					    map[down][j].SGrid=true;
					    map[down][j].Spo=0;
					}
				}
			}
		}
	}
	~Akari(){
		for(int i=0; i<row; i++)
    		delete [] map[i];
		delete [] map;
		for(int i=0; i<row; i++)
    		delete [] Walls[i];
		delete [] Walls;
	}
	//��������
	void SetBulb(int rr,int cc){		
		int left=cc-1,right=cc+1,up=rr-1,down=rr+1;
		int l=left,r=right,u=up,d=down;
		map[rr][cc].IsLight=true;
		if(map[rr][cc].SGrid){		//Ҫ�����ľ���SGrid
			map[rr][cc].Lightup=true;
			map[rr][cc].CanBulb=false;
			if(left>=0 && map[rr][left].type!=-1&&map[rr][left].type!=5){
				Walls[rr][left].avai--;
				Walls[rr][left].Bulbs++; 
			}
			if(right<column&&map[rr][right].type!=-1&&map[rr][right].type!=5){
				Walls[rr][right].avai--;
				Walls[rr][right].Bulbs++; 
			}
			if(up>=0&& map[up][cc].type!=-1&&map[up][cc].type!=5){
				Walls[up][cc].avai--;
				Walls[up][cc].Bulbs++; 
			}
			if(down<row&&map[down][cc].type!=-1&&map[down][cc].type!=5){
				Walls[down][cc].avai--;
				Walls[down][cc].Bulbs++; 
			}
			refresh();
		}
		while(l>=0){		//������� Ӱ�������������ǽ 
			if(map[rr][l].type==5&&map[rr][l].SGrid==false){
				map[rr][l].Lightup=true;
				l--;
				continue; 
			}
			else if(map[rr][l].type==5&&map[rr][l].SGrid){
				map[rr][l].Lightup=true;
				if(map[rr][l].CanBulb==false) {
					l--;
					continue;
				}
				map[rr][l].CanBulb=false;
				if(up>=0&&(map[up][l].type==1||map[up][l].type==2||map[up][l].type==3)){
					Walls[up][l].avai--;
				}
				if(down<row&&(map[down][l].type==1||map[down][l].type==2||map[down][l].type==3)){
					Walls[down][l].avai--;
				}
				if(l-1>=0&&(map[rr][l-1].type==1||map[rr][l-1].type==2||map[rr][l-1].type==3)){
					Walls[rr][l-1].avai--;
				}
				l--;
			}
			else if(map[rr][l].type!=5) break;
		}
		while(r<column){		//���ҵ��� Ӱ�������� 
			if(map[rr][r].type==5&&map[rr][r].SGrid==false){
				map[rr][r].Lightup=true;
				r++;
				continue; 
			}
			else if(map[rr][r].type==5&&map[rr][r].SGrid){
				map[rr][r].Lightup=true;
				if(map[rr][r].CanBulb==false) {
					r++;continue;
				}
				map[rr][r].CanBulb=false;
				if(up>=0&&(map[up][r].type==1||map[up][r].type==2||map[up][r].type==3)){
					Walls[up][r].avai--;
				}
				if(down<row&&(map[down][r].type==1||map[down][r].type==2||map[down][r].type==3)){
					Walls[down][r].avai--;
				}
				if(r+1<column&&(map[rr][r+1].type==1||map[rr][r+1].type==2||map[rr][r+1].type==3)){
					Walls[rr][r+1].avai--;
				}
				r++;
			}
			else if(map[rr][r].type!=5) break;
		}
		while(u>=0){		//���ϵ��� (Ӱ������) 
			if(map[u][cc].type==5&&map[u][cc].SGrid==false){
				map[u][cc].Lightup=true;
				u--;
				continue; 
			}
			else if(map[u][cc].type==5&&map[u][cc].SGrid){	//�������� 
				map[u][cc].Lightup=true;
				if(map[u][cc].CanBulb==false) {
					u--;continue;
				} 
				map[u][cc].CanBulb=false;
				if(left>=0&&(map[u][left].type==1||map[u][left].type==2||map[u][left].type==3)){
					Walls[u][left].avai--;
				}
				if(right<column&&(map[u][right].type==1||map[u][right].type==2||map[u][right].type==3)){
					Walls[u][right].avai--;
				}
				if(u-1>=0&&(map[u-1][cc].type==1||map[u-1][cc].type==2||map[u-1][cc].type==3)){
					Walls[u-1][cc].avai--;
				}
				u--;
			}
			else if(map[u][cc].type!=5) break;
		}
		while(d<row){	//���µ��� 
			if(map[d][cc].type==5&&map[d][cc].SGrid==false){
				map[d][cc].Lightup=true;
				d++;
				continue; 
			}
			else if(map[d][cc].type==5&&map[d][cc].SGrid){
				map[d][cc].Lightup=true;
				if(map[d][cc].CanBulb==false){
					d++;continue;
				} 
				map[d][cc].CanBulb=false;
				if(left>=0&&(map[d][left].type==1||map[d][left].type==2||map[d][left].type==3)){
					Walls[d][left].avai--;
				}
				if(right<column&&(map[d][right].type==1||map[d][right].type==2||map[d][right].type==3)){
					Walls[d][right].avai--;
				}
				if(d+1<row&&(map[d+1][cc].type==1||map[d+1][cc].type==2||map[d+1][cc].type==3)){
					Walls[d+1][cc].avai--;
				}
				d++;
			}
			else if(map[rr][r].type!=5) break;
		}
	}  
	
	//�׶�һ����ʼ������ǽ0��4 
	void zeroandfour(int hh,int ll){
		int data=Walls[hh][ll].type;
		int left=ll-1;
		int right=ll+1;
		int down=hh+1;
		int up=hh-1;
		if(data==4){
			Walls[hh][ll].finish=true;
			Walls[hh][ll].Bulbs=4;
			SetBulb(hh,ll-1);
			SetBulb(hh,ll+1);
			SetBulb(hh-1,ll);
			SetBulb(hh+1,ll);
		}
		else if(data==0){
			Walls[hh][ll].finish=true;
			Walls[hh][ll].avai=0;
			if(left>=0 && map[hh][left].SGrid==true)
				map[hh][left].CanBulb=false;
			if(right<column && map[hh][right].SGrid==true)
				map[hh][right].CanBulb=false;
			if(down<row && map[down][ll].SGrid==true) 
				map[down][ll].CanBulb=false;
			if(up>=0 && map[up][ll].SGrid==true) 
				map[up][ll].CanBulb=false; 
		}
	}
	
	void zeroandfourtotal(){
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				if(map[i][j].type==4||map[i][j].type==0)
				zeroandfour(i,j);
			}
		}
	} 
	
	//ˢ�º�����������ǽ�������Ϣ����ˢ�� 
	void refresh(){
		int k=0;
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				if(map[i][j].type==1||map[i][j].type==2||map[i][j].type==3){
					if(Walls[i][j].Bulbs==Walls[i][j].type){//����Ѿ�����Ҫ�������ǽ 
						Walls[i][j].finish=true;
						int left=j-1,right=j+1,up=i-1,down=i+1;
						if(left>=0 && map[i][left].SGrid==true)  map[i][left].CanBulb=false;
						if(right<column && map[i][right].SGrid==true)  map[i][right].CanBulb=false;
						if(down<row && map[down][j].SGrid==true)  map[down][j].CanBulb=false;
						if(up>=0 && map[up][j].SGrid==true) map[up][j].CanBulb=false; 
					} 
					int a=0;
					int ll=j-1,rr=j+1,uu=i-1,dd=i+1;
					if(ll>=0&&map[i][ll].CanBulb) a++;
					if(uu>=0&&map[uu][j].CanBulb) a++;
					if(dd<row&&map[dd][j].CanBulb) a++;
					if(rr<column&&map[i][rr].CanBulb) a++;
					Walls[i][j].avai=a;
				}
			}
		}
	} 
	
	//�׶ζ� ������Ψһȷ���Ƶĸ��� 
	//���һ������ǽ��Χ�ܵ���avai���Ѿ�����Ϊ���ݵ�����֮�͵�������ǽ������
	bool onetwothree(int hh,int ll){
		bool ans=false;
		int data=map[hh][ll].type;
		//���Ե� ���õ��� ���Ұ���һ�е��� 
		if(Walls[hh][ll].avai+Walls[hh][ll].Bulbs==data){
				ans=true;
				Walls[hh][ll].finish=true;
				//���������õ��ݵĵط� 
				int left=ll-1,right=ll+1,down=hh+1,up=hh-1;
				int lf=0,rf=0,df=0,uf=0;
				//��Ҫ���㣺���ǵ� û�б����� �����ǵ� 
				if(left>=0 && map[hh][left].IsLight==false && map[hh][left].Lightup==false && map[hh][left].CanBulb==true){
					lf=1;ans=true;
				} 
				if(right<column && map[hh][right].IsLight==false &&map[hh][right].Lightup==false && map[hh][right].CanBulb==true) {
					rf=1;ans=true;
				}
				if(down<row && map[down][ll].IsLight==false &&map[down][ll].Lightup==false&& map[down][ll].CanBulb==true){
					df=1;ans=true;
				}
				if(up>=0 && map[up][ll].IsLight==false &&map[up][ll].Lightup==false &&map[up][ll].CanBulb ==true){
					uf=1;ans=true;
				}
				if(lf==1) SetBulb(hh,left);
				if(rf==1) SetBulb(hh,right);
				if(df==1) SetBulb(down,ll);
				if(uf==1) SetBulb(up,ll);	
		}	
		return ans;	
	} 
	
	bool onetwothreetotal(){
		bool ans=false;
		bool ifdo=false;
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				if(map[i][j].type==1||map[i][j].type==2||map[i][j].type==3){
					if(Walls[i][j].finish) continue;
					ans=onetwothree(i,j);
					if(ans==true) {
						ifdo=true;
						refresh();
					}
				}	
			}
		}
		return ifdo;
	}
	//�������  SGrid�������Ŀ�����Ψһ����������ʹSGrid�������ĸ�������Ϊ����
	bool SetSGrid(){
		int ans=false;
		int k=0;
		int rr;//�� 
		int cc;//�� 
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				if(map[i][j].SGrid==false)continue;
				if(map[i][j].Lightup||map[i][j].IsLight){
					map[i][j].Spo=10;continue;
				}
				int sl=0,sr=0,sd=0,su=0;
				int left=j-1,right=j+1,up=i-1,down=i+1;
				while(left>=0&&map[i][left].type==5){
					if(map[i][left].Lightup||map[i][left].CanBulb==false){
						left--;
					} 
					else{
						sl++;
						left--;	
					}
				}
				while(right<column&&map[i][right].type==5){
					if(map[i][right].Lightup||map[i][right].CanBulb==false) {
						right++;
					}
					else{
						sr++;
						right++;	
					}
				}
				while(up>=0&&map[up][j].type==5){
					if(map[up][j].Lightup||map[up][j].CanBulb==false){
						up--;
					} 
					else{
						su++;
						up--;
					}
				}
				while(down<row&&map[down][j].type==5){
					if(map[down][j].Lightup||map[down][j].CanBulb==false){
						down++;
					} 
					else{
						sd++;
						down++;
					}
				}
				if(map[i][j].CanBulb)  map[i][j].Spo=1+sl+sr+sd+su;
				else if(map[i][j].CanBulb==false)  map[i][j].Spo=sl+sr+sd+su;
			}
		}
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				if(map[i][j].Spo==1&&map[i][j].Lightup==false){//����ֱ�ӵ��� 
					ans=true;
					bool find=false;
					int left=j-1,right=j+1,up=i-1,down=i+1;
					if(map[i][j].CanBulb){
						SetBulb(i,j);break;// ���һ����������Լ� 
					}
					while(find==false&&left>=0&&map[i][left].type==5){
						if(map[i][left].CanBulb==false||map[i][left].Lightup){
							left--;
						} 
						else{
							SetBulb(i,left);
							find=true;
						}
					}
					while(find==false&&right<column&&map[i][right].type==5){
						if(map[i][right].CanBulb==false||map[i][right].Lightup){
							right++;
						} 
						else{
							SetBulb(i,right);
							find=true;
						}
					}
					while(find==false&&up>=0&&map[up][j].type==5){
						if(map[up][j].CanBulb==false||map[up][j].Lightup){
							up--;
						} 
						else{
							SetBulb(up,j);
							find=true;
						}		
					}
					while(find==false&&down<row&&map[down][j].type==5){
						if(map[down][j].CanBulb==false||map[down][j].Lightup){
							down++;
						} 
						else{
							SetBulb(down,j);
							find=true;	
						}
					}
					refresh();
				}
			}
		}
	return ans;	
	} 
	
	bool OneforSGrid(){
		bool ans=false;
		bool ifdo=false;
		ans=SetSGrid();
		if (ans==true) ifdo=true;
		return ifdo;
	}
	//�׶ζ����ܽắ�� 
	void beforeback(){
		bool judge1;
		bool judge2;
		do{ judge1=false;
			judge2=false; 
			refresh();
			judge1=onetwothreetotal();
			judge2=OneforSGrid();
		}while(judge1==true||judge2==true);
	}
	
	//�׶����� �ڻ���֮ǰ����δ��ɵ�����ǽ���г��� 
	//����ǽ1 �ĳ��� 
	void tryofone(int x,int y){
		bool hasdo=false;
		LightUp** tmp1=new LightUp* [row];
		for(int i=0;i<row;i++)
		tmp1[i]=new LightUp[column];
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				tmp1[i][j]=map[i][j];
			}
		}
		NumWall** tmp2=new NumWall* [row];
		for(int i=0;i<row;i++)
		tmp2[i]=new NumWall[column];
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				tmp2[i][j]=Walls[i][j];
			}
		}
		int tmpavai=Walls[x][y].avai;
		int arr[4]={1,1,1,1};	//���ܷŵƣ������˾���0�������ܷŵƾ�һֱ��1������û�Ź����ܷ�Ҳ��1������ͻ�� 
		int left=y-1,right=y+1,up=x-1,down=x+1;
		for(int k=0;k<tmpavai;k++){
			int setx,sety;
			bool set=false;
			if(left>=0&&arr[0]==1&&set==false && map[x][left].CanBulb&&map[x][left].IsLight==false){
				arr[0]=0;
				setx=x;sety=left; 
				set=true;
			} 
			if(right<column && arr[1]==1&&set==false && map[x][right].CanBulb&&map[x][right].IsLight==false) {
				arr[1]=0;
				setx=x;sety=right;
				set=true;
			}
			if(down<row && arr[2]==1&&set==false&& map[down][y].CanBulb&&map[down][y].IsLight==false){
				arr[2]=0;
				setx=down;sety=y;
				set=true;
			}	
			if(up>=0 && arr[3]==1 && set==false && map[up][y].CanBulb && map[up][y].IsLight==false){
				arr[3]=0;
				setx=up;sety=y;
				set=true;
			}
			if(set){
				SetBulb(setx,sety);
				beforeback();
			}
			bool ans=Judge();
			for(int i=0;i<row;i++){
				for(int j=0;j<column;j++){
					Walls[i][j]=tmp2[i][j];
					map[i][j]=tmp1[i][j];
				}
 			}
 			if(ans) continue;		//���ܴ�� 
 			else{
 				hasdo=true;
 				map[setx][sety].CanBulb=false;
 				tmp1[setx][sety].CanBulb=false;
			}
		}
		if(hasdo) refresh();
	}
	//����ǽ2�ĳ��� 
	void tryoftwo(int x,int y){
		bool hasdo=false;
		LightUp** tmp1=new LightUp* [row];
		for(int i=0;i<row;i++)
		tmp1[i]=new LightUp[column];
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				tmp1[i][j]=map[i][j];
			}
		}
		NumWall** tmp2=new NumWall* [row];
		for(int i=0;i<row;i++)
		tmp2[i]=new NumWall[column];
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				tmp2[i][j]=Walls[i][j];
			}
		}
		int k=0,kp=0;
		int arrSGrid1[4]={x,x,x-1,x+1};	//row  �������� 
		int arrSGrid2[4]={y-1,y+1,y,y}; //column
		bool ans;
		if(Walls[x][y].avai==3){
			int setx[3];
			int sety[3];
			while(k<4){
				if(arrSGrid1[k]>=0&&arrSGrid1[k]<row&&arrSGrid2[k]>=0&&arrSGrid2[k]<column){
					if(map[arrSGrid1[k]][arrSGrid2[k]].CanBulb&&map[arrSGrid1[k]][arrSGrid2[k]].IsLight==false){
						setx[kp]=arrSGrid1[k];
						sety[kp]=arrSGrid2[k];
						kp++;
					}
				}
				k++;
			}
			if(Walls[x][y].avai==3&&Walls[x][y].Bulbs==0){
				for(int i=0;i<3;i++){
					int rr=i%3,cc=(i+1)%3;
					SetBulb(setx[rr],sety[rr]);
					SetBulb(setx[cc],sety[cc]);
					beforeback();
					ans=Judge();
					for(int m=0;m<row;m++){
						for(int n=0;n<column;n++){
							Walls[m][n]=tmp2[m][n];
							map[m][n]=tmp1[m][n];
						}
	 			  	}
	 			  	if(ans) continue;
	 		  		else{
	 		  			int kk=0;
	 			  		for(kk;kk<3;kk++){
	 			  			if(kk!=rr&&kk!=cc) break;
						}
						SetBulb(setx[kk],sety[kk]);
						hasdo=true;
						break;
					}
				}
			}
			else if(Walls[x][y].avai==3&&Walls[x][y].Bulbs==1){
				for(int i=0;i<3;i++){
					SetBulb(setx[i],sety[i]);
					beforeback();
					ans=Judge();
					for(int i=0;i<row;i++){
						for(int j=0;j<column;j++){
							Walls[i][j]=tmp2[i][j];
							map[i][j]=tmp1[i][j];
						}
	 			  	}
	 		  		if(ans) continue;
	 		  		else{
	 		  			hasdo=true;
						map[setx[i]][sety[i]].CanBulb=false;
						tmp1[setx[i]][sety[i]].CanBulb=false;
					}
				}
			} 
		}
		else if(Walls[x][y].avai==2){
			int setx[2];
			int sety[2];
			kp=0; 
			while(k<4){
				if(arrSGrid1[k]>=0&&arrSGrid1[k]<row&&arrSGrid2[k]>=0&&arrSGrid2[k]<column){
					if(map[arrSGrid1[k]][arrSGrid2[k]].CanBulb&&map[arrSGrid1[k]][arrSGrid2[k]].IsLight==false){
						setx[kp]=arrSGrid1[k];
						sety[kp]=arrSGrid2[k];
						kp++;
					}
				}
				k++;
			}
			for(int i=0;i<2;i++){
				SetBulb(setx[i],sety[i]);
				beforeback();
				ans=Judge();
				for(int i=0;i<row;i++){
					for(int j=0;j<column;j++){
						Walls[i][j]=tmp2[i][j];
						map[i][j]=tmp1[i][j];
					}
	 		  	}
	 		  	if(ans) continue;
	 		  	else{
	 		  		hasdo=true;
					map[setx[i]][sety[i]].CanBulb=false;
					tmp1[setx[i]][sety[i]].CanBulb=false;
				}
			}
		}
	}
	//����ǽ3�ĳ��� 
	void tryofthree(int x,int y){	 
		LightUp** tmp1=new LightUp* [row];
		for(int i=0;i<row;i++)
		tmp1[i]=new LightUp[column];
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				tmp1[i][j]=map[i][j];
			}
		}
		NumWall** tmp2=new NumWall* [row];
		for(int i=0;i<row;i++)
		tmp2[i]=new NumWall[column];
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				tmp2[i][j]=Walls[i][j];
			}
		}
		
		int tmpavai=Walls[x][y].avai;
		//��ѡ�� 
	 	if(tmpavai==4){
			int arr[4]={1,1,1,1};
			for(int k=0;k<tmpavai;k++){
				cout<<"k "<<k<<endl; 
				int left=y-1,right=y+1,up=x-1,down=x+1;
				int setx,sety;
				bool set=false;
				//�������µ�˳�� 
	 			if(left>=0&&arr[0]==1&&set==false && map[x][left].CanBulb&&map[x][left].IsLight==false){
					arr[0]=0;
					setx=x;sety=left; 
					set=true;
				} 
				if(right<column && arr[1]==1&&set==false && map[x][right].CanBulb&&map[x][right].IsLight==false) {
					arr[1]=0;
					setx=x;sety=right;
					set=true;
				}
				if(up>=0 && arr[2]==1&&set==false && map[up][y].CanBulb&&map[down][y].IsLight==false){
					arr[2]=0;
					setx=up;sety=y;
					set=true;
				}
				if(down<row && arr[3]==1&&set==false&& map[down][y].CanBulb&&map[down][y].IsLight==false){
					arr[3]=0;
					setx=down;sety=y;
					set=true;
				}	
				if(set){
					map[setx][sety].CanBulb=false;
					beforeback();
				}
				bool ans=Judge();
				for(int i=0;i<row;i++){
					for(int j=0;j<column;j++){
						Walls[i][j]=tmp2[i][j];
						map[i][j]=tmp1[i][j];
					}
	 			}
		 		if(ans){
		 			continue; 
				 } 
 				else{//���λ�ò��ܲ���� 
 					map[setx][sety].IsLight=true;
 					tmp1[setx][sety].IsLight=true;
 					SetBulb(setx,sety);
				}
			} 
		}
		if(tmpavai==3){//��ѡ��
			int left=y-1,right=y+1,up=x-1,down=x+1;
			int setx,sety;
			bool set=false;
			int mark[4]; 
			for(int j=0;j<4;j++){
				mark[j]=1;
			}
			//�ҵ��յ�����λ�� 
			if(left>=0 && map[x][left].IsLight==true ){
				mark[0]=0;
			} 
			if(right<column && map[x][right].IsLight==true) {
				mark[1]=0;
			}
			if(up>=0 && map[up][y].IsLight==true){
				mark[2]=0;
			}
			if(down<row && map[down][y].IsLight==true){
				mark[3]=0;
			}
			int arr[4];
			for(int i=0;i<4;i++){
				arr[i]=mark[i];
			}
			for(int k=0;k<tmpavai;k++){
 				if(left>=0&&arr[0]==1&&set==false && map[x][left].CanBulb&&map[x][left].IsLight==false){
					arr[0]=0;
					setx=x;sety=left; 
					set=true;
				} 
				if(right<column && arr[1]==1&&set==false && map[x][right].CanBulb&&map[x][right].IsLight==false) {
					arr[1]=0;
					setx=x;sety=right;
					set=true;
				}
				if(up>=0 && arr[2]==1&&set==false && map[up][y].CanBulb&&map[down][y].IsLight==false){
					arr[2]=0;
					setx=up;sety=y;
					set=true;
				}
				if(down<row && arr[3]==1&&set==false&& map[down][y].CanBulb&&map[down][y].IsLight==false){
					arr[3]=0;
					setx=down;sety=y;
					set=true;
				}				
				if(set){
					map[setx][sety].CanBulb=false;
					beforeback();
				}
				bool ans=Judge();
				for(int i=0;i<row;i++){
					for(int j=0;j<column;j++){
						Walls[i][j]=tmp2[i][j];
						map[i][j]=tmp1[i][j];
					}
 				}
	 			if(ans)	continue; 
				else{//���λ�ò��ܲ���� 
					map[setx][sety].IsLight=true;
					tmp1[setx][sety].IsLight=true;
					SetBulb(setx,sety);
				}
			} 
		}
		if(tmpavai==2){//��ѡһ 
			int left=y-1,right=y+1,up=x-1,down=x+1;
			int setx,sety;
			bool set=false;
			int lf=0,rf=0,df=0,uf=0;
			//�ҵ��յĶ���λ�� 
			int mark[3]; 
			if(left>=0 && map[x][left].IsLight==true ){
				mark[0]=0;
			} 
			if(right<column && map[x][right].IsLight==true) {
				mark[1]=0;
			}
			if(up>=0 && map[up][y].IsLight==true){
				mark[2]=0;
			}
			if(down<row && map[down][y].IsLight==true){
				mark[3]=0;
			}
			int arr[4];
			for(int i=0;i<4;i++){
				arr[i]=mark[i];
			}	
			for(int k=0;k<tmpavai;k++){
	 			if(left>=0&&arr[0]==1&&set==false && map[x][left].CanBulb&&map[x][left].IsLight==false){
					arr[0]=0;
					setx=x;sety=left; 
					set=true;
				} 
				if(right<column && arr[1]==1&&set==false && map[x][right].CanBulb&&map[x][right].IsLight==false) {
					arr[1]=0;
					setx=x;sety=right;
					set=true;
				}
				if(up>=0 && arr[2]==1&&set==false && map[up][y].CanBulb&&map[down][y].IsLight==false){
					arr[2]=0;
					setx=up;sety=y;
					set=true;
				}
				if(down<row && arr[3]==1&&set==false&& map[down][y].CanBulb&&map[down][y].IsLight==false){
					arr[3]=0;
					setx=down;sety=y;
					set=true;
				}	
				
				if(set){
					map[setx][sety].CanBulb=false;
					beforeback();
				}
				bool ans=Judge();
				for(int i=0;i<row;i++){
					for(int j=0;j<column;j++){
						Walls[i][j]=tmp2[i][j];
						map[i][j]=tmp1[i][j];
					}
	 			}
		 		if(ans)	continue; 
 				else{//���λ�ò��ܲ���� 
 					map[setx][sety].IsLight=true;
 					tmp1[setx][sety].IsLight=true;
 					SetBulb(setx,sety);
				}
			} 
		}
		beforeback();
	}
	//����ǽ1��2��ȫ�ֺ���	
	void firsttry(){
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				if(map[i][j].type!=1&&map[i][j].type!=2) continue;
				if(Walls[i][j].finish) continue;
				if(map[i][j].type==1) tryofone(i,j);
				if(map[i][j].type==2) {
					if(Walls[i][j].avai==4&&Walls[i][j].Bulbs==0) continue;
					tryoftwo(i,j);
				} 
			}
		}
		beforeback();
	}
	//����ǽ3��ȫ�ֺ��� 
	void secondtry(){ 
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				if(map[i][j].type==3&&Walls[i][j].finish==false){
					tryofthree(i,j);
				}
			}
		}
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				if(map[i][j].IsLight==true && map[i][j].Lightup==false){
					SetBulb(i,j);
					refresh();
				}
			}
		}
		beforeback();
	}
	
	//�׶��ģ����� 
	bool Judge(){//�жϺ��� ������ĵƻ᲻�����ì�� 
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				if(map[i][j].SGrid){
					if(map[i][j].Spo<1)	return false;
			    }
			    else if(map[i][j].type==1||map[i][j].type==2||map[i][j].type==3){
					if(Walls[i][j].Bulbs>Walls[i][j].type||(Walls[i][j].avai<Walls[i][j].type-Walls[i][j].Bulbs)){
						return false;
					}
			    }
			}
		}
		return true;	
	}
	 
	bool backtrack(int t){//���ݺ��� 
    	if(t==row*column) return true;//ȫ�������� 
    	//�ǲ���δ��ɵ�����ǽ 
		int x=t/column;//��tȷ��λ�� 
    	int y=t%column;
    	if(map[x][y].type==5 || map[x][y].type==-1 ||Walls[x][y].finish==true){//����ǵĻ� ���� �����ǵĻ� t+1
    		return backtrack(t+1);
		}
    	//����ͼ 
		LightUp** tmp1=new LightUp* [row];
		for(int i=0;i<row;i++)
		tmp1[i]=new LightUp[column];
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				tmp1[i][j]=map[i][j];
			}
		}
		NumWall** tmp2=new NumWall* [row];
		for(int i=0;i<row;i++)
		tmp2[i]=new NumWall[column];
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				tmp2[i][j]=Walls[i][j];
			}
		}
		int tmpavai=Walls[x][y].avai;			//�������ǽ��Χ��tmpavai�����ӿ��Էŵ� 
		int flag=0;
        for(int k=0;k<tmpavai;k++){
        	int left=y-1,right=y+1,up=x-1,down=x+1;
			int setx,sety;								//��¼Ҫ������ŵ� 
			bool set=false;
			if(left>=0&&set==false && map[x][left].CanBulb&&map[x][left].IsLight==false){
				setx=x;sety=left; 
				set=true;
			} 
			if(right<column && set==false && map[x][right].CanBulb&&map[x][right].IsLight==false) {
				setx=x;sety=right;
				set=true;
			}
			if(down<row && set==false&& map[down][y].CanBulb&&map[down][y].IsLight==false){
				setx=down;sety=y;
				set=true;
			}	
			if(up>=0 && set==false && map[up][y].CanBulb&&map[up][y].IsLight==false){
				setx=up;sety=y;
				set=true;
			}
			if(set){					//����еط��ŵƣ���setbulb��setx��sety�� 
				SetBulb(setx,sety);
				beforeback();			//���������֮��������Ķ����� 
				firsttry();
   				secondtry();
			}
			if(Judge()==false){
				for(int i=0;i<row;i++){		//��ͼ���ƻ�ȥ 
					for(int j=0;j<column;j++){
						Walls[i][j]=tmp2[i][j];
						map[i][j]=tmp1[i][j];
					}
	 		  	}
	 		  	map[setx][sety].CanBulb=false;
	 		  	tmp1[setx][sety].CanBulb=false; //���ﲻ�ܷŵƣ�����һ����� 
	 		  	continue;    //��������Ե�����������ˣ������ˣ����˳���returnfalse 
			}
          	if(backtrack(t+1)) return true;		//����һ������ǽ�����г��Ե�� 
          	else{
          		 for(int i=0;i<row;i++){		//��ͼ���ƻ�ȥ 
					for(int j=0;j<column;j++){
						Walls[i][j]=tmp2[i][j];
						map[i][j]=tmp1[i][j];
					}
	 		  	}
	 		  	map[setx][sety].CanBulb=false; 
          		tmp1[setx][sety].CanBulb=false; 
			}
		}
		return false;
    }
	
	void backtrackJudge(){			 
     	for(int x=0;x<row;x++){
     		for(int y=0;y<column;y++){
     			if((map[x][y].type==3 || map[x][y].type==2 || map[x][y].type==1)&&Walls[x][y].finish==false){ 
				 	backtrack(x*column+y);
				}
			}
   		}
   	} 
	
	//�׶��壺�����ӡ 
	void LightupNormal(){//������SGrid 
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				if(map[i][j].SGrid==false && map[i][j].Lightup==false&& map[i][j].IsLight ==false)
					map[i][j].IsLight=true;
			}
		}
	}

	void printakari(){//��ӡ����	
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				if(map[i][j].type==-1) cout<<" X ";
				else if(map[i][j].type==0||map[i][j].type==1||map[i][j].type==2||map[i][j].type==3||map[i][j].type==4) cout<<" "<<map[i][j].type<<" ";
				else if(map[i][j].type==5&&map[i][j].IsLight == true) cout<<" ! ";
				else if(map[i][j].type==5&&map[i][j].IsLight == false&&map[i][j].Lightup==false) cout<<" - ";
				else if(map[i][j].type==5&&map[i][j].IsLight == false&&map[i][j].Lightup==true) cout<<" * ";
			} 
			cout<<endl;
		}
	}
};

int main(){
	cout<<"row and column of Akari: ";
	int h;
	int l;
	string s;
	cin>>h>>l;
	cout<<endl;
	cout<<"string of Akari: ";
	cin>>s;
	cout<<endl; 
/*	string s="....10...1.0X...1......X..1...X..2....1.X....0.X....X.1....X.4....2..X...X..1......2...X3.X...XX....";
	string s1="1........1...X.......X...2..X........1.....4............2.....2........X..2...X.......0...1........1" ;
	string s20="..X....................0.X.X0.X..1.X.20......X.......22.X.....2.X....2..XX...2.0X..................X1.0...XX..X....0.X.....X.X2.......X......X3.X.X..X.X2.1.X....................X.."; 
	string s660="....3........1......X....0.X.....X...X...XX..X.X1...0.....1........1....2..X..X..X....X..X...0.X..1..X..1....X.....X....1...0..2...4....X.....X....X..2..X..4.X...X..1....1..2..X..3....2........1.....2...X0.X..2X...1...X.....0.2....1......0........1.... " ;
	string s400="...................1XX3..X..XXX0....2.X...X...0.X..X....2X...XX....1........2................0.........1....0...1....X..1X...X...X...21.1....1.....1....1.X1...1...1...1X..1....X...0....2.........1................1........1....XX...X2....1..X.X...X...1.0....1X10..0..2XX0...................";
	string s14="..2.X..X.....X.3..X................X.0...21.X..X....X..2.X2...X.X................X..X.2.....3..2.2..";
	string s718="X.....1..........X.....X..3.X...X.X..X.X...1.2...2...X.2...X1...X.1...2....X.....X....2.....1....1...X.X...1X...1.1...0...X.1...0.1..X.X...2.X..X.....1.......1..1.....XX.....1..3.......X.....X..0.0...X.2..X.X...1.2...1...X.1...X2...X.0...X....2.....X....X.....0....3...X.1...10...3.X...2...3.1...2.1..X.3...X.2..X.....1..........1.....0" ;
	string s483="....1.........2...1.1.X...2....X..X........2...X...X..1..X...1.....1........X.2...1.X...X1.3..1..2..1.....1....X......X..1.X...1......X..X.....X.1....1..1....1.2.....X..1......1...1.X..X......X....2.....X..X..0..2.11...2.1...1.X........1.....X...1..2..X...1...X........1..1....1...1.1.X...X.........1....";
	string s490="...1...X...2.1......0...X...X......0..1...1...4...XX.0..X....X..X..X......X...X....1.....2..1...2..0.....X....2..X...X....X.1...1......X.....2....1.X.X0....X........X......X.2.1.121X.X.X.X......X........1....01.3.X....X.....X......X...1.X....X...2..X....X.....3..X...1..1.....1....2...1......X..2..1....1..X.11...X...X...X..X......X...1...X......X.0...1...1...";
	string s700="..1...1...1....X...2......3....1...1...2..1....1..1..1...3.....2...1...X......X.....X....1..1...X......1.1......1..X.X.......0...X..1...X..1...1....1.X..X....X...........2.........1.1....3...1..2..1...2...1..2...X..2....X....1..2....1..1.......4.....1........X...X....1..X.....X.....3..X.....1......1.X..X...2..X.......1......2......0......1.......1..1...2..X.X......X.....X..1.....1.....X..1....X...1........0.....3.......1..X....X..X....X....2..X...X..1...3...X..1..X...2....X.X.........2...........X....X..X.X....X...X..X...X..1...X.......X.X..1......1.1......1...2..3....1.....2......1...1...2.....X...1..1..3....1..2...1...X....X......1...X....1...1...0..";
	string s768="..1..X.....X..1..........1........X..20...1...2X..0..................1...1X...1X...X....X....X....X....2.1.X.....0.0.2........2.X.......X.0.X...1...1.X.X.......X.X........1.1.1.....X.X.1....1....X....1....X...XX...11...1..................X..10...X...21..1........1..........0..1.....1..X..";
	string s639="X.......X..01..X.......X.2.2.X.1........X.X.X.3...........1..2...........1...0..0.X..X.X..X...X.....X....X....X....1.......X...X1.1..2.X0...X...X.1..X......1.....2..X.X1.0..1.....1......2..X.1...X...XX.X..X.XX...2.......2....2....1....X.....1...1..X.2..X.2..X...0...........X..2...........2.1.1.X........X.X.1.0.1.......1..XX..1.......X";
	string s50=".1.....X...2.X...X.XX.....X1.1...3.........X.0.X......1...X...1..X.2.....0..X....X............0...XX..1.XX.1..3...0.....1.0X2....1..X..X......1......1..1......X................X......X..1......1......0..1..1....2XX.1.....2...0..2.0X.X..1X...0............X....X..X.....X.2..1...X...3......0.1.X.........0...2.12.....1X.1...2.2...0.....X.";
	string s446="..1....................1...X..2..1XXX1..XXXX........X..2...1...1....0...02..0...2..X..1...2..X......1....2...X...1....0....2......2..1..X...1.....2...X....2....1..X........1..1....2....X...0.....X...X..X..2......0....X....0...2...2....X......1..1...2..1..2...X..XX...1....X...X...2..X........XX1X..XXXXX..2..1...1....................2..";
	string s119="0....0....XX...1.....XXX.......0........X2.1...X1.1..1..1...1X..............1.......X.......3.......1..X.0.........2.2..XXX......X0...0.X......3....0.....XXX.1X....1......1....1X.2XX.....1....X......2.X...X0......1XX..X.1.........X.0..1.......1.......X.......X..............X2...1..2..1.XX...1.2X........X.......X00.....0...X1....X....0";
	string s740="......0..2..2.......X..3.....1.....2..X.....X...X...X.....1..0...0.X......X.....X...1...X.1..X..1..1...4..1...1.X..1....X.......X......X..1...X....1...X...2..1.1...X..X......1...X....2...2..X.....1.0...X..0....0....3...X..X....1......X..1..X.....X.......X....X..X..X...1..X..X..1....X......3...X..1..1......1..X..1.1...2..2...2..2..X...1..1.....X.....X..X.........1...1........X...1........X...X.........2..1.....X.....X..1...X..X..2...1..1...2.1..1..1......X..2..2...1......X....1..X..0..X...X..X..X....X.......X.....X..1..2......X....2..X...X....1....X..X...3.X.....X..2...1....X...1......1..X...1.2..2...X...X....1...1..X......1.......X....X..2.1...1..1...1..X..2..0.X...2...2.....1......1.2...4..X.....2...3...X.....X..1.....X.....1..1.......X..1..2......"; */
	
	Akari a(s,h,l);
	cout<<"---------------start---------------"<<endl;
	a.printakari();
	cout<<"---------------stage1---------------"<<endl;
   	a.zeroandfourtotal();
   	a.printakari();  
   	cout<<"---------------stage2---------------"<<endl;
   	//a.refresh();
	a.beforeback();
   	a.printakari(); 
   	cout<<"---------------stage3---------------"<<endl;
   	a.firsttry();
   	a.secondtry();
   	a.refresh();
   	a.printakari();
   	cout<<"---------------stage4:Backtrack---------------"<<endl;
   	a.backtrackJudge();	
   	a.printakari();
   	cout<<"---------------Solution---------------"<<endl;
   	a.LightupNormal();
   	a.printakari();
	return 0;
}


 


