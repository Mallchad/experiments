



// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <memory>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::cin;

class Solution {
public:
    string getDirections(TreeNode* root, int startValue, int destValue)
    {
        unsigned max_nodes = 1000000;

        string start_path;
        string dest_path;
        start_path.reserve( max_nodes );
        dest_path.reserve( max_nodes );
        memset( (void*)start_path.data(), 0, start_path.capacity() );
        memset( (void*)dest_path.data(), 0, dest_path.capacity() );

        bool nodes_remaining = true;
        // Walk tree for paths to start and destination
        bool start_lost = true;
        bool dest_lost = true;
        TreeNode* x_node = root;
        TreeNode* prev_node = x_node;
        string x_path;
        bool last_left = true;
        x_path.reserve(max_nodes);
        vector<TreeNode*> node_stack;
        node_stack.reserve(max_nodes);

        int i = 0;
        for ( ; nodes_remaining && start_lost && dest_lost && (i<max_nodes) ; ++i)
        {
            bool search_complete = (x_node == root && not x_node->left && not x_node->right);
            if (search_complete)
            {
                break;
            }

            if (x_node->val == startValue)
            {
                start_lost = false;
                start_path = x_path;
                node_stack.clear();
            }
            else if (x_node->val == destValue)
            {
                dest_lost = false;
                dest_path = x_path;
                node_stack.clear();
            }

            if (x_node->left != nullptr)
            {
                node_stack.push_back( x_node );
                x_node = x_node->left;
                x_path.push_back('L');
                last_left = true;
            }
            else if (x_node->right != nullptr)
            {
                x_node = x_node->right;
                x_path.push_back('R');
                last_left = false;
            }
            else
            {
                if (x_path.size() > 0) { x_path.pop_back(); }
                if (node_stack.size() > 0 ) { node_stack.pop_back(); }
                if (last_left) { prev_node->left = nullptr; }
                else { prev_node->right = nullptr; }
                prev_node = node_stack.back();
                last_left = true;
            }
        }

        i = 0;
        char x_dest;
        char x_start;
        start_path.reserve( max_nodes );
        dest_path.reserve( max_nodes );
        int shortest = (start_path.size() < dest_path.size()) ?
            start_path.size() : dest_path.size();
        for (; i<shortest; ++i)
        {
            x_dest = dest_path[i];
            x_start = start_path[i];
            if (x_dest != x_start) { break; }
        }
        string tmp; tmp.reserve(max_nodes);
        string result = start_path.substr( 0, i ) +
            tmp.assign( dest_path.size() - i, 'U' );

        return result;
    }
};

int main()
{
    Solution sol;
    TreeNode* tree = new TreeNode;
    tree->left = new TreeNode;
    tree->left->left = new TreeNode;
    tree->left->left->left = new TreeNode;
    tree->left->right = new TreeNode;
    cout << "Result: " << sol.getDirections( tree, 7, 45 );
}
