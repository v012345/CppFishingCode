#pragma once
#include <string>
#include <vector>
class ticker;
class Node {
  private:
    /* data */
  public:
    Node(/* args */);
    void update(int);
    void addTicker(ticker* tk);
    ticker* getTickerById(std::string id);
    void addChild(Node*);
    ~Node();

  private:
    std::vector<ticker*> tk;
};