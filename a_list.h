
template <typename T>
struct Node {
  T data;
  Node<T>* next;
};

template <typename T>
struct iterator {
   Node<T>* ptr;
   iterator<T>(Node<T>* p =  0) : ptr(p) {}
   int& operator*() {return ptr->data; }
   iterator<T>& operator++() { ptr = ptr->next; return *this; }
   iterator<T> operator++ (int) {
     iterator<T> tmp = *this; ++*this; return tmp;
   }
   bool operator==(const iterator<T>& other) const {
     return ptr == other.ptr;
   }
   bool operator!=(const iterator<T>& other) const {
     return ptr != other.ptr;
   }
 };


namespace a
{
    template <typename T> class list;

template <typename T>
bool operator==(a::list<T>& _obj1, a::list<T>& _obj2) {
  return (_obj1.size() == _obj2.size());
}
  
template <typename T>
  class list {
  private:

    Node<T>* head;
    int elem = 0;
  public:
    //constructors
    list();
    list(const list& obj);
    ~list();

    //Member functions
    list<T>* push_back(T data);
    list<T>* push_front(T data);
    list<T>* insert(int pos, T data);

    list<T>* remove(int pos);
    list<T>* pop_back(); //delete the last element in the list
    list<T>* pop_front(); //delete the first element in the list

    void fetchAt(int pos);
    void reverse();
    void print();
    bool empty();
    int size();
    T front();
    T back();

    iterator<T> begin();
    iterator<T> end();

    //Non-member overloaded functions...operators
    friend bool operator==<T>(a::list<T>& _obj1, a::list<T>& _obj2);
  };
}


//-----constructor-----
template <typename T>
a::list<T>::list() {
  this->head = nullptr;
}

//copy constructor////////////////////////////////////////////////////////////
/*template <typename T>
a::list<T>::list(const a::list<T>& obj) {
  try {
    if(!obj.head) {throw 6;}
    Node<T>* node = new Node<T>();
    Node* b_current = obj.head;
    this->head = node;
    Node* d_current = this->head;
    while (b_current) {
      b_current = b_current->next;
      d_current->data = b_current->data;
      d_current->next = node;
      d_current = d_current->next;
    }
  }
  catch(int x) {
    std::cout << "CopyConstructorError: " << x << ". List is empty for copy.";
  }
}*/

//-----destructor-----
template <typename T>
a::list<T>::~list() {
  // std::cout << "dtor" << std::endl;
  if(head) {
    Node<T>* _tmp = head;
    while (!a::list<T>::empty()) {
      Node<T>* __tmp = _tmp;
      _tmp = _tmp->next;
      __tmp = NULL;
      delete __tmp;
    }
    delete head;
  }
  elem = 0;
}
//insertion element
template <typename T>
a::list<T>* a::list<T>::push_back(T data) {
  Node<T>* node = new Node<T>();
  if(!head) {
    head = node;
    head->data = data;
    head->next = nullptr;
    ++elem;
    return this;
  }
  Node<T>* current =  head;
  while(current->next) {
    current = current->next;
  }
  current->next = node;
  current = current->next;
  current->data = data;
  ++elem;
  return this;
}

//-----adding the element to the top of the list-----
template <typename T>
a::list<T>* a::list<T>::push_front(T data){
  Node<T>* node = new Node<T>();
  if(!head) {
    head = node;
    head->data = data;
    head->next = nullptr;
    ++elem;
    return this;
  }
  Node<T>* currentNode = head;
  head = node;
  node->data = data;
  node->next = currentNode;
  ++elem;
  return this;
}

//-----adding the element with position-----
template <typename T>
a::list<T>* a::list<T>::insert(int pos, T data) {
  Node<T>* node = new Node<T>();
  int count = 0;
  try {
    if(!head || pos < 0 || pos > elem) {throw 1;}
    if(!head) {
      head = node;
      head->data = data;
      head->next = nullptr;
      ++elem;
      return this;
    }
    Node<T>* currentNode = head;
    if(pos == elem) {
      while(currentNode->next) {
        currentNode = currentNode->next;
      }
      currentNode->next = node;
      currentNode = currentNode->next;
      currentNode->data = data;
      ++elem;
      return this;
    }
    Node<T>* previousNode = NULL;
    if(0 == pos) {
      head = node;
      node->data = data;
      node->next = currentNode;
      ++elem;
      return this;
    }
    while(currentNode->next && count < pos) {
      previousNode = currentNode;
      currentNode = currentNode->next;
      ++count;
    }
    previousNode->next = node;
    node->data = data;
    node->next = currentNode;
  }
  catch (int e) {
    std::cout << "InsertAtError: " << e << ". Invalid position. ";
  }
  std::cout << std::endl;
  ++elem;
  return this;
}


