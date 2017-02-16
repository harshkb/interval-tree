// interval tree operation function insert ,search ,delete,print

#include<bits/stdc++.h>
using namespace std;
# define pp pair<int,int>

class node         							 // interval node
{

   public:
    pp data;
    int maxn;
    node*left;
    node*right;
};
node* newnodeform(pp *interval)  					//formation of new node and assign pointer and interval
{
    node* newnode=new node();
    newnode->left=0;
    newnode->right=0;
    newnode->data=*interval;
    newnode->maxn=interval->second;
}
node* insertnode(node* root,pp *interval)   				// insertion of new node form into interval tree
{
    int value=interval->first;
    if(root==0)
    {
        return(newnodeform(interval));
    }
    if(root->data.first>value)
            root->left=insertnode(root->left,interval);
    else
           root->right=insertnode(root->right,interval);
    if(root->maxn<interval->second)
            root->maxn=interval->second;
            return(root);
}
 void print(node*root)              					// print the interval tree
 {
     if(root==0)
        return ;
     else{
      print(root->left);
      cout<<"("<<root->data.first<<","<<root->data.second<<") max ="<<root->maxn<<endl;
      print(root->right);
     }
 }

pp *searchinterval(node*root,pp*pairf)     				  //search an interval in a interval tree
{
    if(root==0)
    return 0 ;
    if(root->data.first<=pairf->second&&pairf->first<=root->data.second)
        {
          return &(root->data);
        }
        if(root->left!=0&&root->left->maxn>=pairf->first)
            return searchinterval(root->left,pairf);
        return searchinterval(root->right,pairf);
}
  node* moveright(node* nnode)      					// move right in an interval tree
{
	if(nnode->right == 0)return nnode;
	return moveright(nnode->right);
}

node* moveleft(node* nnode)         					 // move left in an interval tree
{
	if(nnode->left == 0)return nnode;
	return moveleft(nnode->left);
}


void deleteinterval(node*root,pp* interval)   				 //delete an interval from an interval tree
{

    if(root->data.first==interval->first&&root->data.second==interval->second)
    {
        if(root->right!= 0)
		{
			node* temp = moveleft(root->right);
			root->data.second = temp->data.second;
			root->data.first = temp->data.first;
			root->maxn = temp->maxn;
			temp = 0;
		}
		if(root->left != 0)
		{
			node* temp = moveright(root->left);
			root->data.second = temp->data.second;
			root->data.first = temp->data.first;
			root->maxn = temp->maxn;
			temp = 0;
		}
		else{
			root = 0;
		}
         root=0;
		return  ;

    }
    if(root->data.first >= interval->first)
	{
		deleteinterval(root->left,interval);
	}
	else{
		deleteinterval(root->right,interval);
	}
}

int main()
{

    int n;
	cout<<"Enter the number of interval to insert and the interval"<<endl;
    cin>>n;
    pp a[n];
    int i=0;
    node*root;
    root=0;

    while(i<n)
    {
        int first,second;
        cin>>first>>second;
        a[i]=make_pair(first,second);
        root=insertnode(root,a+i);
        i++;
    }
     cout<<"interval tree form after insertion is "<<endl;
     print(root);
     cout<<endl;
	
	int p,b;
 cin>>p>>b;       							// input interval for deletion
pp  f =make_pair(p,b);
  deleteinterval(root,&f);
  cout<<"("<<p<<","<<b<<") is deleted"<<endl;
	
    int u=0;          							 // Search two interval
    while(u<2)
    {

  int p,b;
  cin>>p>>b;         							 //input interval for search
 pp f =make_pair(p,b);
  pp *overlap =searchinterval(root,&f);
  if(overlap==0)
    cout<<"not found"<<endl;
  else
 cout<<"("<<p<<","<<b<<") is "<<"interval match  to("<< overlap->first<<","<<overlap->second<<")"<<endl;
 u++;
    }
 cout<<"Press 0 to exit, 1 to insert , 2 to delete , 3 to search"<<endl;
	 int input=5;
	while(input!=0)
	{	cin>>input;
	      if(input==1)
	      {
	      		int p,b;
 			cin>>p>>b;       		
			pp  f =make_pair(p,b);
		      root=insertnode(root,&f);
	      }
	 	if(input==2)
		{
			int p,b;
			 cin>>p>>b;       					
			pp  f =make_pair(p,b);
 			 deleteinterval(root,&f);
			  cout<<"("<<p<<","<<b<<") is deleted"<<endl;
		}
	 	 if(input ==3)
	  	{
	      		int p,b;
			  cin>>p>>b;         							 
			 pp f =make_pair(p,b);
			  pp *overlap =searchinterval(root,&f);
			  if(overlap==0)
			    cout<<"not found"<<endl;
			  else
			 cout<<"("<<p<<","<<b<<") is "<<"interval match  to("<< overlap->first<<","<<overlap->second<<")"<<endl;
	  
	 	 }
	}

}

// (15,20) is interval for deletion
// (14,16) and (21,23) are interval for search
/*
Input
6
15 20
10 30
17 19
5 20
12 15
30 40
15 20                          
14 16
21 23

*/

