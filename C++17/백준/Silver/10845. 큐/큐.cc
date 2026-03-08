#include <iostream>
using namespace std;
// 백준 10845
class Node{
private:
  int data; 
  Node *next;
public:
  Node() : next(NULL){}
  ~Node(){}
  void setData(int a){data=a;}
  int getData(){return data;};
  void setLink(Node* p){next = p;}
  Node* getLink(){return next;}
};

// 지금 런타임 에러 (Segfault)뜸 
// 아마 front나 rear쪽 NULL일때 멤버 접근이 발생하나봄
class Queue{
private:
  Node* face;
  Node* rear;
  int count;
public:
  Queue():face(NULL),rear(NULL),count(0){}
  ~Queue(){
    while(!(face==NULL)){
     pop(); 
  }}
  void push(int a){  
    // push 뒤에 넣기
    // rear쪽 접근해서 그 뒤에 넣고
    // rear를 newNode로 
    // 만약 암것도 안들어 있으면 
    // face도 newNode로
    Node* newNode = new Node(); // 새 노드 만들기
    newNode->setData(a); // 값넣기
    if(face==NULL){ // face가 NULL이면 (초기화 상태)
      // 둘다 newNode
      face = newNode; 
      rear = newNode;
      count++;
      return; // 반환
    }
    // face가 != NULL일 경우 (큐에 값이 존재함)
    rear->setLink(newNode); // rear 뒤에 추가
    rear = newNode; // rear를 newNode로
    count++;
    return; // 반환
  }
  int pop(){
    // pop 맨 앞에서 빼기
    // front쪽 접근해서 빼고 
    // front를 다음 요소로
    // 만약 암것도 안들어 있으면 
    // -1 반환
    if(empty()==1){return -1;} 
    // empty == 1이면 -1 반환 (값이 없음)
    int data = face->getData(); // 데이터 저장
    Node* p = face; // p에다가 face 주소 저장
    if(face->getLink()==NULL && face == rear){
      //face 다음 게 NULL이고 face랑 rear가 같으면
      // 할당 해제하고 둘다 NULL로
      delete face;
      face = NULL;
      rear = NULL;
    }else{ 
      // 아니면 face를 다음거로 하고
      // p를 할당 해제
      face = face->getLink();
      delete p;
    }
    count--;
    return data; // 데이터 반환
  }
  int size(){
    return count;
  }
  int empty(){
    if(face == rear && face == NULL){ //face rear 둘다 NULL이면 
      return 1;
    }else{ 
      return 0;
    }
  }
  int front(){
    if(face!=NULL){
      return face->getData();
    }else{
      return -1;
    }
  }
  int back(){
    if(rear!=NULL){
      return rear->getData();
    }else{
      return -1;
    }
  }
};

int main(){
  Queue q;
  int n;
  string str;
  cin >> n;
  for(int i = 0; i < n; i++){
    cin >> str;
    if(str == "push"){
      int m;
      cin >> m;
      q.push(m);
    }else if(str == "pop"){
      cout << q.pop() << endl;
    }else if(str == "size"){
      cout << q.size() << endl;
    }else if(str == "front"){
      cout << q.front() << endl;
    }else if(str == "back"){
      cout << q.back() << endl;
    }else if(str == "empty"){
      cout << q.empty() << endl;
    }
  }
  return 0;
}
  