template <typename T>
a::list<T>* a::list<T>::remove(int pos) {
  try {
    if(pos < 0 || !head) {throw 2;}
    Node<T>* currentNode = head;
    Node<T>* previousNode = NULL;
    if(0 == pos) {
      head = currentNode->next;
      currentNode = NULL;
      --elem;
      return this;
    }
    int count = 0;
    while(count < pos) {
      ++count;
      previousNode = currentNode;
      currentNode = currentNode->next;
    }
    previousNode->next =  currentNode->next;
    currentNode->next = nullptr;
    --elem;
    return this;
  }
  catch (int e) {
    std::cout << "RemoveError: " << e << ". Invalid position.";
  }
  std::cout << std::endl;
}

// -----delete the last element in the list-----
template <typename T>
a::list<T>* a::list<T>::pop_back() {
  try {
    if(!head) {throw 6;}
    Node<T>* currentNode = head;
    Node<T>* previousNode = NULL;
    while(currentNode->next) {
      previousNode = currentNode;
      currentNode = currentNode->next;
    }
    previousNode->next = nullptr;
    --elem;
    return this;
  }
  catch (int e) {
    std::cout << "PopBackError: " << e << ". Invalid position.";
  }
  std::cout << std::endl;
}

//-----delete the firts element in the list-----
template <typename T>
a::list<T>* a::list<T>::pop_front() {
  try {
    if(!head) {throw 7;}
    Node<T>* currentNode = head;
    head = currentNode->next;
    currentNode = NULL;
    --elem;
    return this;
  }
  catch (int e) {
    std::cout << "PopFrontError: " << e << ". Invalid position.";
  }
  std::cout << std::endl;
}

template <typename T>
void a::list<T>::fetchAt(int pos) {
  Node<T>* currentNode = head;
  try {
    if(!head && 0 < pos < 0 || pos < 0) {throw 3;}
    if(0 == pos) {
      std::cout << "At " << pos << " position element is " << head->data;
      return;
    }
    int count = 0;
    while(count < pos) {
      ++count;
      currentNode = currentNode->next;
    }
    std::cout << "At " << pos << " position element is " << currentNode->data << "." << std::endl;
  }
  catch (int e) {
    std::cout << "FetchAtError: " << e << ". Invalid position.";
  }
}

template <typename T>
void a::list<T>::reverse() {
    Node<T>* previousNode = NULL;
	  Node<T>* currentNode = head;
	  Node<T>* nextNode;
	  while (currentNode != NULL)
	  {
	    nextNode = currentNode->next;
		  currentNode->next = previousNode;
		  previousNode = currentNode;
		  currentNode = nextNode;
	  }
	  head = previousNode;
}

//shows count of elements.
template <typename T>
int a::list<T>::size(){
  return elem;
}

//check list is empty or no
template <typename T>
bool a::list<T>::empty(){
  return elem;
}

//return the first element of list, whithout check there is elements or no;
template <typename T>
T a::list<T>::front() {
  return this->head->data;
}

//return the last element of list, whithout check there is elements or no;
template <typename T>
T a::list<T>::back() {
  Node<T>* current = head;
  while(current->next) {
    current = current->next;
  }
  return current->data;
}


/*
template <typename T>
bool operator!=(const list<T>& _obj1, const list<T>& _obj2) {
  return (_obj1.size() != _obj2.size()) ;
}*/

template <typename T>
void a::list<T>::print() {
  try {
    if (!head) {throw 0;}
  }
  catch (int e) {
    std::cout << "PrintError: " << e << ". List is empty.";
  }
  Node<T>* current = head;
  while(current) {
    std::cout << current->data << " --> ";
    current = current->next;
  }
  std::cout << "NULL" << std::endl;
}

template <typename T>
iterator<T> a::list<T>::begin() {
  return iterator<T>(head);
}

template <typename T>
iterator<T> a::list<T>::end() {
  return iterator<T>();
}
