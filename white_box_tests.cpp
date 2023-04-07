//======== Copyright (c) 2022, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2023-03-07
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>
#include "string.h" 

#include "gtest/gtest.h"

#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem 
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v 
//       indexu
//============================================================================//



class empty_hash_table : public:: testing ::Test
{
protected:
    hash_map_t *hash_map;

    virtual void SetUp(){
        hash_map = hash_map_ctor();
    }
    virtual void TearDown(){
        hash_map_dtor(hash_map);
    }
        
};

class non_empty_hash_table : public:: testing ::Test
{
protected:
    hash_map_t *hash_map;

    virtual void SetUp(){
        hash_map = hash_map_ctor();
        const char* prefix = "test";
        for (int i = 0; i < 9; i++) {
            char* key = (char*)malloc(strlen(prefix) + 2);
            snprintf(key, strlen(prefix) + 2, "%s%d", prefix, i);
            hash_map_put(hash_map, key, i);
            free(key);
        }
        

    }
    virtual void TearDown(){
        hash_map_dtor(hash_map);
    }
        
};

class collision_test_hash_table : public:: testing ::Test
{
protected:
    hash_map_t *hash_map;

    virtual void SetUp(){
        hash_map = hash_map_ctor();
        hash_map_put(hash_map, "collision", 6);
    }
    virtual void TearDown(){
        hash_map_dtor(hash_map);
    }
        
};


TEST_F(empty_hash_table, hash_map_clear){
    hash_map_clear(hash_map);
    ASSERT_EQ(hash_map_size(hash_map), 0);
    ASSERT_EQ(hash_map_capacity(hash_map), 8);
    EXPECT_EQ(hash_map->first, nullptr);
    EXPECT_EQ(hash_map->last, nullptr);
    for(int i = 0; i < hash_map_capacity(hash_map); i++){
        ASSERT_EQ(hash_map->index[i], nullptr);
    }
}

TEST_F(empty_hash_table, hash_map_reserve){
    hash_map_reserve(hash_map, HASH_MAP_INIT_SIZE);
    EXPECT_EQ(hash_map_capacity(hash_map), HASH_MAP_INIT_SIZE);
    hash_map_reserve(hash_map, 0);
    EXPECT_EQ(hash_map_capacity(hash_map), 0);
}

TEST_F(empty_hash_table, hash_map_contains){
    EXPECT_EQ(hash_map_contains(hash_map, "test"), false);
}

TEST_F(empty_hash_table, hash_map_put){
    hash_map_reserve(hash_map, 1);
    EXPECT_EQ(hash_map_put(hash_map, "test0", 6), OK);
    EXPECT_EQ(strcmp(hash_map->first->key, "test0"), 0);
    EXPECT_EQ(strcmp(hash_map->last->key, "test0"), 0);
    EXPECT_EQ(hash_map->last->value, 6);
    ASSERT_EQ(hash_map_size(hash_map), 1);
    ASSERT_EQ(hash_map_capacity(hash_map), 1);
    
    hash_map_put(hash_map, "test1", 1);
    ASSERT_EQ(hash_map_size(hash_map), 2);
    ASSERT_EQ(hash_map_capacity(hash_map), 2);
    int tmpValue = 0;
    EXPECT_EQ(hash_map_get(hash_map, "test0", &tmpValue), OK);
    
    EXPECT_EQ(hash_map_reserve(hash_map, 0), VALUE_ERROR);
}

TEST_F(empty_hash_table, hash_map_get){
    int tmpValue = 0;
    int given_value = 6;
    EXPECT_EQ(hash_map_get(hash_map, "test0", &tmpValue), KEY_ERROR);

    hash_map_put(hash_map, "test0", given_value);
    EXPECT_EQ(hash_map_get(hash_map, "test0", &tmpValue), OK);
    EXPECT_EQ(tmpValue, given_value);

}

TEST_F(empty_hash_table, hash_map_pop){
    int tmpValue = 0;
    int given_value = 2;
    EXPECT_EQ(hash_map_pop(hash_map, "test", &tmpValue), KEY_ERROR);

    hash_map_put(hash_map, "test0", given_value);
    EXPECT_EQ(hash_map_pop(hash_map, "test0", &tmpValue), OK);
    EXPECT_EQ(tmpValue, given_value);
    EXPECT_EQ(hash_map_size(hash_map), 1);

}


TEST_F(empty_hash_table, hash_map_remove){
    EXPECT_EQ(hash_map_remove(hash_map, "test2332"), KEY_ERROR);
}


TEST_F(non_empty_hash_table, hash_map_clear){
    int reserved = hash_map_capacity(hash_map);
    hash_map_clear(hash_map);
    EXPECT_EQ(hash_map_capacity(hash_map), reserved);
    EXPECT_EQ(hash_map_size(hash_map), 0);
    EXPECT_EQ(hash_map->first, nullptr);
    EXPECT_EQ(hash_map->last, nullptr);
    for(int i = 0; i < hash_map_capacity(hash_map); i++){
         ASSERT_EQ(hash_map->index[i], nullptr);
    }
}

