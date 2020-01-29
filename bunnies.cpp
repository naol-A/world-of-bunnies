/*

world of bunnies v0.1
written by: naol arega

*/
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>

using namespace std;

//dictionary of different data
int male,prev_male,female,prev_female,mutant,chance,normal;
string sexDict[4]={"male","female","female","male"};
string colorDict[5]={"white","brown","black","spotted"};
string nameDict[8]={"thumper","oreo","bun","coco","daisy mae","bugs bunny","midnight","angel"};

struct bunny{       //data structure for linked list
	string sex;
	string color;
	int age;
	string name;
	bool mutant;
	bunny *next;
}*ancester=NULL;

//prints out detail on to the screen
void report(){
    cout<<endl<<"   reporting"<<endl;
    bunny *temp=ancester;
    mutant=0;
    normal=0;
    if(temp==NULL){
        cout<<"--bunnies are extinct--"<<endl;
        exit(0);
    }
    else
    while(temp->next!=NULL){
        if(temp->age<1){
            cout<<"just born...";
        }
        cout<<"name: "<<temp->name<<" | ";
        cout<<"age: "<<temp->age<<" | ";
        cout<<"sex: "<<temp->sex<<" | ";
        cout<<"color: "<<temp->color<<" | ";
        cout<<"mutation: "<<temp->mutant<<" | "<<endl;
        if(temp->mutant==false){
            if(temp->sex=="female"&&temp->age==2){
                female++;
            }
            else if(temp->sex=="male"&&temp->age==2){
                male++;
            }
            normal++;
        }
        else if(temp->mutant==true){
            mutant++;
        }
        temp=temp->next;
        }
        if(temp->age<1){
            cout<<"just born...";
        }
        cout<<"name: "<<temp->name<<" | ";
        cout<<"age: "<<temp->age<<" | ";
        cout<<"sex: "<<temp->sex<<" | ";
        cout<<"color: "<<temp->color<<" | ";
        cout<<"mutation: "<<temp->mutant<<" | "<<endl;
        if(temp->mutant==false){
            if(temp->sex=="female"&&temp->age==2){
                female++;
            }
            else if(temp->sex=="male"&&temp->age==2){
                male++;
            }
            normal++;
        }
        else if(temp->mutant==true){
            mutant++;
        }
    cout<<"---------------------------------------------------"<<endl;
    cout<<"females: "<<female<<" male: "<<male
        <<" prev_female: "<<prev_female
        <<" prev_male: "<<prev_male
        <<" mutant: "<<mutant
        <<" regular: "<<normal
        <<" total population: "<<mutant+normal<<endl;

    cout<<"   end of report"<<endl;
}

//creates 5 bunnies at the start
void init(){
    cout<<"intializing";
	srand(time(0));
	for(int i=0;i<5;i++){
        bunny *forerunners=new bunny;
		forerunners->sex=sexDict[rand()%3];
		forerunners->color=colorDict[rand()%3];
		forerunners->age=0;
		forerunners->name=nameDict[rand()%7];
        if(rand()%99==1||rand()%99==2){
            forerunners->mutant=true;
        }
        else{
            forerunners->mutant=false;
        }
		if(ancester==NULL){
			ancester=forerunners;
			forerunners->next=NULL;
			cout<<".";
		}
		else{
            bunny *temp=ancester;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            if(temp->next==NULL){
                temp->next=forerunners;
                forerunners->next=NULL;
                cout<<".";
            }
		}
	}
    report();
}

