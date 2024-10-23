#include <iostream>
#include <iomanip>
#include <list>
#define VAT 7
#define SERVICE 10
using namespace std;

class Node{
  public:
    int many;
    string name;
    double price;

  Node(int m,string n,double p){
    many = m;
    name = n;
    price = p;
  }
};

class LinkedList{
  public:
    list <Node> node;

  void add(int many,string name,double price){
    if(many > 0 && price > 0){
      if(!Duplicate(name)){
        Node obj = Node(many,name,price);
        node.push_back(obj);
      }else{
        list <Node>::iterator tpr = node.begin();
        for(int i=0;i<node.size();i++,tpr++){
          if(tpr->name == name && tpr->price == price){
            tpr->many += many;
            break;
          }
        }
      }print();
    }else{
      print();
    }
  }

  void Edit(int n){
    if(!node.empty()){
      if(n > 0 && n <= node.size()){
        int many;
        double price;
        list <Node>::iterator tpr = node.begin();
        advance(tpr,n-1);
        cout<<"\n--------------------------------"<<endl;
        cout<<tpr->many<<" "<<tpr->name<<" "<<tpr->price<<endl;
        cout<<"--------------------------------"<<endl<<endl;
        do{
          cout<<": ";
          cin>>many>>price;
        }while(many <= 0 || price <= 0);
        tpr->many = many;
        tpr->price = price;
        print();	
      }else{
        cout<<"\n--------------------------------"<<endl;
        cout<<n<<" Not in the product"<<endl;
        cout<<"--------------------------------"<<endl<<endl;
      }
    }else{
      print();
    }
  }

  void Delete(int n){
    if(!node.empty()){
      if(n > 0 && n <= node.size()){
        list <Node>::iterator tpr = node.begin();
        advance(tpr,n-1);
        node.erase(tpr);
        print();
      }else{
        cout<<"\n--------------------------------"<<endl;
        cout<<n<<" Not in the product"<<endl;
        cout<<"--------------------------------"<<endl<<endl;
      }

    }else{
      print();
    }
  }

  bool Duplicate(string n){
    if(!node.empty()){
      list <Node>::iterator tpr = node.begin();
      for(int i=0;i<node.size();i++,tpr++){
        if(tpr->name == n){
          return 1;
          break;	
        }
      }
    }return 0;
  }

  void print(){
    if(!node.empty()){
      double total=0,vat=0,service=0;
      list <Node>::iterator tpr = node.begin();
      cout<<"\n--------------------------------"<<endl;
      for(int i=0;i<node.size();i++){
        cout<<i+1<<". "<<tpr->many<<" "<<tpr->name<<" "<<tpr->price<<endl;
        total += tpr->many * tpr->price;
        vat = (total * VAT) / 100; 
        service = (total * SERVICE) / 100; 
        ++tpr;
      }
      cout<<"--------------------------------"<<endl;
      cout<<"SUB TOTAL: "<<setprecision(3)<<total<<endl;
      cout<<"VAT 7%: "<<setprecision(3)<<vat<<endl;
      cout<<"SERVICE 10%: "<<setprecision(3)<<service<<endl;
      cout<<"--------------------------------"<<endl;
      cout<<"TOTAL: "<<setprecision(3)<<(total + vat + service)<<endl;
      cout<<"--------------------------------"<<endl<<endl;
    }else{
      cout<<"\n--------------------------------"<<endl;
      cout<<"Product is empty"<<endl;
      cout<<"--------------------------------"<<endl<<endl;
    }
  }

  void ImportFile(FILE *file){
    list <Node>::iterator tpr = node.begin();
    for(int i=0;i<node.size();i++,tpr++){
      fprintf(file,"%d %s %.2f\n",tpr->many,tpr->name.c_str(),tpr->price);
    }
  }	

};

int main(){
  char cmp;
  int many,n;
  string name;
  double price;
  LinkedList l;
  FILE *file = fopen("XOBAZJR.csv","a");
  
  cout<<"XOBAZJR"<<endl;	

  while(true){
  	cout<<"--------"<<endl;
  	cout<<"- P: push product"<<endl;
  	cout<<"- D: delete product"<<endl;
  	cout<<"- E: edit product"<<endl;
  	cout<<"- X: exit programe"<<endl<<endl;
  
    cout<<": ";
    cin>>cmp;

    if(cmp == 'P'){
      cin>>many>>name>>price;
      l.add(many,name,price);
    }else if(cmp == 'D'){
      cin>>n;
      l.Delete(n);
    }else if(cmp == 'E'){
      cin>>n;
      l.Edit(n);	
    }else if(cmp == 'X'){
    	break;	
	}else{
      cout<<"\n--------------------------------"<<endl;
      cout<<cmp<<" Command is invalid"<<endl;
      cout<<"--------------------------------"<<endl;
    }
  }

  l.print();
  l.ImportFile(file);
  cout<<"--------------------------------"<<endl;
  cout<<"Close the program"<<endl;
  cout<<"--------------------------------"<<endl;

  return 0;
}
