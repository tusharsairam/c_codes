#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 5

typedef struct KDNode {
        int values[2];
        struct KDNode* left;
        struct KDNode* right;
} kd_node_t;

// Comparator function for ascending order sort
static int comp_x(const void* p1, const void* p2)
{
        const int (*ptr_a)[2] = p1;
        const int (*ptr_b)[2] = p2;

        return (*ptr_a)[0] - (*ptr_b)[0];
}

static int comp_y(const void* p1, const void* p2)
{
        const int (*ptr_a)[2] = p1;
        const int (*ptr_b)[2] = p2;

        return (*ptr_a)[1] - (*ptr_b)[1];
}       

// Builds a KD-tree from a given list of points 
kd_node_t* build_kdtree(int point_list[][2], int n,  int depth)
{
        if (n <= 0) {
                return NULL;
        }
        
        // For now, we're dealing with 2D points, so K = 2
        int axis = depth % 2;
        
        if (axis == 0) {
                qsort(point_list, n, sizeof(point_list[0]), comp_x);
        } else {
                qsort(point_list, n, sizeof(point_list[0]), comp_y);
        }
                
        int median_idx = n/2;

        kd_node_t* node = malloc(sizeof(*node));
        node->values[0] = point_list[median_idx][0];
        node->values[1] = point_list[median_idx][1];
        node->left      = NULL;
        node->right     = NULL;

        // depth + 1 because we're going one level deeper
        node->left = build_kdtree(point_list, median_idx, depth + 1);
        node->right = build_kdtree(point_list + median_idx + 1, n - median_idx - 1, depth + 1);

        return node;
}

void print_node(kd_node_t* node) 
{
       printf("(%d, %d)\n", node->values[0], node->values[1]);
}

void print_kdtree(kd_node_t* root)
{
        if (root) {
                print_node(root);
                print_kdtree(root->left);
                print_kdtree(root->right);
        }
}

int main() 
{
        int point_list[N][2] = {{1, 2}, {5, 3}, {9, 7}, {2, 6}, {3, 10}};
        
        kd_node_t* root_node = build_kdtree(point_list, N, 0);
        
        print_kdtree(root_node);

        free(root_node);

        return 0;
}