//kills passed bunny in the parameter
void killBunny(bunny *toBeKilled){
    cout<<toBeKilled->name<<" died"<<endl;
    bunny *temp=ancester;
    bunny *temp2;
    if(toBeKilled->sex=="female")
        if(female!=0)
            female--;
    else if(toBeKilled->sex=="male"){
        if(male!=0)
            male--;
    }
    while(temp->next!=NULL&&temp!=toBeKilled){
        temp2=temp;
        temp=temp->next;
    }
    if(temp==toBeKilled&&temp!=ancester){
        temp2->next=temp->next;
        delete temp;
    }
    else if(toBeKilled==ancester){
        if(toBeKilled->next==NULL){
            ancester=NULL;
            delete temp;
        }
        else{
            ancester=ancester->next;
            delete temp;
        }
    }
    else if(temp==toBeKilled&&temp->next==NULL){
        temp2->next=NULL;
        delete temp;
    }
}

//creates a new bunny as same color as his/her mother
void newBunny(string motherColor){
    bunny *newborn=new bunny;
    newborn->sex=sexDict[rand()%3];
	newborn->color=colorDict[rand()%4];
	newborn->age=0;
	newborn->name=nameDict[rand()%7];
	chance=rand()%99;
	if(chance==1||chance==2){
        newborn->mutant=true;
	}
	else{
        newborn->mutant=false;
	}
	if(ancester==NULL){
		ancester=newborn;
		newborn->next=NULL;
	}
	else{
        bunny *temp=ancester;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        if(temp->next==NULL){
            temp->next=newborn;
            newborn->next=NULL;
        }
	}
}

//this is the main loop for world of bunnies
void main_loop(){
    int lucky=100;
    cout<<endl<<"::main loop::"<<endl;
    for(;;){   //loops until k is pressed and half of them die
        _sleep(500);
        bunny *temp=ancester;
        //bunnies age here
        while(temp->next!=NULL){
            if(temp->age==10&&temp->mutant==false){   //if normals reach 10 age  they die
                killBunny(temp);}
            else if(temp->age==20&&temp->mutant==true){ //if mutants reach age 50 they die
                killBunny(temp);}
            else{
                temp->age++;}
            temp=temp->next;
        }
        if(temp->age==10&&temp->mutant==false){
            killBunny(temp);}
        else if(temp->age==20&&temp->mutant==true){
            killBunny(temp);}
        else{
            temp->age++;}
        //end of aging
        //mutants turn normals
        if(mutant>0&&normal>0){
            int mnt=mutant;
            bunny *temp=ancester;
            cout<<"mnt: "<<mnt<<endl;
            while(mnt>0){
                if(normal<=0){
                    mnt=0;
                }
                else{
                    temp=ancester;
                    while(temp->next!=NULL&&normal>0){
                        if(temp->mutant==false&&rand()%2==0&&mnt>0){
                            temp->mutant=true;
                            cout<<temp->name<<" become mutant"<<endl;
                            mnt--;
                            normal--;
                        }
                        temp=temp->next;
                    }
                    if(temp->mutant==false&&rand()%2==0&&mnt>0){
                        temp->mutant=true;
                        cout<<temp->name<<" become mutant"<<endl;
                        mnt--;
                        normal--;
                    }
                }
            }
        }
        //end of mutation epidemic
        //reproduction cycle
        if(prev_male!=0&&prev_female!=0){
            bunny *temp=ancester;
            for(int i=0;i<prev_female;i++){
                while(temp->next!=NULL){
                    if(temp->sex=="female"){
                        cout<<"adult female found"<<endl;
                        break;
                    }
                    temp=temp->next;
                }
                if((temp->next==NULL&&temp->sex=="female"&&temp->mutant==false)||
                    temp->sex=="female"&&temp->mutant==false){   //mutants and children are excluded from reproduction cycle
                    newBunny(temp->color);
                    temp=temp->next;
                }
            }
            prev_female=female;
            prev_male=male;
        }//end of reproduction cycle
        prev_female=female;
        prev_male=male;
        if(male+female>100){   //half of the population dies when maxed
            bunny *temp=ancester;
            while(temp->next!=NULL){
                temp=temp->next;
                if(lucky%2==0){
                    killBunny(temp);
                }
                lucky--;
            }
        }
        report();
    }
}


int main(){
    init();// 5 bunnies are created
    main_loop();
	return 0;
}