TEST_F(non_empty_hash_table, hash_map_reserve){
    ASSERT_EQ(hash_map_capacity(hash_map), 16);
    EXPECT_EQ(hash_map_reserve(hash_map ,8), VALUE_ERROR);
    EXPECT_EQ(hash_map_reserve(hash_map ,16), OK);
    hash_map_item_t* first_item = hash_map->first;
    hash_map_reserve(hash_map ,14);
    EXPECT_EQ(first_item, hash_map->first);
    EXPECT_EQ(hash_map_reserve(hash_map ,14), OK);
}

TEST_F(non_empty_hash_table, hash_map_contains){
    EXPECT_EQ(hash_map_contains(hash_map, "test1"), true);
    EXPECT_EQ(hash_map_contains(hash_map, "stet1"), false);
}

TEST_F(non_empty_hash_table, hash_map_put){
    EXPECT_EQ(hash_map_put(hash_map, "test0", 6), KEY_ALREADY_EXISTS);
    hash_map_item_t* tmpLast = hash_map->last;
    EXPECT_EQ(hash_map_put(hash_map, "tste1", 89), OK);
    EXPECT_EQ(hash_map->allocated, 16);

    EXPECT_EQ(strcmp(hash_map->last->key, "tste1"), 0);
    EXPECT_EQ(hash_map->last->value, 89);
    EXPECT_EQ(hash_map->last->prev, tmpLast);
}

TEST_F(non_empty_hash_table, hash_map_get){
    int tmpValue = 0;
    EXPECT_EQ(hash_map_get(hash_map, "test1", &tmpValue), OK);
    EXPECT_EQ(tmpValue, 1);
}

TEST_F(non_empty_hash_table, hash_map_remove){
    EXPECT_EQ(hash_map_remove(hash_map, "test5"), OK);
    EXPECT_EQ(hash_map_contains(hash_map, "test5"), false);
}

TEST_F(non_empty_hash_table, hash_map_pop){
    hash_map_item_t* tmp_second_item = hash_map->first->next;
    hash_map_item_t* tmp_prev_item = hash_map->last->prev;
    int tmp_value = 0;
    EXPECT_EQ(hash_map_pop(hash_map, hash_map->first->key, &tmp_value), OK);
    EXPECT_EQ(tmp_second_item, hash_map->first);
    EXPECT_EQ(hash_map_pop(hash_map, hash_map->last->key, &tmp_value), OK);
    EXPECT_EQ(tmp_prev_item, hash_map->last);
}

int item_index(hash_map_t* map, const char* key){
    for(int i = 0; i < map->allocated; i++ ){
        if(map->index[i] != nullptr){
            if(strcmp(map->index[i]->key, key) == 0){
               return i;
            }   
        }
    }
    return -1;
}

size_t hash_local(const char* str)
{
    size_t hash = 0;

    for (size_t idx = 0; str[idx] != '\0'; idx++)
    {
        hash += HASH_FUNCTION_PARAM_A*str[idx] + HASH_FUNCTION_PARAM_B;
    }

    return hash;
}

TEST_F(collision_test_hash_table, collision_hash_index_dependacy){
    int idx1 = 0;
    int idx2 = 0;

    idx1 = item_index(hash_map, "collision");
    hash_map_remove(hash_map, "collision");

    hash_map_put(hash_map, "llcosiion", 8);
    idx2 = item_index(hash_map, "llcosiion");

    EXPECT_EQ(idx1, idx2);

}

size_t hash_map_look(hash_map_t* self, const char* key, size_t hash, 
                              bool ignore_dummy)
{
    size_t idx = hash % self->allocated;
    size_t perturb = hash;

    while ( 
        (self->index[idx] != NULL && 
        (ignore_dummy || self->index[idx] != self->dummy)) &&
        (
            self->index[idx] == self->dummy ||
            (
                (self->index[idx]->hash != hash) || 
                (strcmp(self->index[idx]->key, key) != 0)
            )
        )
    )
    {
        idx = ((idx << 2) + idx + perturb + 1) % self->allocated;
        perturb >>= HASH_MAP_PERTURB_SHIFT;
    }

    return idx;
}

TEST_F(collision_test_hash_table, collision_hash_index_calculation){
    hash_map_reserve(hash_map, 16);

    int idx1 = item_index(hash_map, "collision");

    hash_map_put(hash_map, "sioncolli", 6);
    int idx2 = item_index(hash_map, "sioncolli");
    EXPECT_EQ(idx2, ((idx1 << 2) + idx1 + hash_local("collision") + 1) % hash_map->allocated);
}


/*** Konec souboru white_box_tests.cpp ***/
