#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
#include<unordered_map>
#include<utility>
#include<fstream>
#include<string>
using namespace std;
vector<int>charFreq(256,0);
struct Node
{
	char data;
	unsigned freq;
	string code;
	Node *left, *right;
	Node(char data, unsigned freq)
	{
		left=NULL;
		right=NULL;
		this->data=data;
		this->freq=freq;
		code="";
	}
};
struct Compare
{
	bool operator()(Node *l, Node *r)
	{
		return l->freq>r->freq;
	}
};
void printCode(Node* root, string s, vector<string>&result)
{
	if(root==NULL)
	{
		return ;
	}
	if(root->data!='$')
	{
		result[root->data]=s;
		root->code=s;
		//cout<<root->data<<"  "<<s<<endl;
	}
	printCode(root->left, s+"0", result);
	printCode(root->right, s+"1", result);
}
Node* huffmancode()
{
	priority_queue<Node*, vector<Node*>, Compare> pq;
	Node*left,*right;
	for(int i=0;i<256;i++)
	{
		if(charFreq[i]>0)
		{
			pq.push(new Node(char(i), charFreq[i]));
		}
	}
	while(pq.size()>1)	
	{
		left=pq.top();
		pq.pop();
		right=pq.top();
		pq.pop();
		Node* top=new Node('$', left->freq+right->freq);
		top->left=left;
		top->right=right;
		pq.push(top);
	}
	//vector<string>result(256);
	//printCode(pq.top(), "", result);
	return pq.top();
}
string decompress(string s, Node* root)
{
	int n=s.size(), i=0;
	Node*temp=root;
	string ans="";
	while(i<n)
	{
		if(s[i]=='0')
		{
			temp=temp->left;
			i++;
		}
		else
		{
			temp=temp->right;
			i++;
		}
		if(temp->data!='$')
		{
			ans=temp->data+ans;
			temp=root;
		}
	}
	return ans;
}
int main()
{
	string filename;
	cout<<"Enter File Name:";
	cin>>filename;
	//ifstream read("newf.txt");
	ifstream read(filename);
	string result;
	string text;
	while(getline(read,text))
	{
		result+=text;
	}
	for(int i=0;i<result.size();i++)
	{
		charFreq[result[i]]++;
	}
	
	
	Node* tree=huffmancode();
	vector<string>charResult(256);
	printCode(tree, "", charResult);
	for(int i=0;i<256;i++)
	{
		if(charFreq[i]!=0)
		{
			cout<<char(i)<<": "<<charResult[i]<<endl;
		}
	}
	string ans="";
	for(int i=0;i<result.size();i++)
	{
		ans+=charResult[result[i]];
	}
	cout<<result<<endl;
	cout<<ans<<endl;
	string decomp=decompress(ans,tree);
	cout<<decomp<<endl;
	read.close();
	return 0;	
}
