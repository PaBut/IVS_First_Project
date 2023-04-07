//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Pavlo Butenko
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>
#include <cstdlib>
#include <ctime>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public:: testing ::Test
{
protected:
    BinaryTree *tree;

    virtual void SetUp(){
        tree = new BinaryTree();
    }
    virtual void TearDown(){
        delete tree;
    }
        
};

class NonEmptyTree : public:: testing ::Test
{
protected:
    BinaryTree *tree;

    virtual void SetUp(){
        tree = new BinaryTree();
        tree->InsertNode(0);
        tree->InsertNode(1);
    }
    virtual void TearDown(){
        delete tree;
    }
        
};

class ThreeAxioms : public:: testing ::Test
{
protected:
    BinaryTree *tree;

    virtual void SetUp(){
        tree = new BinaryTree();
        srand(time(NULL));
        int randomNumber = rand() % 200;
        for(int i = 0; i < randomNumber; i++){
            tree->InsertNode(i);
        }
    }
    virtual void TearDown(){
        delete tree;
    }
        
};

TEST_F(EmptyTree ,InsertNode){
    EXPECT_EQ(tree->InsertNode(0).first, true);
    ASSERT_NO_THROW(tree->InsertNode(0));
    BinaryTree::Node_t *node = tree->InsertNode(1).second;
    EXPECT_EQ(tree->InsertNode(1), std :: make_pair(false, node));

}

TEST_F(EmptyTree, DeleteNode){
    ASSERT_NO_THROW(tree->DeleteNode(-1));
    EXPECT_EQ(tree->DeleteNode(-1), false);
}

TEST_F(EmptyTree, FindNode){
    ASSERT_NO_THROW(tree->FindNode(0));
    EXPECT_EQ(tree->FindNode(0), nullptr);
}

TEST_F(NonEmptyTree, InsertNode){
    std :: pair<bool, BinaryTree::Node_t*> tmp = tree->InsertNode(0);
    EXPECT_EQ(tmp.first, false);
    EXPECT_EQ(tmp.second, tree->InsertNode(0).second);
    
}

TEST_F(NonEmptyTree, DeleteNode){
    EXPECT_EQ(tree->DeleteNode(1), true);
}

TEST_F(NonEmptyTree, FindNode){
    BinaryTree :: Node_t* node = tree->InsertNode(2).second;
    EXPECT_FALSE(tree->FindNode(1) == node);
    EXPECT_EQ(tree->FindNode(2), node);
}


TEST_F(ThreeAxioms, FirstAxiom){
    std :: vector<BinaryTree :: Node_t*> array;
    tree->GetLeafNodes(array);

    for(BinaryTree :: Node_t *leafNode : array){
        ASSERT_EQ(leafNode->color, BLACK);
    }
}

TEST_F(ThreeAxioms, SecondAxiom){
    std :: vector<BinaryTree :: Node_t*> array;
    tree->GetNonLeafNodes(array);

    for(BinaryTree :: Node_t *nonLeafNode : array){
        if(nonLeafNode->color == RED){
            ASSERT_EQ(nonLeafNode->pLeft->color, BLACK);
            ASSERT_EQ(nonLeafNode->pRight->color, BLACK);
        }
    }
}

TEST_F(ThreeAxioms, ThirdAxiom){
    std :: vector<BinaryTree :: Node_t*> array;
    tree->GetLeafNodes(array);
    int blackNodesEarlier = -1;

    for(BinaryTree :: Node_t *leafNode : array){
        int blackNodesNow = 0;
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


/*** Konec souboru black_box_tests.cpp ***/
