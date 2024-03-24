# Assignment
## Binary tree
Implement a simple binary tree using smart pointers.

Makes ure to answer questions marked with [*]. You can put the answers in your source code or post
them as Kelvin comments.

Each tree node will contain a value of type `BigData`. Since the value could be quite big,
the value can be shared by some nodes of the tree.
Each node will also contain a left and a right child (both can be possibly missing) and a link
to its parent node (it can also be missing if the current node is the root of the tree).
The parent will be the only owner of its child elements.

[*] What type of pointer should be used for the value and what type should be used for storing
the child nodes? What type of pointer should be used for the parent link? Think about ownership -
who is the owner of what data and which data is shared by whom.

Implement methods for getting the value of a node, its parent and its left/right child.
- `get_parent()`, `bool has_parent()`, `get_left_child()`, `get_right_child()`
Implement method for getting the root node of the tree.
- `get_root()`
Implement methods for taking the left/right child of a node. Taking removes the child from the node and returns it.
- `take_left_child()`, `take_right_child`()
Implement a method for taking a given child of a node. If the given tree is not a child of the node,
throw an exception.
- `take_child(Tree&)`
Implement methods for setting the left/right child of a node. Setting returns the previous child.
- `set_left_child(...)`, `set_right_child(...)`
Implement a method for swapping the left/right child of a node.
- `swap_children()`
Implement a method for finding if two nodes belong to the same tree.
- `bool is_same_tree_as(Tree*)`
Implement a method for replacing the shared value of the current node and of all its descendants
to the passed value.
- `replace_value(...)`

### Bonus task
Implement inorder traversal of the binary tree using the *iterator protocol*.

Example representing this tree:
  0
 / \
1   3
   / \
  2   4

```cpp
auto tree = std::make_unique<Tree>(0);
tree->set_left_child(std::make_unique<Tree>(1));
tree->set_right_child(std::make_unique<Tree>(3));
tree->get_right_child()->set_left_child(std::make_unique<Tree>(2));
tree->get_right_child()->set_right_child(std::make_unique<Tree>(4));

for (auto& node: tree) {
 std::cout << node.get_value() << " ";
}
```
Prints `0, 1, 2, 3, 4`.
