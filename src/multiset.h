#ifndef _multiset_h
#define _multiset_h

#include <memory>

namespace nonstd {

template <typename T>
class MultiSet {
public:
//========================================================================== 
  class Node {
  private:
    T value_;
    std::unique_ptr<Node> left_, right_;
    Node(const T& value) : value_(value) {}
  public:
    Node *left() {
      return this->left_;
    }
    Node *right() {
      return this->right;
    }
    const T& value() const {
      return this->value_;
    }

  private:
    bool &operator<( Node &comp ) { return this->value < comp.value; }
    friend class MultiSet<T>;
  };
//========================================================================== 
private:
  std::unique_ptr<Node> root_;
  int size_;

public:
  MultiSet(): size_(0) { }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  ~MultiSet() {
    // TODO
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  void insert(const T& value) {
    if(!this->root_)  // create root
    {
      root_ = std::unique_ptr<Node>(new Node(value));
      this->size_++;
      return;
    }

    Node* current = root_.get();
    while(true)
    {
      if(value < current->value_) // Left
      {
        if(current->left_)
          current = current->left_.get();
        else
        {
          current->left_ = std::unique_ptr<Node>(new Node(value));
          this->size_++;
          return;;
        }
      }


      else  // Right
      {
        if(current->right_)
          current = current->right_.get();
        else
        {
          current->right_=std::unique_ptr<Node>(new Node(value));
          this->size_++;
          return;
        }
      }
    } // end while

  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  int count(const T& value) {
    return count(value, this->root_.get());
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
private:
  int count(const T& value, Node* localRoot) {
    if(!localRoot) return 0;
    int count__ = 0;
    if(value == localRoot->value_) count__++;
    if(value < localRoot->value_)
      return count(value, localRoot->left_.get()) + count__;
    else
      return count(value, localRoot->right_.get()) + count__;
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
public:
  bool contains(const T& value, Node* localRoot = NULL) {
    Node* current = localRoot ? localRoot : this->root_.get();
    while(current)
    {
      if(value == current->value_)
        return true;
      else if(value < current->value_)
        current = current->left_.get();
      else
        current = current->right_.get();
    }
    return false;
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  int size() {
    return this->size_;
    //return size(this->root_.get());  // I forgot I had a member for this
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
private:
  int size(Node* parent)
  {
    if(!parent)
      return 0;

    int size__ = 0;
    size__ += size(parent->left_.get());
    size__ += size(parent->right_.get());
    return size__ + 1;
  }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
public:
  Node *root() {
    return this->root_;
  }
};
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
} // namespace nonstd
#endif
