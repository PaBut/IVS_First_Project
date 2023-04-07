#include <vector>
#include <cstdlib>
#include <ctime>

#include "red_black_tree.h"

int main(){
    tree = new BinaryTree();
    srand(time(NULL));
    int randomNumber = rand() % 200;
    for(int i = 0; i < randomNumber; i++){
        tree->InsertNode(i);
    }

    std :: vector<BinaryTree :: Node_t*> array;
    tree->GetLeafNodes(array);
    int blackNodesEarlier = -1;

    for(BinaryTree :: Node_t *leafNode : array){
        int blackNodesNow;
        for(BinaryTree :: Node_t *node = leafNode; node != nullptr; node = node->pParent){
            if(node->color == BLACK){
                blackNodesNow++;
            }
        }
        if(blackNodesEarlier != -1){
            ASSERT_EQ(blackNodesNow, blackNodesEarlier);
        }
        blackNodesEarlier = blackNodesNow;
    }
}