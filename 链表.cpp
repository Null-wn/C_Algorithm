#include<iostream>
#include<cstdlib>
using namespace std;

class list{
	public:
		int data;
		class list *next;
};
typedef class list node;
typedef node *link;

link FindNode(link head,int position_data){
	link phead;
	phead = head;
	while(phead != NULL){
		if(phead->data == position_data)return phead;
		phead = phead->next;
	}
	return phead;
}

link InsertNode(link head,int position_data,int data){
	link phead = new node;
	phead = FindNode(head,position_data);
	link insertnode = new node;
	if(!insertnode) return NULL;
	insertnode->data = data;
	insertnode->next = NULL;
	if(phead == NULL){  //插入第一个节点
		insertnode->next = head;
		return insertnode;
	} 
	else if(phead->next == NULL) phead->next = insertnode;  //插入最后一个节点
	else{  //插入中间节点 
		insertnode->next = phead->next;
		phead->next = insertnode;
	}
	return head; 
}

link DeleteNode(link head,int position_data){
	link top = head;  //保留头指针 
	link phead = FindNode(head,position_data);
	if(head == phead){  //删除头结点 
		head = head->next;
		delete phead;
	}
	else{
		while(top->next != phead) top = top->next;
		if(phead->next == NULL){  //删除尾结点 
			top->next = NULL;
			delete phead;
		}
		else{
			top->next = phead->next;
			delete phead;
		} 
	}
	return head;
}

link CreateList(int a[],int n){
	link head,phead,newnode;
	phead = new node;
	if(!phead) return NULL;
	phead->data = a[0];
	head = phead;
	for(int i = 1;i<n;i++){
		newnode = new node;
		newnode->data = a[i];
		newnode->next = NULL;
		phead->next = newnode;
		phead = phead->next;
	}
	return head;
}

 void PrintList(link head){
	link phead = new node;
	phead = head;
	cout<<"链表元素如下: "<<endl;
	while(phead!=NULL){
		cout<<phead->data<<"->";
		head = phead;
		phead = phead->next;  //phead按序往后遍历整个链表
		if(!phead) cout<<"NULL"<<endl;
	}
}

int main(){
	int position_data,data;
	link head,phead;
	int n;
	cout<<"请输入初始链表元素个数: "<<endl;
	cin>>n;
	int a[n];
	cout<<"请依次输入链表元素: ";
	for(int i = 0;i<n;i++) cin>>a[i];
	head = CreateList(a,n);
	PrintList(head);
	cout<<"请输入预插入位置之前的元素和要插入的元素（例：5 8）: ";
	cin>>position_data>>data;
	head = InsertNode(head,position_data,data);
	cout<<"插入之后的";
	PrintList(head); 
	cout<<"请输入想删除的链表元素: ";
	cin>>position_data;
	head = DeleteNode(head,position_data);
	cout<<"删除之后的";
	PrintList(head);
	return 0;
}
