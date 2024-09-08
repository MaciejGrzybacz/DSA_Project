#include <gtest/gtest.h>
#include "src/data_structures/union_find.h"

class UnionFindTest : public ::testing::Test {
protected:
    UnionFind* uf;

    void SetUp() override {
        uf = new UnionFind(10);  // Create a UnionFind with 10 elements
    }

    void TearDown() override {
        delete uf;
    }
};

TEST_F(UnionFindTest, InitialState) {
    EXPECT_EQ(uf->count(), 10);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == j) {
                EXPECT_TRUE(uf->connected(i, j));
            } else {
                EXPECT_FALSE(uf->connected(i, j));
            }
        }
    }
}

TEST_F(UnionFindTest, UniteElements) {
    uf->unite(0, 1);
    EXPECT_TRUE(uf->connected(0, 1));
    EXPECT_EQ(uf->count(), 9);

    uf->unite(2, 3);
    EXPECT_TRUE(uf->connected(2, 3));
    EXPECT_EQ(uf->count(), 8);

    uf->unite(0, 2);
    EXPECT_TRUE(uf->connected(0, 2));
    EXPECT_TRUE(uf->connected(1, 3));
    EXPECT_EQ(uf->count(), 7);
}

TEST_F(UnionFindTest, FindRepresentative) {
    uf->unite(0, 1);
    uf->unite(1, 2);
    uf->unite(2, 3);

    int rep = uf->find(3);
    EXPECT_EQ(uf->find(0), rep);
    EXPECT_EQ(uf->find(1), rep);
    EXPECT_EQ(uf->find(2), rep);
}

TEST_F(UnionFindTest, LargeUnionFind) {
    UnionFind largeUf(1000);
    EXPECT_EQ(largeUf.count(), 1000);

    for (int i = 0; i < 999; i++) {
        largeUf.unite(i, i+1);
    }

    EXPECT_EQ(largeUf.count(), 1);
    EXPECT_TRUE(largeUf.connected(0, 999));
}

TEST_F(UnionFindTest, MultipleUnions) {
    uf->unite(0, 1);
    uf->unite(2, 3);
    uf->unite(4, 5);
    uf->unite(6, 7);
    uf->unite(0, 2);
    uf->unite(4, 6);
    uf->unite(0, 4);

    EXPECT_TRUE(uf->connected(1, 7));
    EXPECT_FALSE(uf->connected(8, 9));
    EXPECT_EQ(uf->count(), 3);
}

TEST_F(UnionFindTest, PathCompression) {
    for (int i = 1; i < 10; i++) {
        uf->unite(0, i);
    }

    for (int i = 1; i < 10; i++) {
        EXPECT_EQ(uf->find(i), uf->find(0));
    }

    EXPECT_EQ(uf->count(), 1);
}